#ifndef PODIUM_H
#define PODIUM_H

#include <iostream>
#include "point.h"

class Podium: public Point
{
private:
    std::string brand;
    double radius;

public:
    static constexpr double MIN_DIMENSION_VALUE = 0.;
    static constexpr double MAX_DIMENSION_VALUE = 100.;
    Podium();
    Podium(double x, double y, double r, std::string brand);
    Podium(const Podium &object);
    virtual ~Podium() { /*std::cout << "~Podium()\n";*/ };
    bool setRadius(double rot);
    void setBrand(std::string brand);
    double getRadius() const;
    const std::string& getBrand() const;
    virtual double area() const;
    virtual std::string objectType() const { return "Podium"; };
    virtual bool equals(Point *other) const;
    virtual void fromString(const std::string &str);

    Podium& operator=(const Podium &object);
    friend bool operator==(const Podium &p1, const Podium &p2) {
        return (p1.getBrand() == p2.getBrand() &&
                p1.getRadius() == p2.getRadius() &&
                p1.getX() == p2.getX() &&
                p1.getY() == p2.getY());
    }

    virtual void print(std::ostream& out) const {
        out << objectType() << " " << getBrand() << " " << getX() << " "
            << getY() << " " << getRadius() << "\n";
    }

    friend std::ostream& operator<<(std::ostream& out, const Podium &p)
    {
        p.print(out);
        return out;
    }
};

#endif // PODIUM_H
