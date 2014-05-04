#include "joystickwidget.h"
#include <QThread>
#include <QMouseEvent>

JoyStickWidget::JoyStickWidget(QWidget* parent) : QWidget(parent)
{
    eventRate = 0;
}

JoyStickWidget::~JoyStickWidget(){
}

void JoyStickWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void JoyStickWidget::mousePressEvent(QMouseEvent * event ){
//    qDebug()<<"mouse pressed";
}

void JoyStickWidget::mouseMoveEvent(QMouseEvent *event){
    eventRate++;
    if(eventRate%10 != 0)
        return ;


    int y = event->y() - this->height();
    int x = event->x();

    if((y<=0) && (y>=-this->height()) && (x>0) && (x<this->width()))
        emit positionChanged(x, abs(y), this->width(), this->height());
}

void JoyStickWidget::mouseReleaseEvent(QMouseEvent *event){
//    qDebug()<<"mouse release";
}

//*****************************************PadControl class, deriver from JoyStickWidget**************************************************


PadControl::PadControl(QWidget *parent):JoyStickWidget(parent)
{

}

PadControl::~PadControl()
{

}

void PadControl::paintEvent(QPaintEvent *){
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QPainter painter(this);
    painter.setPen(Qt::blue);
    painter.drawLine(0, this->height()/2, this->width(), this->height()/2);
    painter.drawLine(this->width()/2, 0, this->width()/2, this->height());
}

void PadControl::mouseReleaseEvent(QMouseEvent *event){
    emit mouseReleased();
}
