#include "mainwindow.h"

#include <QApplication>
#include <QCoreApplication>
#include <QThreadPool>
#include "candevice.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    int res=0;
    return a.exec();
}
