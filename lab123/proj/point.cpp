#include "point.h"
#include "auxiliary.h"
#include <cmath>

Point::Point() {
    x = 0;
    y = 0;
}

Point::Point(double x, double y)
{
    if (!this->setX(x))
        this->x = 0;
    if (!this->setY(y))
        this->y = 0;
}

Point::Point(const Point &object)
{
    setX(object.x);
    setY(object.y);
}

double Point::getX() const {
    return this->x;
}

double Point::getY() const {
    return this->y;
}

double Point::distance(const Point &other) const
{
    return sqrt(pow(this->getX() - other.getX(), 2)
                + pow(this->getY() - other.getY(), 2));
}

double Point::area() const
{
    return 0;
}

bool Point::equals(Point *other) const
{
    return (getX() == other->getX() && getY() == other->getY());
}

void Point::fromString(const std::string &str)
{
    size_t attrAmount = 2;
    size_t i = 0; // char index in str
    size_t j = 0; // attribute index in attrs
    std::string attrs[attrAmount]; // attribute are read here
    for (std::string s : attrs)
        s = "";
    skipSpaces(str, &i);
    while (i < str.size() && str[i] && str[i] != ' ') // skip "Point"
        i++;
    skipSpaces(str, &i);
    while (i < str.size() && str[i] && str[i] != ' ') // read brand
        attrs[j] += str[i++];
    skipSpaces(str, &i);
    j++;
    while (i < str.size() && str[i] && j < attrAmount) { // read remaining attributes
        while (str[i] != ' ') // read attribute
            attrs[j] += str[i++];
        skipSpaces(str, &i);
        j++;
    }
    setX(std::atof(attrs[0].c_str()));
    setY(std::atof(attrs[1].c_str()));
}

bool Point::setX(double x) {
    if (x >= Point::MIN_COORDINATE_VALUE && x <= Point::MAX_COORDINATE_VALUE) {
        this->x = x;
        return true;
    }
    return false;
}

bool Point::setY(double y) {
    if (y >= Point::MIN_COORDINATE_VALUE && y <= Point::MAX_COORDINATE_VALUE) {
        this->y = y;
        return true;
    }
    return false;
}
