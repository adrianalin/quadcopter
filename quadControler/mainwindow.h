#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QSlider>
#include <QLabel>

#include "slider.h"
#include "joystickwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void positionChanged(int x, int y, int width, int height);
    void resetCoordinates();

private:
    QLabel* sliderLabel, *padLabel;
    Ui::MainWindow *ui;
    QGridLayout* layout;

    JoyStickWidget* sliderControl;
    PadControl* padControl;
};

#endif // MAINWINDOW_H
