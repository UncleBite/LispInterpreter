#include "interpreter.hpp"

Interpreter::Interpreter()
{
    env = Environment();
    env.number_map["pi"] = M_PI;
}



Expression Interpreter::eval()
{
    Expression exp;
    exp = parseStatement(mylist);
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

Expression Interpreter::parseStatement(list node)
{

if (node.a.val.string_value == "" && node.a.val.type == None)
 throwError("Error: eval error");

if (node.a.val.string_value == "draw")
{
std::cout<<"(None)"<<std::endl;
}

if(node.a.val.string_value == "point")
{
    if(node.children.size() == 2)
    {

        auto first = parseExpression(node.children[0]);
        auto second = parseExpression(node.children[1]);
        if(first.isType(Number) && second.isType(Number)){

            return Expression(std::make_tuple(first.val.num_value, second.val.num_value));
        }
    }
    else
    throwError("Error: POINT has invalid arguments");
}

if(node.a.val.string_value == "line")
{
    if(node.children.size() == 2)
    {

        auto first = parseExpression(node.children[0]);
        auto second = parseExpression(node.children[1]);

        if(first.isType(Point) && second.isType(Point))
        {
            return Expression(first.val.point_value, second.val.point_value);
        }
    }
    else
    throwError("Error: LINE has invalid arguments");
}

if(node.a.val.string_value == "arc")
{
    if(node.children.size() == 3)
    {
        auto start = parseExpression(node.children[0]);
        auto end = parseExpression(node.children[1]);
        auto angle = parseSymbol(node.children[2]);
        if(start.isType(Point) && end.isType(Point) && angle.isType(Number)){

            return Expression(start.val.point_value, end.val.point_value, angle.val.num_value);
        }
    }

}
    return this->parseDefineStatement(node);
}

Expression Interpreter::parseDefineStatement(list node)
{
    if(node.a.val.string_value == DEFINE)
    {
        if(node.children.size() == 2)
        {
            Expression identifier = parseIdentifer(node.children[0]);
            Expression value = parseAssignmentValue(identifier.val.string_value, node.children[1]);

            if (node.children[0].a.val.string_value =="pi"  )
            {
                    throw InterpreterSemanticError("Error: DEFINE wrong");
            }

//            if ( !value.isType(Number) && !value.isType(Boolean))
//            {
//            throw InterpreterSemanticError("Error: DEFINE wrong");
//            }
            return value;
        }
        else {
            throw InterpreterSemanticError("Error: DEFINE has invalid arguments count");
        }
    }
    return this->parseBeginStatement(node);
}
Expression Interpreter::parseBeginStatement(list node)
{
    if(node.a.val.string_value == BEGIN)
    {
        if(node.children.empty())
        {
            throw InterpreterSemanticError("Error: children is empty");
        }
        else
        {
            Expression temp;
            for (int i = 0; i<node.children.size(); i++)
            {
                temp = parseStatement(node.children[i]);
            }
            return temp;
        }
    }
    return this->parseIfStatement(node);
}
Expression Interpreter::parseIfStatement(list node)
{
    if(node.a.val.string_value == IF)
    {
        if (node.children.size() == 3)
        {
            Expression temp1 = parseStatement(node.children[0]);
            Expression temp2 = parseStatement(node.children[1]);
            Expression temp3 = parseStatement(node.children[2]);
            if (temp1.val.type == Boolean)
            {
                if(temp1.val.bool_value == true)
                return temp2;
                return temp3;
            }
            throw InterpreterSemanticError("Error: argument didn't return boolean value");
        }
        else
        throw InterpreterSemanticError("Error: children number is wrong");
        
    }
    return this->parseExpression(node);
}

Expression Interpreter::parseExpression(list node){
    return parseSymbol(node);
}

Expression Interpreter::parseIdentifer(list node)
{
    if(node.a.isIdentifier())
    {
        if(node.children.empty()){
            return node.a;
        }
        throwError("Error: invalid identifier");
    }
    throw InterpreterSemanticError("Error: expect a identifier");
}


Expression Interpreter::parseSymbol(list node){
    if (node.a.val.type == Symbol)
    {
        if (node.a.val.string_value == "+")
        {
            if(node.children.empty())
            {
                throw InterpreterSemanticError("Error: children is empty");
            }
            else
            {
                double sum = 0;
                for (int i = 0; i<node.children.size(); i++)
                {
                    Expression temp = parseStatement(node.children[i]);
                    if (temp.isType(Number))
                    {
                        sum=sum+temp.val.num_value;
                    }
                    else
                    {
                        throw InterpreterSemanticError("Error: children is wrong type");
                    }
                }
                return Expression(sum);
            }
        }
        else if (node.a.val.string_value == "*")
        {
            if(node.children.empty())
            {
                throw InterpreterSemanticError("Error: children is empty");
            }
            else
            {
                double product = 1;
                for (int i = 0; i<node.children.size(); i++)
                {
                    Expression temp = parseStatement(node.children[i]);
                    
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
        else if (node.a.val.string_value == "-")
        {
            double difference = 0;
            double negation = 0;
            if (node.children.size() ==1)
            {
                Expression temp = parseStatement(node.children[0]);
                if (temp.val.type==Number&&temp.val.type != Symbol)
                {
                    negation = 0 - temp.val.num_value;
                    return Expression(negation);
                }
                throw InterpreterSemanticError("Error: children is not a number");
            }
            else if (node.children.size() == 2)
            {
                Expression temp1 = parseStatement(node.children[0]);
                Expression temp2 = parseStatement(node.children[1]);
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
        else if (node.a.val.string_value == "/")
        {
            double quotient = 1;
            if (node.children.size() == 2)
            {
                Expression temp1 = parseStatement(node.children[0]);
                Expression temp2 = parseStatement(node.children[1]);
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
        else if (node.a.val.string_value == "not")
        {
            if(node.children.empty())
            {
                throw InterpreterSemanticError("Error: children is empty");
            }
            else if (node.children.size() == 1)
            {
                if (node.children[0].a.val.bool_value == true) {
                    return Expression(false);
                }
                if (node.children[0].a.val.bool_value == false)
                return Expression(true);
                throw InterpreterSemanticError("Error: argument type is not correct");
            }
            else
            {
                throw InterpreterSemanticError("Error: not valid number of argument");
            }
        }
        else if (node.a.val.string_value == "and")
        {
            if(node.children.empty())
            {
                throw InterpreterSemanticError("Error: children is empty");
            }
            else
            {
                bool logic_result = true;
                for (int i = 0; i<node.children.size(); i++)
                {
                    Expression temp = parseStatement(node.children[i]);
                    
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
        else if (node.a.val.string_value == "or")
        {
            if(node.children.empty())
            {
                throw InterpreterSemanticError("Error: children is empty");
            }
            else
            {
                bool logic_result = false;
                for (int i = 0; i<node.children.size(); i++)
                {
                    Expression temp = parseStatement(node.children[i]);
                    
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
        else if (node.a.val.string_value == "<" )
        {
            if (node.children.size() == 2)
            {
                Expression temp1 = parseStatement(node.children[0]);
                Expression temp2 = parseStatement(node.children[1]);
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
        else if (node.a.val.string_value == "<=" )
        {
            
            if (node.children.size() == 2)
            {
                Expression temp1 = parseStatement(node.children[0]);
                Expression temp2 = parseStatement(node.children[1]);
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
        else if (node.a.val.string_value == ">" )
        {
            
            if (node.children.size() == 2)
            {
                Expression temp1 = parseStatement(node.children[0]);
                Expression temp2 = parseStatement(node.children[1]);
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
        else if (node.a.val.string_value == ">=" )
        {
            if (node.children.size() == 2)
            {
                Expression temp1 = parseStatement(node.children[0]);
                Expression temp2 = parseStatement(node.children[1]);
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
        else if (node.a.val.string_value == "=" )
        {
            if (node.children.size() == 2)
            {
                Expression temp1 = parseStatement(node.children[0]);
                Expression temp2 = parseStatement(node.children[1]);
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
    }
    return parseValue(node);
}

Expression Interpreter::parseValue(list node){
    if (node.a.val.type == Number)
    {
        if (!node.children.empty() )
        {
            throw InterpreterSemanticError("Error: children is not empty");
        }
        else
        return Expression(node.a.val.num_value);
    }
    else if (node.a.val.type == Boolean)
    {
        if (!node.children.empty() )
        {
            throw InterpreterSemanticError("Error: children is not empty");
        }
        else
        return Expression(node.a.val.bool_value);
        
        return Expression(node.a.val.bool_value);
    }
    else {
        if (env.number_map.find(node.a.val.string_value)!= env.number_map.end()) //find the number
        {
            return Expression(env.return_number(node.a.val.string_value)) ;
        } else if(env.boolean_map.find(node.a.val.string_value)!= env.boolean_map.end())
        {
            return Expression(env.return_boolean(node.a.val.string_value));
        } else {
            return Expression();
        }
    }
}

Expression Interpreter::parseAssignmentValue(std::string identifier, list node)
{
    if (node.a.val.type == Boolean )
    {
        if(env.boolean_allow(identifier)){
            env.add_boolean_map(identifier, node.a.val.bool_value);
            return Expression(node.a.val.bool_value);
        } else {
            throwError("Error: identifier already defined");
        }
    }
    else if (node.a.val.type == Number && env.number_allow(identifier))
    {
        if(env.boolean_allow(identifier)){
            env.add_number_map(identifier, node.a.val.num_value);
            return Expression(node.a.val.num_value);
        } else {
            throwError("Error: identifier already defined");
        }
    }
    return Expression();
}

void Interpreter::throwError(std::string msg){
    throw InterpreterSemanticError(msg);
}
