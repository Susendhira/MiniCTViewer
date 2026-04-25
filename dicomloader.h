#ifndef DICOMLOADER_H
#define DICOMLOADER_H

#include <QString>
#include <QImage>
#include <QStringList>

// Handles all DICOM file loading and conversion to QImage
class DicomLoader
{
public:
    DicomLoader();

    // Load a single DICOM file → returns QImage (grayscale)
    // Returns null QImage on failure
    static QImage loadDicomFile(const QString &filePath);

    // Check if a file is DICOM by extension or magic bytes
    static bool isDicomFile(const QString &filePath);

    // Get patient/study info from DICOM tags
    static QString getDicomInfo(const QString &filePath);
};

#endif // DICOMLOADER_H
