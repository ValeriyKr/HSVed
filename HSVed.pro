#        Copyright 2016 Valeriy Kireev
#
#        This file is part of HSVed.
#
#        HSVed is free software: you can redistribute it and/or modify
#        it under the terms of the GNU General Public License as published by
#        the Free Software Foundation, either version 3 of the License, or
#        (at your option) any later version.
#
#        HSVed is distributed in the hope that it will be useful,
#        but WITHOUT ANY WARRANTY; without even the implied warranty of
#        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#        GNU General Public License for more details.
#
#        You should have received a copy of the GNU General Public License
#        along with HSVed. If not, see <http://www.gnu.org/licenses/>.

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
    Brush/valbrush.cpp \
    brushstore.cpp \
    Filter/filter.cpp \
    Filter/cropfilter.cpp

HEADERS  += hsved.h \
    image.h \
    Brush/brush.h \
    Brush/huebrush.h \
    Brush/satbrush.h \
    Brush/valbrush.h \
    brushstore.h \
    Filter/filter.h \
    Filter/cropfilter.h

FORMS    += hsved.ui \
    Brush/huebrush.ui \
    Brush/satbrush.ui \
    Brush/valbrush.ui \
    brushstore.ui \
    Filter/cropfilter.ui
