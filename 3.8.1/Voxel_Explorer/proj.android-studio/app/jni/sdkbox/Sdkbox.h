/****************************************************************************

 Copyright (c) 2014-2015 SDKBOX Inc

 ****************************************************************************/

#ifndef _CC_SDKBOX_H_
#define _CC_SDKBOX_H_

#define SDKBOX_VERSION_STR  "sdkbox V2.1.1.2"

/**
 * Only certain compilers support __attribute__((deprecated)).
 */
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#define SDKBOX_DEPRECATED_ATTRIBUTE __attribute__((deprecated))
#elif _MSC_VER >= 1400 //vs 2005 or higher
#define SDKBOX_DEPRECATED_ATTRIBUTE __declspec(deprecated)
#else
#define SDKBOX_DEPRECATED_ATTRIBUTE
#endif

/**
 * SDKBOX_DEPRECATED(4.0) or SDKBOX_DEPRECATED(4.0, "not going to need this anymore") etc.
 */
#define SDKBOX_DEPRECATED(...) SDKBOX_DEPRECATED_ATTRIBUTE

 #include <string>

namespace sdkbox {

    void init( const char* application_token, const char* application_key, const char* store = "all", bool debug = false);
    void setProjectType(const char* project_type);

    void sessionStart();
    void sessionEnd();


    enum AdActionType {

        LOADED=0,             // content loaded
        LOAD_FAILED,        // content failed to load

        CLICKED,            // clicked on content

        REWARD_STARTED,
        REWARD_ENDED,       // reward achieved
        REWARD_CANCELED,    // reward aborted

        AD_STARTED,         // start showing.
        AD_CANCELED,        // start showing.
        AD_ENDED,            // content shown

        ADACTIONTYPE_UNKNOWN

    };

    enum AdType {
        BANNER=0,
        VIDEO,
        INTERSTITIAL,
        REWARDED,

        ADTYPE_UNKNOWN
    };


    std::string  AdActionTypeToString( AdActionType t );
    AdActionType intToAdActionType( int v );

    std::string AdTypeToString( AdType t );
    int         AdTypeToInt( AdType t );
    AdType      intToAdType( int t );
}

#endif//_CC_SDKBOX_H_
