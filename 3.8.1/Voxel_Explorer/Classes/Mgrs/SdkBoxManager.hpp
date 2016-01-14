//
//  SdkBoxManager.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 16/1/14.
//
//

#ifndef SdkBoxManager_hpp
#define SdkBoxManager_hpp

#include "cocos2d.h"
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
#include "PluginGoogleAnalytics/PluginGoogleAnalytics.h"
#endif
class SdkBoxManager : public cocos2d::Ref
{
    SdkBoxManager();
    ~SdkBoxManager();
public:
    static SdkBoxManager* getInstance();
#pragma mark GoogleAnalytics
    void registerGoogleAnalytics();
    void logScreen(std::string title);
    ///example : logEvent("Achievement", "Unlocked", "Slay 10 dragons", 5);
    void logEvent(std::string eventCategory, std::string eventAction, std::string eventLabel, int value);
    void logException(std::string exceptionDescription, bool isFatal);
    void logTiming(std::string timingCategory, int timingInterval, std::string timingName, std::string timingLabel);
    void logSocial(std::string socialNetwork, std::string socialAction, std::string socialTarget);
};

#endif /* SdkBoxManager_hpp */
