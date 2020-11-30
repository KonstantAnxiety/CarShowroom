#include "car.h"
#include "cmath"
#include "vector.h"
#include "auxiliary.h"

Car::Car(): Point() {
    this->setWidth(1);
    this->setLength(1);
    this->setRotation(0);
    this->setBrand("UNKNOWN_BRAND");
}

Car::Car(double w, double len, double x, double y, double rot,
         std::string brand): Point(x, y) {
    if (!this->setWidth(w))
        this->width = 1;
    if (!this->setLength(len))
        this->length = 1;
    this->setRotation(rot);
    this->setBrand(brand);
}

Car::Car(const Car &object): Point(object) {
    this->setWidth(object.width);
    this->setLength(object.length);
    this->setRotation(object.rotation);
    this->setBrand(object.brand);
}

bool Car::setWidth(double w) {
    if (w > Car::MIN_DIMENSION_VALUE && w <= Car::MAX_DIMENSION_VALUE) {
        this->width = w;
        return true;
    }
    return false;
}

bool Car::setLength(double len) {
    if (len > Car::MIN_DIMENSION_VALUE && len <= Car::MAX_DIMENSION_VALUE) {
        this->length = len;
        return true;
    }
    return false;
}

void Car::setRotation(double rot) {
    this->rotation = rot;
}

void Car::setBrand(std::string brand) {
    this->brand = std::move(brand);
}

double Car::getWidth() const {
    return this->width;
}

double Car::getLength() const {
    return this->length;
}

double Car::getRotation() const {
    return this->rotation;
}

const std::string& Car::getBrand() const {
    return this->brand;
}

void Car::getRectCoordinateas(Point *rect)
{
    size_t i;
    for (i = 0; i < 4; ++i)
        rect[i] = Point(*this);

    double sine = sin(getRotation());
    double cosine = cos(getRotation());
    Point halfLengthVector(cosine * getLength() / 2.0,
                           sine * getLength() / 2.0);
    Point halfWidthVector(-sine * getWidth() / 2.0,
                          cosine * getWidth() / 2.0);

    rect[0] += halfLengthVector; rect[0] -= halfWidthVector;
    rect[1] += halfLengthVector; rect[1] += halfWidthVector;
    rect[2] -= halfLengthVector; rect[2] += halfWidthVector;
    rect[3] -= halfLengthVector; rect[3] -= halfWidthVector;
}

double Car::area() const
{
    return (width * length);
}

bool Car::equals(Point *other) const
{
    Car *car = dynamic_cast<Car*>(other);
    return (car && getBrand() == car->getBrand() &&
            getLength() == car->getLength() &&
            std::abs(getRotation() - car->getRotation()) < 10e-6 &&
            getWidth() == car->getWidth() &&
            getX() == car->getX() &&
            getY() == car->getY());
}

void Car::fromString(const std::string &str)
{
    size_t attrAmount = 6;
    size_t i = 0; // char index in str
    size_t j = 0; // attribute index in attrs
    std::string attrs[attrAmount]; // attribute are read here
    for (std::string s : attrs)
        s = "";
    skipSpaces(str, &i);
    while (i < str.size() && str[i] && str[i] != ' ') // skip "Car"
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
    setWidth(std::atof(attrs[1].c_str()));
    setLength(std::atof(attrs[2].c_str()));
    setX(std::atof(attrs[3].c_str()));
    setY(std::atof(attrs[4].c_str()));
    setRotation(std::atof(attrs[5].c_str()));
}

Car &Car::operator=(const Car &object)
{
    this->setWidth(object.getWidth());
    this->setLength(object.getLength());
    this->setX(object.getX());
    this->setY(object.getY());
    this->setRotation(object.getRotation());
    this->setBrand(object.getBrand());
    return *this;
}
