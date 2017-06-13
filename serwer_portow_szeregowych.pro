TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

QMAKE_CC = gcc-4.9
QMAKE_CXX = g++-4.9

SOURCES += main.cpp \
    serialPort/serialport.cpp

target.path=/opt/$${TARGET}/bin
INSTALLS += target

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    serialPort/serialport.hpp

