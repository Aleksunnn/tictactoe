#include "mainwindow.h"
#include <QApplication>
#include "mainwidget.h"
#include "table.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
