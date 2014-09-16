#ifndef BLUETOOTHREADWRITE_H
#define BLUETOOTHREADWRITE_H

#include <QObject>
#include <QBluetoothSocket>
#include <QBluetoothServiceInfo>

#include "bluetoothstatus.h"

class BluetoothReadWrite : public QObject
{
    Q_OBJECT

public:
    explicit BluetoothReadWrite(BluetoothStatus* status, QObject* parent=0);
    void connectToService(QBluetoothServiceInfo service);
    void disconnectFromService();
    void writeSocket(const QString &message) const;

private slots:
    void connectedToService();
    void disconnectedFromService();
    void readSocket();

private:
    QBluetoothSocket* m_btSocket;
    BluetoothStatus* m_bluetoothStatus;
};

#endif // BLUETOOTHREADWRITE_H
