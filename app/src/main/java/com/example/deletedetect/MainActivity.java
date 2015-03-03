package com.example.deletedetect;

import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.os.UserManager;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;


public class MainActivity extends ActionBarActivity {

    private int processPid = -1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        startService(new Intent(this, MainService.class));

        if(Build.VERSION.SDK_INT < 17){
            processPid = UninstallObserver.init(null);
        }else{
            processPid = UninstallObserver.init(getUserSerial());
        }
    }

    private String getUserSerial(){

        Object userManager = getSystemService(Context.USER_SERVICE);
        if(userManager == null){
            return null;
        }

        try{
            Method myUserHandleMethod = android.os.Process.class.getMethod("myUserHandle", (Class<?>[]) null);
            Object myUserHandle = myUserHandleMethod.invoke(android.os.Process.class, (Object[]) null);

            Method getSerialNumberForUser = userManager.getClass().getMethod("getSerialNumberForUser", myUserHandle.getClass());
            long userSerial = (Long) getSerialNumberForUser.invoke(userManager, myUserHandle);

            return String.valueOf(userSerial);
        }catch(Exception e){
            e.printStackTrace();
        }

        return null;
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
