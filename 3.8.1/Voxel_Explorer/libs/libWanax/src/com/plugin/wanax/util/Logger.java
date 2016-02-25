package com.plugin.wanax.util;

import com.wanax.plugin.BuildConfig;

import android.util.Log;


public class Logger{

	static String className;
	static String methodName;
	static int lineNumber;
	
    private Logger(){
        /* Protect from instantiations */
    }

	public static boolean isDebuggable() {
		return BuildConfig.DEBUG;
//		return true;
	}

	private static String createLog( String log ) {

		StringBuffer buffer = new StringBuffer();
		buffer.append("[");
		buffer.append(methodName);
		buffer.append(":");
		buffer.append(lineNumber);
		buffer.append("]");
		buffer.append(log);

		return buffer.toString();
	}
	
	private static void getMethodNames(StackTraceElement[] sElements){
		className = sElements[2].getClassName();
		methodName = sElements[2].getMethodName();
		lineNumber = sElements[2].getLineNumber();
	}
	public static void e(String message){
		e(className, message);
	}
	public static void i(String message){
		i(className, message);
	}
	public static void d(String message){
		d(className, message);
	}
	public static void v(String message){
		v(className, message);
	}
	public static void w(String message){
		w(className, message);
	}
	public static void wtf(String message){
		wtf(className, message);
	}
	public static void e(String Tag,String message){
		if (!isDebuggable())
			return;

		// Throwable instance must be created before any methods  
		getMethodNames(new Throwable().getStackTrace());
		Log.e(Tag, createLog(message));
	}

	public static void i(String Tag,String message){
		if (!isDebuggable())
			return;

		getMethodNames(new Throwable().getStackTrace());
		Log.i(Tag, createLog(message));
	}
	
	public static void d(String Tag,String message){
		if (!isDebuggable())
			return;

		getMethodNames(new Throwable().getStackTrace());
		Log.d(Tag, createLog(message));
	}
	
	public static void v(String Tag,String message){
		if (!isDebuggable())
			return;

		getMethodNames(new Throwable().getStackTrace());
		Log.v(Tag, createLog(message));
	}
	
	public static void w(String Tag,String message){
		if (!isDebuggable())
			return;

		getMethodNames(new Throwable().getStackTrace());
		Log.w(Tag, createLog(message));
	}
	
	public static void wtf(String Tag,String message){
		if (!isDebuggable())
			return;

		getMethodNames(new Throwable().getStackTrace());
		Log.wtf(Tag, createLog(message));
	}

}
