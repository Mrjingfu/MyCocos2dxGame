package com.wanax.google;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.Toast;

import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.games.Games;
import com.google.android.gms.games.Player;
import com.google.android.gms.plus.Plus;
import com.wanax.google.basegameUtils.BaseGameUtils;
import com.wanax.mazejump.R;

public class GoogleGameManager {

	private static GoogleGameManager m_pGoogleGameManager = null;
	private final String TAG = "GoogleGameManager";
	private GoogleApiClient mGoogleApiClient;
	private Activity m_pContext;
	private boolean mAutoStartSignInFlow = true;
	private boolean mResolvingConnectionFailure = false;
	private static final int RC_SIGN_IN = 9001;
	private static final int RC_UNUSED = 5001;
	private GoogleGameManager() {

	};
	public void onStart()
	{
		Log.d(TAG, "onStart(): connecting");
		connect();
	}
	
	public static GoogleGameManager getInstace() {
		if (null == m_pGoogleGameManager)
			m_pGoogleGameManager = new GoogleGameManager();
		return m_pGoogleGameManager;
	}
	public void onActivityResult(int requestCode, int resultCode, Intent intent)
	{
		Log.d(TAG, "onActivityResult:"+requestCode);
        if (requestCode == RC_SIGN_IN) {
            mResolvingConnectionFailure = false;
            if (resultCode == Activity.RESULT_OK) {
                connect();
            } else {
                BaseGameUtils.showActivityResultError(m_pContext, requestCode, resultCode, R.string.signin_other_error);
            }
        }
	}
	public void onStop()
	{
		Log.d(TAG, "onStop(): disconnecting");
		if(isConnected())
		{
			disconnect();
		}
	}
	
	public void openLeaderBoard()
	{
		Log.d(TAG, "openLeaderBoard");
		if (isConnected()) {
            m_pContext.startActivityForResult(Games.Leaderboards.getAllLeaderboardsIntent(mGoogleApiClient),
                    RC_UNUSED);
        } else {
        	connect();
//            BaseGameUtils.makeSimpleDialog(m_pContext, m_pContext.getString(R.string.leaderboards_not_available)).show();
        }
	}

	public void disconnect()
	{
		if (isConnected()) {
            mGoogleApiClient.disconnect();
        }
	}
	public void connect() {
		Log.d(TAG, "connect");
		if (!isConnected()) {
			mGoogleApiClient.connect();
		}
	}
    public boolean isConnected() {
        return (mGoogleApiClient != null && mGoogleApiClient.isConnected());
    }

	public void init(Activity context) {
		Log.d(TAG, "init");
		if (null == m_pContext)
			m_pContext = context;
		if (null == mGoogleApiClient) {
			mGoogleApiClient = new GoogleApiClient.Builder(m_pContext)
					.addConnectionCallbacks(m_connectionCallback)
					.addOnConnectionFailedListener(m_ConnectionFailedListener)
					.addApi(Plus.API).addScope(Plus.SCOPE_PLUS_LOGIN)
					.addApi(Games.API).addScope(Games.SCOPE_GAMES).build();
		}
	}

	public GoogleApiClient.ConnectionCallbacks m_connectionCallback = new GoogleApiClient.ConnectionCallbacks() {

		@Override
		public void onConnectionSuspended(int arg0) {
			 Log.d(TAG, "onConnectionSuspended(): attempting to connect");
			 connect();
		}

		@Override
		public void onConnected(Bundle arg0) {
			 Log.d(TAG, "onConnected(): connected to Google APIs");
			 Player p = Games.Players.getCurrentPlayer(mGoogleApiClient);
			 String displayName;
		        if (p == null) {
		            Log.w(TAG, "mGamesClient.getCurrentPlayer() is NULL!");
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
			 Log.d(TAG, "onConnectionFailed(): attempting to resolve");
			 if (mResolvingConnectionFailure) {
		            Log.d(TAG, "onConnectionFailed(): already resolving");
		            return;
		       }
			 if ( mAutoStartSignInFlow) {
		            mAutoStartSignInFlow = false;
		            mResolvingConnectionFailure = true;
		            if (!BaseGameUtils.resolveConnectionFailure(m_pContext, mGoogleApiClient, connectionResult,
		                    RC_SIGN_IN, m_pContext.getString(R.string.signin_other_error))) {
		                mResolvingConnectionFailure = false;
		            }
		        }
			
		}
	};

	public void reportScore(int score)
	{
		
		if(score>=0 && mGoogleApiClient!=null)
		{
			Log.d(TAG, "reportScore: "+score);
			Games.Leaderboards.submitScore(mGoogleApiClient, m_pContext.getString(R.string.leaderboard_best_results),
					score);
		}
	}
}
