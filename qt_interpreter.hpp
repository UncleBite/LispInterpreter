#ifndef QTINTERPRETER_HPP
#define QTINTERPRETER_HPP

#include <QObject>
#include <QGraphicsItem>
#include "interpreter.hpp"
#include "qgraphics_arc_item.hpp"
#include "qgraphics_point_item.hpp"
#include "qt_environment.hpp"
#include "canvas_widget.hpp"


class QtInterpreter : public QObject, public Interpreter
{
    Q_OBJECT
public:
    // Default construct an QtInterpreter with the default environment and an empty AST
    QtInterpreter(QObject * parent = nullptr);

    void createGraphicsItem(Expression expr);

    Expression parseStatement(list node);
    Expression parseDrawStatement(list node);

    Expression parseAssignmentValue(std::string identifier, list node);

    Expression parseExpression(list node);
    Expression parseValue(list node);
    Expression parseArcExpression(list node);
    Expression parseLineExpression(list node);
    Expression parsePointExpression(list node);

    QtEnvironment qtEnv;
signals:
    // a signal emitting a graphic to be drawn as a pointer
    void drawGraphic(QGraphicsItem* item);

    // a signal emitting an informational message
    void info(QString message);

    // a signal emitting an error message
    void error(QString message);

public slots:
    // a public slot that accepts and expression string and parses/evaluates it
    void parseAndEvaluate(QString entry);

};

#endif // QTINTERPRETER_HPP
