#include <Qt/qapplication.h>
#include "mainWin.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWin w;
    a.setGeometry(100,100,500,500);
    a.setMainWidget(&w);
    w.show();

    return a.exec();
}
