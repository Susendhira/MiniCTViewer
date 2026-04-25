#include "dicomloader.h"

#include <QFile>
#include <QFileInfo>
#include <QDebug>

// DCMTK headers
#include <dcmtk/dcmimgle/dcmimage.h>
#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmdata/dcfilefo.h>
#include <dcmtk/dcmdata/dcxfer.h>
#include <dcmtk/oflog/oflog.h>

DicomLoader::DicomLoader() {}

// ── Check if file is DICOM ────────────────────────────────────────────────────
bool DicomLoader::isDicomFile(const QString &filePath)
{
    QString ext = QFileInfo(filePath).suffix().toLower();
    if (ext == "dcm" || ext == "dicom") return true;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) return false;
    if (file.size() < 132) { file.close(); return false; }

    file.seek(128);
    QByteArray magic = file.read(4);
    file.close();

    return (magic == "DICM");
}

// ── Load DICOM file ───────────────────────────────────────────────────────────
QImage DicomLoader::loadDicomFile(const QString &filePath)
{
    // Silence DCMTK logs
    OFLog::configure(OFLogger::FATAL_LOG_LEVEL);

    // ── Step 1: Load the raw dataset first ───────
    DcmFileFormat fileFormat;
    OFCondition cond = fileFormat.loadFile(
        filePath.toStdString().c_str(),
        EXS_Unknown,          // auto detect transfer syntax
        EGL_withoutGL,        // no group length
        DCM_MaxReadLength,
        ERM_autoDetect        // auto detect file format
    );

    if (cond.bad()) {
        qWarning() << "DcmFileFormat load failed:" << cond.text()
                   << "File:" << filePath;
        // Try anyway with DicomImage directly
    }

    // ── Step 2: Create DicomImage with ALL lenient flags ──
    unsigned long flags =
        CIF_MayDetachPixelData      |
        CIF_TakeOverExternalDataset |
        CIF_IgnoreModalityTransformation;

    DicomImage *dcmImage = new DicomImage(
        filePath.toStdString().c_str(), flags);

    if (!dcmImage) {
        qWarning() << "DicomImage creation failed for:" << filePath;
        return QImage();
    }

    EI_Status status = dcmImage->getStatus();
    qDebug() << "DICOM status:" << DicomImage::getString(status)
             << "File:" << QFileInfo(filePath).fileName();

    // Continue even with warnings
    if (status == EIS_Normal ||
        status == EIS_MissingAttribute ||
        status == EIS_InvalidValue)
    {
        // ── Step 3: Set windowing ─────────────────
        if (dcmImage->getWindowCount() > 0) {
            dcmImage->setWindow(0); // use first window
        } else {
            dcmImage->setMinMaxWindow(); // auto window
        }

        int width  = (int)dcmImage->getWidth();
        int height = (int)dcmImage->getHeight();

        qDebug() << "DICOM dimensions:" << width << "x" << height;

        if (width <= 0 || height <= 0) {
            qWarning() << "Bad dimensions";
            delete dcmImage;
            return QImage();
        }

        // ── Step 4: Try 8-bit output ──────────────
        QImage result(width, height, QImage::Format_Grayscale8);
        unsigned long bufSize = (unsigned long)(width * height);

        if (dcmImage->getOutputData(result.bits(), bufSize, 8)) {
            qDebug() << "8-bit render SUCCESS";
            delete dcmImage;
            return result;
        }

        qWarning() << "8-bit render failed, trying 16-bit...";

        // ── Step 5: Fallback 16-bit ───────────────
        QVector<quint16> buf16(width * height, 0);
        unsigned long buf16Size = (unsigned long)(width * height * 2);

        if (dcmImage->getOutputData(buf16.data(), buf16Size, 16)) {
            qDebug() << "16-bit render SUCCESS";

            quint16 minVal = 65535, maxVal = 0;
            for (int i = 0; i < width * height; ++i) {
                if (buf16[i] < minVal) minVal = buf16[i];
                if (buf16[i] > maxVal) maxVal = buf16[i];
            }
            quint16 range = (maxVal > minVal) ? (maxVal - minVal) : 1;
            qDebug() << "16-bit range:" << minVal << "to" << maxVal;

            for (int y = 0; y < height; ++y) {
                uchar *line = result.scanLine(y);
                for (int x = 0; x < width; ++x) {
                    quint16 val = buf16[y * width + x];
                    line[x] = (uchar)(((val - minVal) * 255) / range);
                }
            }
            delete dcmImage;
            return result;
        }

        qWarning() << "Both 8-bit and 16-bit failed";
        delete dcmImage;
        return QImage();

    } else {
        qWarning() << "Unrecoverable DICOM error:"
                   << DicomImage::getString(status);
        delete dcmImage;
        return QImage();
    }
}

// ── Get DICOM metadata ────────────────────────────────────────────────────────
QString DicomLoader::getDicomInfo(const QString &filePath)
{
    OFLog::configure(OFLogger::FATAL_LOG_LEVEL);

    DcmFileFormat fileFormat;
    OFCondition status = fileFormat.loadFile(
        filePath.toStdString().c_str(),
        EXS_Unknown, EGL_withoutGL,
        DCM_MaxReadLength, ERM_autoDetect);

    if (status.bad()) return "DICOM info unavailable";

    DcmDataset *dataset = fileFormat.getDataset();
    if (!dataset) return "No dataset";

    OFString patientName, studyDate, modality;
    dataset->findAndGetOFString(DCM_PatientName, patientName);
    dataset->findAndGetOFString(DCM_StudyDate,   studyDate);
    dataset->findAndGetOFString(DCM_Modality,    modality);

    QString info;
    if (!QString(patientName.c_str()).isEmpty())
        info += QString("Patient: %1  ").arg(patientName.c_str());
    if (!QString(studyDate.c_str()).isEmpty())
        info += QString("Date: %1  ").arg(studyDate.c_str());
    if (!QString(modality.c_str()).isEmpty())
        info += QString("Modality: %1").arg(modality.c_str());

    return info.isEmpty() ? "DICOM file loaded" : info;
}
