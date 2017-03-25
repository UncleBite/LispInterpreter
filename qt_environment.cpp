#include "qt_environment.hpp"

QtEnvironment::QtEnvironment()
{
    std::map<std::string, Expression> point_map;
    std::map<std::string, Expression> line_map;
    std::map<std::string, Expression> arc_map;
}


bool QtEnvironment::contains(std::map<std::string, Expression> map, std::string name)
{
    return !(map.find(name) == map.end());
}

bool QtEnvironment::point_allow(std::string str)
{
    return point_map.find(str) == point_map.end();
}

bool QtEnvironment::line_allow(std::string str)
{
    return line_map.find(str) == line_map.end();
}

bool QtEnvironment::arc_allow(std::string str)
{
    return arc_map.find(str) == arc_map.end();
}
void QtEnvironment::add_point_map(std::string str, Expression point)
{
    if (point_allow(str))
    {
        point_map.insert({str, point});
    }
    else
    {
        throw InterpreterSemanticError("Error: already defined");
    }

    return;
}
void QtEnvironment::add_line_map(std::string str, Expression line)
{
    if (line_allow(str))
    {
        line_map.insert({str, line});
    }
    else
    {
        throw InterpreterSemanticError("Error: already defined");
    }
    return;
}
void QtEnvironment::add_arc_map(std::string str, Expression arc)
{
    if (arc_allow(str))
    {
        arc_map.insert({str, arc});
    }
    else
    {
        throw InterpreterSemanticError("Error: already defined");
    }
    return;
}

Expression QtEnvironment::return_point(std::string str)
{
    if (point_map.find(str) == point_map.end())
    return Expression();
    it_point = point_map.find(str);
    return it_point->second;
}

Expression QtEnvironment::return_line(std::string str)
{
    if (line_map.find(str) == line_map.end())
    return Expression();
    it_line = line_map.find(str);
    return it_line->second;
}

Expression QtEnvironment::return_arc(std::string str)
{
    if (arc_map.find(str) == arc_map.end())
    return Expression();
    it_arc = arc_map.find(str);
    return it_arc->second;
}
