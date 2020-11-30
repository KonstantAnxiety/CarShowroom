#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point
{
protected:
    double x, y;
public:
    static constexpr double MIN_COORDINATE_VALUE = -100.;
    static constexpr double MAX_COORDINATE_VALUE = 100.;
    Point();
    Point(double x, double y);
    Point(const Point &object);
    virtual ~Point() { /*std::cout << "~P()\n";*/ };
    bool setX(double x);
    bool setY(double y);
    double getX() const;
    double getY() const;
    double distance(const Point &other) const;
    virtual double area() const;
    virtual std::string objectType() const { return "Point"; };
    virtual bool equals(Point *other) const;
    virtual void fromString(const std::string &str);

    friend Point operator+(Point a, const Point &b) {
        return Point(a.getX()+b.getX(), a.getY()+b.getY());
    }

    Point& operator+=(const Point &b) {
        this->setX(this->getX() + b.getX());
        this->setY(this->getY() + b.getY());
        return *this;
    }

    Point& operator-=(const Point &b) {
        this->setX(this->getX() - b.getX());
        this->setY(this->getY() - b.getY());
        return *this;
    }

    Point& operator=(const Point &b) {
        this->setX(b.getX());
        this->setY(b.getY());
        return *this;
    }

    virtual void print(std::ostream& out) const {
        out << objectType() << " " << getX() << " " << getY() << "\n";
    }

    friend std::ostream& operator<<(std::ostream& out, const Point &p)
    {
        p.print(out);
        return out;
    }
};

#endif // POINT_H
