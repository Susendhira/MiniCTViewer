#include "imageviewer.h"
#include <QPainter>
#include <QMouseEvent>
#include <cmath>

ImageViewer::ImageViewer(QWidget *parent)
    : QWidget(parent),
      m_zoomFactor(1.0),
      m_panOffset(0, 0),
      m_isPanning(false),
      m_brightness(0),
      m_contrast(0),
      m_annotationMode(false),
      m_annotationType(Annotation::Line),
      m_isDrawing(false)
{
    setMouseTracking(true);
    setMinimumSize(400, 400);
    setCursor(Qt::OpenHandCursor);
}

void ImageViewer::setImage(const QPixmap &pixmap)
{
    m_originalPixmap = pixmap;
    m_annotations.clear();
    applyImageAdjustments();
    update();
}

void ImageViewer::resetView()
{
    m_zoomFactor = 1.0;
    m_panOffset  = QPoint(0, 0);
    update();
}

void ImageViewer::setZoomFactor(double factor)
{
    m_zoomFactor = qBound(0.1, factor, 10.0);
    update();
}

void ImageViewer::setBrightness(int value)
{
    m_brightness = value;
    applyImageAdjustments();
    update();
}

void ImageViewer::setContrast(int value)
{
    m_contrast = value;
    applyImageAdjustments();
    update();
}

void ImageViewer::setAnnotationMode(bool enabled, Annotation::Type type)
{
    m_annotationMode = enabled;
    m_annotationType = type;
    setCursor(enabled ? Qt::CrossCursor : Qt::OpenHandCursor);
}

void ImageViewer::applyImageAdjustments()
{
    if (m_originalPixmap.isNull()) return;

    QImage img = m_originalPixmap.toImage().convertToFormat(QImage::Format_RGB32);

    double contrast = (100.0 + m_contrast) / 100.0;
    int    bright   = m_brightness;

    for (int y = 0; y < img.height(); ++y) {
        QRgb *line = reinterpret_cast<QRgb*>(img.scanLine(y));
        for (int x = 0; x < img.width(); ++x) {
            QColor c(line[x]);

            int r = qBound(0, (int)((c.red()   - 128) * contrast + 128) + bright, 255);
            int g = qBound(0, (int)((c.green() - 128) * contrast + 128) + bright, 255);
            int b = qBound(0, (int)((c.blue()  - 128) * contrast + 128) + bright, 255);

            line[x] = qRgb(r, g, b);
        }
    }

    m_displayPixmap = QPixmap::fromImage(img);
}

QPoint ImageViewer::toImageCoords(const QPoint &widgetPos)
{
    int imgW = (int)(m_displayPixmap.width()  * m_zoomFactor);
    int imgH = (int)(m_displayPixmap.height() * m_zoomFactor);
    int x0   = (width()  - imgW) / 2 + m_panOffset.x();
    int y0   = (height() - imgH) / 2 + m_panOffset.y();

    double ix = (widgetPos.x() - x0) / m_zoomFactor;
    double iy = (widgetPos.y() - y0) / m_zoomFactor;
    return QPoint((int)ix, (int)iy);
}

QPoint ImageViewer::toWidgetCoords(const QPoint &imagePos)
{
    int imgW = (int)(m_displayPixmap.width()  * m_zoomFactor);
    int imgH = (int)(m_displayPixmap.height() * m_zoomFactor);
    int x0   = (width()  - imgW) / 2 + m_panOffset.x();
    int y0   = (height() - imgH) / 2 + m_panOffset.y();

    return QPoint((int)(imagePos.x() * m_zoomFactor) + x0,
                  (int)(imagePos.y() * m_zoomFactor) + y0);
}

void ImageViewer::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);

    if (m_displayPixmap.isNull()) {
        painter.setPen(Qt::gray);
        painter.drawText(rect(), Qt::AlignCenter, "No Image Loaded");
        return;
    }

    int imgW = (int)(m_displayPixmap.width()  * m_zoomFactor);
    int imgH = (int)(m_displayPixmap.height() * m_zoomFactor);
    int x0   = (width()  - imgW) / 2 + m_panOffset.x();
    int y0   = (height() - imgH) / 2 + m_panOffset.y();

    painter.drawPixmap(x0, y0, imgW, imgH, m_displayPixmap);

    painter.setPen(QPen(Qt::yellow, 2));
    for (const Annotation &ann : m_annotations) {
        QPoint s = toWidgetCoords(ann.startPoint);
        QPoint e = toWidgetCoords(ann.endPoint);

        if (ann.type == Annotation::Line) {
            painter.drawLine(s, e);
            double dist = std::sqrt(std::pow(ann.endPoint.x() - ann.startPoint.x(), 2)
                                  + std::pow(ann.endPoint.y() - ann.startPoint.y(), 2));
            painter.drawText(e + QPoint(5, -5), QString("%1 px").arg((int)dist));
        } else {
            painter.drawRect(QRect(s, e).normalized());
            int w = std::abs(ann.endPoint.x() - ann.startPoint.x());
            int h = std::abs(ann.endPoint.y() - ann.startPoint.y());
            painter.drawText(e + QPoint(5, -5), QString("%1 x %2 px").arg(w).arg(h));
        }
    }

    if (m_isDrawing) {
        painter.setPen(QPen(Qt::cyan, 2, Qt::DashLine));
        if (m_annotationType == Annotation::Line) {
            painter.drawLine(m_drawStart, m_drawEnd);
        } else {
            painter.drawRect(QRect(m_drawStart, m_drawEnd).normalized());
        }
    }
}

void ImageViewer::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (m_annotationMode) {
            m_isDrawing  = true;
            m_drawStart  = event->pos();
            m_drawEnd    = event->pos();
        } else {
            m_isPanning      = true;
            m_lastMousePos   = event->pos();
            setCursor(Qt::ClosedHandCursor);
        }
    }
}

void ImageViewer::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isPanning) {
        QPoint delta  = event->pos() - m_lastMousePos;
        m_panOffset  += delta;
        m_lastMousePos = event->pos();
        update();
    } else if (m_isDrawing) {
        m_drawEnd = event->pos();
        update();
    }
}

void ImageViewer::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (m_isPanning) {
            m_isPanning = false;
            setCursor(Qt::OpenHandCursor);
        } else if (m_isDrawing) {
            m_isDrawing = false;

            Annotation ann;
            ann.type       = m_annotationType;
            ann.startPoint = toImageCoords(m_drawStart);
            ann.endPoint   = toImageCoords(m_drawEnd);
            m_annotations.append(ann);

            emit annotationFinished(ann);
            update();
        }
    }
}

void ImageViewer::wheelEvent(QWheelEvent *event)
{
    double factor = (event->delta() > 0) ? 1.15 : 0.87;
    m_zoomFactor  = qBound(0.1, m_zoomFactor * factor, 10.0);
    update();
}
