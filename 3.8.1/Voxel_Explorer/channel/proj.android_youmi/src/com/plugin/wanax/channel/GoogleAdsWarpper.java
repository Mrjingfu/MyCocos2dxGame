package com.plugin.wanax.channel;

import android.app.Activity;
import android.content.Intent;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.view.WindowManager;

import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.InterstitialAd;
import com.plugin.wanax.util.Logger;
import com.plugin.wanax.warpper.AdsWarpper;
import com.plugin.wanax.warpper.IActivityCallBack;
import com.plugin.wanax.warpper.PluginWrapper;

public class GoogleAdsWarpper implements AdsWarpper,IActivityCallBack {
	private static String MY_AD_BANNER_UNIT_ID = "ca-app-pub-3628527903442392/7420311060";
	private static String MY_AD_INTERSTITIAL_UNIT_ID = "ca-app-pub-3628527903442392/9335945464";
	private AdView adView;
	private InterstitialAd interstitial;
	private WindowManager windowMgr;
	private Activity mActivity = null;

	@Override
	public void initAds(Activity activity) {
		mActivity = activity;
		windowMgr = mActivity.getWindowManager();
		requestAndLoadInterstitialAds();
		PluginWrapper.getInstace().setActivityCallback(this);
	}

	@Override
	public void showAds() {
		if (null != adView) {
			if (null != windowMgr) {
				windowMgr.removeView(adView);
			}
			adView.destroy();
			adView = null;
		}
		adView = new AdView(mActivity);
		adView.setAdUnitId(MY_AD_BANNER_UNIT_ID);
		adView.setAdSize(AdSize.BANNER);
		adView.setAdListener(new BannerAdsListener());

		WindowManager.LayoutParams params = new WindowManager.LayoutParams();
		params.type = WindowManager.LayoutParams.TYPE_APPLICATION_PANEL;
		params.width = WindowManager.LayoutParams.WRAP_CONTENT;
		params.height = WindowManager.LayoutParams.WRAP_CONTENT;
		params.flags |= WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;
		params.gravity = Gravity.BOTTOM | Gravity.LEFT;
		windowMgr.addView(adView, params);
		adView.setVisibility(View.GONE);

		AdRequest adRequest = new AdRequest.Builder().build();
		adView.loadAd(adRequest);
	}

	@Override
	public void hideAds() {
		if (null != adView) {
			if (null != windowMgr) {
				windowMgr.removeView(adView);
			}
			adView.destroy();
			adView = null;
		}
	}

	@Override
	public void playInterstitialAds() {
		if (null != interstitial) {
			if (isInterstitialAdsReady())
				interstitial.show();
			else
				Logger.e("The interstitial didn't finish loading or failed to load");
				
		} else
			requestAndLoadInterstitialAds();
	}
	
	public boolean isInterstitialAdsReady()
	{	
		return interstitial.isLoaded();
	}
	
	

	public void requestAndLoadInterstitialAds() {
		if (null == interstitial) {
			interstitial = new InterstitialAd(mActivity);
			interstitial.setAdUnitId(MY_AD_INTERSTITIAL_UNIT_ID);
			interstitial.setAdListener(new InterstitialAdsListener());
		}
		AdRequest adRequest = new AdRequest.Builder().build();
		interstitial.loadAd(adRequest);
		Logger.d("interstitial isLoad:"+isInterstitialAdsReady());
	}

	private class BannerAdsListener extends AdListener {
		public void onAdLoaded() {
			Logger.d("BannerAds : onAdLoaded");
			if (null != adView) {
				adView.setVisibility(View.VISIBLE);
			}
		}

		@Override
		public void onAdFailedToLoad(int errorCode) {
			String errorReason = "";
			switch (errorCode) {
			case AdRequest.ERROR_CODE_INTERNAL_ERROR:
				errorReason = "Internal error";
				break;
			case AdRequest.ERROR_CODE_INVALID_REQUEST:
				errorReason = "Invalid request";
				break;
			case AdRequest.ERROR_CODE_NETWORK_ERROR:
				errorReason = "Network Error";
				break;
			case AdRequest.ERROR_CODE_NO_FILL:
				errorReason = "No fill";
				break;
			}
			Logger.e("BannerAds : failed to receive ad (" + errorReason + ")");
		}

		@Override
		public void onAdOpened() {
			Logger.d("BannerAds : onAdOpened");
		}

		@Override
		public void onAdClosed() {
			Logger.d("BannerAds : onAdClosed");
		}

		@Override
		public void onAdLeftApplication() {
			Logger.d("BannerAds : onAdLeftApplication");
		}
	}

	private class InterstitialAdsListener extends AdListener {
		@Override
		public void onAdLoaded() {
			Log.d("AppActivity", "InterstitialAds: onAdLoaded");
		}

		@Override
		public void onAdFailedToLoad(int errorCode) {
			String errorReason = "";
			switch (errorCode) {
			case AdRequest.ERROR_CODE_INTERNAL_ERROR:
				errorReason = "Internal error";
				break;
			case AdRequest.ERROR_CODE_INVALID_REQUEST:
				errorReason = "Invalid request";
				break;
			case AdRequest.ERROR_CODE_NETWORK_ERROR:
				errorReason = "Network Error";
				break;
			case AdRequest.ERROR_CODE_NO_FILL:
				errorReason = "No fill";
				break;
			}
			Logger.e("InterstitialAds : failed to receive ad (" + errorReason
					+ ")");
			requestAndLoadInterstitialAds();
		}

		@Override
		public void onAdOpened() {
			Logger.d("InterstitialAds : onAdOpened");
		}

		@Override
		public void onAdClosed() {
			Logger.d("InterstitialAds : onAdClosed");
			requestAndLoadInterstitialAds();
		}

		@Override
		public void onAdLeftApplication() {
			Logger.d("AppActivity", "InterstitialAds : onAdLeftApplication");
		}
	}

	@Override
	public void onActivityResult(int paramInt1, int paramInt2,
			Intent paramIntent) {
		
	}

	@Override
	public void onStart() {
		
	}

	@Override
	public void onPause() {
		
	}

	@Override
	public void onResume() {
		
	}

	@Override
	public void onNewIntent(Intent paramIntent) {
		
	}

	@Override
	public void onStop() {
		
	}

	@Override
	public void onDestroy() {
		if (null != adView) {
			if (null != windowMgr) {
				windowMgr.removeViewImmediate(adView);
			}
			adView.destroy();
			adView = null;
		}

	}

	@Override
	public void onRestart() {
		
	}

}
