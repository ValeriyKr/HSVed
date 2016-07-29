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

#ifndef FILTER_H
#define FILTER_H

#include <QString>
#include <QImage>

class Filter {
public:
    explicit Filter();
    virtual const QString &name() = 0;
    virtual void affect(QImage &pixmap) = 0;
    virtual const QString params() const = 0;
    virtual void setParams(const QString &params) = 0;
    virtual ~Filter() = 0;
};

#endif // FILTER_H
