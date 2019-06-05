greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
#CONFIG += console c++11

CONFIG -= app_bundle
CONFIG += qt
CONFIG += core

DEFINES += QT_DEPRECATED_WARNINGS

PKGCONFIG += opencv

INCLUDEPATH += -I/usr/local/include/opencv
LIBS += $(shell pkg-config opencv --libs)

SOURCES += main.cpp \
    modules/container.cpp \
    modules/classifier.cpp \
    modules/dataparser.cpp \
    modules/imageprocessing.cpp

SUBDIRS += Qt_disease_detector.pro

HEADERS += \
    modules/container.h \
    modules/classifier.h \
    modules/dataparser.h \
    modules/imageprocessing.h
