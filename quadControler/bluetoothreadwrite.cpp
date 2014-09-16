#include "bluetoothreadwrite.h"

BluetoothReadWrite::BluetoothReadWrite(BluetoothStatus *status, QObject *parent) :
    QObject(parent),
    m_btSocket(new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this)),
    m_bluetoothStatus(status)
{
    connect(m_btSocket, SIGNAL(connected()), this, SLOT(connectedToService()));
    connect(m_btSocket, SIGNAL(disconnected()), this, SLOT(disconnectedFromService()));
    connect(m_btSocket, SIGNAL(readyRead()), this, SLOT(readSocket()));
}

void BluetoothReadWrite::connectToService(QBluetoothServiceInfo service)
{
    Q_ASSERT(m_btSocket);
    m_btSocket->connectToService(service);
}

void BluetoothReadWrite::connectedToService()
{
    qDebug()<<Q_FUNC_INFO;
    m_bluetoothStatus->setBluetoothStatus(BluetoothStatus::BtStatus::connected);
    writeSocket(QStringLiteral("test"));
}

void BluetoothReadWrite::disconnectFromService()
{
    qDebug()<<Q_FUNC_INFO;
    Q_ASSERT(m_btSocket);
    m_btSocket->disconnectFromService();
}

void BluetoothReadWrite::disconnectedFromService()
{
    qDebug()<<Q_FUNC_INFO;
    m_bluetoothStatus->setBluetoothStatus(BluetoothStatus::BtStatus::disconnected);
}

void BluetoothReadWrite::writeSocket(const QString &message) const
{
    QByteArray text = message.toUtf8() + '\n';
    qDebug() << m_btSocket->write(text) << " bytes sent";
}

void BluetoothReadWrite::readSocket()
{
    char buf[20];
    memset(buf, 0x00, sizeof(buf));
    m_btSocket->read(buf, sizeof(buf));
    qDebug()<<"Data received : " << buf;
}
