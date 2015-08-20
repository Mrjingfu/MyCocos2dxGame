/****************************************************************************

 Copyright (c) 2014-2015 Chukong Technologies

 ****************************************************************************/
#ifndef _PLUGIN_GA_
#define _PLUGIN_GA_

#include <string>
#include <vector>

using namespace std;

namespace sdkbox
{

    class PluginGoogleAnalytics
    {
    public:

        PluginGoogleAnalytics();
        ~PluginGoogleAnalytics();

        /*!
         * initialize the plugin instance.
         */
        static void init();

        /*!
         * The analytics session is being explicitly started at plugin initialization time.
         */
        static void startSession();

        /*!
         * You normally will never stop a session manually.
         */
        static void stopSession();

        /*!
         * Manually request dispatch of hits. By default, data is dispatched from the
         * Google Analytics SDK for Android every 5 minutes.
         */
        static void dispatchHits();

        /*!
         * Change the dispatch info time period to the desired amount of seconds.
         */
        static void dispatchPeriodically( int seconds );

        /*!
         * Stop periodically sending info. Then manually the <code>dispatchPeridically</code>
         * or <code>dispatchHits</code> should be called.
         */
        static void stopPeriodicalDispatch();

        /*!
         * Log screen info. title is the title of a screen. Screens are logical units
         * inside your app you'd like to identify at analytics panel.
         */
        static void logScreen(string title);

        /*!
         * GoogleAnalytics::logEvent("Achievement", "Unlocked", "Slay 10 dragons", 5);
         */
        static void logEvent(string eventCategory, string eventAction, string eventLabel, int value);

        /*!
         * Log an exception. It is a basic support for in-app events.
         */
        static void logException(string exceptionDescription, bool isFatal);

        /*!
         * Measure a time inside the application.
         */
        static void logTiming(string timingCategory, int timingInterval, string timingName, string timingLabel);

        /*!
         * Log a social event.
         */
        static void logSocial(string socialNetwork, string socialAction, string socialTarget);

        /*!
         * While running on dry run, the tracked events won't be sent to the actual
         * analytics account.
         */
        static void setDryRun( bool dr );

        /*!
         * Enable advertising tracking when in google's ad vendors.
         */
        static void enableAdvertisingTracking( bool e );

        /*!
         * Create a tracker identified by the google analytics tracker id XX-YYYYYYYY-Z.
         * If the tracker already existed, no new tracker will be created. In any case, the
         * tracker associated with tracker id will be set as default tracker for  analytics
         * operations.
         */
        static void createTracker( string trackerId );

        /*!
         * Enable a tracker identified by a trackerId. If the tracker does not exist,
         * nothing will happen.
         */
        static void enableTracker( string trackerId );

        #ifdef OBFUSCATED
        _f2c23a1f452545d1b214e79dbf1beba5
        #endif
    };

}

#endif
