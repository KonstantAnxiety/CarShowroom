#include <iostream>
#include "auxiliary.h"
#include "math.h"
#include "carshowroom.h"

void printCarShowroom(const CarShowroom &object)
{
    for (size_t i = 0; i < object.objects.getSize(); ++i) {
        std::cout << i << ". " << *(object.objects[i]);
    }
}

void skipSpaces(const std::string &str, size_t *i) {
    while (*i < str.size() && str[*i] && str[*i] == ' ') // skip spaces
        (*i)++;
}

double distance(const Point &v, const Point &w)
{
    return sqrt(pow(w.getX() - v.getX(), 2)
                + pow(w.getY() - v.getY(), 2));
}

double vectorLength(const Point &v)
{
    return sqrt(v.getX()*v.getX() + v.getY()*v.getY());
}

double scalarProduct(const Point &v, const Point &w)
{
    return v.getX()*w.getX() + v.getY()*w.getY();
}

double angleBetweenTwoVectors(const Point &v, const Point &w)
{
    return acos(scalarProduct(v, w) / (vectorLength(v) * vectorLength(w)));
}

void getRectCoordinates(const Car &c, Point *rect)
{
    size_t i;
    for (i = 0; i < 4; ++i)
        rect[i] = c;

    double sine = sin(c.getRotation());
    double cosine = cos(c.getRotation());
    Point halfLengthVector(cosine * c.getLength() / 2.0,
                           sine * c.getLength() / 2.0);
    Point halfWidthVector(-sine * c.getWidth() / 2.0,
                          cosine * c.getWidth() / 2.0);

    rect[0] += halfLengthVector; rect[0] -= halfWidthVector;
    rect[1] += halfLengthVector; rect[1] += halfWidthVector;
    rect[2] -= halfLengthVector; rect[2] += halfWidthVector;
    rect[3] -= halfLengthVector; rect[3] -= halfWidthVector;
}

bool segmentIntersection(const Point &a, const Point &b,
                         const Point &c, const Point &d)
{
    // segments AB and CD
    double xa = a.getX(), ya = a.getY(),
           xb = b.getX(), yb = b.getY(),
           xc = c.getX(), yc = c.getY(),
           xd = d.getX(), yd = d.getY(),
           maindet, det1, det2, s = -1, t = -1;
    maindet = (xb-xa)*(-yd+yc) - (yb-ya)*(-xd+xc);
    det1 = (xb-xa)*(yc-ya) - (yb-ya)*(xc-xa);
    det2 = (-yd+yc)*(xc-xa) - (-xd+xc)*(yc-ya);
    if (maindet != 0) {
        t = det1 / maindet;
        s = det2 / maindet;
    }
    if ((t >= 0 && t <= 1) && (s >= 0 && s <= 1))
        return true;
    return false;
}

bool rectSegmentIntersection(Point *r1, Point *r2)
{
    size_t i = 0, j = 0;
    bool intersection = false;
    while (i < 4 && !intersection) {
        j = 0;
        while (j < 4 && !intersection) {
            intersection = segmentIntersection(r1[i], r1[(i+1)%4],
                                               r2[j], r2[(j+1)%4]);
            j++;
        }
        i++;
    }
    return intersection;
}
