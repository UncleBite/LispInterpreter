//
//  interpreter.hpp
//  project1
//
//  Created by yuqiao liang on 2/13/17.
//  Copyright © 2017 yuqiao liang. All rights reserved.
//


#ifndef INTERPRETER_H
#define INTERPRETER_H


#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <list>
#include <map>


#include "expression.hpp"
#include "environment.hpp"

class Interpreter
{
public:

    // Default construct an Interpreter with the default environment and an empty AST
    Interpreter();

    // Given a vtscript program as a std::istream, attempt to parse into an internal AST
    // return true on success, false on failure
    bool parse(std::istream & expression) noexcept;

    // Evaluate the current AST and return the resulting Expression
    // throws InterpreterSemanticError if a semantic error is encountered
    // the exception message string should document the nature of the semantic error

    Expression eval();


    Environment env;

    virtual Expression parseStatement(list node);
    Expression parseDefineStatement(list node);
    Expression parseIfStatement(list node);
    Expression parseBeginStatement(list node);

    virtual Expression parseAssignmentValue(std::string identifier, list node);

    virtual Expression parseExpression(list node);
    virtual Expression parseValue(list node);

    Expression parseSymbol(list node);
    Expression parseIdentifer(list node);

    void throwError(std::string msg);


    list mylist;
};

#endif // INTERPRETER_H
