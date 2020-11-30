#include "carshowroom.h"
#include "auxiliary.h"
#include <cmath>

CarShowroom::CarShowroom()
{
    width = 100;
    length = 100;
}

CarShowroom::CarShowroom(const CarShowroom &other)
{
    objects.clear();
    width = other.getWidth();
    length = other.getLength();
    for (size_t i = 0; i < other.objects.getSize(); ++i)
        objects.push_back(other.objects.at(i));
}

CarShowroom::CarShowroom(double w, double len, size_t n)
{
    width = w;
    length = len;
    objects = Vector<std::shared_ptr<Point>>(n);
}

void CarShowroom::setWidth(double w)
{
    if (w == 0)
        w = 50;
    width = std::abs(w);
}

void CarShowroom::setLength(double len)
{
    if (len == 0)
        len = 50;
    length = std::abs(len);
}

void CarShowroom::fullReport() const
{
    carIntersections(1);
    podiumIntersections(1);
    wallCarIntersections(1);
    wallPodiumIntersections(1);
    carPodiumAdequacy(1);
}

void CarShowroom::writeToFile(const std::string &filename) const
{
    std::ofstream fout;
    fout.open(filename);
    for (size_t i = 0; i < objects.getSize(); ++i) {
        objects[i]->print(fout);
    }
    fout.close();
}

bool CarShowroom::readFromFile(const std::string &filename)
{
    std::ifstream fin(filename);
    if (!fin) {
        std::cout << "Can't open file: " << filename << '\n';
        fin.close();
        return false;
    }

    objects.clear();
    std::string objectType;
    std::string input;
    size_t i; // char id in input when reading objectType
    while (!fin.eof()) {
        std::getline(fin, input);
        if (!input[0])
            break;
        i = 0;
        objectType = "";
        skipSpaces(input, &i);
        while (input[i] != ' ') // read attribute
            objectType += input[i++];
        Point *newObject;
        if (objectType == "Car")
            newObject = new Car;
        else if (objectType == "Podium")
            newObject = new Podium;
        else
            newObject = new Point;
        newObject->fromString(input);
        objects.push_back(std::shared_ptr<Point>(newObject));
    }
    fin.close();
    return true;
}

long CarShowroom::wallCarIntersections(bool verbose) const
{
    if (verbose)
        std::cout << "Wall-car intersections:\n";
    long intersectionCount = 0;
    size_t i, p;
    Point rect[4];
    for (i = 0; i < objects.getSize(); ++i) {
        Car *car = dynamic_cast<Car*>(objects[i].get());
        if (!car)
            continue;
        getRectCoordinates(*car, rect);
        p = 0;
        while (p < 4 && rect[p].getX() >= 0 && rect[p].getY() >= 0 &&
               rect[p].getX() <= length && rect[p].getY() <= width)
            p++;
        if (p < 4) {
            intersectionCount++;
            if (verbose)
                std::cout << "--Car " << i << " intersects a wall or is outside.\n";
        }
    }
    if (verbose)
        std::cout << "----Total: " << intersectionCount << "\n";
    return intersectionCount;
}

long CarShowroom::wallPodiumIntersections(bool verbose) const
{
    if (verbose)
        std::cout << "Wall-podium intersections:\n";
    long intersectionCount = 0;
    size_t i;
    for (i = 0; i < objects.getSize(); ++i) {
        Podium *podium = dynamic_cast<Podium*>(objects[i].get());
        if (!podium)
            continue;
        double cr = podium->getRadius(),
               cx = podium->getX(),
               cy = podium->getY();
        if (cx < cr || cy < cr || cx > (length-cr) || cy > (width-cr)) {
            intersectionCount++;
            if (verbose)
                std::cout << "--Podium " << i << " intersects a wall or is outside.\n";
        }
    }
    if (verbose)
        std::cout << "----Total: " << intersectionCount << "\n";
    return intersectionCount;
}

long CarShowroom::carIntersections(bool verbose) const
{
    if (verbose)
        std::cout << "Car intersections:\n";
    long intersectionCount = 0;
    bool intersection;
    size_t i, j, p1, p2, k;
    Point iRect[4];
    Point jRect[4];
    Point vectors[4];
    for (i = 0; i < objects.getSize()-1 && !objects.empty(); ++i) {
        Car *car1 = dynamic_cast<Car*>(objects[i].get());
        if (!car1)
            continue;
        for (j = i+1; j < objects.getSize(); ++j) {
            Car *car2 = dynamic_cast<Car*>(objects[j].get());
            if (!car2)
                continue;
            getRectCoordinates(*car1, iRect);
            getRectCoordinates(*car2, jRect);
            intersection = false;
            if (rectSegmentIntersection(iRect, jRect)) // intersecting segments
                intersection = true;
            double angle = 0;
            p1 = 0;
            while (p1 < 4 && !intersection) { // one inside the other
                for (k = 0; k < 4; ++k)
                    vectors[k] = Point(jRect[k]);
                for (p2 = 0; p2 < 4; ++p2)
                    vectors[p2] -= iRect[p1];
                angle = angleBetweenTwoVectors(vectors[0], vectors[1]) +
                        angleBetweenTwoVectors(vectors[1], vectors[2]) +
                        angleBetweenTwoVectors(vectors[2], vectors[3]) +
                        angleBetweenTwoVectors(vectors[3], vectors[0]);
                if (std::abs(angle - 2*M_PI) < 10e-6)
                    intersection = true;
                p1++;
            }
            if (intersection) {
                intersectionCount++;
                if (verbose)
                    std::cout << "--Cars " << i <<
                                 " and " << j << " intersect.\n";
            }
        }
    }
    if (verbose)
        std::cout << "----Total: " << intersectionCount << "\n";
    return intersectionCount;
}

