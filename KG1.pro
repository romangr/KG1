#-------------------------------------------------
#
# Project created by QtCreator 2015-10-06T17:50:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KG1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    figure.cpp \
    matrix.cpp \
    showwindow.cpp \
    parabola.cpp \
    ruledparabols.cpp \
    ruledsurface.cpp \
    curve.cpp \
    trianglesurface.cpp \
    triangle.cpp \
    linesegment.cpp \
    sidedfigure.cpp \
    lightedsurface.cpp \
    trianglefigure.cpp

HEADERS  += mainwindow.h \
    figure.h \
    matrix.h \
    showwindow.h \
    parabola.h \
    ruledparabols.h \
    ruledsurface.h \
    curve.h \
    trianglesurface.h \
    triangle.h \
    linesegment.h \
    sidedfigure.h \
    lightedsurface.h \
    trianglefigure.h

FORMS    += mainwindow.ui \
    showwindow.ui
