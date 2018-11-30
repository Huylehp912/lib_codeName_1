package com.sdmc.jni;

import android.util.Log;

public class CoreSSLog {
	
	private static final String TAG = "CoreSS";
	
	public static void i(String tag, String msg) {
		Log.i(TAG, tag + " : " + msg);
	}
	
	public static void e(String tag, String msg) {
		Log.e(TAG, tag + " : " + msg);
	}
	
	public static void e(String tag, String msg, Throwable tr) {
		Log.e(TAG, msg, tr);
	}
	
	public static void w(String tag, String msg) {
		Log.w(TAG, tag + " : " + msg);
	}
	
	public static void d(String tag, String msg) {
		Log.d(TAG, tag + " : " + msg);
	}
	
}
