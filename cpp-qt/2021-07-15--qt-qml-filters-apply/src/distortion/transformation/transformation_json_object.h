#ifndef CREATEQJSONOBJECT_H
#define CREATEQJSONOBJECT_H

#include <QString>
#include <QJsonObject>


//int float double
template<typename T>
QJsonObject createQJsonObject(QString type,
                          QString name,
                          T min,
                          T max,
                          T value){
    return QJsonObject{
        { "type", type },
        { "name", name },
        { "value", value },
        { "min", min },
        { "max", max } };
}

#endif // CREATEQJSONOBJECT_H
