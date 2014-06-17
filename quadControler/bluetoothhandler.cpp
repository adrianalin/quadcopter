#include "bluetoothhandler.h"

BluetoothControler::BluetoothControler(QObject *parent) : QObject(parent)
{

}

void BluetoothControler::getDeviceInfo()
{
    QBluetoothLocalDevice localDevice;
    QString localDeviceName;

    // Check if Bluetooth is available on this device
    if (localDevice.isValid()) {

        // Turn Bluetooth on
        localDevice.powerOn();

        // Read local device name
        localDeviceName = localDevice.name();
        qDebug()<<"localDevice.name() = "<<localDeviceName;

        // Make it visible to others
        localDevice.setHostMode(QBluetoothLocalDevice::HostDiscoverable);
    } else {
        qDebug()<<"localDevice.isValid() returned false; no bluetooth device found";
    }
}

// In your local slot, read information about the found devices
void BluetoothControler::deviceDiscovered(const QBluetoothDeviceInfo &device)
{
    qDebug() << "Found new device:" << device.name() << '(' << device.address().toString() << ')';
}

void BluetoothControler::startDiscovery()
{
    getDeviceInfo();

    // Create a discovery agent and connect to its signals
    QBluetoothDeviceDiscoveryAgent *discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
            this, SLOT(deviceDiscovered(QBluetoothDeviceInfo)));

    // Start a discovery
    discoveryAgent->start();
}

void BluetoothControler::readSocket()
{
    qDebug()<<"read socket";
}

void BluetoothControler::connected()
{
    qDebug()<<"connected socket";
}

void BluetoothControler::disconnected()
{
    qDebug()<<"disconnected socket";
}

void BluetoothControler::startClient(const QBluetoothServiceInfo &remoteService)
{
    if (socket)
        return;

    // Connect to service
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    qDebug() << "Create socket";
    socket->connectToService(remoteService);
    qDebug() << "ConnectToService done";

    connect(socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
}
