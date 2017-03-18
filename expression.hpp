//
//  expression.hpp
//  project1
//
//  Created by yuqiao liang on 2/15/17.
//  Copyright © 2017 yuqiao liang. All rights reserved.
//

#ifndef expression_hpp
#define expression_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include "interpreter_semantic_error.hpp"
enum atom_type {None, Boolean, Number, Symbol,Special_symbol};

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
    
// Equality operator for two Expressions, two expressions are equal if the have the same
// type, atom value, and number of arguments
bool operator==(const Expression & exp) const noexcept;
    
    
    struct Value
    {
        bool bool_value;
        double  num_value;
        std::string string_value;
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

#endif /* expression_hpp */
