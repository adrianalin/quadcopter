#ifndef JOYSTICKWIDGET_H
#define JOYSTICKWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QStyleOption>
#include <QPainter>

class JoyStickWidget: public QWidget
{
    Q_OBJECT

private:
    int eventRate;

protected:

    void mousePressEvent(QMouseEvent* event );
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    void paintEvent(QPaintEvent *);

signals:
    void positionChanged(int x, int y, int width, int height);

public:
    JoyStickWidget(QWidget *parent=0);
    ~JoyStickWidget();
};

//*********************************************************************************************************************************************

class PadControl: public JoyStickWidget{
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent* event);

signals:
    void mouseReleased();

public:
    PadControl(QWidget* parent);
    ~PadControl();
};

#endif // JOYSTICKWIDGET_H
