//
// Created by Aaron on 6/15/2017.
//

#include <QApplication>

#include "notepad.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("Notepad");

    notepad n;
    n.show();

    return app.exec();
}