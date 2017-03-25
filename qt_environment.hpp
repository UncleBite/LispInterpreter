#ifndef QT_ENVIRONMENT_HPP
#define QT_ENVIRONMENT_HPP

#include "environment.hpp"
class QtEnvironment : public Environment
{
public:
    QtEnvironment();
    bool contains(std::map<std::string, Expression> map, std::string str);

    bool point_allow(std::string str);
    bool line_allow(std::string str);
    bool arc_allow(std::string str);
    void add_point_map(std::string str, Expression point);
    void add_line_map(std::string str, Expression line);
    void add_arc_map(std::string str, Expression arc);
    Expression return_point(std::string str);
    Expression return_line(std::string str);
    Expression return_arc(std::string str);

    std::map<std::string, Expression> point_map;
    std::map<std::string, Expression> line_map;
    std::map<std::string, Expression> arc_map;
    std::map<std::string, Expression>::iterator it_point = point_map.begin();
    std::map<std::string, Expression>::iterator it_line = line_map.begin();
    std::map<std::string, Expression>::iterator it_arc = arc_map.begin();

};

#endif // QT_ENVIRONMENT_HPP
