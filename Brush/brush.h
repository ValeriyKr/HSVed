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
