TEMPLATE = app
TARGET = basic_calculator

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    basiccalculator.cpp \
    main.cpp \
    math/divide.c

HEADERS += \
    basiccalculator.h \
    math/math.h \
    test.h
