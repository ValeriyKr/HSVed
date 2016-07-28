/*
        Copyright 2016 Valeriy Kireev

        This file is part of HSVed.

        HSVed is free software: you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
        the Free Software Foundation, either version 3 of the License, or
        (at your option) any later version.

        HSVed is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
        GNU General Public License for more details.

        You should have received a copy of the GNU General Public License
        along with HSVed. If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef BRUSH_H
#define BRUSH_H

#include <thread>
#include <mutex>

#include <QObject>
#include <QWidget>
#include <QPoint>
#include <QPainter>
#include <QQueue>
#include <QString>
#include <QDebug>

using mutex_t = std::mutex;

class Brush {
public:
    static const int default_size {20};

    explicit Brush();
    virtual const QString & name() = 0;
    static void affectBrushWrapper(const Brush &brush, mutex_t &mutex, QImage &pixmap, QQueue<QPoint> &points);
    int size();
    virtual void affect(QImage &pixmap, const QPoint &point) const = 0;
    virtual void setSize(int size);
    virtual void sizeChanged(int size) = 0;
    virtual void showSettings() = 0;
    virtual void hideSettings() = 0;
    virtual ~Brush() = 0;

protected:
    int _size;
};

#endif // BRUSH_H
