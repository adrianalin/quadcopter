#include "bluetoothhandler.h"

BluetoothHandler::BluetoothHandler(BluetoothStatus* bluetoothStatus, QObject *parent) : QObject(parent),
    m_discoveryAgent(new QBluetoothServiceDiscoveryAgent(this)),
    m_bluetoothStatus(bluetoothStatus)
{
    m_socket = NULL;

    connect(m_discoveryAgent, SIGNAL(serviceDiscovered(QBluetoothServiceInfo)),
            this, SLOT(serviceDiscovered(QBluetoothServiceInfo)));
    connect(m_discoveryAgent, SIGNAL(finished()), this, SLOT(discoveryFinished()));
    connect(m_discoveryAgent, SIGNAL(canceled()), this, SLOT(discoveryFinished()));
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
    m_bluetoothStatus->setBluetoothStatus(BluetoothStatus::BtStatus::disconnected);
    if(m_socket){
        delete m_socket;
        m_socket = NULL;
    }
}

void BluetoothHandler::connected()
{
    m_bluetoothStatus->setBluetoothStatus(BluetoothStatus::BtStatus::connected);
    qDebug()<<"connected socket";
    writeSocket("test");
}

void BluetoothHandler::connectBluetooth()
{
    Q_ASSERT(!m_socket);
    if(!m_service.isValid())
        return ;

    // Connect to service
    m_socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
    connect(m_socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    qDebug() << "Create socket";
    m_socket->connectToService(m_service);
    qDebug() << "ConnectToService done";
}

void BluetoothHandler::discoveryFinished()
{
    qDebug()<<Q_FUNC_INFO;
    m_bluetoothStatus->setBluetoothStatus(BluetoothStatus::BtStatus::finishedScanning);
    connectBluetooth();
}

void BluetoothHandler::serviceDiscovered(const QBluetoothServiceInfo &serviceInfo)
{
    //    qDebug() << "Discovered service on"
    //             << serviceInfo.device().name() << serviceInfo.device().address().toString();
    //    qDebug() << "\tService name:" << serviceInfo.serviceName();
    //    qDebug() << "\tDescription:"
    //             << serviceInfo.attribute(QBluetoothServiceInfo::ServiceDescription).toString();
    //    qDebug() << "\tProvider:"
    //             << serviceInfo.attribute(QBluetoothServiceInfo::ServiceProvider).toString();
    //    qDebug() << "\tL2CAP protocol service multiplexer:"
    //             << serviceInfo.protocolServiceMultiplexer();
    //    qDebug() << "\tRFCOMM server channel:" << serviceInfo.serverChannel();
    qDebug()<<Q_FUNC_INFO;

    QString remoteName;
    if (serviceInfo.device().name().isEmpty())
        remoteName = serviceInfo.device().address().toString();
    else
        remoteName = serviceInfo.device().name();

    qDebug()<<"remoteName = "<<remoteName;
    if(!remoteName.contains("HC-06"))
    {
        qWarning()<<"This is not HC-06";
        return;
    }
    Q_ASSERT(serviceInfo.isValid());
    m_service = serviceInfo;
}

void BluetoothHandler::startDiscovery()
{
    qDebug()<<Q_FUNC_INFO;
    getDeviceInfo();

    if (m_discoveryAgent->isActive())
        m_discoveryAgent->stop();

    //    m_discoveryAgent->setUuidFilter(uuid);
    m_discoveryAgent->start();
    m_bluetoothStatus->setBluetoothStatus(BluetoothStatus::BtStatus::scanning);
}

void BluetoothHandler::getDeviceInfo()
{
    QBluetoothLocalDevice localDevice;
    Q_ASSERT(localDevice.isValid());

    localDevice.powerOn();
    qDebug() << "localDevice.name() = " << localDevice.name();
}
