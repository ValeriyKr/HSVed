/*
        Copyright 2016 Valeriy Kireev

        This file is part of HSVed.

        HSVed is free software: you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
        the Free Software Foundation, either version 3 of the License, or
        (at your option) any later version.

        HSVed is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
        GNU General Public License for more details.

        You should have received a copy of the GNU General Public License
        along with HSVed. If not, see <http://www.gnu.org/licenses/>.
*/

#include "hsved.h"
#include "ui_hsved.h"

HSVed::HSVed(QWidget *parent) :
    QMainWindow(parent),
    currentBrush {nullptr},
    ui(new Ui::HSVed)
{
    ui->setupUi(this);
    QObject::connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(close()));
    QObject::connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(close()));
    QObject::connect(ui->actionSave_As, SIGNAL(triggered()), this, SLOT(close()));
    QObject::connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    QObject::connect(ui->actionBrushes, SIGNAL(triggered()), &brushes, SLOT(show()));
    QObject::connect(ui->actionFilters, SIGNAL(triggered()), this, SLOT(close()));

    image = new Image(QFileDialog::getOpenFileName(this, "Image", QDir::homePath()));
    ui->imageView->setScene(const_cast<QGraphicsScene*> (image->scene()));

    ui->imageView->installEventFilter(this);
    ui->imageView->setMouseTracking(true);
    ui->imageView->viewport()->setMouseTracking(true);
    ui->imageView->viewport()->installEventFilter(this);

    ui->imageView->setCursor(cursor);
    brushes.show();
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
    QWidget::showEvent(event);
    ui->imageView->fitInView(image->scene()->sceneRect(), Qt::KeepAspectRatio);
}


void HSVed::paintEvent() {
    if (image->edited) {
        image->updateScene();
        image->edited = false;
    }
}


void HSVed::closeEvent(QCloseEvent *event) {
    QWidget::closeEvent(event);
    QApplication::exit(0);
}


bool HSVed::eventFilter(QObject *watched, QEvent *event) {
    if (watched == ui->imageView || watched == ui->imageView->viewport()) {
        switch (event->type()) {
        case QEvent::MouseButtonPress:
        case QEvent::MouseMove:
        {
            auto me = static_cast<QMouseEvent*>(event);
            if (me->buttons() == Qt::LeftButton) {
                toHandle.enqueue(posOnImage(me->pos()));
                return true;
            } else if (me->button() == Qt::RightButton) {
                brushes.show();
                return true;
            }
            break;
        }
        case QEvent::MouseButtonRelease:
        {
            undo.push_back(image->pixmap().copy(QRect(0, 0, image->size().width(), image->size().height())));
            redo.clear();
            while (!toHandle.empty()) {
                brushes.current().affect(image->pixmap(), toHandle.dequeue());
            }
            paintEvent();
            return true;
        }
        case QEvent::Wheel:
        {
            auto we = static_cast<QWheelEvent*>(event);
            if (we->delta() > 0) {
                brushes.current().setSize(static_cast<int> (brushes.current().size()*1.1) + 1);
            } else {
                brushes.current().setSize(static_cast<int> (brushes.current().size()*0.9));
            }
            return true;
        }
        case QEvent::KeyRelease:
        {
            auto ke = static_cast<QKeyEvent*>(event);
            switch (ke->key()) {
            case Qt::Key_S:
            {
                if (ke->modifiers() & Qt::ControlModifier) {
                    image->save(QFileDialog::getSaveFileName(this, "Image", QDir::homePath(), "Images (*.jpg)"), "JPG", 100);
                }
                break;
            }
            case Qt::Key_Z:
            {
                if (ke->modifiers() & Qt::ControlModifier) {
                    if (undo.isEmpty()) break;
                    redo.push_back(image->pixmap());
                    image->setPixmap(undo.top());
                    undo.pop_back();
                }
                break;
            }
            case Qt::Key_R:
            {
                if (ke->modifiers() & Qt::ControlModifier) {
                    if (redo.isEmpty()) break;
                    undo.push(image->pixmap());
                    image->setPixmap(redo.top());
                    redo.pop();
                }
                break;
            }
            default:
                break;
            }
        }
        default:
            return false;
        }
    }
    return false;
}


HSVed::~HSVed() {
    delete image;
    delete ui;
}
