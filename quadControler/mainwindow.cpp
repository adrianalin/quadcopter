#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    bluetoothClient = new BluetoothControler(this);

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

    connect(sliderControl, SIGNAL(positionChanged(int,int,int,int)), this, SLOT(positionChanged(int,int,int,int)));
    connect(padControl, SIGNAL(positionChanged(int,int,int,int)), this, SLOT(positionChanged(int,int,int,int)));
    connect(padControl, SIGNAL(mouseReleased()), this, SLOT(resetCoordinates()));

    createActions();
    createMenus();
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
    scanAction = new QAction("Scan", this);
    scanAction->setStatusTip("Scan for bluetooth devices");

    connect(scanAction, SIGNAL(triggered()), bluetoothClient, SLOT(startDiscovery()));
}

void MainWindow::createMenus()
{
    scanMenu = menuBar()->addMenu("Settings");
    scanMenu->addAction(scanAction);
}
