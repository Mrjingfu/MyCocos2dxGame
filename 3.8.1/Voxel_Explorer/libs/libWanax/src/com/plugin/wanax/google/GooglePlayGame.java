package com.plugin.wanax.google;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.content.Intent;
import android.content.IntentSender;
import android.os.Bundle;
import android.util.Log;
import android.widget.Toast;

import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.GooglePlayServicesUtil;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.games.Games;
import com.google.android.gms.games.GamesActivityResultCodes;
import com.google.android.gms.games.Player;
import com.google.android.gms.plus.Plus;
import com.plugin.wanax.util.Logger;
import com.plugin.wanax.util.ResourcesManager;
import com.plugin.wanax.warpper.IActivityCallBack;
import com.wanax.plugin.R;



public class GooglePlayGame implements IActivityCallBack{

	private final String TAG = "GoogleGameManager";
	private GoogleApiClient mGoogleApiClient;
	private Activity m_pContext;

	private static final int RC_SIGN_IN = 9001;
	private static final int RC_UNUSED = 5001;
	
	public GooglePlayGame() {

	};


	public void disconnect()
	{
		if (isSignedIn()) {
            mGoogleApiClient.disconnect();
        }
	}
	public void connect() {
		Logger.d( "connect");
		if (!isSignedIn()) {
			mGoogleApiClient.connect();
		}
	}
    private boolean isSignedIn() {
        return (mGoogleApiClient != null && mGoogleApiClient.isConnected());
    }

	public void init(Activity context) {
		Logger.d( "init");
		if (null == m_pContext)
			m_pContext = context;
		if (null == mGoogleApiClient) {			
			mGoogleApiClient = new GoogleApiClient.Builder(m_pContext)
            .addConnectionCallbacks(m_connectionCallback)
            .addOnConnectionFailedListener(m_ConnectionFailedListener)
            .addApi(Plus.API).addScope(Plus.SCOPE_PLUS_LOGIN)
            .addApi(Games.API).addScope(Games.SCOPE_GAMES)
            .build();
		}
	}

	public GoogleApiClient.ConnectionCallbacks m_connectionCallback = new GoogleApiClient.ConnectionCallbacks() {

		@Override
		public void onConnectionSuspended(int arg0) {
			Logger.d("onConnectionSuspended(): attempting to connect");
			 connect();
		}

		@Override
		public void onConnected(Bundle arg0) {
			Logger.d("onConnected(): connected to Google APIs");
			 Player p = Games.Players.getCurrentPlayer(mGoogleApiClient);
			 String displayName;
		        if (p == null) {
		        	Logger.w(TAG, "mGamesClient.getCurrentPlayer() is NULL!");
		            displayName = "???";
		        } else {
		            displayName = p.getDisplayName();
		        }
		       Toast.makeText(m_pContext, "Hello, " + displayName, Toast.LENGTH_SHORT).show();
		}
	};

	public GoogleApiClient.OnConnectionFailedListener m_ConnectionFailedListener = new GoogleApiClient.OnConnectionFailedListener() {

		@Override
		public void onConnectionFailed(ConnectionResult connectionResult) {
			Logger.e("onConnectionFailed errorCode:"+connectionResult.getErrorCode());
		            if (!resolveConnectionFilure( connectionResult,
		                    RC_SIGN_IN, "")) {
		            	 Logger.e("onConnectionFailed(): attempting to resolve");
		            }
	
			
		}
	};

	public boolean resolveConnectionFilure(ConnectionResult result, int requestCode,
            String fallbackErrorMessage)
	{
		 if (result.hasResolution()) {
	            try {
	                result.startResolutionForResult(m_pContext, requestCode);
	                return true;
	            } catch (IntentSender.SendIntentException e) {
	                // The intent was canceled before it was sent.  Return to the default
	                // state and attempt to connect to get an updated ConnectionResult.
	            	mGoogleApiClient.connect();
	                return false;
	            }
	        } else {
	            // not resolvable... so show an error message
	            int errorCode = result.getErrorCode();
	            Dialog dialog = GooglePlayServicesUtil.getErrorDialog(errorCode,
	            		m_pContext, requestCode);
	            if (dialog != null) {
	                dialog.show();
	            } 
	            return false;
	        }
	}
	
	
	
