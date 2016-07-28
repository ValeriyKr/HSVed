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

#ifndef HUEBRUSH_H
#define HUEBRUSH_H

#include <cmath>

#include <QObject>
#include <QWidget>
#include <QPoint>
#include <QPainter>
#include <QPixmap>
#include <QImage>
#include <QColor>
#include <QString>
#include <QDebug>

#include <Brush/brush.h>

namespace Ui {
class HueBrush;
}

class HueBrush : public QWidget, public Brush
{
    Q_OBJECT

public:
    explicit HueBrush(QWidget *parent = 0);
    const QString & name();
    ~HueBrush();

public slots:
    void affect(QImage &pixmap, const QPoint &point) const;
    void showSettings();
    void hideSettings();
    void setSize(int size);
    void setHardness(double hardness);
    void setIntensity(int intensity);

signals:
    void sizeChanged(int size);

private:
    Ui::HueBrush *ui;
    double _hardness;
    int _intensity;
    static const QString _name;
};

#endif // HUEBRUSH_H
