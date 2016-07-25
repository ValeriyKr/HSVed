#ifndef VALBRUSH_H
#define VALBRUSH_H

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
class ValBrush;
}

class ValBrush : public QWidget, public Brush
{
    Q_OBJECT

public:
    explicit ValBrush(QWidget *parent = 0);
    const QString & name();
    ~ValBrush();

public slots:
    void affect(QImage &pixmap, const QPoint &point) const;
    void showSettings();
    void hideSettings();
    void setSize(int size);
    void setHardness(double hardness);
    void setIntensity(int intensity);

signals:
    void sizeChanged(int size);

private:
    Ui::ValBrush *ui;
    double _hardness;
    int _intensity;
    static const QString _name;
};

#endif // VALBRUSH_H
