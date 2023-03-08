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

  /// Returns launch intent for installed package,
  /// or if not installed returns invalid val.
  /// Check via `.isValid()`.
  QAndroidJniObject getLaunchIntentForApp(QString pkgName) {
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod(
        "org/qtproject/qt5/android/QtNative", "activity",
        "()Landroid/app/Activity;");

    QAndroidJniObject appContext = activity.callObjectMethod(
        "getApplicationContext", "()Landroid/content/Context;");

    QAndroidJniObject packageManager = appContext.callObjectMethod(
        "getPackageManager", "()Landroid/content/pm/PackageManager;");

    return packageManager.callObjectMethod(
        "getLaunchIntentForPackage",
        "(Ljava/lang/String;)Landroid/content/Intent;",
        QAndroidJniObject::fromString(pkgName).object<jstring>());
  }

  void isAppInstalled(QString pkgName) {
    QAndroidJniObject intent = getLaunchIntentForApp(pkgName);

    if (!intent.isValid()) {
      qDebug() << "app is not installed";
    } else {
      qDebug() << "app is installed";
    }
  }

  void openPlayStoreForApp(QString pkgName) {
    QAndroidJniObject url =
        QAndroidJniObject::fromString("market://details?id=" + pkgName);

    QAndroidJniObject intent = QAndroidJniObject::callStaticObjectMethod(
        "android/content/Intent", "parseUri",
        "(Ljava/lang/String;I)Landroid/content/Intent;", url.object<jstring>(),
        0x00000001);
    // 0x00000001 == URI_INTENT_SCHEME

    QtAndroid::startActivity(intent, 0, 0);
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

  void openAppByPkgNameOrPlayStore(QString pkgName) {
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

    if (!intent.isValid()) {
      QAndroidJniObject url =
          QAndroidJniObject::fromString("market://details?id=" + pkgName);

      intent = QAndroidJniObject::callStaticObjectMethod(
          "android/content/Intent", "parseUri",
          "(Ljava/lang/String;I)Landroid/content/Intent;",
          url.object<jstring>(), 0x00000001);
      // 0x00000001 == URI_INTENT_SCHEME
    }

    QtAndroid::startActivity(intent, 0, 0);
  }

  void openAppByPkgNameWithStrArg(QString pkgName, QString strArg) {
    QAndroidJniObject intent = getLaunchIntentForApp(pkgName);

    intent.callObjectMethod(
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
