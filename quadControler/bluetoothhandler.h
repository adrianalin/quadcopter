#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork/QTcpSocket>
#include <QtCore>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothServiceInfo>
#include <QBluetoothSocket>

class BluetoothControler : public QObject
{
    Q_OBJECT

public:
    explicit BluetoothControler(QObject *parent = 0);
    void startClient(const QBluetoothServiceInfo &remoteService);

public slots:
    void startDiscovery();

private slots:
    void readSocket();
    void connected();
    void disconnected();
    void deviceDiscovered(const QBluetoothDeviceInfo &device);

private:
    void getDeviceInfo();
    QBluetoothSocket* socket;
};

#endif // CLIENT_H
