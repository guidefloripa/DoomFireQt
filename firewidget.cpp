#include "firewidget.h"

#include "doomfire.h"

#include <QDebug>
#include <QColor>
#include <QPainter>

class FireWidget::Priv{

public:

    Priv(int w, int h) {
        df = new DoomFire(w, h);
        df->createFire();

        colorTable.push_back(QColor(7, 7, 7).rgb());
        colorTable.push_back(QColor(31, 7, 7).rgb());
        colorTable.push_back(QColor(47, 15, 7).rgb());
        colorTable.push_back(QColor(71, 15, 7).rgb());
        colorTable.push_back(QColor(87, 23, 7).rgb());
        colorTable.push_back(QColor(103, 31, 7).rgb());
        colorTable.push_back(QColor(119, 31, 7).rgb());
        colorTable.push_back(QColor(143, 39, 7).rgb());
        colorTable.push_back(QColor(159, 47, 7).rgb());
        colorTable.push_back(QColor(175, 63, 7).rgb());
        colorTable.push_back(QColor(191, 71, 7).rgb());
        colorTable.push_back(QColor(199, 71, 7).rgb());
        colorTable.push_back(QColor(223, 79, 7).rgb());
        colorTable.push_back(QColor(223, 87, 7).rgb());
        colorTable.push_back(QColor(223, 87, 7).rgb());
        colorTable.push_back(QColor(215, 95, 7).rgb());
        colorTable.push_back(QColor(215, 95, 7).rgb());
        colorTable.push_back(QColor(215, 103, 15).rgb());
        colorTable.push_back(QColor(207, 111, 15).rgb());
        colorTable.push_back(QColor(207, 119, 15).rgb());
        colorTable.push_back(QColor(207, 127, 15).rgb());
        colorTable.push_back(QColor(207, 135, 23).rgb());
        colorTable.push_back(QColor(199, 135, 23).rgb());
        colorTable.push_back(QColor(199, 143, 23).rgb());
        colorTable.push_back(QColor(199, 151, 31).rgb());
        colorTable.push_back(QColor(191, 159, 31).rgb());
        colorTable.push_back(QColor(191, 159, 31).rgb());
        colorTable.push_back(QColor(191, 167, 39).rgb());
        colorTable.push_back(QColor(191, 167, 39).rgb());
        colorTable.push_back(QColor(191, 175, 47).rgb());
        colorTable.push_back(QColor(183, 175, 47).rgb());
        colorTable.push_back(QColor(183, 183, 47).rgb());
        colorTable.push_back(QColor(183, 183, 55).rgb());
        colorTable.push_back(QColor(207, 207, 111).rgb());
        colorTable.push_back(QColor(223, 223, 159).rgb());
        colorTable.push_back(QColor(239, 239, 199).rgb());
        colorTable.push_back(QColor(255, 255, 255).rgb());
    }

    ~Priv() {
        delete df;
    }

    DoomFire *df;
    bool fireOn;
    QVector<QRgb> colorTable;
};


FireWidget::FireWidget(int w, int h, QWidget *parent) : QWidget(parent)
{
    d = new Priv(w, h);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerUpdate()));
    timer->start(70);
}

FireWidget::~FireWidget()
{
    delete d;
}

void FireWidget::paintEvent(QPaintEvent *event)
{
    QImage img(d->df->getAlignedFireVector(), d->df->witdh(), d->df->height(), QImage::Format_Indexed8);
    img.setColorTable(d->colorTable);

    QPainter p(this);
    p.drawImage(QPoint(0, 0), img);

    //qDebug() << "paint" << d->df->witdh() << d->df->height();
}

void FireWidget::onTimerUpdate()
{
    d->df->propagateFire();
    update();
}

void FireWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (d->fireOn) {
        timer->stop();
        //d->df->destroyFire();
        d->fireOn = false;
    }
    else {
        timer->start(30);
        //d->df->createFire();
        d->fireOn = true;
    }
    update();
}
