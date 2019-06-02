TEMPLATE = app
#CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt
CONFIG += core

SOURCES += main.cpp \
    modules/container.cpp

SUBDIRS += Qt_disiease_detector.pro

HEADERS += \
    modules/container.h
