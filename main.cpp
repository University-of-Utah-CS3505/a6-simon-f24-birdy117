#include "mainwindow.h"

#include <QApplication>

/*
 * Aaron Perez CS3505
 * A6: Qt Simon Game
 * Github User: birdy117
 * https://github.com/University-of-Utah-CS3505/a6-simon-f24-birdy117
 * This file is the main function that runs the MainWindow.cpp file
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
