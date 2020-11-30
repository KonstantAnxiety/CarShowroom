#include "podiumarray.h"
#include <auxiliary.h>

PodiumArray::PodiumArray()
{
    podiums = Vector<Podium>();
}

PodiumArray::PodiumArray(size_t n)
{
    if (n == 0)
        podiums = Vector<Podium>();
    podiums = Vector<Podium>(n);
}

PodiumArray::PodiumArray(const PodiumArray &object)
{
    podiums.clear();
    for (size_t i = 0; i < object.getSize(); ++i)
        podiums.push_back(object.podiums.at(i));
}

long PodiumArray::intersections(bool verbose) const
{
    if (verbose)
        std::cout << "Podium intersections:\n";
    long intersectionCount = 0;
    size_t i, j;
    for (i = 0; i < podiums.getSize()-1; ++i) {
        for (j = i+1; j < podiums.getSize(); ++j) {
            if (distance(podiums[i], podiums[j]) <
                    podiums[i].getRadius() + podiums[j].getRadius()) {
                intersectionCount++;
                if (verbose)
                    std::cout << "Podiums " << i << " and " <<
                                 j << " intersect.\n";
            }
        }
    }
    if (verbose)
        std::cout << "---Total: " << intersectionCount << "\n";
    return intersectionCount;
}

void PodiumArray::push_back(const Podium &object)
{
    podiums.push_back(object);
}

void PodiumArray::pop_back()
{
    podiums.pop_back();
}

void PodiumArray::clear()
{
    podiums.clear();
}

const Podium &PodiumArray::at(size_t pos) const
{
    return podiums.at(pos);
}

void PodiumArray::set(size_t pos, const Podium &object)
{
    podiums.set(pos, object);
}

void PodiumArray::del(size_t pos)
{
    podiums.del(pos);
}

void PodiumArray::insert(size_t pos, const Podium &object)
{
    podiums.insert(pos, object);
}

bool PodiumArray::empty() const
{
    return podiums.empty();
}

size_t PodiumArray::getSize() const
{
    return podiums.getSize();
}

size_t PodiumArray::getCapacity() const
{
    return podiums.getCapacity();
}

void PodiumArray::writeToFile(const std::string &filename) const
{
    std::ofstream fout;
    fout.open(filename);
    fout << podiums;
}

bool PodiumArray::readFromFile(const std::string &filename)
{
    std::ifstream fin(filename);
    if (!fin) {
        std::cout << "Can't open file: " << filename << '\n';
        return false;
    }
    podiums.clear();

    Podium inputPodium;
    std::string tmp = "";
    std::string input;
    if (!fin.eof())
        std::getline(fin, input);
    while (!fin.eof()) {
        size_t i = 0;
        readToSpace(i, input, tmp);
        inputPodium.setBrand(tmp);
        readToSpace(i, input, tmp);
        inputPodium.setX(std::atof(tmp.c_str()));
        readToSpace(i, input, tmp);
        inputPodium.setY(std::atof(tmp.c_str()));
        readToSpace(i, input, tmp);
        inputPodium.setRadius(std::atof(tmp.c_str()));
        podiums.push_back(inputPodium);
        std::getline(fin, input);
    }
    return true;
}

const Podium &PodiumArray::operator[](size_t i) const
{
    return podiums.at(i);
}
