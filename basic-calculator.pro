TEMPLATE = app
TARGET = basic_calculator

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    basiccalculator.cpp \
    main.cpp \
    math/divide.c \
    math/gcd.c \
    math/lcm.c \
    math/modulus.c \
    math/multiply.c \
    math/prime.c \
    math/sqrt.c

HEADERS += \
    basiccalculator.h \
    math/math.h
