package com.example.deletedetect;

/**
 * Created by caifangmao on 15/3/3.
 */
public class UninstallObserver {

    static{
        System.loadLibrary("detect");
    }

    public static native int init(String userSerial);
}
