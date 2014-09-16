#ifndef CLIENT_H
#define CLIENT_H

#include <QtCore>
#include <QBluetoothServiceDiscoveryAgent>
#include <QBluetoothServiceInfo>
#include "bluetoothreadwrite.h"

#include "bluetoothstatus.h"

class BluetoothHandler : public QObject
{
    Q_OBJECT

public:
    explicit BluetoothHandler(BluetoothStatus* bluetoothStatus, QObject *parent = 0);

public slots:
    void disconnectBluetooth();
    void startDiscovery();

private slots:
    void serviceDiscovered(const QBluetoothServiceInfo &serviceInfo);
    void discoveryFinished();

private:
    void getDeviceInfo();

    QBluetoothServiceDiscoveryAgent *m_discoveryAgent;
    BluetoothStatus* m_bluetoothStatus;
    QBluetoothServiceInfo m_service;
    BluetoothReadWrite* m_bluetoothrw;
};

#endif // CLIENT_H
