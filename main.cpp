#include "GUI/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}


//http://tango.freedesktop.org/Tango_Icon_Library
//http://asmaloney.com/2013/11/code/converting-between-cvmat-and-qimage-or-qpixmap/
