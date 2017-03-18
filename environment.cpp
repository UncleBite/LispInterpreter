//
//  environment.cpp
//  project1
//
//  Created by yuqiao liang on 2/14/17.
//  Copyright © 2017 yuqiao liang. All rights reserved.
//

#include "environment.hpp"




Environment::Environment()
{
    std::map<std::string,bool> boolean_map;
    std::map<std::string,double> number_map;
}

bool Environment::boolean_allow(std::string str)
{
    return boolean_map.find(str) == boolean_map.end();
}

bool Environment::number_allow(std::string str)
{
    return number_map.find(str) == number_map.end();
}
void Environment::add_boolean_map(std::string str,bool bool_value)
{
    if (boolean_allow(str))
    {
        boolean_map.insert({str, bool_value});
    }
    else
    {
        throw InterpreterSemanticError("Error: already defined");
    }
    
    return;
}
void Environment::add_number_map(std::string str, double num_value)
{
    if (number_allow(str))
    {
        number_map.insert({str, num_value});
    }
    else
    {
        throw InterpreterSemanticError("Error: already defined");
    }
    return;
}

bool Environment::return_boolean(std::string str)
{
    if (boolean_map.find(str) == boolean_map.end())
    return false;
    it_bool = boolean_map.find(str);
    return it_bool->second;
}

double Environment::return_number(std::string str)
{
    if (number_map.find(str) == number_map.end())
    return 0;
    it_num = number_map.find(str);
    return it_num->second;
}

