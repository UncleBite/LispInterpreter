#include "main_window.hpp"
#include <QApplication>
#include <QDesktopWidget>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    QDesktopWidget *deskdop = QApplication::desktop();
    w.move((deskdop->width() - w.width())/2, (deskdop->height() - w.height())/2);

    return a.exec();
}
