#include "repl_widget.hpp"

REPLWidget::REPLWidget(QWidget *parent) : QWidget(parent)
{
    lineEdit = new QLineEdit;
    //lineEdit->setFocus(Qt::ActiveWindowFocusReason);
}

