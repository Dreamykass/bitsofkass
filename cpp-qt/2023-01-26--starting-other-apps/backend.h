#ifndef BACKEND_H
#define BACKEND_H

#include <QDebug>
#include <QObject>
#include <QtAndroidExtras/QAndroidIntent>
#include <QtAndroidExtras/QAndroidJniObject>
#include <QtAndroidExtras/QtAndroid>

class Backend : public QObject {
  Q_OBJECT
public slots:

  int backendCheck() {
    static int i = 0;
    return i++;
  }

  void openAppByPkgName(QString pkgName) {
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod(
        "org/qtproject/qt5/android/QtNative", "activity",
        "()Landroid/app/Activity;");

    QAndroidJniObject appContext = activity.callObjectMethod(
        "getApplicationContext", "()Landroid/content/Context;");

    QAndroidJniObject packageManager = appContext.callObjectMethod(
        "getPackageManager", "()Landroid/content/pm/PackageManager;");

    QAndroidJniObject intent = packageManager.callObjectMethod(
        "getLaunchIntentForPackage",
        "(Ljava/lang/String;)Landroid/content/Intent;",
        QAndroidJniObject::fromString(pkgName).object<jstring>());

    QtAndroid::startActivity(intent, 0, 0);
  }

  void openAppByPkgNameWithStrArg(QString pkgName, QString strArg) {
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod(
        "org/qtproject/qt5/android/QtNative", "activity",
        "()Landroid/app/Activity;");

    QAndroidJniObject appContext = activity.callObjectMethod(
        "getApplicationContext", "()Landroid/content/Context;");

    QAndroidJniObject packageManager = appContext.callObjectMethod(
        "getPackageManager", "()Landroid/content/pm/PackageManager;");

    QAndroidJniObject intent = packageManager.callObjectMethod(
        "getLaunchIntentForPackage",
        "(Ljava/lang/String;)Landroid/content/Intent;",
        QAndroidJniObject::fromString(pkgName).object<jstring>());

    packageManager.callObjectMethod(
        "putExtra",
        "(Ljava/lang/String;Ljava/lang/String;)Landroid/content/Intent;",
        QAndroidJniObject::fromString("arg").object<jstring>(),
        QAndroidJniObject::fromString(strArg).object<jstring>());

    QtAndroid::startActivity(intent, 0, 0);
  }
};

// -
// -
// -
// -
// -
// -
// -
// -
// -
// -
// -
// -
// -
// -
// -
// -
// -
// -
// -
// -
// -

#endif // BACKEND_H
