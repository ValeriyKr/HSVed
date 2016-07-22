#include "hsved.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HSVed w;
    w.show();

    return a.exec();
}
