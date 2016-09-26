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
    void save(const QString &filename, const QString &format, const int quality);
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
