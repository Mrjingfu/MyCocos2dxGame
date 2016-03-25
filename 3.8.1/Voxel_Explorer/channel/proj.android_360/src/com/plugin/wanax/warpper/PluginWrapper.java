package com.plugin.wanax.warpper;

import java.util.Vector;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.opengl.GLSurfaceView;
import android.os.Handler;
import android.os.Looper;

public class PluginWrapper {
	private Vector<IActivityCallBack> mActivityCallback = new Vector();
	public static PluginWrapper mWanaxWrapperInstance = null;
	public Context mContext = null;
	protected GLSurfaceView mGLSurfaceView = null;
	protected Handler mMainThreadHandler = null;
	protected Handler sGLThreadHandler = null;

	public static PluginWrapper getInstace() {
		if (null == mWanaxWrapperInstance)
			mWanaxWrapperInstance = new PluginWrapper();
		return mWanaxWrapperInstance;
	}

	public void init(Activity paramContext) {
		mContext = paramContext;
		if ((paramContext != null) && ((mContext instanceof Activity))) {
			mContext = ((Activity) mContext).getWindow().getDecorView()
					.getContext();
		}
		if (mMainThreadHandler == null) {
			mMainThreadHandler = new Handler(Looper.getMainLooper());
		}
		
		 WanaxWrapper.getInstance().init(paramContext);
	}
	
	
	public void setGLSurfaceView(GLSurfaceView paramGLSurfaceView) {
		mGLSurfaceView = paramGLSurfaceView;
	}

	public void runOnGLThread(Runnable paramRunnable) {
		if (mGLSurfaceView != null) {
			mGLSurfaceView.queueEvent(paramRunnable);
			return;
		}
		if (sGLThreadHandler != null) {
			sGLThreadHandler.post(paramRunnable);
			return;
		}
		paramRunnable.run();
	}

	public void runOnMainThread(Runnable paramRunnable) {
		if (mMainThreadHandler != null) {
			mMainThreadHandler.post(paramRunnable);
			return;
		}
		if ((mContext != null) && ((mContext instanceof Activity))) {
			((Activity) mContext).runOnUiThread(paramRunnable);
		}
	}
	
	public void onStart()
	{
		for (int i = 0; i < mActivityCallback.size(); i++) {
			((IActivityCallBack) mActivityCallback.get(i)).onStart();
		}
	}

	public void onActivityResult(int paramInt1, int paramInt2,
			Intent paramIntent) {
		for (int i = 0; i < mActivityCallback.size(); i++) {
			((IActivityCallBack) mActivityCallback.get(i)).onActivityResult(
					paramInt1, paramInt2, paramIntent);
		}
	}

	public void onPause() {
		for (int i = 0; i < mActivityCallback.size(); i++) {
			((IActivityCallBack) mActivityCallback.get(i)).onPause();
		}
	}

	public void onResume() {
		for (int i = 0; i < mActivityCallback.size(); i++) {
			((IActivityCallBack) mActivityCallback.get(i)).onResume();
		}
	}

	public void onNewIntent(Intent paramIntent) {
		for (int i = 0; i < mActivityCallback.size(); i++) {
			((IActivityCallBack) mActivityCallback.get(i))
					.onNewIntent(paramIntent);
		}
	}

	public void onStop() {
		for (int i = 0; i < mActivityCallback.size(); i++) {
			((IActivityCallBack) mActivityCallback.get(i)).onStop();
		}
	}

	public void onDestroy() {
		for (int i = 0; i < mActivityCallback.size(); i++) {
			((IActivityCallBack) mActivityCallback.get(i)).onDestroy();
		}
	}

	public void onRestart() {
		for (int i = 0; i < mActivityCallback.size(); i++) {
			((IActivityCallBack) mActivityCallback.get(i)).onRestart();
		}
	}

	public void setActivityCallback(IActivityCallBack paramIActivityCallback) {
		mActivityCallback.add(paramIActivityCallback);
	}
}
