#include "satbrush.h"
#include "ui_satbrush.h"


const QString SatBrush::_name {"Saturation"};


SatBrush::SatBrush(QWidget *parent) :
    QWidget {parent},
    Brush {},
    ui(new Ui::SatBrush),
    _hardness {1.0},
    _intensity {20}
{
    ui->setupUi(this);
    QObject::connect(ui->ctrlSize, SIGNAL(valueChanged(int)), this, SLOT(setSize(int)));
    QObject::connect(this, SIGNAL(sizeChanged(int)), ui->ctrlSize, SLOT(setValue(int)));
    QObject::connect(ui->ctrlHardness, SIGNAL(valueChanged(double)), this, SLOT(setHardness(double)));
    QObject::connect(ui->ctrlIntensity, SIGNAL(valueChanged(int)), this, SLOT(setIntensity(int)));
}

const QString & SatBrush::name() {
    return _name;
}


void SatBrush::affect(QImage &pixmap, const QPoint &point) const {
    int xmin = std::max(0, point.x()-_size);
    int xmax = std::min(pixmap.width(), point.x()+_size);
    int ymin = std::max(0, point.y()-_size);
    int ymax = std::min(pixmap.height(), point.y()+_size);
    QColor pixel;
    for (int i = xmin; i < xmax; ++i)
        for (int j = ymin; j < ymax; ++j) {
            int deltaSquare {(i-point.x())*(i-point.x()) + (j-point.y())*(j-point.y())};
            if (deltaSquare <= _size*_size) {
                double delta {std::sqrt(deltaSquare)};
                pixel = pixmap.pixelColor(i, j);
                pixel.setHsv(pixel.hue(),
                    std::max(0,
                        std::min(255,
                            static_cast<int> (pixel.saturation() + _intensity *
                                              (delta/_size <= _hardness ?
                                                  1 :
                                                  1 - (delta-_size*_hardness)/(_size*(1-_hardness)))))
                    ),
                    pixel.value()
                );
                pixmap.setPixelColor(i, j, pixel);
            }
        }
}


void SatBrush::showSettings() {
    this->hide();
    this->show();
}


void SatBrush::hideSettings() {
    this->hide();
}


void SatBrush::setSize(int size) {
    _size = std::min(2048, std::max(1, size));
    emit sizeChanged(size);
}


void SatBrush::setHardness(double hardness) {
    _hardness = std::min(1.0, std::max(0.0, hardness));
}


void SatBrush::setIntensity(int intensity) {
    _intensity = std::min(255, std::max(-255, intensity));
}


SatBrush::~SatBrush() {
    delete ui;
}
