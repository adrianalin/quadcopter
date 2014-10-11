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

void BluetoothReadWrite::sendCommand(const QVector<int> &data)
{
    static char charData[3];
    static const int lengthOfData = sizeof(charData) / sizeof(char);

    m_btData = data;
    qDebug()<<"Data to send: " << m_btData[0] << " " << m_btData[1] << " " << m_btData[2];
    charData[0] = static_cast<char>(m_btData[0]);
    charData[1] = static_cast<char>(m_btData[1]);
    charData[2] = static_cast<char>(m_btData[2]);

    if (m_bluetoothStatus->bluetoothStatus() == BluetoothStatus::BtStatus::connected)
        writeSocket(charData, lengthOfData);
    else
        qDebug() << "Could not send data. Disconnected.";
}

void BluetoothReadWrite::writeSocket(const char* message, const int len) const
{
    qDebug() << "Write to socket : " << message;
    if (m_btSocket->write(message, len) != len)
        qDebug() << "Could not send all data";
}

void BluetoothReadWrite::readSocket()
{
    char buf[20];
    memset(buf, 0x00, sizeof(buf));
    m_btSocket->read(buf, sizeof(buf));
    qDebug()<<"Data received : " << buf;
}
