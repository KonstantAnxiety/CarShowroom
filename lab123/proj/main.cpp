#include <iostream>
#include <assert.h>
#include <string>
#include "auxiliary.h"
#include "car.h"
#include "podium.h"
#include "vector.h"
#include "carshowroom.h"
#include "tests.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();

    /*CarShowroom q;
    q.readFromFile("showroom.txt");
    q.fullReport();

    std::cout << "\n=== TESTS ===\n";

    // assert copy
    CarShowroom qCopy(q);
    assert(q == qCopy);

    // assert initialization constructor
    size_t size = integer(1, 10);
    CarShowroom qInit(100, 100, size);
    assert(qInit.objects.getSize() == size);

    // assert add/insert/del/erase
    size = q.objects.getSize();
    q.objects.push_back(std::shared_ptr<Point>(new Car(1, 1, 1, 1, 1, "A")));
    assert(q.objects.getSize() == ++size);
    q.objects.pop_back();
    assert(q.objects.getSize() == --size);
    q.objects.insert(0, std::shared_ptr<Point>(new Car(1, 1, 1, 1, 1, "A")));
    assert(q.objects.getSize() == ++size);
    q.objects.del(0);
    assert(q.objects.getSize() == --size);

    // assert clear
    q.objects.clear();
    assert(q.objects.getSize() == 0);

    // assert at
    printCarShowroom(qCopy);

    // assert files
    qCopy.writeToFile("showroom.txt");
    q.readFromFile("showroom.txt");
    assert(q == qCopy);

    std::cout << "\nAll tests completed\n";

    std::cout << "\nPress any key to quit.\n";
    */
    //return 0;
}
