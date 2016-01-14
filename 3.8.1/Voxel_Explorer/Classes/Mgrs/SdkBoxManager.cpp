//
//  SdkBoxManager.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 16/1/14.
//
//

#include "SdkBoxManager.hpp"
USING_NS_CC;
SdkBoxManager* g_pSdkBoxManagerInstance = nullptr;
SdkBoxManager* SdkBoxManager::getInstance()
{
    if( g_pSdkBoxManagerInstance == nullptr )
        g_pSdkBoxManagerInstance = new SdkBoxManager();
    
    return g_pSdkBoxManagerInstance;
}
SdkBoxManager::SdkBoxManager()
{
}
SdkBoxManager::~SdkBoxManager()
{
}
#pragma mark GoogleAnalytics
void SdkBoxManager::registerGoogleAnalytics()
{
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
    sdkbox::PluginGoogleAnalytics::init();
    sdkbox::PluginGoogleAnalytics::enableAdvertisingTracking(true);
#endif
}
void SdkBoxManager::logScreen(std::string title)
{
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
    sdkbox::PluginGoogleAnalytics::logScreen(title);
#endif
}
void SdkBoxManager::logEvent(std::string eventCategory, std::string eventAction, std::string eventLabel, int value)
{
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
    sdkbox::PluginGoogleAnalytics::logEvent(eventCategory, eventAction, eventLabel, value);
#endif
}
void SdkBoxManager::logException(std::string exceptionDescription, bool isFatal)
{
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
    sdkbox::PluginGoogleAnalytics::logException(exceptionDescription, isFatal);
#endif
}
void SdkBoxManager::logTiming(std::string timingCategory, int timingInterval, std::string timingName, std::string timingLabel)
{
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
    sdkbox::PluginGoogleAnalytics::logTiming(timingCategory, timingInterval, timingName, timingLabel);
#endif
}
void SdkBoxManager::logSocial(std::string socialNetwork, std::string socialAction, std::string socialTarget)
{
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
    sdkbox::PluginGoogleAnalytics::logSocial(socialNetwork, socialAction, socialTarget);
#endif
}