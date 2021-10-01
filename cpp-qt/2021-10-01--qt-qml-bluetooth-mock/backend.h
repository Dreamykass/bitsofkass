#ifndef BACKEND_H
#define BACKEND_H

#include "device.h"
#include "state.h"
#include <QDebug>
#include <QObject>

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(Device &device_, QObject &qml_, QObject *parent = nullptr)
        : QObject(parent), qml(qml_), device(device_)
    {
        qDebug("backend constructed");
    }

public slots: // from qml
    State::StateType getCurrentState() { return current_state; }
    QString getCurrentStateStr() { return stateToString(current_state); }

    /// user clicked the "start device discovery" button
    void startDiscovery()
    {
        changeState(State::Discovery);
        device.startDiscovery();
    }

    /// user has selected a peripheral and wants to connect to it
    /// this changes state to Connecting,
    /// tells qml to change page, and tells the device to start connecting
    void selectPeripheral(QString name, QString address)
    {
        qDebug() << "selected peripheral: " << name << address;
        changeState(State::Connecting);
        QMetaObject::invokeMethod(&qml, "connecting");
        device.connectToPeripheral(name, address);
    }

public slots: // from the device
    /// device is searching for peripherals, and has found one
    /// this calls qml to add a peripheral to list
    void foundPeripheral(QString name, QString address)
    {
        qDebug() << "foundPeripheral, invoking qml";
        QMetaObject::invokeMethod(qml.findChild<QObject *>("initial_page"),
                                  "foundPeripheral",
                                  Q_ARG(QVariant, name),
                                  Q_ARG(QVariant, address));
    }

    void connected()
    {
        qDebug() << "connected to peripheral";
        changeState(State::Connected);
        QMetaObject::invokeMethod(&qml, "connected");
    }

private:
    void changeState(State::StateType new_state)
    {
        current_state = new_state;
        qDebug() << "changed state to: " << stateToString(new_state);
    }

private:
    State::StateType current_state = State::Initial;
    Device &device;
    QObject &qml;
};

#endif // BACKEND_H
