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
