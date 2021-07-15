#ifndef BACKEND_H
#define BACKEND_H

#include "distortion.h"
#include <QJsonArray>
#include <QObject>

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);

public slots:
    QJsonArray getDistortionDescriptions();

private:
};

#endif // BACKEND_H
