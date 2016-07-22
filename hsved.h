#ifndef HSVED_H
#define HSVED_H

#include <thread>
#include <functional>

#include <QMainWindow>
#include <QString>
#include <QPixmap>
#include <QPoint>
#include <QGraphicsScene>
#include <QResizeEvent>
#include <QSize>
#include <QMouseEvent>
#include <QVector>
#include <QQueue>
#include <QThread>
#include <QDebug>

#include <image.h>
#include <Brush/huebrush.h>

namespace Ui {
class HSVed;
}

class HSVed : public QMainWindow
{
    Q_OBJECT
    typedef void (HSVed::*member)();

public:
    explicit HSVed(QWidget *parent = 0);
    const QPoint posOnImage(const QPoint &pos) const;
    ~HSVed();

protected:
    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *event);
    void paintEvent(QPaintEvent *event);
    void paintEvent();
    void closeEvent(QCloseEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);

signals:
    void windowResized(QSize size);

private:
    QVector<Brush*> brushes;
    QQueue<QPoint> toHandle;
    Image *image;
    Ui::HSVed *ui;
};

#endif // HSVED_H
