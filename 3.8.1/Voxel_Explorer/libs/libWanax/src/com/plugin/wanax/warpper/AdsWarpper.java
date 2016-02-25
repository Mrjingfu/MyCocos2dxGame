package com.plugin.wanax.warpper;

import android.app.Activity;

public interface AdsWarpper {
	
	public void initAds(Activity activity);
	public void showAds();//显示Banner
	public void hideAds();//隐藏Banner
	public void playInterstitialAds();//开屏广告

}
