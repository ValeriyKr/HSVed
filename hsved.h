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

#ifndef HSVED_H
#define HSVED_H

#include <thread>
#include <functional>

#include <QMainWindow>
#include <QString>
#include <QPixmap>
#include <QPoint>
#include <QGraphicsScene>
#include <QResizeEvent>
#include <QSize>
#include <QMouseEvent>
#include <QVector>
#include <QQueue>
#include <QCursor>
#include <QDebug>

#include "image.h"
#include "brushstore.h"
#include "Brush/huebrush.h"
#include "Brush/satbrush.h"
#include "Brush/valbrush.h"
#include "Filter/filter.h"
#include "Filter/cropfilter.h"

namespace Ui {
class HSVed;
}

class HSVed : public QMainWindow
{
    Q_OBJECT
    typedef void (HSVed::*member)();

public:
    explicit HSVed(QWidget *parent = 0);
    const QPoint posOnImage(const QPoint &pos) const;
    ~HSVed();

protected:
    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *event);
    //void paintEvent(QPaintEvent *event);
    void paintEvent();
    void closeEvent(QCloseEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);

signals:
    void windowResized(QSize size);

private:
    Brush* currentBrush;
    //QVector<Brush*> brushes;
    BrushStore brushes;
    QQueue<QPoint> toHandle;
    Image *image;
    Ui::HSVed *ui;
    QCursor cursor;
};

#endif // HSVED_H
