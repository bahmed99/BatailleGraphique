#include "game.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    srand((int)time(0));
    QApplication a(argc, argv);
    Game w;
    w.setWindowIcon(QIcon(":/images/1.ico"));

    w.show();
    return a.exec();
}
