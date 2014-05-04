#ifndef SLIDER_H
#define SLIDER_H

#include <QWidget>
#include <QDebug>
#include<QStyleOption>
#include<QPainter>
#include<QThread>

class Slider: public QWidget
{
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent* event );
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    void paintEvent(QPaintEvent *);

public:
    Slider(QWidget* parent=0);
    ~Slider();
};

#endif // SLIDER_H
