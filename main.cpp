#include "mainwindow.h"
#include "gamewindow.h"
#include "server.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server server;

    MainWindow w;
    GameWindow g;
    w.show();
    g.show();
    return a.exec();
}
