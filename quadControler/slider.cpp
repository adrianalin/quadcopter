#include "slider.h"

Slider::Slider(QWidget *parent) : QWidget(parent)
{
}

Slider::~Slider(){
}

void Slider::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void Slider::mousePressEvent(QMouseEvent * event ) {
    Q_UNUSED(event)
}

void Slider::mouseMoveEvent(QMouseEvent *event) {
    Q_UNUSED(event)
    QThread::msleep(200);
}

void Slider::mouseReleaseEvent(QMouseEvent *event) {
    Q_UNUSED(event)
}
