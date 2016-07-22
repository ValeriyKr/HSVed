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
