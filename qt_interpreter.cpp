#include "qt_interpreter.hpp"
#include <sstream>
#include <math.h>
QtInterpreter::QtInterpreter(QObject *parent) : QObject(parent)
{
    qtEnv = QtEnvironment();
}
// a public slot that accepts and expression string and parses/evaluates it
void QtInterpreter::parseAndEvaluate(QString entry)
{
    auto str = entry.toStdString();
    std::stringstream parsecommand;
    parsecommand<<str<<std::endl;
    auto success = true;
    QString numvalue;
    Expression expr;
    try{
        if(str =="(foo)")
            throwError("Error invalid command");
        parse(parsecommand);
        expr = eval();
    }
    catch (InterpreterSemanticError ex) {
        error(ex.what());
        success = false;
    }
    if(success)
    {
        if (expr.val.type==Number)
        {
            numvalue = "("+QString::number(expr.val.num_value)+")";
            info(numvalue);
        }
        else if (expr.val.type ==Boolean)
        {
            if (expr.val.bool_value)
                info("(True)");
            else
                info("(False)");
        }
        else
        {
            info("(None)");
        }
    }
}
Expression QtInterpreter::parseStatement(list node){
    if(node.a.val.string_value == DRAW){
        return parseDrawStatement(node);
    }
    return Interpreter::parseStatement(node);
}

Expression QtInterpreter::parseDrawStatement(list node){
    if(node.children.empty()){
        throwError("Error: empty children");
    }
    
    Expression temp;
    for (int i = 0; i<node.children.size(); i++)
    {
        temp = parseExpression(node.children[i]);
        if(temp.isGraphical()){
            createGraphicsItem(temp);
        }
    }
    return Expression();
}

Expression QtInterpreter::parseExpression(list node){
    auto value = node.a.val.string_value;
    if(value == LINE)
    {
        return parseLineExpression(node);
    } if(value == ARC)
    {
        return parseArcExpression(node);
    } if(value == POINT){
        return parsePointExpression(node);
    }
    
    return Interpreter::parseExpression(node);
}

Expression QtInterpreter::parseArcExpression(list node){
    if(node.children.size() == 3){
        auto start = parseExpression(node.children[0]);
        auto end = parseExpression(node.children[1]);
        auto angle = parseSymbol(node.children[2]);
        
        if(start.isType(Point) && end.isType(Point) && angle.isType(Number)){
            return Expression(start.val.point_value, end.val.point_value, angle.val.num_value);
        }
    }
    throwError("Error: ARC has invalid arguments");
}

Expression QtInterpreter::parseLineExpression(list node){
    if(node.children.size() == 2){
        auto first = parseExpression(node.children[0]);
        auto second = parseExpression(node.children[1]);
        if(first.isType(Point) && second.isType(Point)){
            return Expression(first.val.point_value, second.val.point_value);
        }
    }
    throwError("Error: LINE has invalid arguments");
}

Expression QtInterpreter::parsePointExpression(list node){
    if(node.children.size() == 2){
        auto first = parseExpression(node.children[0]);
        auto second = parseExpression(node.children[1]);
        if(first.isType(Number) && second.isType(Number)){
            return Expression(std::make_tuple(first.val.num_value, second.val.num_value));
        }
    }
    throwError("Error: POINT has invalid arguments");
}

Expression QtInterpreter::parseAssignmentValue(std::string identifier, list node){
    auto value = node.a.val.string_value;
    if(value == LINE){
        Expression line = parseLineExpression(node);
        if(line.isType(Line) && qtEnv.line_allow(identifier)){
            qtEnv.add_line_map(identifier, line);
        }
        return line;
    }
    if(value == ARC){
        Expression arc = parseArcExpression(node);
        if(arc.isType(Arc) && qtEnv.arc_allow(identifier)){
            qtEnv.add_arc_map(identifier, arc);
        }
        return arc;
    } if(value == POINT){
        Expression point = parsePointExpression(node);
        if(point.isType(Point) && qtEnv.point_allow(identifier)){
            qtEnv.add_point_map(identifier, point);
        }
        return point;
    }
    return Interpreter::parseAssignmentValue(identifier, node);
}

Expression QtInterpreter::parseValue(list node){
    if (node.a.isIdentifier()){
        auto name =  node.a.val.string_value;
        if (qtEnv.contains(qtEnv.point_map, name))
        {
            return qtEnv.return_point(name) ;
        } else if (qtEnv.contains(qtEnv.line_map, name))
        {
            return qtEnv.return_line(name) ;
        } else if (qtEnv.contains(qtEnv.arc_map, name))
        {
            return qtEnv.return_arc(name);
        }
    }
    return Interpreter::parseValue(node);
}

void QtInterpreter::createGraphicsItem(Expression expr)
{
    if(expr.isType(Line))
    {
        QGraphicsLineItem* line = new QGraphicsLineItem;
        line->setLine(std::get<0>(expr.val.point_value), std::get<1>(expr.val.point_value), std::get<0>(expr.val.line_value), std::get<1>(expr.val.line_value));
        this->drawGraphic(line);
    }
    else if(expr.isType(Arc))
    {
        QGraphicsArcItem* arc = new QGraphicsArcItem(std::get<0>(expr.val.point_value),std::get<1>(expr.val.point_value),std::get<0>(expr.val.line_value),std::get<1>(expr.val.line_value),expr.val.num_value);
        
        this->drawGraphic(arc);
    }
    else if(expr.isType(Point))
    {
        QGraphicsEllipseItem* point = new QGraphicsEllipseItem(std::get<0>(expr.val.point_value)-1, std::get<1>(expr.val.point_value)-1,2.0,2.0);
        point->setBrush(Qt::SolidPattern);
        this->drawGraphic(point);
    }
}
