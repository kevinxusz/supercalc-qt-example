#include "supercalc.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SuperCalc w;
    w.show();

    return a.exec();
}
