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

    explicit BluetoothStatus(QObject* parent = 0);
    void setBluetoothStatus(BtStatus status);
    BtStatus bluetoothStatus();

signals:
    void statusChanged(BluetoothStatus::BtStatus);

private:
    BluetoothStatus::BtStatus m_bluetoothStatus = BtStatus::disconnected;
};

#endif // BLUETOOTHSTATUS_H
