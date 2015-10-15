//
//  NativeBridge.cpp
//  MazeJump
//
//  Created by wang haibo on 15/8/17.
//
//

#include "NativeBridge.h"
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
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
void NativeBridge::setRootViewController(RootViewController* viewController)
{
    mViewController = viewController;
}
void NativeBridge::openItunesURL()
{
    CCLOG("openItunesURL");
    if(mViewController != nil)
        [mViewController openItunesURL];
}
#endif
void NativeBridge::initAdmob()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
//    std::string remove = localStorageGetItem("RemoveAds");
//    if(remove.empty())
//        localStorageSetItem("RemoveAds", "false");
//    
//    bool removeAds = Value(localStorageGetItem("RemoveAds")).asBool();
//    if (!removeAds) {
//        CCLOG("initAdmob");
//        [mViewController initAdmob];
//    }
#endif
}
void NativeBridge::showAdsView()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
//    bool removeAds = Value(localStorageGetItem("RemoveAds")).asBool();
//    if (!removeAds) {
//        CCLOG("showAdsView");
//        if(mViewController != nil)
//            [mViewController showAdsView];
//    }
#endif
}
void NativeBridge::hideAdsView()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    CCLOG("hideAdsView");
    if(mViewController != nil)
        [mViewController hideAdsView];
#endif
}
void NativeBridge::playInterstitialAds()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
//    bool removeAds = Value(localStorageGetItem("RemoveAds")).asBool();
//    if (!removeAds) {
//        CCLOG("playInterstitialAds");
//        if(mViewController != nil)
//            [mViewController playInterstitialAds];
//    }
#endif
}
void NativeBridge::showIndicatorView()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    CCLOG("showIndicatorView");
    if(mViewController != nil)
        [mViewController showIndicatorView];
#endif
}
void NativeBridge::hideIndicatorView()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    CCLOG("hideIndicatorView");
    if(mViewController != nil)
        [mViewController hideIndicatorView];
#endif
}

void NativeBridge::showRateAppView()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    CCLOG("showRateAppView");
    if(mViewController != nil)
    {
        LanguageType lt= CCApplication::getInstance()->getCurrentLanguage();
        switch (lt) {
            case LanguageType::CHINESE:
                [mViewController showRateAppViewCH];
                break;
                
            default:
                [mViewController showRateAppViewEN];
                break;
        }
    }
#endif
}
std::string NativeBridge::generateUUID()
{
    std::string ret;
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    CCLOG("generateUUID");
    if(mViewController != nil)
        ret = [[mViewController generateUUID] UTF8String];
#endif
    return ret;
}