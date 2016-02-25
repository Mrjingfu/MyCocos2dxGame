package com.plugin.wanax.warpper;

import com.plugin.wanax.google.GoogleAdsWarpper;
import com.plugin.wanax.google.GooglePlayGame;

import android.app.Activity;

public class WanaxWrapper {
	
	private static WanaxWrapper mInstance = null;
	private  GooglePlayGame mGooglePlayGame = null;
	private  GoogleAdsWarpper mGoogleAdsWarpper = null;
	private Activity mActity = null;
    
	public static WanaxWrapper getInstance()
	{
		if(null ==mInstance )
			mInstance = new WanaxWrapper();
		return mInstance;
	}
	
	public void init(Activity actity)
	{
		mActity = actity;
        mGooglePlayGame = new GooglePlayGame();
        mGooglePlayGame.init(actity);
        
        mGoogleAdsWarpper = new GoogleAdsWarpper();
        mGoogleAdsWarpper.initAds(actity);
        
        PluginWrapper.getInstace().setActivityCallback(mGooglePlayGame);
        PluginWrapper.getInstace().setActivityCallback(mGoogleAdsWarpper);
	}

	public GooglePlayGame getGooglePlayGame() {
		return mGooglePlayGame;
	}


	public GoogleAdsWarpper getGoogleAdsWarpper() {
		return mGoogleAdsWarpper;
	}

	public Activity getActity() {
		return mActity;
	}

	
	
	
}
