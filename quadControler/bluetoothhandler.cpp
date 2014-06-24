#include "bluetoothhandler.h"

BluetoothHandler::BluetoothHandler(QObject *parent) : QObject(parent)
{
    m_socket = NULL;
}

void BluetoothHandler::startDiscovery()
{
    m_remoteSelector.startDiscovery();
    if (m_remoteSelector.exec() == QDialog::Accepted) {
        QBluetoothServiceInfo service = m_remoteSelector.service();

        qDebug() << "Connecting to service 2" << service.serviceName()
                 << "on" << service.device().name();

        connectBluetooth(service);
    }
}

void BluetoothHandler::writeSocket(const QString &message) const
{
    QByteArray text = message.toUtf8() + '\n';
    qDebug() << m_socket->write(text) << " bytes sent";
}

void BluetoothHandler::readSocket()
{
    char buf[20];
    memset(buf, 0x00, sizeof(buf));
    qDebug()<<"readSocket";

    m_socket->read(buf, sizeof(buf));
    qDebug()<<"Data received : " << buf;
}

void BluetoothHandler::disconnectBluetooth() {
    qDebug()<<"disconnectBluetooth";
    if(m_socket) {
        m_socket->disconnectFromService();
    }
}

void BluetoothHandler::disconnected()
{
    qDebug()<<"disconnected";
    if(m_socket){
        delete m_socket;
        m_socket = NULL;
    }
    emit bluetoothDisconnected();
}

void BluetoothHandler::connectBluetooth(const QBluetoothServiceInfo &remoteService)
{
    if (m_socket)
        return;

    // Connect to service
    m_socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
    connect(m_socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    qDebug() << "Create socket";
    m_socket->connectToService(remoteService);
    qDebug() << "ConnectToService done";
}

void BluetoothHandler::connected()
{
    qDebug()<<"connected socket";
    writeSocket("test");
    emit bluetoothConnected();
}
