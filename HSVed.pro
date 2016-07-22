#-------------------------------------------------
#
# Project created by QtCreator 2016-07-19T14:28:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HSVed
TEMPLATE = app


SOURCES += main.cpp\
        hsved.cpp \
    image.cpp \
    Brush/brush.cpp \
    Brush/huebrush.cpp \
    Brush/satbrush.cpp \
    Brush/valbrush.cpp

HEADERS  += hsved.h \
    image.h \
    Brush/brush.h \
    Brush/huebrush.h \
    Brush/satbrush.h \
    Brush/valbrush.h

FORMS    += hsved.ui \
    Brush/huebrush.ui \
    Brush/satbrush.ui \
    Brush/valbrush.ui
