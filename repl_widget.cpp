#include "repl_widget.hpp"

REPLWidget::REPLWidget(QWidget *parent) : QWidget(parent)
{

    lineEdit = new QLineEdit;

    auto scriptLabel = new QLabel(tr("vtscript>"));
    auto layout2 = new QHBoxLayout;
    layout2->addWidget(scriptLabel);
    layout2->addWidget(lineEdit);
    setLayout(layout2);
    //lineEdit->setFocus(Qt::ActiveWindowFocusReason);
}

