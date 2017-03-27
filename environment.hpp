#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H


#define _USE_MATH_DEFINES
#include <cmath>

#include <stdio.h>
#include <map>
#include <iterator>
#include "expression.hpp"

class Environment
{

public:

    Environment();
    bool boolean_allow(std::string str);
    bool number_allow(std::string str);
    void add_boolean_map(std::string str,bool bool_value);
    void add_number_map(std::string str,double num_value);
    bool return_boolean(std::string str);
    double return_number(std::string str);
    std::map<std::string,bool> boolean_map;
    std::map<std::string,double> number_map;
    std::map<std::string, bool>::iterator it_bool = boolean_map.begin();
    std::map<std::string, double>::iterator it_num = number_map.begin();
};

#endif // ENVIRONMENT_H
