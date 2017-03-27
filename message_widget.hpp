#ifndef MESSAGE_WIDGET_HPP
#define MESSAGE_WIDGET_HPP

#include <QWidget>
#include <QLineEdit>

class MessageWidget : public QWidget
{
    Q_OBJECT
public:
    MessageWidget(QWidget * parent = nullptr);

    QLineEdit* value;

signals:

public slots:
    // a public slot accepting an informational message to display, clearing any error formatting
    void info(QString message);

    // a public slot accepting an error message to display as selected text highlighted with a red background.
    void error(QString message);
private:
};

#endif // MESSAGE_WIDGET_HPP
