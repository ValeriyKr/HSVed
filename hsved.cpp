#include "hsved.h"
#include "ui_hsved.h"

HSVed::HSVed(QWidget *parent) :
    QMainWindow(parent),
    currentBrush {nullptr},
    ui(new Ui::HSVed)
{
    ui->setupUi(this);

    image = new Image("/home/valeriyk/av6.png");
    ui->imageView->setScene(const_cast<QGraphicsScene*> (image->scene()));

    ui->imageView->installEventFilter(this);
    ui->imageView->setMouseTracking(true);
    ui->imageView->viewport()->setMouseTracking(true);
    ui->imageView->viewport()->installEventFilter(this);

    brushes.push_back(new HueBrush());
    brushes.push_back(new SatBrush());
    brushes.push_back(new ValBrush());
    currentBrush = brushes[2];
}


const QPoint HSVed::posOnImage(const QPoint &pos) const {
    return QPoint(static_cast<int> (pos.x() * (1.0*image->size().width() / ui->imageView->width())),
                  static_cast<int> (pos.y() * (1.0*image->size().height() / ui->imageView->height()))
                 );
}


void HSVed::resizeEvent(QResizeEvent *event) {
    QSize is {image->size()};
    QSize es {event->size()};

    // Count real accessable space
    es.setHeight(es.height() - (ui->statusBar->height() + ui->menuBar->height() + ui->mainToolBar->height()));

    /*
        Need to next condition:
            image_width/image_height == scene_width/scene_height
        , and image have to be smaller than window.
    */
    int h, w;
    if (is.width() >= is.height()) {
        w = es.width();
        h = static_cast<int> (is.height() * (1.0*w / is.width()));
        if (h > es.height()) {
            h = es.height();
            w = static_cast<int> (is.width() * (1.0*h / is.height()));
        }
    } else {
        h = es.height();
        w = static_cast<int> (is.width() * (1.0*h / is.height()));
        if (w > es.width()) {
            w = es.width();
            h = static_cast<int> (is.height() * (1.0*w / is.height()));
        }
    }
    ui->imageView->setGeometry(0, 0, w, h);
    ui->imageView->fitInView(image->scene()->sceneRect(), Qt::KeepAspectRatio);

    emit windowResized(event->size());
}


void HSVed::showEvent(QShowEvent *event) {
    ui->imageView->fitInView(image->scene()->sceneRect(), Qt::KeepAspectRatio);
}


void HSVed::paintEvent(QPaintEvent *event) {
    if (image->edited) {
        image->updateScene();
        image->edited = false;
    }
}


void HSVed::paintEvent() {
    if (image->edited) {
        image->updateScene();
        image->edited = false;
    }
}


void HSVed::closeEvent(QCloseEvent *event) {
    QApplication::exit(0);
}


bool HSVed::eventFilter(QObject *watched, QEvent *event) {
//    Uncomment this, if not only imageView will handled
//    if (watched == ui->imageView || watched == ui->imageView->viewport()) {
        if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseMove) {
            auto me = static_cast<QMouseEvent*>(event);
            if (me->buttons() == Qt::LeftButton) {
                //QPoint pos = posOnImage(me->pos());
                //Brush::affect(*brushes[0], image->painter(), pos);

                /*std::thread t(Brush::affectBrushWrapper, std::cref(*brushes[0]),
                              std::ref(image->painter_mutex), std::ref(image->painter()),
                              std::cref(pos)
                             );
                t.detach();*/
                //qDebug() << "done";
                //paintEvent();
                toHandle.enqueue(posOnImage(me->pos()));
                return true;
            } else if (me->button() == Qt::RightButton) {
                currentBrush->showSettings();
            }
        } else if (event->type() == QEvent::MouseButtonRelease) {
            while (!toHandle.empty()) {
                currentBrush->affect(image->pixmap(), toHandle.dequeue());
            }
            /*std::thread t(Brush::affectBrushWrapper, std::cref(*brushes[0]),
                          std::ref(image->paintMutex), std::ref(image->pixmap()),
                          std::ref(toHandle)
                         );
            t.join();*/
            paintEvent();
            return true;
        } else if (event->type() == QEvent::Wheel) {
            auto we = static_cast<QWheelEvent*>(event);
            if (we->delta() > 0) {
                currentBrush->setSize(static_cast<int> (currentBrush->size()*1.1) + 1);
            } else {
                currentBrush->setSize(static_cast<int> (currentBrush->size()*0.9));
            }
        }
//    }
    return false;
}


HSVed::~HSVed() {
    delete image;
    delete ui;
}
