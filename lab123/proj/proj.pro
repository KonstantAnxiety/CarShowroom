TEMPLATE = app
CONFIG += c++17
CONFIG -= app_bundle
CONFIG += qt
QT     += core gui
QT     += widgets

SOURCES += \
        auxiliary.cpp \
        car.cpp \
        cardialog.cpp \
        carshowroom.cpp \
        dimensionsdialog.cpp \
        main.cpp \
        mainwindow.cpp \
        mygraphicview.cpp \
        podium.cpp \
        point.cpp \
        tests.cpp

HEADERS += \
    auxiliary.h \
    car.h \
    cardialog.h \
    carshowroom.h \
    dimensionsdialog.h \
    mainwindow.h \
    mygraphicview.h \
    podium.h \
    point.h \
    tests.h \
    vector.h

FORMS += \
    cardialog.ui \
    dimensionsdialog.ui \
    mainwindow.ui
