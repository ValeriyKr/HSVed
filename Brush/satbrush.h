#ifndef SATBRUSH_H
#define SATBRUSH_H

#include <cmath>

#include <QObject>
#include <QWidget>
#include <QPoint>
#include <QPainter>
#include <QPixmap>
#include <QImage>
#include <QColor>
#include <QString>
#include <QDebug>

#include <Brush/brush.h>

namespace Ui {
class SatBrush;
}

class SatBrush : public QWidget, public Brush
{
    Q_OBJECT

public:
    explicit SatBrush(QWidget *parent = 0);
    const QString & name();
    ~SatBrush();

public slots:
    void affect(QImage &pixmap, const QPoint &point) const;
    void showSettings();
    virtual void setSize(int size);
    void setHardness(double hardness);
    void setIntensity(int intensity);

signals:
    void sizeChanged(int size);

private:
    Ui::SatBrush *ui;
    double _hardness;
    int _intensity;
    static const QString _name;
};

#endif // SATBRUSH_H
