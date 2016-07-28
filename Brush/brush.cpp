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

#include "Brush/brush.h"

Brush::Brush()
  : _size {Brush::default_size}
{

}


void Brush::affectBrushWrapper(const Brush &brush, mutex_t &mutex, QImage &pixmap, QQueue<QPoint> &points) {
    //std::unique_lock<mutex_t> lock{mutex};
    while (!points.empty()) {
        std::unique_lock<mutex_t> lock{mutex};
        qDebug() << "affect";
        brush.affect(pixmap, points.dequeue());
    }
}


int Brush::size() {
    return this->_size;
}


void Brush::setSize(int size) {
    this->_size = size;
    sizeChanged(size);
}


Brush::~Brush() {}
