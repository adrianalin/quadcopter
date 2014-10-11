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
    void sendCommand(const QVector<int> &data);

private slots:
    void connectedToService();
    void disconnectedFromService();
    void writeSocket(const char* message, const int len) const;
    void readSocket();

private:
    QBluetoothSocket* m_btSocket;
    BluetoothStatus* m_bluetoothStatus;
    QVector<int> m_btData;
};

#endif // BLUETOOTHREADWRITE_H
