#ifndef REPL_WIDGET_HPP
#define REPL_WIDGET_HPP

#include <list>
#include <QWidget>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
class REPLWidget : public QWidget
{
    Q_OBJECT
public:
    REPLWidget(QWidget *parent = nullptr);
    QLabel* scriptLabel;
    QLineEdit* lineEdit;

signals:
    // A signal that sends the current edited text as a QString when the return key is pressed.
    void lineEntered(QString);

public slots:

private:
    std::list<QString>* history;
};

#endif // REPL_WIDGET_HPP
