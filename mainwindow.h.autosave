#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include "imageviewer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void connectSignals();
    void openFolder();
    void goToSlice(int index);
    void nextSlice();
    void prevSlice();
    void onBrightnessChanged(int value);
    void onContrastChanged(int value);
    void onAnnotationFinished(const Annotation &ann);
    void enableLineTool();
    void enableRectTool();
    void disableAnnotation();

private:
    Ui::MainWindow *ui;
    ImageViewer *m_viewer;
    QStringList m_imagePaths;
    int m_currentSlice;

    void loadSlice(int index);
    void updateSliceLabel();
    void setupViewer();
    void setupResponsiveLayout();
    void applyStyleSheet();
};

#endif // MAINWINDOW_H