long CarShowroom::podiumIntersections(bool verbose) const
{
    if (verbose)
        std::cout << "Podium intersections:\n";
    long intersectionCount = 0;
    size_t i, j;
    for (i = 0; i < objects.getSize()-1 && !objects.empty(); ++i) {
        Podium *podium1 = dynamic_cast<Podium*>(objects[i].get());
        if (!podium1)
            continue;
        for (j = i+1; j < objects.getSize(); ++j) {
            Podium *podium2 = dynamic_cast<Podium*>(objects[j].get());
            if (!podium2)
                continue;
            if (distance(*podium1, *podium2) <
                    podium1->getRadius() + podium2->getRadius()) {
                intersectionCount++;
                if (verbose)
                    std::cout << "--Podiums " << i << " and " <<
                                 j << " intersect.\n";
            }
        }
    }
    if (verbose)
        std::cout << "----Total: " << intersectionCount << "\n";
    return intersectionCount;
}

long CarShowroom::carPodiumAdequacy(bool verbose) const
{
    if (verbose)
        std::cout << "Car-podium adequacy:\n";
    size_t i, j, p, pointsInCircle, mismatches = 0;
    Point iRect[4];
    for (i = 0; i < objects.getSize(); ++i) {
        Car *car = dynamic_cast<Car*>(objects[i].get());
        if (!car)
            continue;
        getRectCoordinates(*car, iRect);
        for (j = 0; j < objects.getSize(); ++j) {
            Podium *podium = dynamic_cast<Podium*>(objects[j].get());
            if (!podium)
                continue;
            pointsInCircle = 0;
            p = 0;
            while (p < 4) {// for each point of a rectangle check if it is in a circle
                pointsInCircle += (distance(*podium, iRect[p++]) <=
                        podium->getRadius());
            }
            if (pointsInCircle > 0 && pointsInCircle < 4) {
                mismatches++;
                if (verbose)
                    std::cout << "--Car " << i <<
                                 " intersects podium " << j << "\n";
            } else if (pointsInCircle == 4) {
                if (car->getBrand() != podium->getBrand()) {
                    mismatches++;
                    if (verbose)
                        std::cout << "--Car " << i <<
                                     " mismathes podium " << j << "\n";
                }
            }
        }
    }
    if (verbose)
        std::cout << "----Total: " << mismatches << "\n";
    return mismatches;
}

// -----------------------------------------------------------------------------

QString CarShowroom::getWallCarIntersections(bool verbose) const
{
    QString ret;
    if (verbose)
        ret.append("Wall-car intersections:\n");
    long intersectionCount = 0;
    size_t i, p;
    Point rect[4];
    for (i = 0; i < objects.getSize(); ++i) {
        Car *car = dynamic_cast<Car*>(objects[i].get());
        if (!car)
            continue;
        getRectCoordinates(*car, rect);
        p = 0;
        while (p < 4 && rect[p].getX() >= 0 && rect[p].getY() >= 0 &&
               rect[p].getX() <= length && rect[p].getY() <= width)
            p++;
        if (p < 4) {
            intersectionCount++;
            if (verbose) {
                ret.append("--Car ");
                ret.append(QString::number(i));
                ret.append(" intersects a wall or is outside.\n");
            }
        }
    }
    if (verbose) {
        ret.append("----Total: ");
        ret.append(QString::number(intersectionCount));
        ret.append("\n");
    }
    return ret;
}

QString CarShowroom::getWallPodiumIntersections(bool verbose) const
{
    QString ret;
    if (verbose)
        ret.append("Wall-podium intersections:\n");
    long intersectionCount = 0;
    size_t i;
    for (i = 0; i < objects.getSize(); ++i) {
        Podium *podium = dynamic_cast<Podium*>(objects[i].get());
        if (!podium)
            continue;
        double cr = podium->getRadius(),
               cx = podium->getX(),
               cy = podium->getY();
        if (cx < cr || cy < cr || cx > (length-cr) || cy > (width-cr)) {
            intersectionCount++;
            if (verbose) {
                ret.append("--Podium ");
                ret.append(QString::number(i));
                ret.append(" intersects a wall or is outside.\n");
            }
        }
    }
    if (verbose) {
        ret.append("----Total: ");
        ret.append(QString::number(intersectionCount));
        ret.append("\n");
    }
    return ret;
}

