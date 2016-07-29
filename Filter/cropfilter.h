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

#ifndef CROPFILTER_H
#define CROPFILTER_H

#include <QDialog>
#include <QImage>
#include <QRect>

#include "Filter/filter.h"

namespace Ui {
class CropFilter;
}

class CropFilter : public QDialog, public Filter
{
    Q_OBJECT

public:
    explicit CropFilter(QDialog *parent = 0);
    const QString &name();
    const QString params() const;
    void setParams(const QString &params);
    ~CropFilter();

public slots:
    void affect(QImage &pixmap);

private:
    Ui::CropFilter *ui;
    static const QString _name;
    static const QString sep;
    QRect rect;
    QImage *image;

private slots:
    void continueAffecting();
};

#endif // CROPFILTER_H
