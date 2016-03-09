//
//  NativeBridge.h
//  MazeJump
//
//  Created by wang haibo on 15/8/17.
//
//

#ifndef __TinyFlare__NativeBridge__
#define __TinyFlare__NativeBridge__

#include "cocos2d.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#import <UIKit/UIKit.h>
#import "RootViewController.h"
#endif
class NativeBridge : public cocos2d::Ref
{
    NativeBridge();
public:
    static NativeBridge* getInstance();
    virtual ~NativeBridge();
    
    bool isNetworkAvailable();
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    void setRootViewController(RootViewController* viewController);
    void openItunesURL();
    bool isBelowIPhone4S();
#endif
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    void exitGame();
    void openGooglePlay();
#endif
    void initAdmob();
    void playInterstitialAds();
    bool isInterstitialAdsReady();
    void requestAndLoadInterstitialAds();
private:
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS 
    RootViewController* mViewController;
#endif
};

#endif /* defined(__TinyFlare__NativeBridge__) */
