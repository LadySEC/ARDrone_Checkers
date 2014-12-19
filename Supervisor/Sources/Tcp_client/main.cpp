#include "mainwindow.h"
#include <QApplication>
#include <QLineEdit>
#include <QtPlugin>

/*Q_IMPORT_PLUGIN(qtaccessiblewidgets)
Q_IMPORT_PLUGIN(qjpeg)
Q_IMPORT_PLUGIN(qgif)*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();
}
