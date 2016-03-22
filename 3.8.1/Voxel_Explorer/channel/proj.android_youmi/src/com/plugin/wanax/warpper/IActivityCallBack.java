package com.plugin.wanax.warpper;

import android.content.Intent;

public interface IActivityCallBack {
	 public abstract void onActivityResult(int paramInt1, int paramInt2, Intent paramIntent);
	  
	  public abstract void onStart();
	 
	  public abstract void onPause();
	  
	  public abstract void onResume();
	  
	  public abstract void onNewIntent(Intent paramIntent);
	  
	  public abstract void onStop();
	  
	  public abstract void onDestroy();
	  
	  public abstract void onRestart();
}
