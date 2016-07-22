#include "image.h"


Image::Image(const QString &file, QObject *parent)
  : QObject(parent),
    edited {true},
    _scene {new QGraphicsScene(this)},
    filename {file},
    _pixmap {new QImage(filename)},
    _size {_pixmap->width(), _pixmap->height()}
{
    updateScene();
}


const QSize & Image::size() const {
    return _size;
}


QImage & Image::pixmap() {
    edited = true;
    return *_pixmap;
}


const QGraphicsScene * Image::scene() const {
    return _scene;
}


void Image::updateScene() {
    QPixmap p {QPixmap::fromImage(*this->_pixmap)};
    _scene->addPixmap(p);
    _scene->setSceneRect(this->_pixmap->rect());
}


Image::~Image() {
    delete _scene;
    delete _pixmap;
}



