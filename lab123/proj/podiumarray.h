#pragma once
#ifndef PODIUMARRAY_H
#define PODIUMARRAY_H

#include <vector.h>
#include <podium.h>

class PodiumArray
{
private:
    Vector<Podium> podiums;
public:
    PodiumArray();
    PodiumArray(size_t n);
    PodiumArray(const PodiumArray &object);
    ~PodiumArray() = default;
    long intersections(bool verbose = 0) const;
    void push_back(const Podium &object);
    void pop_back();
    void clear();
    const Podium& at(size_t pos) const;
    void set(size_t pos, const Podium &object);
    void del(size_t pos);
    void insert(size_t pos, const Podium &object);
    bool empty() const;
    size_t getSize() const;
    size_t getCapacity() const;
    void writeToFile(const std::string &filename) const;
    bool readFromFile(const std::string &filename);

    const Podium &operator[](size_t i) const;
    friend bool operator==(const PodiumArray &p1, const PodiumArray &p2) {
        if (p1.getSize() != p2.getSize())
            return false;
        size_t cnt;
        if (p1.getSize() > p2.getSize())
            cnt = p2.getSize();
        else
            cnt = p1.getSize();
        bool equal = 1;
        while (equal && cnt > 0) {
            cnt--;
            equal = (equal && (p1.at(cnt) == p2.at(cnt)));
        }
        return equal;
    }

    friend std::ostream& operator<<(std::ostream& out, const PodiumArray &object)
    {
        for (size_t i = 0; i < object.getSize(); ++i)
            out << object.at(i);
        return out;
    }
};

#endif // PODIUMARRAY_H
