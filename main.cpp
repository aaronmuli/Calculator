#include "orbit_calc.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Orbit_calc w;
    w.show();
    return a.exec();
}
