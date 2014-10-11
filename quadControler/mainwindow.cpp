#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , sliderLabel(new QLabel("0", this))
  , padLabel(new QLabel("x=0 y=0", this))
  , statusLabel(new QLabel("Disconnected", this))
  , sliderControl(new JoyStickWidget(this))
  , padControl(new PadControl(this))
  , m_bluetoothRW(new BluetoothReadWrite(&m_bluetoothStatus, this))
  , m_bluetoothHandler(new BluetoothHandler(&m_bluetoothStatus, m_bluetoothRW, this))
  , m_btData()
{
    ui->setupUi(this);
    setCentralWidget(ui->widget);
    layout = new QGridLayout(ui->widget);

    sliderLabel->setMaximumHeight(15);
    padLabel->setMaximumHeight(15);
    statusLabel->setMaximumHeight(15);

    sliderControl->setObjectName("sliderControl");
    padControl->setObjectName("padControl");

    sliderControl->setMaximumWidth(80);
    sliderControl->setStyleSheet("border: 1px solid black; border-radius: 10px;");
    padControl->setStyleSheet("border: 1px solid black; border-radius: 10px;");

    ui->widget->setLayout(layout);
    layout->addWidget(sliderControl, 0, 0);
    layout->addWidget(padControl, 0, 1);
    layout->addWidget(sliderLabel, 1, 0);
    layout->addWidget(padLabel, 1, 1);
    layout->addWidget(statusLabel, 2, 0);

    // joystick related
    connect(sliderControl, &JoyStickWidget::positionChanged, this, &MainWindow::onSliderPositionChanged);
    connect(padControl, &PadControl::positionChanged, this, &MainWindow::onPadControlPositionChanged);

    // bluetooth related
    connect(&m_bluetoothStatus, &BluetoothStatus::statusChanged, this, &MainWindow::bluetoothStatusChanged);

    m_scanMenu = menuBar()->addMenu("Settings");
    createActions();

    m_btData.fill(0, 3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSliderPositionChanged(int y)
{
    sliderLabel->setText(QString::number(y));
    Q_ASSERT(y<255);
    m_btData[0] = y;
    m_bluetoothRW->sendCommand(m_btData);
}

void MainWindow::onPadControlPositionChanged(int x, int y)
{
    padLabel->setText("x=" + QString::number(x) + " y=" + QString::number(y));
    Q_ASSERT(x<255);
    Q_ASSERT(y<255);
    m_btData[1] = x;
    m_btData[2] = y;
    m_bluetoothRW->sendCommand(m_btData);
}

void MainWindow::createActions()
{
    m_scanAction = new QAction("Scan", this);
    m_disconnectBluetoothAction = new QAction("Disconnect", this);

    connect(m_scanAction, &QAction::triggered, m_bluetoothHandler, &BluetoothHandler::startDiscovery);
    connect(m_disconnectBluetoothAction, &QAction::triggered, m_bluetoothHandler, &BluetoothHandler::disconnectBluetooth);
    m_scanMenu->addAction(m_scanAction);
}

void MainWindow::bluetoothStatusChanged(BluetoothStatus::BtStatus status)
{
    switch(status)
    {
    case BluetoothStatus::BtStatus::connected:
        statusLabel->setText("Connected");
        m_scanMenu->removeAction(m_scanAction);
        m_scanMenu->addAction(m_disconnectBluetoothAction);
        break;
    case BluetoothStatus::BtStatus::disconnected:
        statusLabel->setText("Disconnected");
        m_scanMenu->removeAction(m_disconnectBluetoothAction);
        m_scanMenu->addAction(m_scanAction);
        break;
    case BluetoothStatus::BtStatus::scanning:
        statusLabel->setText("Scanning...");
        break;
    case BluetoothStatus::BtStatus::finishedScanning:
        statusLabel->setText("Finished scaning");
        break;
    default:
        break ;
    }
}
