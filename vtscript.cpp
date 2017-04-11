//
//  main.cpp
//  project1
//
//  Created by yuqiao liang on 2/19/17.
//  Copyright © 2017 yuqiao liang. All rights reserved.
//

#include <stdio.h>

#include "tokenize.hpp"
#include "interpreter.hpp"
#include <sstream>





int main(int argc, char *argv[])
{
    Interpreter a;
    if (argc == 1) //if no input, then repl
    {
        while (true)
        {
            std::cout<<"vtscript> ";
            std::string replcommand;
            std::getline(std::cin,replcommand);
            std::stringstream parsecommand;
            parsecommand<<replcommand<<std::endl;
            
            try {
                if(!a.parse(parsecommand))
                {
                    std::cout<<"Error: eval not valid"<<std::endl;
                }
                else{
                a.eval();
                }
            } catch (InterpreterSemanticError ex) {
                std::cout << ex.what() << std::endl;
            }
        }
    }
    if (argc ==2 )// if one input(file_name)
    {
        std::fstream file_in(argv[1]);
        
        if (!file_in.good()) {
            std::cout<<"Error: cannot open this file"<<std::endl;
            exit(EXIT_FAILURE);
        }
        
        try {
            if(!a.parse(file_in))
            {
                std::cout<<"Error: eval not valid"<<std::endl;
                    exit(EXIT_FAILURE);
            }
            else
            a.eval();
        } catch (InterpreterSemanticError ex1)
        {
            std::cout << ex1.what() << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else if (argc == 3) //if input is third argument
    {
        std::string input;
        input = argv[2];
        std::stringstream sstream(input);
        try {
            if(!a.parse(sstream))
            {
                std::cout<<"Error: eval not valid"<<std::endl;
                    exit(EXIT_FAILURE);
            }
            else
            {
            a.eval();
            }
        } catch (InterpreterSemanticError ex2) {
            std::cout << ex2.what() << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    exit(EXIT_SUCCESS);
}
