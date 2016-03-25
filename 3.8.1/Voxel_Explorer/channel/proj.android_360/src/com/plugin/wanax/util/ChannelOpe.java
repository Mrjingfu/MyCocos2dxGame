package com.plugin.wanax.util;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.DialogInterface.OnClickListener;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.Uri;

import com.plugin.wanax.warpper.PluginWrapper;
import com.plugin.wanax.warpper.WanaxWrapper;
import com.wanax.voxelexplorer.R;

public class ChannelOpe {

	
	public static boolean isReady = false;
	
	
	public static void playInterstitialAds() {
		Logger.d("playInterstitialAds");
		PluginWrapper.getInstace().runOnMainThread(new Runnable() {

			@Override
			public void run() {
				WanaxWrapper.getInstance().getAdsWarpper()
						.playInterstitialAds();

			}
		});

	}

	public static boolean isInterstitialAdsReady() {
		Logger.d("isInterstitialAdsReady");
		PluginWrapper.getInstace().runOnMainThread(new Runnable() {

			@Override
			public void run() {
				isReady= WanaxWrapper.getInstance().getAdsWarpper()
						.isInterstitialAdsReady();
				Logger.d("isInterstitialAdsReady isReady:"+isReady);
			}
		});
		return isReady;

	}
	public static void requestAndLoadInterstitialAds()
	{
		PluginWrapper.getInstace().runOnMainThread(new Runnable() {

			@Override
			public void run() {
				WanaxWrapper.getInstance().getAdsWarpper().requestAndLoadInterstitialAds();

			}
		});
	}

	public static void openGooglePlay() {
		Logger.d("openGooglePlay");
		PluginWrapper.getInstace().runOnMainThread(new Runnable() {

			@Override
			public void run() {

				final String appPackageName = WanaxWrapper.getInstance()
						.getActity().getPackageName(); // getPackageName() from
														// Context or Activity
				WanaxWrapper
				.getInstance()
				.getActity()
				.startActivity(
						new Intent(
								Intent.ACTION_VIEW,
								Uri.parse("https://play.google.com/store/apps/details?id="
										+ appPackageName)));

			}
		});

	}

	public static void exitGame() {
		Logger.d("exitGame");
		PluginWrapper.getInstace().runOnMainThread(new Runnable() {

			@Override
			public void run() {
				AlertDialog.Builder builder = new AlertDialog.Builder(
						WanaxWrapper.getInstance().getActity());
				builder.setMessage(R.string.str_exit);
				builder.setIcon(android.R.drawable.ic_dialog_info);
				builder.setPositiveButton(R.string.str_ok,
						new OnClickListener() {

							@Override
							public void onClick(DialogInterface dialog,
									int which) {
								WanaxWrapper.getInstance().getActity().finish();
								System.exit(0);
							}
						});
				builder.setNegativeButton(R.string.str_cancel,
						new OnClickListener() {

							@Override
							public void onClick(DialogInterface dialog,
									int which) {
								dialog.dismiss();
							}
						}).show();
			}
		});

	}

	public static void googleGameConnect() {
		Logger.d("googleGameConnect");

		PluginWrapper.getInstace().runOnMainThread(new Runnable() {

			@Override
			public void run() {

			}

		});

	}

	public static void openLeaderBoard() {
		Logger.d("openLeaderBoard");
		PluginWrapper.getInstace().runOnMainThread(new Runnable() {

			@Override
			public void run() {

			}

		});

	}

	public static void openAchievementBoard() {
		Logger.d("openAchievementBoard");
		PluginWrapper.getInstace().runOnMainThread(new Runnable() {

			@Override
			public void run() {

			}

		});
	}

	public static void reportLevel(final int score) {
		Logger.d("reportLevel");
		PluginWrapper.getInstace().runOnMainThread(new Runnable() {

			@Override
			public void run() {

			}

		});

	}
	public static void reportMoney(final int score) {
		Logger.d("reportMoney");
		PluginWrapper.getInstace().runOnMainThread(new Runnable() {

			@Override
			public void run() {

			}

		});

	}
	
	public static void reportAchievement(final String activeIDName,final int step)
	{
		Logger.d("reportMoney");
		PluginWrapper.getInstace().runOnMainThread(new Runnable() {

			@Override
			public void run() {

			}

		});
	}

	public static boolean isNetworkAvailable() {
		Logger.d("isNetworkAvailable");
		ConnectivityManager cm = (ConnectivityManager) WanaxWrapper
				.getInstance().getActity()
				.getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo ni = cm.getActiveNetworkInfo();
		return ni != null && ni.isConnectedOrConnecting();
	}
}
