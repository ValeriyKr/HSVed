#ifndef HUEBRUSH_H
#define HUEBRUSH_H

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
class HueBrush;
}

class HueBrush : public QWidget, public Brush
{
    Q_OBJECT

public:
    explicit HueBrush(QWidget *parent = 0);
    const QString & name();
    ~HueBrush();

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
    Ui::HueBrush *ui;
    double _hardness;
    int _intensity;
    static const QString _name;
};

#endif // HUEBRUSH_H
