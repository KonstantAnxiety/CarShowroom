#pragma once
#ifndef CARARRAY_H
#define CARARRAY_H

#include <vector.h>
#include <car.h>

class CarArray
{
private:
    Vector<Car> cars;
public:
    CarArray();
    CarArray(size_t n);
    CarArray(const CarArray &object);
    ~CarArray() = default;
    long intersections(bool verbose = 0) const;
    void push_back(const Car &object);
    void pop_back();
    void clear();
    const Car& at(size_t pos) const;
    void set(size_t pos, const Car &object);
    void del(size_t pos);
    void insert(size_t pos, const Car &object);
    bool empty() const;
    size_t getSize() const;
    size_t getCapacity() const;
    void writeToFile(const std::string &filename) const;
    bool readFromFile(const std::string &filename);

    const Car &operator[](size_t i) const;
    friend bool operator==(const CarArray &c1, const CarArray &c2) {
        if (c1.getSize() != c2.getSize())
            return false;
        size_t cnt;
        if (c1.getSize() > c2.getSize())
            cnt = c2.getSize();
        else
            cnt = c1.getSize();
        bool equal = 1;
        while (equal && cnt > 0) {
            cnt--;
            equal = (equal && (c1.at(cnt) == c2.at(cnt)));
        }
        return equal;
    }
    friend std::ostream& operator<<(std::ostream& out, const CarArray &object)
    {
        for (size_t i = 0; i < object.getSize(); ++i)
            out << object.at(i);
        return out;
    }
};

#endif // CARARRAY_H
