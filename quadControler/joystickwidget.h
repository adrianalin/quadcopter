#ifndef JOYSTICKWIDGET_H
#define JOYSTICKWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QStyleOption>
#include <QPainter>

class JoyStickWidget: public QWidget
{
    Q_OBJECT

public:
    JoyStickWidget(QWidget *parent=0);
    ~JoyStickWidget();

protected:
    void mousePressEvent(QMouseEvent* event );
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent *);

signals:
    void positionChanged(int y);

private:
    int m_eventRate;
    int m_accelerate;
    void setAccelerate(int y);
};

//*********************************************************************************************************************************************

class PadControl: public JoyStickWidget
{
    Q_OBJECT

public:
    PadControl(QWidget* parent);
    ~PadControl();

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

signals:
    void positionChanged(int x, int y);

private:
    void setXY(int x, int y);
    int m_x;
    int m_y;
};

#endif // JOYSTICKWIDGET_H
