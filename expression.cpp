//
//  expression.cpp
//  project1
//
//  Created by yuqiao liang on 2/15/17.
//  Copyright © 2017 yuqiao liang. All rights reserved.
//

#include "expression.hpp"

Expression::Expression()
{
    val.type = None;
}



// Construct an Expression with a single Boolean atom with value
Expression::Expression(bool value)
{
    val.type = Boolean;
    val.bool_value = value;
}

// Construct an Expression with a single Number atom with value
Expression::Expression(double value)
{
    val.type = Number;
    val.num_value = value;

}

// Construct an Expression with a single Symbol atom with value
Expression::Expression(const std::string & value)
{
    if (value == DEFINE||value == BEGIN|| value == IF)
    {
    val.type = Special_symbol;
    val.string_value = value;
    }
    else if (value == "True" )
    {
        val.type = Boolean;
        val.bool_value = true;
    }
    else if (value == "False" )
    {
        val.type = Boolean;
        val.bool_value = false;
    }
      else
      {
    val.type = Symbol;
    val.string_value = value;
    }
}


bool Expression::operator==(const Expression & exp) const noexcept
{
     if(this->val.type == exp.val.type)
     {
         if (this->val.type == Number)
         {
             return this->val.num_value == exp.val.num_value;
         }
         if (this->val.type == Symbol)
         {
             return this->val.string_value == exp.val.string_value;
         }
         if (this->val.type == Boolean)
         {
             return this->val.bool_value == exp.val.bool_value;
         }
     }
        return false;
}
