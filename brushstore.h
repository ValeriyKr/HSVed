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

#ifndef BRUSHSTORE_H
#define BRUSHSTORE_H

#include <QWidget>
#include <QVector>
#include <QDebug>

#include "Brush/brush.h"
#include "Brush/huebrush.h"
#include "Brush/satbrush.h"
#include "Brush/valbrush.h"

namespace Ui {
class BrushStore;
}

class BrushStore : public QWidget
{
    Q_OBJECT

public:
    explicit BrushStore(QWidget *parent = 0);
    Brush & operator[](std::size_t index);
    const Brush & operator[](std::size_t index) const;
    Brush & current();
    const Brush & current() const;
    ~BrushStore();

public slots:
    void brushChanged(int index);
    void showBrushSettings();
    void show();

private:
    Ui::BrushStore *ui;
    QVector<Brush*> brushes;
    std::size_t _currentIndex;
};

#endif // BRUSHSTORE_H
