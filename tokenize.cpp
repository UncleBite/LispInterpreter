
#include "tokenize.hpp"

std::list<std::string> tokenize(const std::string & str)
{
    std::list<std::string> tokens;
    const char * s = str.c_str();
    while (*s!=0)
    {
        while (*s == ' ')
        { ++s;}
        while (*s == '\r')
        {++s;}
        if (*s == '(' || *s == ')')
        {tokens.push_back(*s++ == '(' ? "(" : ")");
        }
        else {
            const char * t = s;
            while (*t !=0 && *t != ' ' && *t != '(' && *t != ')' && *t!= '\r')
            { ++t;}
            tokens.push_back(std::string(s, t));
            s = t;
        }
    }
    return tokens;
}


list build_ast(std::list<std::string> &tokens)
{
    if (tokens.size() == 0)
    {
        throw new InterpreterSemanticError("Error: invalid input");
    }
    if (tokens.front() == "(")
    {
        tokens.pop_front();
        list newlist;
        if (isnumeric(tokens.front()) && tokens.front() !="-")
        {
            newlist.a = Expression(atof(tokens.front().c_str()));
        }
        else
        {
            newlist.a = Expression(tokens.front());
        }
        tokens.pop_front();
        while ( tokens.front() !=")")
        {
            newlist.children.push_back(build_ast(tokens));
        }
        tokens.pop_front();
        return newlist;
    }
    else if (tokens.front() == ")")
    {
        std::cout<<"Error: syntax error! "<<std::endl;
        throw InterpreterSemanticError("Error: invalid input");
    }
    else
    {
        list list_temp;
        list_temp.a = atom(tokens.front());
        tokens.pop_front();

        return list_temp;
    }
}

Expression atom(std::string token)
{
    if (
        token == "define"||token == "if"||token == "begin" ||
        token == ""|| token == "draw"|| token == "line"||
            token == "point"||token == "arc"
    )
    {
        return Expression(token); //symbol
    }
    else if (token == "True")
    {
        return Expression(true);
    }
    else if (token == "False")
    {
        return Expression(false);
    }
    else if (isnumeric(token) )
    {
        return Expression(atof(token.c_str()));//number
    }
    else if (token == "line")
    {
        return Expression(true);
    }
    else if (token == "True")
    {
        return Expression(true);
    }
    else if (token == "True")
    {
        return Expression(true);
    }

    else
    {
        int i =0;
        while (token.c_str()[i])
        {
            if ((!(isalpha(token.c_str()[i]))) == 0)

                return Expression(token);
        }
        return Expression(token);
    }
}

bool isnumeric(std::string st) {
    char * pEnd = NULL;
    double d = strtod(st.c_str(), &pEnd);
    return (*pEnd==0);
}

bool Interpreter::parse(std::istream & expression) noexcept
{
    std::string str;
    std::string whole_str;
    bool flag = false;
    while (!expression.eof())
    {
        getline(expression, str);
        if (!str.empty())
        {
            for (std::string::iterator it=str.begin(); it!=str.end(); ++it)
            {
                if (*it == ';' )
                {
                    str.erase(it,str.end());
                    break;
                }
            }
            whole_str += str;
        }
    }
    int counter = 0;

    for (std::string::iterator whole_it=whole_str.begin(); whole_it!=whole_str.end(); ++whole_it)
    {
        if (*whole_it == '(' )
        {
            counter+=1;
            flag = true;
        }
        if(*whole_it == ')')
            counter-=1;
    }

    if(counter != 0)
    {

        return false;
    }
    if (!flag)
    {

        return false;
    }
    std::string valid_space = " ";
    if (whole_str[0] == '('&& whole_str[2]==')' && whole_str.length() == 3 && (whole_str.find(valid_space)!=std::string::npos))
    {
        return false;
    }


    std::string test_string = whole_str.substr(1,whole_str.size()-2);


    if (isdigit (test_string[0]))
    {
        for (size_t n = 0; n < test_string.length(); n++)
        {
                if(isnumeric(test_string))
                   {
                    break;
                   }
            if (!isdigit( test_string[n] ))
            {

                return false;
            }
        }
    }

    if (test_string[0] == '@')
    {
        return true;
    }
    if (whole_str[0]=='('&& whole_str[1] == ')')
    {

        return false;
    }

    list a;
    std::list<std::string> b;
    b = tokenize(whole_str);


    a = build_ast(b);
    mylist = a;
    return !(b.size()!=0 && b.front()!="");
}



