#ifndef AUXILIARY_H
#define AUXILIARY_H

#include <iostream>
#include "point.h"
#include "car.h"
#include "carshowroom.h"

void printCarShowroom(const CarShowroom &object);

void skipSpaces(const std::string &str, size_t *i);

double distance(const Point &v, const Point &w);

double angleBetweenTwoVectors(const Point &v, const Point &w);

double vectorLength(const Point &v);

double scalarProduct(const Point &v, const Point &w);

void getRectCoordinates(const Car &c, Point *rect);

bool segmentIntersection(const Point &a1, const Point &a2,
                         const Point &b1, const Point &b2);

bool rectSegmentIntersection(Point *r1, Point *r2);

#endif // AUXILIARY_H
