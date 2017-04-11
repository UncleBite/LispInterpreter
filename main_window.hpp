#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <canvas_widget.hpp>
#include <QLabel>
#include "repl_widget.hpp"
#include "message_widget.hpp"
#include "qt_interpreter.hpp"
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();
    // Default construct a MainWidow, using filename as the script file to attempt to preload
    MainWindow(std::string filename, QWidget * parent = nullptr);
    void resizeEvent(QResizeEvent* event);
    void init();
    void render(QString qstr);
private slots:
    void scriptChanged();

private:
    QtInterpreter* qtInterpreter;
    CanvasWidget* canvas;
    

    REPLWidget* repl;
    MessageWidget* msg;
};

#endif // WINDOW_H