	public void reportScore(int score,String leaderStr)
	{
		Logger.d( "leaderStr:"+leaderStr+" reportScore: "+score);
		if(isSignedIn() && score>=0 )
		{
			Logger.d( "commit reportScore: "+score);
			Games.Leaderboards.submitScore(mGoogleApiClient, leaderStr,
					score);
		}
	}
	
	public void reportAchievement(String achieveIDName,int step )
	{

		Logger.d("reportAchievement:"+achieveIDName+":"+step);
		if(isSignedIn() && step>0)
		{
			Logger.d("commit reportAchievement:"+achieveIDName+":"+step);
			String achieveValue = m_pContext.getResources().getString(ResourcesManager.getStringId(m_pContext, achieveIDName));
			Games.Achievements.setSteps(mGoogleApiClient,achieveValue ,step);
		}
	}

	public void openLeaderBoard()
	{
		Logger.d("openLeaderBoard");
		if (isSignedIn()) {
            m_pContext.startActivityForResult(Games.Leaderboards.getAllLeaderboardsIntent(mGoogleApiClient),
                    RC_UNUSED);
        } else {
        	connect();
        }
	}
	public void openAchievementBoard()
	{
		if (isSignedIn()) {
            m_pContext.startActivityForResult(Games.Achievements.getAchievementsIntent(mGoogleApiClient),
                    RC_UNUSED);
        } else {
        	connect();
        }
	}
	
	@Override
	public void onStart()
	{
		Logger.d("onStart(): connecting");
//		connect();
	}
	@Override
	public void onStop()
	{
		Logger.d("onStop(): disconnecting");
//		if(isConnected())
//		{
//			disconnect();
//		}
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
	public void onDestroy() {
		
	}
	@Override
	public void onRestart() {
		
	}
	@Override
	public void onActivityResult(int requestCode, int resultCode, Intent intent)
	{
		Logger.d("onActivityResult:"+requestCode);
        if (requestCode == RC_SIGN_IN) {
            if (resultCode == Activity.RESULT_OK) {
                connect();
            } else {
            	if (m_pContext == null) {
            		Logger.e("*** No Activity. Can't show failure dialog!");
                    return;
                }
               AlertDialog.Builder alertBuilder = new AlertDialog.Builder(m_pContext);
               alertBuilder.setNegativeButton(android.R.string.ok, null);
               String msg = "";
                switch (resultCode) {
                    case GamesActivityResultCodes.RESULT_APP_MISCONFIGURED:
                    	msg = m_pContext.getString(R.string.app_misconfigured);
                        break;
                    case GamesActivityResultCodes.RESULT_SIGN_IN_FAILED:
                    	msg = m_pContext.getString(R.string.sign_in_failed);
                        break;
                    case GamesActivityResultCodes.RESULT_LICENSE_FAILED:
                    	msg = m_pContext.getString(R.string.license_failed);
                    	break;
                    default:
                        // No meaningful Activity response code, so generate default Google
                        // Play services dialog
                        final int errorCode = GooglePlayServicesUtil.isGooglePlayServicesAvailable(m_pContext);
                        Dialog errorDialog = GooglePlayServicesUtil.getErrorDialog(errorCode,
                        		m_pContext, requestCode, null);
                        if (errorDialog == null) {
                        	Logger.e(
                                    "No standard error dialog available. Making fallback dialog.");
                            msg =  m_pContext.getString(R.string.signin_other_error);
                        }else
                        {
                        	errorDialog.show();
                        	return;
                        }
                        	
                }
                if(!msg.isEmpty())
                {
                    alertBuilder.setMessage(msg);
                    alertBuilder.create().show();
                }

            }
        }else if(requestCode == RC_UNUSED)
        {
        	if(resultCode ==10001 && isSignedIn())
        		mGoogleApiClient.disconnect();
        }
	}

}
