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
#endif
//void NativeBridge::showAdsView()
//{
//#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
//    if (!EncrytionUtility::getBoolForKey("RemoveAds",false)) {
//        CCLOG("showAdsView");
//        if(mViewController != nil)
//            [mViewController showAdsView];
//    }
//#endif
//}
//void NativeBridge::hideAdsView()
//{
//#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
//    CCLOG("hideAdsView");
//    if(mViewController != nil)
//        [mViewController hideAdsView];
//#endif
//}
//void NativeBridge::playInterstitialAds()
//{
//#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
//    if (!EncrytionUtility::getBoolForKey("RemoveAds",false)) {
//        CCLOG("playInterstitialAds");
//        if(mViewController != nil)
//            [mViewController playInterstitialAds];
//    }
//#endif
//}
//void NativeBridge::showIndicatorView()
//{
//#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
//    CCLOG("showIndicatorView");
//    if(mViewController != nil)
//        [mViewController showIndicatorView];
//#endif
//}
//void NativeBridge::hideIndicatorView()
//{
//#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
//    CCLOG("hideIndicatorView");
//    if(mViewController != nil)
//        [mViewController hideIndicatorView];
//#endif
//}
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
void NativeBridge::openItunesURL()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    CCLOG("openItunesURL");
    if(mViewController != nil)
       [mViewController openItunesURL];
#endif
}
//void NativeBridge::logWithUserData()
//{
//#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
//    cocos2d::Value currentStage(EncrytionUtility::getIntegerForKey("CurrentStage", 1));
//    cocos2d::Value currentStardustNum(EncrytionUtility::getIntegerForKey("TotalGems", 0));
//    cocos2d::Value stardustDropLevel(EncrytionUtility::getIntegerForKey("StardustDropLevel", 1));
//    cocos2d::Value itemDropLevel(EncrytionUtility::getIntegerForKey("ItemDropLevel", 1));
//    cocos2d::Value itemEffectLevel(EncrytionUtility::getIntegerForKey("ItemEffectLevel", 1));
//    
//    NSDictionary* dictionary = [NSDictionary dictionaryWithObjectsAndKeys:
//                                [NSString stringWithUTF8String: currentStage.asString().c_str()],@"CurrentStage",
//                                [NSString stringWithUTF8String: currentStardustNum.asString().c_str()],@"TotalGems",
//                                [NSString stringWithUTF8String: stardustDropLevel.asString().c_str()],@"StardustDropLevel",
//                                [NSString stringWithUTF8String: itemDropLevel.asString().c_str()],@"ItemDropLevel",
//                                [NSString stringWithUTF8String: itemEffectLevel.asString().c_str()],@"ItemEffectLevel", nil];
//    [Flurry logEvent:@"USER_DATA" withParameters:dictionary];
//#endif
//}