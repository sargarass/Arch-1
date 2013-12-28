TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CFLAGS += -O3 -std=c99 -frounding-math -fsignaling-nans #-m128bit-long-double
#QMAKE_CFLAGS += -fp-model strict
SOURCES += main.c


HEADERS +=
