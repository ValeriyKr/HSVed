#include "cropfilter.h"
#include "ui_cropfilter.h"

const QString CropFilter::_name {"Crop"};

CropFilter::CropFilter(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::CropFilter),
    image {nullptr}
{
    ui->setupUi(this);
    setModal(true);
}


const QString &CropFilter::name() {
    return _name;
}


void CropFilter::affect(QImage &pixmap) {
    image = &pixmap;
    show();
}


void CropFilter::continueAffecting() {
    rect = QRect(ui->ctrlX->text().toInt(), ui->ctrlY->text().toInt(),
                 ui->ctrlWidth->text().toInt(), ui->ctrlHeight->text().toInt()
           );
    close();
    if (nullptr != image) {
        *image = image->copy(rect);
        image = nullptr;
    } else {
        // throw exception
    }
}


const QString &CropFilter::params() const {

}


void CropFilter::setParams(const QString &params) {

}


CropFilter::~CropFilter()
{
    delete ui;
}
