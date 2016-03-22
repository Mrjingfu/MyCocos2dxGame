package com.plugin.wanax.warpper;

import com.plugin.wanax.channel.GoogleAdsWarpper;
import com.plugin.wanax.channel.YoumiAdsWarpper;

import android.app.Activity;

public class WanaxWrapper {
	
	private static WanaxWrapper mInstance = null;
	private  AdsWarpper mAdsWarpper = null;
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
        
		mAdsWarpper = new GoogleAdsWarpper();
        mAdsWarpper.initAds(actity);
       
	}



	public AdsWarpper getAdsWarpper() {
		return mAdsWarpper;
	}

	public Activity getActity() {
		return mActity;
	}

	
	
	
}
