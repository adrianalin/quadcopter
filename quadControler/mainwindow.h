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
#include "bluetoothreadwrite.h"

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
    QMenu* m_scanMenu;
    QAction* m_scanAction;
    QAction* m_disconnectBluetoothAction;
    QLabel* sliderLabel;
    QLabel* padLabel;
    QLabel* statusLabel;
    QGridLayout* layout;

    JoyStickWidget* sliderControl;
    PadControl* padControl;

    BluetoothStatus m_bluetoothStatus;
    BluetoothReadWrite* m_bluetoothRW;
    BluetoothHandler* m_bluetoothHandler;

    QVector<int> m_btData;
};

#endif // MAINWINDOW_H
