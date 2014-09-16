#include "bluetoothstatus.h"

BluetoothStatus::BluetoothStatus(QObject *parent): QObject(parent)
{
}

void BluetoothStatus::setBluetoothStatus(BtStatus status)
{
    if (m_bluetoothStatus == status)
        return;
    m_bluetoothStatus = status;
    emit statusChanged(m_bluetoothStatus);
}
