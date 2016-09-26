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

#include "image.h"


Image::Image(const QString &file, QObject *parent)
  : QObject(parent),
    edited {true},
    _scene {new QGraphicsScene(this)},
    filename {file},
    _pixmap {new QImage(filename)},
    _size {_pixmap->size()}
{
    updateScene();
}


const QSize & Image::size() const {
    return _size;
}


QImage &Image::pixmap() {
    edited = true;
    return *_pixmap;
}


const QGraphicsScene * Image::scene() const {
    return _scene;
}


void Image::save(const QString &filename, const QString &format, const int quality) {
    _pixmap->save(filename, format.toStdString().c_str(), quality);
}


void Image::updateScene() {
    _size = _pixmap->size();
    QPixmap p {QPixmap::fromImage(*this->_pixmap)};
    _scene->addPixmap(p);
    _scene->setSceneRect(this->_pixmap->rect());
}


Image::~Image() {
    delete _scene;
    delete _pixmap;
}



