#ifndef CARSHOWROOM_H
#define CARSHOWROOM_H

#include <memory>
#include "point.h"
#include "car.h"
#include "podium.h"
#include "vector.h"

class CarShowroom
{
private:
    double width, length;
public:
    Vector<std::shared_ptr<Point>> objects;
    CarShowroom();
    CarShowroom(const CarShowroom &other);
    CarShowroom(double width, double length, size_t n);
    double getWidth() const { return width; };
    double getLength() const { return length; };
    void setWidth(double w);
    void setLength(double len);
    long wallCarIntersections(bool verbose = 0) const;
    long wallPodiumIntersections(bool verbose = 0) const;
    long carIntersections(bool verbose = 0) const;
    long podiumIntersections(bool verbose = 0) const;
    long carPodiumAdequacy(bool verbose = 0) const;
    QString getWallCarIntersections(bool verbose = 0) const;
    QString getWallPodiumIntersections(bool verbose = 0) const;
    QString getCarIntersections(bool verbose = 0) const;
    QString getPodiumIntersections(bool verbose = 0) const;
    QString getCarPodiumAdequacy(bool verbose = 0) const;
    void fullReport() const;
    void writeToFile(const std::string &filename) const;
    bool readFromFile(const std::string &filename);

    friend bool operator==(const CarShowroom &c1, const CarShowroom &c2) {
        bool eq = (c1.width == c2.width &&
                   c1.length == c2.length &&
                   c1.objects.getSize() == c2.objects.getSize());
        size_t i = 0;
        while (i < c1.objects.getSize() && eq) {
            eq = eq && (c1.objects[i].get()->equals(c2.objects[i].get()));
            i++;
        }
        return eq;
    }
};

#endif // CARSHOWROOM_H
