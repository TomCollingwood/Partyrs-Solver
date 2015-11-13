TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CFLAGS+=-std=c99

HEADERS+=person.h
SOURCES += main.c

include(deployment.pri)
qtcAddDeployment()

