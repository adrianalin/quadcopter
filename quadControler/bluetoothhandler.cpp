#include <QBluetoothLocalDevice>
#include "bluetoothhandler.h"

BluetoothHandler::BluetoothHandler(BluetoothStatus *bluetoothStatus, BluetoothReadWrite *btRW, QObject *parent) : QObject(parent),
    m_discoveryAgent(new QBluetoothServiceDiscoveryAgent(this)),
    m_bluetoothStatus(bluetoothStatus),
    m_bluetoothRW(btRW)
{
    // bluetooth discovery signals
    connect(m_discoveryAgent, SIGNAL(serviceDiscovered(QBluetoothServiceInfo)),
            this, SLOT(serviceDiscovered(QBluetoothServiceInfo)));
    connect(m_discoveryAgent, SIGNAL(finished()), this, SLOT(discoveryFinished()));
    connect(m_discoveryAgent, SIGNAL(canceled()), this, SLOT(discoveryFinished()));
}

void BluetoothHandler::disconnectBluetooth()
{
    m_bluetoothRW->disconnectFromService();
}

void BluetoothHandler::discoveryFinished()
{
    qDebug()<<Q_FUNC_INFO;
    m_bluetoothStatus->setBluetoothStatus(BluetoothStatus::BtStatus::finishedScanning);
    if (!m_service.isValid())
    {
        qWarning()<<"Service is not valid; cancel connection;";
        return ;
    }
    m_bluetoothRW->connectToService(m_service);
}

void BluetoothHandler::serviceDiscovered(const QBluetoothServiceInfo &serviceInfo)
{
    qDebug()<<Q_FUNC_INFO;
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

    QString remoteName;
    if (serviceInfo.device().name().isEmpty())
        remoteName = serviceInfo.device().address().toString();
    else
        remoteName = serviceInfo.device().name();

    qDebug() << "remoteName = " << remoteName;
    if (!remoteName.contains("aerial"))
    {
        qWarning()<<"This is not aerial";
        return;
    }
    Q_ASSERT (serviceInfo.isValid());
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
    qDebug()<<Q_FUNC_INFO;
    QBluetoothLocalDevice localDevice;
    localDevice.powerOn();

    Q_ASSERT(localDevice.isValid());
    qDebug() << "localDevice.name() = " << localDevice.name();
}
