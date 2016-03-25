package com.plugin.wanax.channel;

import net.youmi.android.AdManager;
import net.youmi.android.spot.SpotDialogListener;
import net.youmi.android.spot.SpotManager;
import android.app.Activity;
import android.content.Intent;

import com.plugin.wanax.util.Logger;
import com.plugin.wanax.warpper.AdsWarpper;
import com.plugin.wanax.warpper.IActivityCallBack;

public class YoumiAdsWarpper implements AdsWarpper,IActivityCallBack {

	private Activity mActivity = null;
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
		
	}

	@Override
	public void onRestart() {
		
	}

	@Override
	public void initAds(Activity activity) {
		if (null == mActivity) {
			mActivity = activity;
			AdManager.getInstance(activity).init("1568a6310b8ede4b", "2403de0a5dd55c54");
		}
		requestAndLoadInterstitialAds();
	}

	@Override
	public void showAds() {
		
	}

	@Override
	public void hideAds() {
		
	}

	@Override
	public void playInterstitialAds() {
		SpotManager.getInstance(mActivity).showSpotAds(mActivity, new SpotDialogListener() {
			
			@Override
			public void onSpotClosed() {
				Logger.d("SpotManager onSpotClosed");
			}
			
			@Override
			public void onSpotClick(boolean arg0) {
				Logger.d("SpotManager onSpotClick");
			}
			
			@Override
			public void onShowSuccess() {
				Logger.d("SpotManager onShowSuccess");
				YoumiAdsWarpper.this.requestAndLoadInterstitialAds();
			}
			
			@Override
			public void onShowFailed() {
				Logger.d("SpotManager onShowFailed");
				YoumiAdsWarpper.this.requestAndLoadInterstitialAds();
			}
		});
	}

	@Override
	public boolean isInterstitialAdsReady() {
		return true;
	}

	@Override
	public void requestAndLoadInterstitialAds() {
		SpotManager.getInstance(mActivity).loadSpotAds();
	}
	

}
