#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork/QTcpSocket>
#include <QtCore>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothServiceInfo>
#include <QBluetoothSocket>
#include "remoteselector.h"

class BluetoothHandler : public QObject
{
    Q_OBJECT

public:
    explicit BluetoothHandler(QObject *parent = 0);
    void connectBluetooth(const QBluetoothServiceInfo &remoteService);
    void writeSocket(const QString &message) const;

public slots:
    void disconnectBluetooth();
    void startDiscovery();

private slots:
    void readSocket();
    void connected();
    void disconnected();

signals:
    void bluetoothDisconnected();
    void bluetoothConnected();

private:
    QBluetoothSocket* m_socket;
    RemoteSelector m_remoteSelector;
};

#endif // CLIENT_H
