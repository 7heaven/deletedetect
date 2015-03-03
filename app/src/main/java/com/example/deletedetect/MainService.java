package com.example.deletedetect;

import android.app.ActivityManager;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageManager;
import android.os.Handler;
import android.os.IBinder;
import android.util.Log;

import java.util.List;

/**
 * Created by caifangmao on 15/3/3.
 */
public class MainService extends Service{

    private PackageManager packageManager;
    private ActivityManager activityManager;


    private UninstallIntentReceiver receiver;

    private String previousActivity = "";

    private Handler handler = new Handler();
    private Runnable runnable = new Runnable(){
        @Override
        public void run(){
            List<ActivityManager.RunningTaskInfo> taskInfos = activityManager.getRunningTasks(1);
            String activityName = taskInfos.get(0).topActivity.getClassName();

            if(!activityName.equals(previousActivity)){
                Log.d("activity:", activityName);

                previousActivity = activityName;
            }


            handler.postDelayed(this, 500L);
        }
    };

    @Override
    public IBinder onBind(Intent intent){
        return null;
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId){

        packageManager = this.getPackageManager();
        activityManager = (ActivityManager) this.getSystemService(Context.ACTIVITY_SERVICE);

        handler.post(runnable);

        IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction("android.intent.action.QUERY_PACKAGE_RESTART");
        intentFilter.addDataScheme("package");
        intentFilter.setPriority(0);

        this.registerReceiver(receiver, intentFilter);

        return super.onStartCommand(intent, flags, startId);
    }

    @Override
    public void onDestroy(){
        this.unregisterReceiver(receiver);
        super.onDestroy();
    }
}
