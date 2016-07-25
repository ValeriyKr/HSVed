#ifndef BRUSHSTORE_H
#define BRUSHSTORE_H

#include <QWidget>
#include <QVector>
#include <QDebug>

#include "Brush/brush.h"
#include "Brush/huebrush.h"
#include "Brush/satbrush.h"
#include "Brush/valbrush.h"

namespace Ui {
class BrushStore;
}

class BrushStore : public QWidget
{
    Q_OBJECT

public:
    explicit BrushStore(QWidget *parent = 0);
    Brush & operator[](std::size_t index);
    const Brush & operator[](std::size_t index) const;
    Brush & current();
    const Brush & current() const;
    ~BrushStore();

public slots:
    void brushChanged(int index);
    void showBrushSettings();

private:
    Ui::BrushStore *ui;
    QVector<Brush*> brushes;
    std::size_t _currentIndex;
};

#endif // BRUSHSTORE_H
