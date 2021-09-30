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
public:
    explicit Device(QObject *parent = nullptr);

signals: // to the backend
    void foundPeripheralSig(QString name, QString address);
    void connectedSig();

public slots: // from the backend
    void startDiscovery()
    {
        qDebug("starting device discovery...");
        current_state = State::Discovery;

        device_discovery_agent = new QBluetoothDeviceDiscoveryAgent();
        device_discovery_agent->setLowEnergyDiscoveryTimeout(5000);
        connect(device_discovery_agent,
                &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
                this,
                &Device::foundPeripheral);
        connect(device_discovery_agent,
                QOverload<QBluetoothDeviceDiscoveryAgent::Error>::of(
                    &QBluetoothDeviceDiscoveryAgent::error),
                this,
                &Device::deviceScanError);
        connect(device_discovery_agent,
                &QBluetoothDeviceDiscoveryAgent::finished,
                this,
                &Device::deviceScanFinished);
        device_discovery_agent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
    }

    void connectToPeripheral(QString name, QString address)
    {
        Q_ASSERT(!found_devices.empty());
        for (auto dev : found_devices)
            if (dev.address().toString() == address && dev.name() == name)
                current_peripheral = dev;
        Q_ASSERT(current_peripheral.address().toString() == address);

        current_state = State::Connecting;

        controller = QLowEnergyController::createCentral(current_peripheral);

        connect(controller, &QLowEnergyController::connected, this, &Device::connected);
        connect(controller,
                QOverload<QLowEnergyController::Error>::of(&QLowEnergyController::error),
                this,
                &Device::connectionError);
        connect(controller, &QLowEnergyController::disconnected, this, &Device::disconnected);
        connect(controller,
                &QLowEnergyController::serviceDiscovered,
                this,
                &Device::serviceDiscovered);
        connect(controller,
                &QLowEnergyController::discoveryFinished,
                this,
                &Device::serviceScanDone);

        controller->connectToDevice();
    }

private slots: // from the bluetooth stuff
    void foundPeripheral(const QBluetoothDeviceInfo &info)
    {
        if (current_state != State::Discovery) {
            qDebug("current_state != State::Discovery");
            qDebug("invalid state? -=-=-=-=-=-=-=-=-");
            return;
        }

        qDebug() << "found device: " << info.name();
        qDebug() << "address: " << info.address();
        if (info.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration) {
            qDebug("and it is low energy");
            found_devices.push_back(info);
            emit foundPeripheralSig(info.name(), info.address().toString());
        }
    }

    void deviceScanError(QBluetoothDeviceDiscoveryAgent::Error error)
    {
        if (current_state != State::Discovery) {
            qDebug("current_state != State::Discovery");
            qDebug("invalid state? -=-=-=-=-=-=-=-=-");
            return;
        }

        qDebug("deviceScanError");
        qDebug("invalid state? -=-=-=-=-=-=-=-=-");
    }

    void deviceScanFinished()
    {
        if (current_state != State::Discovery) {
            qDebug("current_state != State::Discovery");
            qDebug("invalid state? -=-=-=-=-=-=-=-=-");
            return;
        }

        qDebug("finished scan");
    }

    void connected()
    {
        if (current_state != State::Connecting) {
            qDebug("current_state != State::Connecting");
            qDebug("invalid state? -=-=-=-=-=-=-=-=-");
            return;
        }

        connectedSig();

        current_state = State::Connected;

        controller->discoverServices();
    }

    void disconnected()
    {
        if (current_state != State::Connected) {
            qDebug("current_state != State::Connected");
            qDebug("invalid state? -=-=-=-=-=-=-=-=-");
            return;
        }

        qDebug("disconnected?");
        qDebug("invalid state? -=-=-=-=-=-=-=-=-");
    }

    void connectionError(QLowEnergyController::Error err)
    {
        qDebug("connectionError?");
        qDebug("invalid state? -=-=-=-=-=-=-=-=-");
    }

    void serviceDiscovered(const QBluetoothUuid &new_service)
    {
        if (current_state != State::Connected) {
            qDebug("current_state != State::Connected");
            qDebug("invalid state? -=-=-=-=-=-=-=-=-");
            return;
        }

        qDebug() << "serviceDiscovered, uuid: " << new_service.toString();
    }

    void serviceScanDone()
    {
        if (current_state != State::Connected) {
            qDebug("current_state != State::Connected");
            qDebug("invalid state? -=-=-=-=-=-=-=-=-");
            return;
        }

        qDebug("serviceScanDone");
    }

private:
    State::StateType current_state = State::Initial;
    QBluetoothDeviceDiscoveryAgent *device_discovery_agent = nullptr;
    QList<QBluetoothDeviceInfo> found_devices;
    QBluetoothDeviceInfo current_peripheral;
    QLowEnergyController *controller = nullptr;
};

#endif // DEVICE_H
