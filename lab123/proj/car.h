#ifndef CAR_H
#define CAR_H

#include <iostream>
#include "point.h"
#include <QGraphicsScene>

class Car: public Point
{
private:
    std::string brand;
    double width, length;
    double rotation;

public:
    static constexpr double MIN_DIMENSION_VALUE = 0.;
    static constexpr double MAX_DIMENSION_VALUE = 100.;
    Car();
    Car(double w, double len, double x, double y,
        double rot, std::string brand);
    Car(const Car &object);
    virtual ~Car() { /*std::cout << "~Car()\n";*/ };
    bool setWidth(double w);
    bool setLength(double len);
    void setRotation(double rot);
    void setBrand(std::string brand);
    double getWidth() const;
    double getLength() const;
    double getRotation() const;
    const std::string& getBrand() const;
    void getRectCoordinateas(Point *rect);
    virtual double area() const;
    virtual std::string objectType() const { return "Car"; };
    virtual bool equals(Point *other) const;
    void fromString(const std::string &str);
    const Car& copy() const;

    Car& operator=(const Car &object);
    friend bool operator==(const Car &c1, const Car &c2) {
        return (c1.getBrand() == c2.getBrand() &&
                c1.getLength() == c2.getLength() &&
                std::abs(c1.getRotation() - c2.getRotation()) < 10e-6 &&
                c1.getWidth() == c2.getWidth() &&
                c1.getX() == c2.getX() &&
                c1.getY() == c2.getY());
    }

    virtual void print(std::ostream& out) const {
        out << objectType() << " " << getBrand() << " " << getWidth() << " "
            << getLength() << " " << getX() << " " << getY() << " " << getRotation() << "\n";
    }

    friend std::ostream& operator<<(std::ostream& out, const Car &p)
    {
        p.print(out);
        return out;
    }
};

#endif // CAR_H
