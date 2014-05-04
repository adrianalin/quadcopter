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

void Slider::mousePressEvent(QMouseEvent * event ){
    qDebug()<<"slider pressed";
}

void Slider::mouseMoveEvent(QMouseEvent *event){
    qDebug()<<"slider move";
    QThread::msleep(200);
}

void Slider::mouseReleaseEvent(QMouseEvent *event){
    qDebug()<<"slider release";
}
