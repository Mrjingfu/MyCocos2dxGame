//
//  NativeBridge.cpp
//  MazeJump
//
//  Created by wang haibo on 15/8/17.
//
//

#include "NativeBridge.h"
#include "UtilityHelper.h"
USING_NS_CC;

static NativeBridge *s_NativeBridge = nullptr;
NativeBridge::NativeBridge()
{
}
NativeBridge* NativeBridge::getInstance()
{
    if (! s_NativeBridge)
    {
        s_NativeBridge = new NativeBridge();
    }
    
    return s_NativeBridge;
}
NativeBridge::~NativeBridge()
{
}

bool NativeBridge::isNetworkAvailable()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    CCLOG("isNetworkAvailable");
    if(mViewController != nil)
        return [mViewController isNetworkAvailable];
#endif
    return false;
}
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
void NativeBridge::setRootViewController(RootViewController* viewController)
{
    mViewController = viewController;
}
void NativeBridge::openItunesURL()
{
    CCLOG("openItunesURL");
    
    if(mViewController != nil)
        [mViewController openItunesURL : [NSString stringWithUTF8String: UtilityHelper::getAppStoreURL().c_str()]];
}
bool NativeBridge::isBelowIPhone4S()
{
    if(mViewController != nil)
        return [mViewController isBelowIPhone4S];
    return false;
}
#endif
void NativeBridge::initAdmob()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    CCLOG("initAdmob");
    [mViewController initAdmob];
#endif
}
void NativeBridge::playInterstitialAds()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    CCLOG("playInterstitialAds");
    if(mViewController != nil)
        [mViewController playInterstitialAds];
#endif
}
bool NativeBridge::isInterstitialAdsReady()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    CCLOG("isInterstitialAdsReady");
    if(mViewController != nil)
        return [mViewController isInterstitialAdsReady];
#endif
    return false;
}
void NativeBridge::requestAndLoadInterstitialAds()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    CCLOG("requestAndLoadInterstitialAds");
    if(mViewController != nil)
        [mViewController requestAndLoadInterstitialAds];
#endif
}