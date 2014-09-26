#include "joystickwidget.h"
#include <QThread>
#include <QMouseEvent>

JoyStickWidget::JoyStickWidget(QWidget* parent) : QWidget(parent)
  , m_eventRate(0)
  , m_accelerate(0)
{
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

void JoyStickWidget::mousePressEvent(QMouseEvent * event ) {
    Q_UNUSED(event)
}

void JoyStickWidget::mouseMoveEvent(QMouseEvent *event) {
    m_eventRate++;
    if (m_eventRate % 10 != 0)
        return ;

    int y = event->y() - this->height();
    int x = event->x();

    if((y<=0) && (y>=-this->height()) && (x>0) && (x<this->width()))
        setAccelerate(abs(y));
}

void JoyStickWidget::setAccelerate(int y)
{
    if (m_accelerate == y)
        return ;
    m_accelerate = y;
    emit positionChanged(m_accelerate);
}

void JoyStickWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
}

//*****************************************PadControl class, deriver from JoyStickWidget**************************************************


PadControl::PadControl(QWidget *parent):JoyStickWidget(parent)
{

}

PadControl::~PadControl()
{

}

void PadControl::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QPainter painter(this);
    painter.setPen(Qt::blue);
    painter.drawLine(0, this->height()/2, this->width(), this->height()/2);
    painter.drawLine(this->width()/2, 0, this->width()/2, this->height());
}

void PadControl::mouseMoveEvent(QMouseEvent *event)
{
    int xCoord, yCoord;
    int y = event->y() - this->height();
    int x = event->x();
    if((y<=0) && (y>=-this->height()) && (x>0) && (x<this->width()))
    {
        xCoord = event->x() - this->width()/2;
        yCoord = this->height()/2 - event->y();
        setXY(xCoord, yCoord);
    }
}

void PadControl::setXY(int x, int y)
{
    if((m_x == x) && (m_y == y))
        return ;
    m_x = x;
    m_y = y;
    emit positionChanged(m_x, m_y);
}

void PadControl::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    setXY(0, 0);
}
