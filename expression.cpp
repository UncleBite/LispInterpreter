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
    if (value == DEFINE || value == BEGIN|| value == IF ||
            value == POINT || value == LINE || value == ARC || value == DRAW)
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

// Construct an Expression with a single Point atom with value
Expression::Expression(std::tuple<double,double> value)
{
    val.type = Point;
    val.point_value = value;
}

// Construct an Expression with a single Line atom withstarting
// point start and ending point end
Expression::Expression(std::tuple<double,double> start, std::tuple<double,double> end)
{
    val.type = Line;
    val.point_value = start;
    val.line_value = end;
}

// Construct an Expression with a single Arc atom with center
// point center, starting point start, and spanning angle angle in radians
Expression::Expression(std::tuple<double,double> center, std::tuple<double,double> start, double angle)
{
    val.type = Arc;
    val.point_value = center;
    val.line_value = start;
    val.num_value = angle;
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

bool Expression::isType(atom_type type)
{
    return val.type == type;
}


bool Expression::isGraphical()
{
    return val.type == Point || val.type == Line || val.type == Arc;
}


bool Expression::isOperator()
{
    auto token = val.string_value;
    return this->isType(Symbol) && (
        token == "+" || token == "-"||token == "*"||token == "/"||token == "not"||
        token == "and"||token == "or"||token == "<"||token == "<="||token == ">"||
        token == ">="||token == "="||token == "+"
    );
}

bool Expression::isIdentifier()
{
    return this->isType(Symbol) && !this->isOperator();
}
