//
//  tokenize.hpp
//  project1
//
//  Created by yuqiao liang on 2/13/17.
//  Copyright © 2017 yuqiao liang. All rights reserved.
//

#ifndef tokenize_h
#define tokenize_h

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
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <algorithm>
#include <cctype>
#include <stdlib.h>     /* strtod */


#include "interpreter.hpp"

std::list<std::string> tokenize(const std::string &str);


std::string repl();

list build_ast(std::list<std::string> &token);
bool isnumeric(std::string st);





Expression atom(std::string token);



#endif /* tokenize_h */
