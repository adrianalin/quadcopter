#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->widget);

    layout = new QGridLayout(ui->widget);
    sliderControl = new JoyStickWidget(this);
    padControl = new PadControl(this);
    sliderLabel = new  QLabel("0", this);
    padLabel = new QLabel("x=0 y=0",this);
    statusLabel = new QLabel("Disconnected",this);
    m_bluetoothHandler = new BluetoothHandler(&m_bluetoothStatus, this);

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
    connect(sliderControl, SIGNAL(positionChanged(int,int,int,int)), this, SLOT(positionChanged(int,int,int,int)));
    connect(padControl, SIGNAL(positionChanged(int,int,int,int)), this, SLOT(positionChanged(int,int,int,int)));
    connect(padControl, SIGNAL(mouseReleased()), this, SLOT(resetCoordinates()));

    // bluetooth related
    connect(&m_bluetoothStatus, &BluetoothStatus::statusChanged, this, &MainWindow::bluetoothStatusChanged);

    m_scanMenu = menuBar()->addMenu("Settings");
    createActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::positionChanged(int x, int y, int width, int height)
{
    int xCoord, yCoord;


    if(QObject::sender()->objectName() == "sliderControl")
    {
        sliderLabel->setText(QString::number(y));
    }
    else if(QObject::sender()->objectName() == QString("padControl"))
    {
        xCoord = x-width/2;
        yCoord = y-height/2;
        padLabel->setText("x=" + QString::number(xCoord) + " y=" + QString::number(yCoord));
    }
}

void MainWindow::resetCoordinates(){
    padLabel->setText("x=0 y=0");
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
