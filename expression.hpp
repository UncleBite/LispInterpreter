#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <stdio.h>
#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include "interpreter_semantic_error.hpp"

#if !defined(_VARIADIC_MAX)
    #define _VARIADIC_MAX  5
#endif

enum atom_type {None, Boolean, Number, Point, Line, Arc, Symbol, Special_symbol};

class Expression{
public:
    // Default construct an Expression of type None
    Expression();

    // Construct an Expression with a single Boolean atom with value
    Expression(bool value);

    // Construct an Expression with a single Number atom with value
    Expression(double value);

    // Construct an Expression with a single Symbol atom with value
    Expression(const std::string & value);

    // Construct an Expression with a single Point atom with value
    Expression(std::tuple<double,double> value);

    // Construct an Expression with a single Line atom withstarting
    // point start and ending point end
    Expression(std::tuple<double,double> start, std::tuple<double,double> end);

    // Construct an Expression with a single Arc atom with center
    // point center, starting point start, and spanning angle angle in radians
    Expression(std::tuple<double,double> center, std::tuple<double,double> start, double angle);

    // Equality operator for two Expressions, two expressions are equal if the have the same
    // type, atom value, and number of arguments
    bool operator==(const Expression & exp) const noexcept;

    bool isType(atom_type type);
    bool isGraphical();
    bool isOperator();
    bool isIdentifier();

    struct Value
    {
        bool bool_value;
        double num_value;
        std::string string_value;
        std::tuple<double, double> point_value;
        std::tuple<double, double> line_value;
        atom_type type;
    };

    Value val;

};

struct list //defite list
{
    Expression a;
    std::vector<list> children;
};
const std::string DEFINE  = "define";
const std::string BEGIN  = "begin";
const std::string IF  = "if";
const std::string DRAW = "draw";
const std::string POINT = "point";
const std::string LINE  = "line";
const std::string ARC  = "arc";


#endif // EXPRESSION_H
