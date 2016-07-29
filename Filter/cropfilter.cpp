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

#include "cropfilter.h"
#include "ui_cropfilter.h"

const QString CropFilter::_name {"Crop"};
const QString CropFilter::sep {";"};

CropFilter::CropFilter(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::CropFilter),
    image {nullptr}
{
    ui->setupUi(this);
    setModal(true);

    QObject::connect(ui->ctrlApply, SIGNAL(clicked(bool)), this, SLOT(continueAffecting()));
    QObject::connect(ui->ctrlCancel, SIGNAL(clicked(bool)), this, SLOT(reject()));
}


const QString &CropFilter::name() {
    return _name;
}


void CropFilter::affect(QImage &pixmap) {
    image = &pixmap;
    exec();
}


void CropFilter::continueAffecting() {
    rect = QRect(ui->ctrlX->text().toInt(), ui->ctrlY->text().toInt(),
                 ui->ctrlWidth->text().toInt(), ui->ctrlHeight->text().toInt()
           );
    close();
    if (nullptr != image) {
        QImage newImage {image->copy(rect)};
        *image = std::move(newImage);
        image = nullptr;
    } else {
        // throw exception
    }
}


const QString CropFilter::params() const {
    return QString(rect.x() + sep + rect.y() + sep +
                   rect.width() + sep + rect.height());
}


void CropFilter::setParams(const QString &params) {
    auto args = params.split(sep);
    if (args.length() != 4) { // x, y, width and height
        // throw
    }
    rect = QRect(args[0].toInt(), args[1].toInt(),  // x, y
                 args[2].toInt(), args[3].toInt()); // w, h
}


CropFilter::~CropFilter()
{
    delete ui;
}
