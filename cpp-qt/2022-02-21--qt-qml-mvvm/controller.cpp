#include "controller.h"
#include "view_model.h"
#include <QDebug>
#include <QTimer>

Controller::Controller(QObject *qml_main_window_, QObject *parent) : QObject(parent)
{
    this->qml_main_window = qml_main_window_;

    this->mv_variant.emplace<MvBoot>();
    const auto view_url = viewUrlFromMvVariant(this->mv_variant);
    QMetaObject::invokeMethod(this->qml_main_window, "setView", Q_ARG(QVariant, view_url));

    QTimer::singleShot(200, this, &Controller::finishedBooting);
}

QObject *Controller::getCurrentView()
{
    QVariant view = {};
    QMetaObject::invokeMethod(this->qml_main_window, "getView", Q_RETURN_ARG(QVariant, view));
    return view.value<QObject *>();
}

void Controller::finishedBooting()
{
    this->mv_variant.emplace<MvOosScreen>();
    const auto view_url = viewUrlFromMvVariant(this->mv_variant);
    QMetaObject::invokeMethod(this->qml_main_window, "setView", Q_ARG(QVariant, view_url));

    QTimer::singleShot(200, this, &Controller::statusChecksOk);
}

void Controller::statusChecksOk()
{
    this->mv_variant.emplace<MvLoginScreen>();
    const auto view_url = viewUrlFromMvVariant(this->mv_variant);
    QMetaObject::invokeMethod(this->qml_main_window, "setView", Q_ARG(QVariant, view_url));

    std::get<MvLoginScreen>(this->mv_variant).connectToView(this->getCurrentView());
    connect(this->getCurrentView(), SIGNAL(clickedLogin()), this, SLOT(onClickedLogin()));
}

void Controller::onClickedLogin()
{
    auto *mv_maybe = std::get_if<MvLoginScreen>(&this->mv_variant);
    Q_ASSERT(mv_maybe);
    auto &mv = *mv_maybe;

    qDebug() << "checking username: " << mv.username;
}
