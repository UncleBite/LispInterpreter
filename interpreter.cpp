//
//  interpreter.cpp
//  project1
//
//  Created by yuqiao liang /Users/Frank/Documents/3574/project1/project1/project1-UncleBite/tokenize.cppon 2/13/17.
//  Copyright © 2017 yuqiao liang. All rights reserved.
//


#include "interpreter.hpp"

Interpreter::Interpreter()
{
    env = Environment();
    env.number_map["pi"] = M_PI;
}



Expression Interpreter::eval()
{

    Expression exp;
    exp = traversePost(mylist);
    if (exp.val.type==Number)
    {
        std::cout<<"("<<exp.val.num_value<<")"<<std::endl;
    }
    else if (exp.val.type ==Boolean)
    {
        if (exp.val.bool_value)
                    std::cout<<"("<<"True"<<")"<<std::endl;
        else
                    std::cout<<"("<<"False"<<")"<<std::endl;
    }
    return exp;

}


 Expression Interpreter::traversePost(list _list)
{
    

       if (_list.a.val.type== Number)
       {
           if (!_list.children.empty() )
           {
               throw InterpreterSemanticError("Error: children is not empty");
           }
           else
               
           return Expression(_list.a.val.num_value);
       }
        else if (_list.a.val.type == Boolean)
        {
            if (!_list.children.empty() )
            {
               throw InterpreterSemanticError("Error: children is not empty");
            }
            else
                return Expression(_list.a.val.bool_value);
            
            return Expression(_list.a.val.bool_value);
        }
        else if (_list.a.val.type == Symbol)
        {
            if (_list.a.val.string_value == "+")
            {
                if(_list.children.empty())
                {
               throw InterpreterSemanticError("Error: children is empty");
                }
                else
                {
                    double sum = 0;
                for (int i = 0; i<_list.children.size(); i++)
                {
                    Expression temp = traversePost(_list.children[i]);
                    if (temp.val.type != Number && temp.val.type != Symbol)
                    {
                        throw InterpreterSemanticError("Error: children is wrong type");
                    }
                    else
                    {
                        sum=sum+temp.val.num_value;
                    }
                }
                    return Expression(sum);
                }
            }
    else if (_list.a.val.string_value == "*")
    {
        if(_list.children.empty())
        {
               throw InterpreterSemanticError("Error: children is empty");
        }
        else
        {
            double product = 1;
            for (int i = 0; i<_list.children.size(); i++)
            {
                Expression temp = traversePost(_list.children[i]);

                if (temp.val.type != Number && temp.val.type != Symbol)
                {
               throw InterpreterSemanticError("Error: children is wrong type");
                }
                else
                {
                    product=product*temp.val.num_value;
                }
            }
            return Expression(product);
        }
    }
    else if (_list.a.val.string_value == "-")
    {
            double difference = 0;
            double negation = 0;
            if (_list.children.size() ==1)
            {
                Expression temp = traversePost(_list.children[0]);
                if (temp.val.type==Number&&temp.val.type != Symbol)
                {
                    negation = 0 - temp.val.num_value;
                    return Expression(negation);
                }
               throw InterpreterSemanticError("Error: children is not a number");
            }
            else if (_list.children.size() == 2)
            {
                Expression temp1 = traversePost(_list.children[0]);
                Expression temp2 = traversePost(_list.children[1]);
             if(temp1.val.type == Number && temp2.val.type == Number )
             {
                 difference =temp1.val.num_value-temp2.val.num_value;
                 return Expression(difference);
             }
               throw InterpreterSemanticError("Error: children is not a number");
            }
            else
            throw InterpreterSemanticError("Error: children number is wrong");
        
    }
    else if (_list.a.val.string_value == "/")
    {
        double quotient = 1;
        if (_list.children.size() == 2)
        {
            Expression temp1 = traversePost(_list.children[0]);
            Expression temp2 = traversePost(_list.children[1]);
            if(temp1.val.type == Number && temp2.val.type == Number )
            {
                quotient =temp1.val.num_value / temp2.val.num_value;
                return Expression(quotient);
            }
                throw InterpreterSemanticError("Error: children is not a number");
        }
        else
        throw InterpreterSemanticError("Error: children number is wrong");
    }
            else if (_list.a.val.string_value == "not")
            {
                if(_list.children.empty())
                {
                    throw InterpreterSemanticError("Error: children is empty");
                }
                else if (_list.children.size() == 1)
                {
                    if (_list.children[0].a.val.bool_value == true) {
                        return Expression(false);
                    }
                    if (_list.children[0].a.val.bool_value == false)
                        return Expression(true);
                        throw InterpreterSemanticError("Error: argument type is not correct");
                }
                else
                {
                      throw InterpreterSemanticError("Error: not valid number of argument");
                }
            }
            else if (_list.a.val.string_value == "and")
            {
                if(_list.children.empty())
                {
                    throw InterpreterSemanticError("Error: children is empty");
                }
                else
                {
                    bool logic_result = true;
                for (int i = 0; i<_list.children.size(); i++)
                {
                    Expression temp = traversePost(_list.children[i]);
                    
                    if (temp.val.type != Boolean)
                    {
                        throw InterpreterSemanticError("Error: children is not logic operator");
                    }
                    else
                    {
                        logic_result= logic_result && temp.val.bool_value;
                    }
                }
                    return Expression(logic_result);
                }
            }
            else if (_list.a.val.string_value == "or")
            {
                if(_list.children.empty())
                {
                    throw InterpreterSemanticError("Error: children is empty");
                }
                else
                {
                    bool logic_result = false;
                    for (int i = 0; i<_list.children.size(); i++)
                    {
                        Expression temp = traversePost(_list.children[i]);
                        
                        if (temp.val.type != Boolean)
                        {
                            throw InterpreterSemanticError("Error: children is not logic operator");
                        }
                        else
                        {
                            logic_result= logic_result || temp.val.bool_value;
                        }
                    }
                    return Expression(logic_result);
                }
            }
            else if (_list.a.val.string_value == "<" )
            {

                if (_list.children.size() == 2)
                {
                    Expression temp1 = traversePost(_list.children[0]);
                    Expression temp2 = traversePost(_list.children[1]);
                    if(temp1.val.type == Number && temp2.val.type == Number )
                    {
                        if (temp1.val.num_value < temp2.val.num_value)
                        return Expression(true);
                        return Expression(false);
                    }
                        throw InterpreterSemanticError("Error: children is not a number");
                }
                else
                    throw InterpreterSemanticError("Error: children number is wrong");
            }
            else if (_list.a.val.string_value == "<=" )
            {
                
                if (_list.children.size() == 2)
                {
                    Expression temp1 = traversePost(_list.children[0]);
                    Expression temp2 = traversePost(_list.children[1]);
                    if(temp1.val.type == Number && temp2.val.type == Number )
                    {
                        if (temp1.val.num_value < temp2.val.num_value)
                            return Expression(true);
                        if (temp1.val.num_value == temp2.val.num_value)
                            return Expression(true);
                            return Expression(false);
                    }
                        throw InterpreterSemanticError("Error: children is not a number");
                }
                    throw InterpreterSemanticError("Error: children number is wrong");
            }
            else if (_list.a.val.string_value == ">" )
            {
                
                if (_list.children.size() == 2)
                {
                    Expression temp1 = traversePost(_list.children[0]);
                    Expression temp2 = traversePost(_list.children[1]);
                    if(temp1.val.type == Number && temp2.val.type == Number )
                    {
                        if (temp1.val.num_value > temp2.val.num_value)
                            return Expression(true);
                            return Expression(false);
                    }
                        throw InterpreterSemanticError("Error: children is not a number");
                }
                else
                    throw InterpreterSemanticError("Error: children number is wrong");
                
            }
            else if (_list.a.val.string_value == ">=" )
            {
                if (_list.children.size() == 2)
                {
                    Expression temp1 = traversePost(_list.children[0]);
                    Expression temp2 = traversePost(_list.children[1]);
                    if(temp1.val.type == Number && temp2.val.type == Number )
                    {
                        if (temp1.val.num_value > temp2.val.num_value)
                            return Expression(true);
                        if (temp1.val.num_value == temp2.val.num_value)
                            return Expression(true);
                            return Expression(false);
                    }
                        throw InterpreterSemanticError("Error: children is not a number");
                }
                    throw InterpreterSemanticError("Error: children number is wrong");
            }
            else if (_list.a.val.string_value == "=" )
            {
                if (_list.children.size() == 2)
                {
                    Expression temp1 = traversePost(_list.children[0]);
                    Expression temp2 = traversePost(_list.children[1]);
                    if(temp1.val.type == Number && temp2.val.type == Number )
                    {
                        if (temp1.val.num_value == temp2.val.num_value)
                            return Expression(true);
                            return Expression(false);
                    }
                        throw InterpreterSemanticError("Error: children is not a number");
                }
                    throw InterpreterSemanticError("Error: children number is wrong");
            }
            else
            {
                if (env.number_map.find(_list.a.val.string_value)!= env.number_map.end()) //find the number
                {
                    return Expression(env.return_number(_list.a.val.string_value)) ;
                }
                if(env.boolean_map.find(_list.a.val.string_value)!= env.boolean_map.end())
                {
                    return Expression(env.return_boolean(_list.a.val.string_value));
                }
            }
        }
        else if (_list.a.val.type == Special_symbol)
        {
            if (_list.a.val.string_value == "if")
            {
                if (_list.children.size() == 3)
                {
                    Expression temp1 = traversePost(_list.children[0]);
                    Expression temp2 = traversePost(_list.children[1]);
                    Expression temp3 = traversePost(_list.children[2]);
                    if (temp1.val.type==Boolean)
                    {
                        if(temp1.val.bool_value == true )
                            return temp2;
                            return temp3;
                    }
                        throw InterpreterSemanticError("Error: argument didn't return boolean value");
                }
                else
                    throw InterpreterSemanticError("Error: children number is wrong");
            }
            else if (_list.a.val.string_value == "begin")
            {
                if(_list.children.empty())
                {
                    throw InterpreterSemanticError("Error: children is empty");
                }
                else
                {
                    Expression temp;
                    for (int i = 0; i<_list.children.size(); i++)
                    {
                        temp = traversePost(_list.children[i]);
                    }
                    return temp;
                }
            }
            else if (_list.a.val.string_value == "define")
            {
                if (_list.children.size() == 2)
                {
                    if (_list.children[0].a.val.string_value == "begin"||_list.children[0].a.val.string_value == "define"||_list.children[0].a.val.string_value == "if")
                    {
                        throw InterpreterSemanticError("Error: DEFINE is not valid");
                        return Expression();
                    }
                    Expression temp0 = traversePost(_list.children[0]);
                    Expression temp = traversePost(_list.children[1]);
                    if (env.boolean_allow(_list.children[0].a.val.string_value)&& temp.val.type==Boolean)
                    {
                    env.add_boolean_map(_list.children[0].a.val.string_value, temp.val.bool_value);
                        return Expression(temp.val.bool_value);
                    }
                    else if (env.number_allow(_list.children[0].a.val.string_value)&& temp.val.type==Number)
                    {
                    env.add_number_map(_list.children[0].a.val.string_value, temp.val.num_value);
                        return Expression(temp.val.num_value);
                    }
                    else
                    throw InterpreterSemanticError("Error: DEFINE not valid");
                }
                else
                    throw InterpreterSemanticError("Error: DEFINE has too much arguments");
           }
        }
        else
              throw InterpreterSemanticError("Error: eval not valid");
    return Expression();

}





