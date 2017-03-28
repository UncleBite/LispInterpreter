#include "message_widget.hpp"
#include <QLayout>
#include <QPalette>

MessageWidget::MessageWidget(QWidget * parent) : QWidget(parent)
{
   // label =new QLabel("vtscript>");
    value = new QLineEdit;
    value->setReadOnly(true);
    auto label =new QLabel("message:");
    //QLayout *Layout1 = new QLayout;
    auto layout1 = new QHBoxLayout;
    layout1->addWidget(label);
    layout1->addWidget(value);
    setLayout(layout1);
}

// a public slot accepting an informational message to display, clearing any error formatting
void MessageWidget::info(QString message)
{
    QPalette p;
    p.setColor(QPalette::Highlight,Qt::blue);
    value->deselect();
    value->setText(message);
   // value->setStyleSheet("color:black");
    value->setPalette(p);
}

// a public slot accepting an error message to display as selected text highlighted with a red background.
void MessageWidget::error(QString message)
{   QPalette p;
p.setColor(QPalette::Highlight,Qt::red);
    value->setText(message);
    value->selectAll();
value->setPalette(p);
 //   value->setStyleSheet("color:black;background-color: white;selection-background-color: red;selection-color: white");
}
