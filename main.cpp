#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Mini CT Viewer");
    a.setOrganizationName("SurgeonLabs");
    MainWindow w;
    w.show();
    return a.exec();
}
