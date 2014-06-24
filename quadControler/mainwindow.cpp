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
    bluetoothClient = new BluetoothHandler(this);

    sliderLabel->setMaximumHeight(20);
    padLabel->setMaximumHeight(20);

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

    // joystick related
    connect(sliderControl, SIGNAL(positionChanged(int,int,int,int)), this, SLOT(positionChanged(int,int,int,int)));
    connect(padControl, SIGNAL(positionChanged(int,int,int,int)), this, SLOT(positionChanged(int,int,int,int)));
    connect(padControl, SIGNAL(mouseReleased()), this, SLOT(resetCoordinates()));

    // bluetooth related
    connect(bluetoothClient, SIGNAL(bluetoothConnected()), this, SLOT(bluetoothConnected()));
    connect(bluetoothClient, SIGNAL(bluetoothDisconnected()), this, SLOT(bluetoothDisconnected()));

    m_scanMenu = menuBar()->addMenu("Settings");
    createActions();
    bluetoothDisconnectedMenu();
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
    m_disconnectBluetooth = new QAction("Disconnect", this);

    connect(m_scanAction, SIGNAL(triggered()), bluetoothClient, SLOT(startDiscovery()));
    connect(m_disconnectBluetooth, SIGNAL(triggered()), bluetoothClient, SLOT(disconnectBluetooth()));
}

void MainWindow::bluetoothConnected() {
    QMessageBox::warning(this, tr("QuadControler"),
                         "Connected to HC-06!",
                         QMessageBox::Ok);
    bluetoothConnectedMenu();
}

void MainWindow::bluetoothDisconnected() {
    QMessageBox::warning(this, tr("QuadControler"),
                         "Disconnected from HC-06!",
                         QMessageBox::Ok);
    bluetoothDisconnectedMenu();
}

void MainWindow::bluetoothDisconnectedMenu() {
    m_scanMenu->removeAction(m_disconnectBluetooth);
    m_scanMenu->addAction(m_scanAction);
}

void MainWindow::bluetoothConnectedMenu() {
    m_scanMenu->removeAction(m_scanAction);
    m_scanMenu->addAction(m_disconnectBluetooth);
}
