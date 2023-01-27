package com.mycompany.myapp;

import android.content.pm.PackageManager;
import android.content.Intent;
import android.content.Context;
import android.app.Activity;

public class PackageActivity {
    public static boolean runApplication(String packageName)
    {
        Activity activity = org.qtproject.qt5.android.QtNative.activity();
        PackageManager pm = activity.getApplicationContext().getPackageManager();
        Intent intent = pm.getLaunchIntentForPackage(packageName);
        if (intent != null) {
            activity.startActivity(intent);
            return true;
        } else {
            return false;
        }
    }
}
