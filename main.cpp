#include "mainwindow.h"

#include <QApplication>

/*
 * Aaron Perez CS3505
 * A6: Qt Simon Game
 *
 * This header file lays out the slots and functions to be implemented in the main .cpp file.
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