QString CarShowroom::getCarIntersections(bool verbose) const
{
    QString ret;
    if (verbose)
        ret.append("Car intersections:\n");
    long intersectionCount = 0;
    bool intersection;
    size_t i, j, p1, p2, k;
    Point iRect[4];
    Point jRect[4];
    Point vectors[4];
    for (i = 0; i < objects.getSize()-1 && !objects.empty(); ++i) {
        Car *car1 = dynamic_cast<Car*>(objects[i].get());
        if (!car1)
            continue;
        for (j = i+1; j < objects.getSize(); ++j) {
            Car *car2 = dynamic_cast<Car*>(objects[j].get());
            if (!car2)
                continue;
            getRectCoordinates(*car1, iRect);
            getRectCoordinates(*car2, jRect);
            intersection = false;
            if (rectSegmentIntersection(iRect, jRect)) // intersecting segments
                intersection = true;
            double angle = 0;
            p1 = 0;
            while (p1 < 4 && !intersection) { // one inside the other
                for (k = 0; k < 4; ++k)
                    vectors[k] = Point(jRect[k]);
                for (p2 = 0; p2 < 4; ++p2)
                    vectors[p2] -= iRect[p1];
                angle = angleBetweenTwoVectors(vectors[0], vectors[1]) +
                        angleBetweenTwoVectors(vectors[1], vectors[2]) +
                        angleBetweenTwoVectors(vectors[2], vectors[3]) +
                        angleBetweenTwoVectors(vectors[3], vectors[0]);
                if (std::abs(angle - 2*M_PI) < 10e-6)
                    intersection = true;
                p1++;
            }
            if (intersection) {
                intersectionCount++;
                if (verbose) {
                    ret.append("--Cars ");
                    ret.append(QString::number(i));
                    ret.append(" and ");
                    ret.append(QString::number(j));
                    ret.append(" intersect.\n");
                }
            }
        }
    }
    if (verbose) {
        ret.append("----Total: ");
        ret.append(QString::number(intersectionCount));
        ret.append("\n");
    }
    return ret;
}

QString CarShowroom::getPodiumIntersections(bool verbose) const
{
    QString ret;
    if (verbose)
        ret.append("Podium intersections:\n");
    long intersectionCount = 0;
    size_t i, j;
    for (i = 0; i < objects.getSize()-1 && !objects.empty(); ++i) {
        Podium *podium1 = dynamic_cast<Podium*>(objects[i].get());
        if (!podium1)
            continue;
        for (j = i+1; j < objects.getSize(); ++j) {
            Podium *podium2 = dynamic_cast<Podium*>(objects[j].get());
            if (!podium2)
                continue;
            if (distance(*podium1, *podium2) <
                    podium1->getRadius() + podium2->getRadius()) {
                intersectionCount++;
                if (verbose){
                    ret.append("--Podiums ");
                    ret.append(QString::number(i));
                    ret.append(" and ");
                    ret.append(QString::number(j));
                    ret.append(" intersect.\n");
                }
            }
        }
    }
    if (verbose) {
        ret.append("----Total: ");
        ret.append(QString::number(intersectionCount));
        ret.append("\n");
    }
    return ret;
}

QString CarShowroom::getCarPodiumAdequacy(bool verbose) const
{
    QString ret;
    if (verbose)
        ret.append("Car-podium adequacy:\n");
    size_t i, j, p, pointsInCircle, mismatches = 0;
    Point iRect[4];
    for (i = 0; i < objects.getSize(); ++i) {
        Car *car = dynamic_cast<Car*>(objects[i].get());
        if (!car)
            continue;
        getRectCoordinates(*car, iRect);
        for (j = 0; j < objects.getSize(); ++j) {
            Podium *podium = dynamic_cast<Podium*>(objects[j].get());
            if (!podium)
                continue;
            pointsInCircle = 0;
            p = 0;
            while (p < 4) {// for each point of a rectangle check if it is in a circle
                pointsInCircle += (distance(*podium, iRect[p++]) <=
                        podium->getRadius());
            }
            if (pointsInCircle > 0 && pointsInCircle < 4) {
                mismatches++;
                if (verbose) {
                    ret.append("--Car ");
                    ret.append(QString::number(i));
                    ret.append(" intersects podium ");
                    ret.append(QString::number(j));
                    ret.append("\n");
                }
            } else if (pointsInCircle == 4) {
                if (car->getBrand() != podium->getBrand()) {
                    mismatches++;
                    if (verbose) {
                        ret.append("--Car ");
                        ret.append(QString::number(i));
                        ret.append(" mismathes podium ");
                        ret.append(QString::number(j));
                        ret.append("\n");
                    }
                }
            }
        }
    }
    if (verbose) {
        ret.append("----Total: ");
        ret.append(QString::number(mismatches));
        ret.append("\n");
    }
    return ret;
}
