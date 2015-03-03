package com.example.deletedetect;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

/**
 * Created by caifangmao on 15/3/3.
 */
public class UninstallIntentReceiver extends BroadcastReceiver {

    @Override
    public void onReceive(Context context, Intent intent){
        String[] packageNames = intent.getStringArrayExtra("android.intent.extra.PACKAGES");

        if(packageNames != null){
            for(String name : packageNames){
                if(name != null){
                    Log.d("intent", name);
                    if(name.equals(context.getPackageName())){
                        new ListenActivities(context).start();
                    }
                }
            }
        }
    }
}
