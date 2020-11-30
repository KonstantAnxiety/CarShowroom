#ifndef TESTS_H
#define TESTS_H

#include <float.h>
#include <QRandomGenerator>
#include <QDateTime>
#include <QStringList>
#include "car.h"

double realNumber(double from = -DBL_MAX/2, double to = DBL_MAX/2);

int integer(int from = INT_MIN, int to = INT_MAX);

const std::string& itemFrom(const std::string list[], const int size);

std::string carBrand();

void assertValidity(const Car &object);

void assertEquality(const Car &first, const Car &second);

void assertDefault();

void assertInitialization();

void assertStability(Car &object);

#endif // TESTS_H
