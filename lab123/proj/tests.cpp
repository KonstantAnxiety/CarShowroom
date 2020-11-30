#ifndef TESTS_H
#define TESTS_H

#include <float.h>
#include <QRandomGenerator>
#include <QDateTime>
#include <QStringList>
#include "car.h"

double realNumber(double from = -DBL_MAX/2, double to = DBL_MAX/2) {
    return from + (to - from) * QRandomGenerator::global()->generateDouble();
}

int integer(int from = INT_MIN, int to = INT_MAX) {
    return QRandomGenerator::global()->bounded(from, to);
}

const std::string& itemFrom(const std::string list[], const int size) {
    return (list[QRandomGenerator::global()->bounded(0, size)]);
}

std::string carBrand() {
    static std::string carBrands[] = {"BMW", "Lamborghini", "Mercedes",
                                      "Acura", "Audi", "Chevrolet", "Datsun",
                                      "Honda", "Mazda", "Peugeot", "Seat"};
    return itemFrom(carBrands, sizeof(carBrands)/sizeof(carBrands[0]));
}

void assertValidity(const Car &object)
{
    assert(object.getWidth() > Car::MIN_DIMENSION_VALUE);
    assert(object.getWidth() <= Car::MAX_DIMENSION_VALUE);

    assert(object.getLength() > Car::MIN_DIMENSION_VALUE);
    assert(object.getLength() <= Car::MAX_DIMENSION_VALUE);

    assert(object.getX() >= Car::MIN_COORDINATE_VALUE);
    assert(object.getX() <= Car::MAX_COORDINATE_VALUE);

    assert(object.getY() >= Car::MIN_COORDINATE_VALUE);
    assert(object.getY() <= Car::MAX_COORDINATE_VALUE);
}

void assertEquality(const Car &first, const Car &second)
{
    assert(first.getWidth() == second.getWidth());
    assert(first.getLength() == second.getLength());
    assert(first.getX() == second.getX());
    assert(first.getY() == second.getY());
    assert(first.getRotation() == second.getRotation());
    assert(first.getBrand() == second.getBrand());
}

void assertDefault() {
    Car defaultObject;
    assertValidity(defaultObject);
    assert(defaultObject.getWidth() == 1);
    assert(defaultObject.getLength() == 1);
    assert(defaultObject.getX() == 0);
    assert(defaultObject.getY() == 0);
    assert(defaultObject.getBrand() == "UNKNOWN_BRAND");
}

void assertInitialization() {
    std::string brand = carBrand();
    double validDimension = realNumber((Car::MIN_DIMENSION_VALUE+
                                                Car::MAX_DIMENSION_VALUE)/2,
                                               Car::MAX_DIMENSION_VALUE);
    double validCoordinate = realNumber((Car::MIN_COORDINATE_VALUE+
                                                 Car::MAX_COORDINATE_VALUE)/2,
                                                Car::MAX_COORDINATE_VALUE);

    Car validCar(validDimension, validDimension, validCoordinate,
                 validCoordinate, validDimension, brand);
    assert(validCar.getWidth() == validDimension);
    assert(validCar.getLength() == validDimension);
    assert(validCar.getX() == validCoordinate);
    assert(validCar.getY() == validCoordinate);

    double errorDimension = realNumber(Car::MAX_DIMENSION_VALUE);
    double errorCoordinate = realNumber(Car::MAX_COORDINATE_VALUE);
    Car errorCar(errorDimension, errorDimension, errorCoordinate,
                  errorCoordinate, errorDimension, brand);
    assert(errorCar.getWidth() != errorDimension);
    assert(errorCar.getLength() != errorDimension);
    assert(errorCar.getX() != errorCoordinate);
    assert(errorCar.getY() != errorCoordinate);
}

void assertStability(Car &object)
{
    double value, error;

    value = realNumber(Car::MIN_DIMENSION_VALUE, Car::MAX_DIMENSION_VALUE);
    error = realNumber(Car::MAX_DIMENSION_VALUE);

    object.setWidth(value);
    assert(object.getWidth() == value);
    object.setWidth(error);
    assert(object.getWidth() != error);
    assert(object.getWidth() == value);

    object.setLength(value);
    assert(object.getLength() == value);
    object.setLength(error);
    assert(object.getLength() != error);
    assert(object.getLength() == value);

    value = realNumber(Car::MIN_COORDINATE_VALUE, Car::MAX_COORDINATE_VALUE);
    error = realNumber(Car::MAX_COORDINATE_VALUE);

    object.setX(value);
    assert(object.getX() == value);
    object.setX(error);
    assert(object.getX() != error);
    assert(object.getX() == value);

    object.setY(value);
    assert(object.getY() == value);
    object.setY(error);
    assert(object.getY() != error);
    assert(object.getY() == value);
}

#endif // TESTS_H
