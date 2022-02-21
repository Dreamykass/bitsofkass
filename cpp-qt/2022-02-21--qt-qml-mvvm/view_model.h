#ifndef VIEW_MODEL_H
#define VIEW_MODEL_H

#include <variant>
#include <QDebug>
#include <QObject>

class MvBoot : public QObject
{
    Q_OBJECT
public:
    inline static const QString view_url = "BootView.qml";
};

struct MvOosScreen : public QObject
{
    Q_OBJECT
public:
    inline static const QString view_url = "OosScreenView.qml";
};

struct MvLoginScreen : public QObject
{
    Q_OBJECT
public:
    inline static const QString view_url = "LoginScreen.qml";
    void connectToView(QObject *view_)
    {
        connect(view_, SIGNAL(setUsername(QString)), this, SLOT(onSetUsername(QString)));
    }

public slots:
    void onSetUsername(QString username_)
    {
        qDebug() << "onSetUsername: " << username_;
        this->username = username_;
    }

public:
    QString username;
};

using MvVariant = std::variant<MvBoot, MvOosScreen, MvLoginScreen>;

inline QString viewUrlFromMvVariant(const MvVariant &mv_var_)
{
    return std::visit([](auto &mv) { return mv.view_url; }, mv_var_);
}

#endif // VIEW_MODEL_H
