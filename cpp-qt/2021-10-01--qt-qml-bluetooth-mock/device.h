#ifndef DEVICE_H
#define DEVICE_H

#include "state.h"
#include <QDebug>
#include <QObject>
#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>
#include <QtBluetooth/QBluetoothServiceDiscoveryAgent>
#include <QtBluetooth/QBluetoothServiceInfo>
#include <QtBluetooth/QLowEnergyController>

class Device : public QObject
{
    Q_OBJECT

signals: // to the backend
    //    virtual void foundPeripheralSig(QString name, QString address) = 0;
    //    virtual void connectedSig() = 0;

public slots: // from the backend
    virtual void startDiscovery() = 0;

    virtual void connectToPeripheral(QString name, QString address) = 0;

private slots: // from the bluetooth stuff
               // **** **** //

private:
    // **** **** //
};

#endif // DEVICE_H
