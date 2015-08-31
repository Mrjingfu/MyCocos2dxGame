/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package org.cocos2dx.cpp;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Hashtable;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.content.Intent;
import android.net.Uri;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.provider.Settings;
import android.telephony.TelephonyManager;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.view.WindowManager;

import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.InterstitialAd;
public class AppActivity extends Cocos2dxActivity {
	private static String MY_AD_BANNER_UNIT_ID = "ca-app-pub-3628527903442392/7420311060";
	private static String MY_AD_INTERSTITIAL_UNIT_ID = "ca-app-pub-3628527903442392/8897044266";
	private final static int HANDLER_PLAY = 1;
	private static AppActivity context;
	private AdView adView;
	private InterstitialAd interstitial;
	private ProgressDialog progressDialog;
	private WindowManager windowMgr;

	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		context = this;
		windowMgr = (WindowManager) context.getSystemService("window");

		requestAndLoadInterstitialAds();
	}

	private static Handler handler = new Handler() {
		public void handleMessage(Message msg) {
			switch (msg.what) {
			case HANDLER_PLAY: {
				if (context.interstitial.isLoaded())
					context.interstitial.show();
				else
					Log.d("AppActivity",
							"The interstitial didn't finish loading or failed to load");
			}
				break;
			}
			super.handleMessage(msg);
		}
	};

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
			Log.d("AppActivity",
					"InterstitialAds : failed to receive ad (" + errorReason
							+ ")");
			context.requestAndLoadInterstitialAds();
		}

		@Override
		public void onAdOpened() {
			Log.d("AppActivity", "InterstitialAds : onAdOpened");
		}

		@Override
		public void onAdClosed() {
			Log.d("AppActivity", "InterstitialAds : onAdClosed");
			context.requestAndLoadInterstitialAds();
		}

		@Override
		public void onAdLeftApplication() {
			Log.d("AppActivity", "InterstitialAds : onAdLeftApplication");
		}
	}

	private void requestAndLoadInterstitialAds() {
		// Create the interstitial.
		if (null == interstitial) {
			interstitial = new InterstitialAd(this);
			interstitial.setAdUnitId(MY_AD_INTERSTITIAL_UNIT_ID);
			interstitial.setAdListener(new InterstitialAdsListener());
		}
		// Create ad request.
		AdRequest adRequest = new AdRequest.Builder().build();

		// Begin loading your interstitial.
		interstitial.loadAd(adRequest);
	}

	public void displayInterstitialAds() {

		Message msg = new Message();
		msg.what = HANDLER_PLAY;
		handler.sendMessage(msg);
	}

	private class BannerAdsListener extends AdListener {
		@Override
		public void onAdLoaded() {
			Log.d("SpaceGeometryWars", "BannerAds : onAdLoaded");
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
			Log.d("SpaceGeometryWars", "BannerAds : failed to receive ad ("
					+ errorReason + ")");
		}

		@Override
		public void onAdOpened() {
			Log.d("SpaceGeometryWars", "BannerAds : onAdOpened");
		}

		@Override
		public void onAdClosed() {
			Log.d("SpaceGeometryWars", "BannerAds : onAdClosed");
		}

		@Override
		public void onAdLeftApplication() {
			Log.d("SpaceGeometryWars", "BannerAds : onAdLeftApplication");
		}
	}

	public void showAds() {
		context.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (null != adView) {
					if (null != windowMgr) {
						windowMgr.removeView(adView);
					}
					adView.destroy();
					adView = null;
				}
				// ¥¥Ω®adView°£
				adView = new AdView(context);
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

				// ≤‚ ‘Admob ± π”√≤‚ ‘Device
				AdRequest adRequest = new AdRequest.Builder().build();
				adView.loadAd(adRequest);
			}
		});
	}

	public void hideAds() {
		context.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (null != adView) {
					if (null != windowMgr) {
						windowMgr.removeView(adView);
					}
					adView.destroy();
					adView = null;
				}
			}
		});
	}

	public void showIndicatorView() {
		context.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				progressDialog = ProgressDialog.show(context, null, null);
			}
		});
	}

	public void hideIndicatorView() {
		context.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				progressDialog.dismiss();
			}
		});
	}

	@Override
	protected void onStart() {
		super.onStart();
	}

	@Override
	protected void onStop() {
		super.onStop();
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
		super.onDestroy();
	}

	public static void playInterstitialAds() {
		context.displayInterstitialAds();
	}

	public static void setAdVisible(boolean b) {
		if (b)
			context.showAds();
		else
			context.hideAds();
	}

	public static void setIndicatorViewVisible(boolean b) {
		if (b)
			context.showIndicatorView();
		else
			context.hideIndicatorView();
	}

	public static void showRateAppView() 
	{
		
	}
	
	public static void openGooglePlay() {
		final String appPackageName = context.getPackageName(); // getPackageName() from Context or Activity object
        try {
        	context.startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse("market://details?id=" + appPackageName)));
        } catch (android.content.ActivityNotFoundException anfe) {
        	context.startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse("https://play.google.com/store/apps/details?id=" + appPackageName)));
        }
	}

	public static String generateUUID() {
		TelephonyManager telephonyManager = (TelephonyManager) context
				.getSystemService(Context.TELEPHONY_SERVICE);
		String imei = telephonyManager.getDeviceId();
		String imsi = telephonyManager.getSubscriberId();

		WifiManager wifiMan = (WifiManager) context.getSystemService("wifi");
		String m_szWLANMAC = wifiMan.getConnectionInfo().getMacAddress();
		String android_id = Settings.Secure.getString(
				context.getContentResolver(), Settings.System.ANDROID_ID);
		m_szWLANMAC = m_szWLANMAC != null ? m_szWLANMAC : "";
		imei = imei != null ? imei : "";
		imsi = imsi != null ? imsi : "";

		String m_szLongID = imei + m_szWLANMAC+imsi + android_id  ;
		MessageDigest m = null;
		try {
			m = MessageDigest.getInstance("MD5");
		} catch (NoSuchAlgorithmException e) {
			e.printStackTrace();
		}
		m.update(m_szLongID.getBytes(), 0, m_szLongID.length());
		byte p_md5Data[] = m.digest();
		String m_szUniqueID = new String();
		for (int i = 0; i < p_md5Data.length; i++) {
			int b = (0xFF & p_md5Data[i]);
			if (b <= 0xF)
				m_szUniqueID += "0";
			m_szUniqueID += Integer.toHexString(b);
		} 
		m_szUniqueID = m_szUniqueID.toUpperCase();
		return m_szUniqueID;
	}

	public static void logWithUserData(Hashtable<String, String> data) {
		final Hashtable<String, String> curData = data;
	}
	
	public static void exitGame()
	{
		context.runOnUiThread(new Runnable() {
			
			@Override
			public void run() {
				AlertDialog.Builder builder = new AlertDialog.Builder(context);  
                builder.setMessage("确定退出吗?");  
                builder.setIcon(android.R.drawable.ic_dialog_info);  
                builder.setPositiveButton("确定", new OnClickListener() {  
                       
                    @Override  
                    public void onClick(DialogInterface dialog, int which) {
                    	context.finish();
                        System.exit(0);                       
                    }  
                });  
                builder.setNegativeButton("取消", new OnClickListener() {  
                       
                    @Override  
                    public void onClick(DialogInterface dialog, int which) {  
                        dialog.dismiss();   
                    }  
                }).show();           
			}
		});
	}
}
