#include "keyboard.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Keyboard k;
    k.show();
    return a.exec();
}
