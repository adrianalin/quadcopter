#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QSlider>
#include <QLabel>

#include "slider.h"
#include "joystickwidget.h"
#include "bluetoothhandler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    void createActions();
    void createMenus();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void positionChanged(int x, int y, int width, int height);
    void resetCoordinates();

private:
    BluetoothControler* bluetoothClient;
    QMenu* scanMenu;
    QAction* scanAction;
    QLabel* sliderLabel, *padLabel;
    Ui::MainWindow *ui;
    QGridLayout* layout;

    JoyStickWidget* sliderControl;
    PadControl* padControl;
};

#endif // MAINWINDOW_H
