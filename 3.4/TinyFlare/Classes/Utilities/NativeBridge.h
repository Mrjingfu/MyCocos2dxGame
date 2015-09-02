//
//  NativeBridge.h
//  TinyFlare
//
//  Created by wang haibo on 15/5/14.
//
//

#ifndef __TinyFlare__NativeBridge__
#define __TinyFlare__NativeBridge__

#include "cocos2d.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#import <UIKit/UIKit.h>
#import "RootViewController.h"
#import "Flurry.h"
#endif
class NativeBridge : public cocos2d::Ref
{
    NativeBridge();
public:
    static NativeBridge* getInstance();
    virtual ~NativeBridge();
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    void setRootViewController(RootViewController* viewController);
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    void exitGame();
#endif
    void showAdsView();
    void hideAdsView();
    void playInterstitialAds();
    void showIndicatorView();
    void hideIndicatorView();
    void showRateAppView();
    void logWithUserData();
private:
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    RootViewController* mViewController;
#endif
};

#endif /* defined(__TinyFlare__NativeBridge__) */
