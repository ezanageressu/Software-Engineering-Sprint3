#include <QApplication>
#include <iostream>

#include "mainwindow.h"
#include "pencil.h"
#include "pencil.cpp"
#include "production.h"
#include "production.cpp"
#include "wallet.h"
#include "wallet.cpp"

int main(int argc, char *argv[])
{
    /// Create new instance of QApplication
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
