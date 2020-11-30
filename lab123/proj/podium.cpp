#include "podium.h"
#include "auxiliary.h"
#include <cmath>

Podium::Podium(): Point() {
    //std::cout << "Default constructor\n";
    this->setRadius(1);
    this->setBrand("UNKNOWN_BRAND");
}

Podium::Podium(double x, double y, double r, std::string brand): Point(x, y) {
    //std::cout << "Parametrized constructor\n";
    if (!this->setRadius(r))
        this->radius = 1;
    this->setBrand(brand);
}

Podium::Podium(const Podium &object): Point(object) {
    //std::cout << "Copy constructor\n";
    this->setRadius(object.radius);
    this->setBrand(object.brand);
}

bool Podium::setRadius(double len) {
    if (len > Podium::MIN_DIMENSION_VALUE && len <= Podium::MAX_DIMENSION_VALUE) {
        this->radius = len;
        return true;
    }
    return false;
}

void Podium::setBrand(std::string brand) {
    this->brand = std::move(brand);
}

double Podium::getRadius() const {
    return this->radius;
}

const std::string& Podium::getBrand() const {
    return this->brand;
}

double Podium::area() const
{
    return (M_PI * pow(getRadius(), 2));
}

bool Podium::equals(Point *other) const
{
    Podium *podium = dynamic_cast<Podium*>(other);
    return (podium && getBrand() == podium->getBrand() &&
            getRadius() == podium->getRadius() &&
            getX() == podium->getX() &&
            getY() == podium->getY());
}

void Podium::fromString(const std::string &str)
{
    size_t attrAmount = 4;
    size_t i = 0; // char index in str
    size_t j = 0; // attribute index in attrs
    std::string attrs[attrAmount]; // attribute are read here
    for (std::string s : attrs)
        s = "";
    skipSpaces(str, &i);
    while (i < str.size() && str[i] && str[i] != ' ') // skip "Podium"
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
    setBrand(attrs[0]);
    setX(std::atof(attrs[1].c_str()));
    setY(std::atof(attrs[2].c_str()));
    setRadius(std::atof(attrs[3].c_str()));
}

Podium &Podium::operator=(const Podium &object)
{
    this->setX(object.x);
    this->setY(object.y);
    this->setRadius(object.radius);
    this->setBrand(object.brand);
    return *this;
}
