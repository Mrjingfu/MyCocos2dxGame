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

import org.cocos2dx.lib.Cocos2dxActivity;

public class AppActivity extends Cocos2dxActivity {
    
//    private static String MY_AD_INTERSTITIAL_UNIT_ID = "ca-app-pub-3628527903442392/9335945464";
//    private final static int HANDLER_PLAY = 1;
//    private static AppActivity context;
//    private InterstitialAd interstitial;
//    
//    protected void onCreate(Bundle savedInstanceState) {
//        super.onCreate(savedInstanceState);
//        context = this;
//        
//        requestAndLoadInterstitialAds();
//        GoogleGameManager.getInstace().init(this);
//    }
//    
//    private static Handler handler = new Handler() {
//        public void handleMessage(Message msg) {
//        switch (msg.what) {
//            case HANDLER_PLAY: {
//                if (context.interstitial.isLoaded())
//                    context.interstitial.show();
//                else
//                    Log.d("AppActivity", "The interstitial didn't finish loading or failed to load");
//                }
//                break;
//            }
//        super.handleMessage(msg);
//        }
//    };
//
//    private class InterstitialAdsListener extends AdListener {
//        @Override
//        public void onAdLoaded() {
//            Log.d("AppActivity", "InterstitialAds: onAdLoaded");
//        }
//    
//        @Override
//        public void onAdFailedToLoad(int errorCode) {
//            String errorReason = "";
//            switch (errorCode) {
//                case AdRequest.ERROR_CODE_INTERNAL_ERROR:
//                    errorReason = "Internal error";
//                    break;
//                case AdRequest.ERROR_CODE_INVALID_REQUEST:
//                    errorReason = "Invalid request";
//                    break;
//                case AdRequest.ERROR_CODE_NETWORK_ERROR:
//                    errorReason = "Network Error";
//                    break;
//                case AdRequest.ERROR_CODE_NO_FILL:
//                    errorReason = "No fill";
//                    break;
//            }
//            Log.d("AppActivity",
//                  "InterstitialAds : failed to receive ad (" + errorReason
//                  + ")");
//            context.requestAndLoadInterstitialAds();
//        }
//    
//        @Override
//        public void onAdOpened() {
//            Log.d("AppActivity", "InterstitialAds : onAdOpened");
//        }
//    
//        @Override
//        public void onAdClosed() {
//            Log.d("AppActivity", "InterstitialAds : onAdClosed");
//            context.requestAndLoadInterstitialAds();
//        }
//    
//        @Override
//        public void onAdLeftApplication() {
//            Log.d("AppActivity", "InterstitialAds : onAdLeftApplication");
//        }
//    }
//    private void requestAndLoadInterstitialAds() {
//        // Create the interstitial.
//        if (null == interstitial) {
//            interstitial = new InterstitialAd(this);
//            interstitial.setAdUnitId(MY_AD_INTERSTITIAL_UNIT_ID);
//            interstitial.setAdListener(new InterstitialAdsListener());
//        }
//        // Create ad request.
//        AdRequest adRequest = new AdRequest.Builder().build();
//
//        // Begin loading your interstitial.
//        interstitial.loadAd(adRequest);
//    }
//
//    public void displayInterstitialAds() {
//
//        Message msg = new Message();
//        msg.what = HANDLER_PLAY;
//        handler.sendMessage(msg);
//    }
//
//    @Override
//    protected void onStart() {
//        super.onStart();
//        //		GoogleGameManager.getInstace().onStart();
//    }
//    
//    @Override
//    protected void onStop() {
//        super.onStop();
//        //		GoogleGameManager.getInstace().onStop();
//    }
//    
//    @Override
//    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
//        super.onActivityResult(requestCode, resultCode, data);
//        GoogleGameManager.getInstace().onActivityResult(requestCode, resultCode, data);
//    }
//    
//    @Override
//    public void onDestroy() {
//        super.onDestroy();
//    }
//    
//    public static void playInterstitialAds() {
//        context.displayInterstitialAds();
//    }
//    
//    public static void openGooglePlay() {
//        final String appPackageName = context.getPackageName(); // getPackageName() from Context or Activity object
//        try {
//            context.startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse("market://details?id=" + appPackageName)));
//        } catch (android.content.ActivityNotFoundException anfe) {
//            context.startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse("https://play.google.com/store/apps/details?id=" + appPackageName)));
//        }
//    }
//    
//    public static void logWithUserData(Hashtable<String, String> data) {
//        final Hashtable<String, String> curData = data;
//    }
//    
//    public static void exitGame()
//    {
//        context.runOnUiThread(new Runnable() {
//            
//            @Override
//            public void run() {
//                AlertDialog.Builder builder = new AlertDialog.Builder(context);
//                builder.setMessage(R.string.str_exit);
//                builder.setIcon(android.R.drawable.ic_dialog_info);
//                builder.setPositiveButton(R.string.str_ok, new OnClickListener() {
//                    
//                    @Override
//                    public void onClick(DialogInterface dialog, int which) {
//                        context.finish();
//                        System.exit(0);
//                    }
//                });
//                builder.setNegativeButton(R.string.str_cancel, new OnClickListener() {
//                    
//                    @Override
//                    public void onClick(DialogInterface dialog, int which) {
//                        dialog.dismiss();
//                    }
//                }).show();           
//            }
//        });
//    }
//    
//    public static void googleGameConnect()
//    {
//        Log.d("AppActivity", "googleGameConnect");
//        context.runOnUiThread(new Runnable() {
//            
//            @Override
//            public void run() {
//                GoogleGameManager.getInstace().connect();
//            }
//        });
//    }
//    
//    public static void openLeaderBoard()
//    {
//        context.runOnUiThread(new Runnable() {
//            
//            @Override
//            public void run() {
//                GoogleGameManager.getInstace().openLeaderBoard();
//            }
//        });
//        
//    }
//    
//    public static void reportScore(final int score)
//    {
//        context.runOnUiThread(new Runnable() {
//            
//            @Override
//            public void run() {
//                GoogleGameManager.getInstace().reportScore(score);
//            }
//        });
//        
//    }
}
