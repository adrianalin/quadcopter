#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork/QTcpSocket>
#include <QtCore>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothServiceInfo>
#include <QBluetoothSocket>
#include <QBluetoothServiceDiscoveryAgent>

#include "bluetoothstatus.h"

class BluetoothStatus;

class BluetoothHandler : public QObject
{
    Q_OBJECT

public:
    explicit BluetoothHandler(BluetoothStatus* bluetoothStatus, QObject *parent = 0);
    void connectBluetooth();
    void writeSocket(const QString &message) const;

public slots:
    void disconnectBluetooth();
    void startDiscovery();

private slots:
    void readSocket();
    void connected();
    void disconnected();
    void serviceDiscovered(const QBluetoothServiceInfo &serviceInfo);
    void discoveryFinished();

private:
    void getDeviceInfo();

    QBluetoothServiceDiscoveryAgent *m_discoveryAgent;
    BluetoothStatus* m_bluetoothStatus;
    QBluetoothServiceInfo m_service;
    QBluetoothSocket* m_socket;
};

#endif // CLIENT_H
