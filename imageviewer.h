#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <QPixmap>
#include <QPoint>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>

struct Annotation {
    enum Type { Line, Rectangle };
    Type type;
    QPoint startPoint;
    QPoint endPoint;
};

class ImageViewer : public QWidget
{
    Q_OBJECT

public:
    explicit ImageViewer(QWidget *parent = nullptr);

    void setImage(const QPixmap &pixmap);
    void setZoomFactor(double factor);
    void resetView();
    void setBrightness(int value);
    void setContrast(int value);
    void setAnnotationMode(bool enabled, Annotation::Type type);
    double currentZoom() const { return m_zoomFactor; }

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

signals:
    void annotationFinished(const Annotation &ann);

private:
    QPixmap m_originalPixmap;
    QPixmap m_displayPixmap;
    double m_zoomFactor;
    QPoint m_panOffset;
    QPoint m_lastMousePos;
    bool m_isPanning;
    int m_brightness;
    int m_contrast;
    bool m_annotationMode;
    Annotation::Type m_annotationType;
    bool m_isDrawing;
    QPoint m_drawStart;
    QPoint m_drawEnd;

    QList<Annotation> m_annotations;

    void applyImageAdjustments();
    QPoint toImageCoords(const QPoint &widgetPos);
    QPoint toWidgetCoords(const QPoint &imagePos);
};

#endif // IMAGEVIEWER_H
