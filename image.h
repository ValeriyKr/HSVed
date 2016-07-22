#ifndef IMAGE_H
#define IMAGE_H

#include <mutex>

#include <QString>
#include <QGraphicsScene>
#include <QPixmap>
#include <QPainter>
#include <QSize>
#include <QDebug>

class Image : public QObject
{
    Q_OBJECT
public:
    bool edited;
    std::mutex paintMutex;

    explicit Image(const QString &file, QObject *parent = 0);
    const QSize & size() const;
    QImage & pixmap();
    const QGraphicsScene * scene() const;
    ~Image();

signals:

public slots:
    void updateScene();

private:
    QGraphicsScene *_scene;
    QString filename;
    QImage *_pixmap;
    QSize _size;
};

#endif // IMAGE_H
