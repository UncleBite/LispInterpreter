#include "message_widget.hpp"

MessageWidget::MessageWidget(QWidget * parent) : QWidget(parent)
{
    value = new QLineEdit;
    value->setReadOnly(true);
}

// a public slot accepting an informational message to display, clearing any error formatting
void MessageWidget::info(QString message)
{
    value->setText(message);
    value->setStyleSheet("color:black");

}

// a public slot accepting an error message to display as selected text highlighted with a red background.
void MessageWidget::error(QString message)
{
    value->setText(message);
    value->setStyleSheet("color:red");
}
