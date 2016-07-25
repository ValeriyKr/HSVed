#include "brushstore.h"
#include "ui_brushstore.h"

BrushStore::BrushStore(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BrushStore),
    _currentIndex {0}
{
    ui->setupUi(this);

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


BrushStore::~BrushStore() {
    delete ui;
}
