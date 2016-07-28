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

#include "brushstore.h"
#include "ui_brushstore.h"

BrushStore::BrushStore(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BrushStore),
    _currentIndex {0}
{
    ui->setupUi(this);
    this->setMinimumSize(this->size());
    this->setMaximumSize(this->size());

    brushes.push_back(new HueBrush);
    brushes.push_back(new SatBrush);
    brushes.push_back(new ValBrush);
    for (auto b : brushes) {
        ui->ctrlBrushChoise->addItem(b->name());
    }

    QObject::connect(ui->ctrlBrushChoise, SIGNAL(currentIndexChanged(int)), this, SLOT(brushChanged(int)));
    QObject::connect(ui->ctrlBrushSettings, SIGNAL(clicked(bool)), this, SLOT(showBrushSettings()));
}


Brush &BrushStore::operator[](std::size_t index) {
    return *brushes[index];
}


const Brush &BrushStore::operator[](std::size_t index) const {
    return *brushes[index];
}


Brush &BrushStore::current() {
    return *brushes[_currentIndex];
}


const Brush &BrushStore::current() const {
    return *brushes[_currentIndex];
}


void BrushStore::brushChanged(int index) {
    brushes[_currentIndex]->hideSettings();
    _currentIndex = index;
}


void BrushStore::showBrushSettings() {
    brushes[_currentIndex]->showSettings();
}


void BrushStore::show() {
    hide();
    QWidget::show();
}


BrushStore::~BrushStore() {
    delete ui;
}
