#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QSlider>
#include <QLabel>

#include "slider.h"
#include "joystickwidget.h"
#include "bluetoothhandler.h"
#include "bluetoothstatus.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    void createActions();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void bluetoothStatusChanged(BluetoothStatus::BtStatus status);
    void onSliderPositionChanged(int y);
    void onPadControlPositionChanged(int x, int y);

private:
    Ui::MainWindow *ui;
    BluetoothStatus m_bluetoothStatus;
    BluetoothHandler* m_bluetoothHandler;
    QMenu* m_scanMenu;
    QAction* m_scanAction;
    QAction* m_disconnectBluetoothAction;
    QLabel* sliderLabel;
    QLabel* padLabel;
    QLabel* statusLabel;
    QGridLayout* layout;

    JoyStickWidget* sliderControl;
    PadControl* padControl;
};

#endif // MAINWINDOW_H
