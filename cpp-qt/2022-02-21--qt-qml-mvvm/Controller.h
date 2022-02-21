#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "view_model.h"
#include <QObject>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *qml_main_window_, QObject *parent = nullptr);

public:
    QObject *getCurrentView();

public slots:
    void finishedBooting();
    void statusChecksOk();

    void onClickedLogin();

signals:

private:
    QObject *qml_main_window = {};
    MvVariant mv_variant = {};
};

#endif // CONTROLLER_H
