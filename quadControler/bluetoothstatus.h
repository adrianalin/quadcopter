#ifndef BLUETOOTHSTATUS_H
#define BLUETOOTHSTATUS_H

#include <QObject>

class BluetoothStatus : public QObject
{
    Q_OBJECT
public:
    enum class BtStatus {
        scanning,
        connected,
        finishedScanning,
        disconnected
    };

    BluetoothStatus();
    void setBluetoothStatus(BtStatus status);

signals:
    void statusChanged(BluetoothStatus::BtStatus);

private:
    BluetoothStatus::BtStatus m_bluetoothStatus = BtStatus::disconnected;
};

#endif // BLUETOOTHSTATUS_H
