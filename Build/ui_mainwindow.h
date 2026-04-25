/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *viewerFrame;
    QWidget *controlPanel;
    QPushButton *openFolderBtn;
    QGroupBox *brightnessGroup;
    QSlider *brightnessSlider;
    QLabel *brightnessValueLabel;
    QGroupBox *annotationGroup;
    QPushButton *lineToolBtn;
    QPushButton *rectToolBtn;
    QPushButton *disableToolBtn;
    QGroupBox *contrastGroup;
    QSlider *contrastSlider;
    QLabel *contrastValueLabel;
    QGroupBox *groupBox;
    QPushButton *zoomInBtn;
    QPushButton *zoomOutBtn;
    QPushButton *resetViewBtn;
    QFrame *navBar;
    QPushButton *prevBtn;
    QSlider *sliceSlider;
    QLabel *sliceLabel;
    QLabel *statusLabel;
    QPushButton *nextBtn;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(983, 686);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        viewerFrame = new QFrame(centralwidget);
        viewerFrame->setObjectName(QString::fromUtf8("viewerFrame"));
        viewerFrame->setGeometry(QRect(30, 20, 591, 561));
        viewerFrame->setFrameShape(QFrame::StyledPanel);
        viewerFrame->setFrameShadow(QFrame::Raised);
        controlPanel = new QWidget(centralwidget);
        controlPanel->setObjectName(QString::fromUtf8("controlPanel"));
        controlPanel->setGeometry(QRect(620, 20, 331, 561));
        openFolderBtn = new QPushButton(controlPanel);
        openFolderBtn->setObjectName(QString::fromUtf8("openFolderBtn"));
        openFolderBtn->setGeometry(QRect(40, 40, 251, 51));
        brightnessGroup = new QGroupBox(controlPanel);
        brightnessGroup->setObjectName(QString::fromUtf8("brightnessGroup"));
        brightnessGroup->setGeometry(QRect(40, 110, 251, 71));
        brightnessSlider = new QSlider(brightnessGroup);
        brightnessSlider->setObjectName(QString::fromUtf8("brightnessSlider"));
        brightnessSlider->setGeometry(QRect(10, 30, 231, 16));
        brightnessSlider->setOrientation(Qt::Horizontal);
        brightnessValueLabel = new QLabel(brightnessGroup);
        brightnessValueLabel->setObjectName(QString::fromUtf8("brightnessValueLabel"));
        brightnessValueLabel->setGeometry(QRect(16, 50, 221, 20));
        brightnessValueLabel->setAlignment(Qt::AlignCenter);
        annotationGroup = new QGroupBox(controlPanel);
        annotationGroup->setObjectName(QString::fromUtf8("annotationGroup"));
        annotationGroup->setGeometry(QRect(40, 290, 251, 151));
        lineToolBtn = new QPushButton(annotationGroup);
        lineToolBtn->setObjectName(QString::fromUtf8("lineToolBtn"));
        lineToolBtn->setGeometry(QRect(10, 30, 231, 25));
        lineToolBtn->setCheckable(true);
        rectToolBtn = new QPushButton(annotationGroup);
        rectToolBtn->setObjectName(QString::fromUtf8("rectToolBtn"));
        rectToolBtn->setGeometry(QRect(10, 70, 231, 25));
        rectToolBtn->setCheckable(true);
        disableToolBtn = new QPushButton(annotationGroup);
        disableToolBtn->setObjectName(QString::fromUtf8("disableToolBtn"));
        disableToolBtn->setGeometry(QRect(10, 110, 231, 25));
        contrastGroup = new QGroupBox(controlPanel);
        contrastGroup->setObjectName(QString::fromUtf8("contrastGroup"));
        contrastGroup->setGeometry(QRect(40, 200, 251, 71));
        contrastSlider = new QSlider(contrastGroup);
        contrastSlider->setObjectName(QString::fromUtf8("contrastSlider"));
        contrastSlider->setGeometry(QRect(10, 30, 231, 16));
        contrastSlider->setOrientation(Qt::Horizontal);
        contrastValueLabel = new QLabel(contrastGroup);
        contrastValueLabel->setObjectName(QString::fromUtf8("contrastValueLabel"));
        contrastValueLabel->setGeometry(QRect(20, 50, 221, 20));
        contrastValueLabel->setAlignment(Qt::AlignCenter);
        groupBox = new QGroupBox(controlPanel);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(40, 480, 251, 71));
        zoomInBtn = new QPushButton(groupBox);
        zoomInBtn->setObjectName(QString::fromUtf8("zoomInBtn"));
        zoomInBtn->setGeometry(QRect(10, 30, 71, 25));
        zoomOutBtn = new QPushButton(groupBox);
        zoomOutBtn->setObjectName(QString::fromUtf8("zoomOutBtn"));
        zoomOutBtn->setGeometry(QRect(90, 30, 71, 25));
        resetViewBtn = new QPushButton(groupBox);
        resetViewBtn->setObjectName(QString::fromUtf8("resetViewBtn"));
        resetViewBtn->setGeometry(QRect(170, 30, 71, 25));
        navBar = new QFrame(centralwidget);
        navBar->setObjectName(QString::fromUtf8("navBar"));
        navBar->setGeometry(QRect(30, 580, 921, 61));
        navBar->setFrameShape(QFrame::StyledPanel);
        navBar->setFrameShadow(QFrame::Raised);
        prevBtn = new QPushButton(navBar);
        prevBtn->setObjectName(QString::fromUtf8("prevBtn"));
        prevBtn->setGeometry(QRect(10, 20, 61, 25));
        sliceSlider = new QSlider(navBar);
        sliceSlider->setObjectName(QString::fromUtf8("sliceSlider"));
        sliceSlider->setGeometry(QRect(80, 20, 341, 21));
        sliceSlider->setOrientation(Qt::Horizontal);
        sliceLabel = new QLabel(navBar);
        sliceLabel->setObjectName(QString::fromUtf8("sliceLabel"));
        sliceLabel->setGeometry(QRect(500, 20, 91, 21));
        sliceLabel->setAlignment(Qt::AlignCenter);
        statusLabel = new QLabel(navBar);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        statusLabel->setGeometry(QRect(630, 16, 251, 31));
        statusLabel->setAlignment(Qt::AlignCenter);
        statusLabel->setWordWrap(false);
        nextBtn = new QPushButton(navBar);
        nextBtn->setObjectName(QString::fromUtf8("nextBtn"));
        nextBtn->setGeometry(QRect(430, 20, 61, 25));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 983, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        openFolderBtn->setText(QCoreApplication::translate("MainWindow", "Open Folder", nullptr));
        brightnessGroup->setTitle(QCoreApplication::translate("MainWindow", "Brightness", nullptr));
        brightnessValueLabel->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        annotationGroup->setTitle(QCoreApplication::translate("MainWindow", "Annotation Tools", nullptr));
        lineToolBtn->setText(QCoreApplication::translate("MainWindow", "Draw Line", nullptr));
        rectToolBtn->setText(QCoreApplication::translate("MainWindow", "Draw Rectangle", nullptr));
        disableToolBtn->setText(QCoreApplication::translate("MainWindow", "Disable Tool", nullptr));
        contrastGroup->setTitle(QCoreApplication::translate("MainWindow", "Contrast", nullptr));
        contrastValueLabel->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Zoom", nullptr));
        zoomInBtn->setText(QCoreApplication::translate("MainWindow", "Zoom +", nullptr));
        zoomOutBtn->setText(QCoreApplication::translate("MainWindow", "Zoom -", nullptr));
        resetViewBtn->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        prevBtn->setText(QCoreApplication::translate("MainWindow", "Prev", nullptr));
        sliceLabel->setText(QCoreApplication::translate("MainWindow", "No images", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "Ready", nullptr));
        nextBtn->setText(QCoreApplication::translate("MainWindow", "Next", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
