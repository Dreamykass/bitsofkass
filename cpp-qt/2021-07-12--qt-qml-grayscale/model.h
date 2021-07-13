#ifndef MODEL_H
#define MODEL_H

#include "image_provider.h"
#include <QDebug>
#include <QMetaObject>

class Model : public QObject
{
    Q_OBJECT

public:
    explicit Model(QObject *parent = 0, ImageProvider *prov_ = 0)
    {
        qml = parent;
        prov = prov_;
    }

public slots:
    void buttonOkOnClicked()
    {
        qDebug("ok");

        auto *text1 = qml->findChild<QObject *>("text1");
        if (text1)
            text1->setProperty("text", text1->property("text").toString() + " 9");
    }
    void buttonCancelOnClicked()
    {
        qDebug("cancel");

        QMetaObject::invokeMethod(qml,
                                  "text2SetText",
                                  QGenericReturnArgument(),
                                  Q_ARG(QVariant, QString("new text")));
    }
    void loadImages(const QString &filename)
    {
        //        QMetaObject::invokeMethod((QObject *) prov,
        //                                  "loadImages",
        //                                  Qt::QueuedConnection,
        //                                  Q_ARG(QString, filename));
        prov->loadImages(filename);
    }

private:
    QObject *qml;
    ImageProvider *prov;
};

#endif // MODEL_H
