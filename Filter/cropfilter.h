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
