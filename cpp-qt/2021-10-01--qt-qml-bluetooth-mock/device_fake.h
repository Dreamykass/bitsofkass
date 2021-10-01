#ifndef DEVICE_FAKE_H
#define DEVICE_FAKE_H

#include "device.h"
#include "state.h"
#include <QDebug>
#include <QObject>
#include <QTimer>
#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>
#include <QtBluetooth/QBluetoothServiceDiscoveryAgent>
#include <QtBluetooth/QBluetoothServiceInfo>
#include <QtBluetooth/QLowEnergyController>

class FakeDevice : public Device
{
    Q_OBJECT
public:
    explicit FakeDevice(QObject *parent = nullptr){};

signals: // to the backend
    void foundPeripheralSig(QString name, QString address);
    void connectedSig();

public slots: // from the backend
    void startDiscovery()
    {
        qDebug("starting device discovery...");
        current_state = State::Discovery;

        foundPeripheralSig("Fake Device", "0123-4567-89ab-cdef");
    }

    void connectToPeripheral(QString name, QString address)
    {
        current_state = State::Connecting;

        QTimer::singleShot(2000, this, &FakeDevice::connected);
    }

private slots: // from the fake timer stuffs
    void connected()
    {
        current_state = State::Connected;
        connectedSig();
    }

private:
    State::StateType current_state = State::Initial;
};

#endif // DEVICE_FAKE_H
