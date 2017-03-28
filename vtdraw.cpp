#include "main_window.hpp"
#include <QApplication>
#include <QDesktopWidget>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w;
    std::string file;
if (argc == 2)
{
    file = argv[1];
    w = new MainWindow(file);
}
else
{
    w = new MainWindow();
}
    QDesktopWidget *deskdop = QApplication::desktop();
    w->move((deskdop->width() - w->width())/2, (deskdop->height() - w->height())/2);
    w->show();
    return a.exec();
}
