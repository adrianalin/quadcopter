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
    void encodeMessage(const QVector<int> &data);

private slots:
    void connectedToService();
    void disconnectedFromService();
    void writeSocket(const char* message, const int len);
    void readSocket();

private:
    QBluetoothSocket* m_btSocket;
    BluetoothStatus* m_bluetoothStatus;
};

#endif // BLUETOOTHREADWRITE_H
