#include "bluetoothreadwrite.h"

BluetoothReadWrite::BluetoothReadWrite(BluetoothStatus *status, QObject *parent) :
    QObject(parent),
    m_btSocket(new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this)),
    m_bluetoothStatus(status)
{
    connect(m_btSocket, SIGNAL(connected()), this, SLOT(connectedToService()));
    connect(m_btSocket, SIGNAL(disconnected()), this, SLOT(disconnectedFromService()));
    connect(m_btSocket, &QBluetoothSocket::readyRead, this, &BluetoothReadWrite::readSocket);
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

void BluetoothReadWrite::encodeMessage(const QVector<int> &data)
{
    /* i - integer
     * parameter will be encoded as:
     ** i<numberLength><paramNumber>
     *
     * ex. data[3] = {12, 124, -12}
     * 12 -> i212
     * 124 -> i3124
     * -12 -> i3-12
     * message = i212i3124i3-12s -> total length is 15
     *
     * l- length
     * final message will be encoded as:
     ** l<numberLength><messageLengthNumber>
     * final message will be -> l215i212i3124i3-12
     */
    Q_ASSERT(data.length() == 3);

    static QString message, paramString, messageLength;
    message.clear();

    paramString = QString::number(data[0]);
    message = message + "i" + QString::number(paramString.length()) + paramString;
    paramString = QString::number(data[1]);
    message = message + "i" + QString::number(paramString.length()) + paramString;
    paramString = QString::number(data[2]);
    message = message + "i" + QString::number(paramString.length()) + paramString + "s";

    message.prepend(QString::number(message.length()));

    qDebug() << "message = " << message;

    if (m_bluetoothStatus->bluetoothStatus() == BluetoothStatus::BtStatus::connected)
        writeSocket(message.toUtf8(), message.length());
    else
        qDebug() << "Could not send data. Disconnected.";
}

void BluetoothReadWrite::writeSocket(const char* message, const int len)
{
    if (m_btSocket->write(message, len) != len)
        qDebug() << "Could not send all data";
}

void BluetoothReadWrite::readSocket()
{
    char buf[20];
    memset(buf, 0x00, sizeof(buf));
    m_btSocket->readLine(buf, sizeof(buf));
    qDebug()<<"Data received : " << buf;
}
