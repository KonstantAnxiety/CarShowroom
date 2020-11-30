#include <CarArray.h>
#include <auxiliary.cpp>

CarArray::CarArray()
{
    cars = Vector<Car>();
}

CarArray::CarArray(size_t n)
{
    if (n == 0)
        cars = Vector<Car>();
    cars = Vector<Car>(n);
}

CarArray::CarArray(const CarArray &object)
{
    cars.clear();
    for (size_t i = 0; i < object.getSize(); ++i)
        cars.push_back(object.cars.at(i));
}

void CarArray::push_back(const Car &object)
{
    cars.push_back(object);
}

void CarArray::pop_back()
{
    this->cars.pop_back();
}

void CarArray::clear()
{
    cars.clear();
}

const Car &CarArray::at(size_t pos) const
{
    return cars.at(pos);
}

void CarArray::set(size_t pos, const Car &object)
{
    cars.set(pos, object);
}

void CarArray::del(size_t pos)
{
    cars.del(pos);
}

void CarArray::insert(size_t pos, const Car &object)
{
    cars.insert(pos, object);
}

bool CarArray::empty() const
{
    return (cars.empty());
}

size_t CarArray::getSize() const
{
    return cars.getSize();
}

size_t CarArray::getCapacity() const
{
    return cars.getCapacity();
}

const Car &CarArray::operator[](size_t i) const
{
    return cars.at(i);
}

long CarArray::intersections(bool verbose) const
{
    if (verbose)
        std::cout << "Car intersections:\n";
    long intersectionCount = 0;
    bool intersection;
    size_t i, j, p1, p2, k;
    for (i = 0; i < cars.getSize()-1; ++i) {
        for (j = i+1; j < cars.getSize(); ++j) {
            Point iRect[4]; getRectCoordinates(cars[i], iRect);
            Point jRect[4]; getRectCoordinates(cars[j], jRect);
            Point vectors[4];
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
                if (abs(angle - 2*M_PI) < 10e-6)
                    intersection = true;
                p1++;
            }
            if (intersection) {
                intersectionCount++;
                if (verbose)
                    std::cout << "Cars " << i <<
                                 " and " << j << " intersect.\n";
            }
        }
    }
    if (verbose)
        std::cout << "---Total: " << intersectionCount << "\n";
    return intersectionCount;
}

void CarArray::writeToFile(const std::string &filename) const
{
    std::ofstream fout;
    fout.open(filename);
    fout << cars;
}

bool CarArray::readFromFile(const std::string &filename)
{
    std::ifstream fin(filename);
    if (!fin) {
        std::cout << "Can't open file: " << filename << '\n';
        return false;
    }

    cars.clear();
    Car inputCar;
    std::string tmp = "";
    std::string input;
    if (!fin.eof())
        std::getline(fin, input);
    while (!fin.eof()) {
        size_t i = 0;
        readToSpace(i, input, tmp);
        inputCar.setBrand(tmp);
        readToSpace(i, input, tmp);
        inputCar.setWidth(std::atof(tmp.c_str()));
        readToSpace(i, input, tmp);
        inputCar.setLength(std::atof(tmp.c_str()));
        readToSpace(i, input, tmp);
        inputCar.setX(std::atof(tmp.c_str()));
        readToSpace(i, input, tmp);
        inputCar.setY(std::atof(tmp.c_str()));
        readToSpace(i, input, tmp);
        inputCar.setRotation(std::atof(tmp.c_str()));
        cars.push_back(inputCar);
        std::getline(fin, input);
    }
    return true;
}
