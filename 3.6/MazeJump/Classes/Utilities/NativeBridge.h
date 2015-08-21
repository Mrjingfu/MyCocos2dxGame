//
//  NativeBridge.h
//  MazeJump
//
//  Created by wang haibo on 15/8/17.
//
//

#ifndef __MazeJump__NativeBridge__
#define __MazeJump__NativeBridge__

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
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    void setRootViewController(RootViewController* viewController);
    void openItunesURL();
#endif
    
    void initAdmob();
    void showAdsView();
    void hideAdsView();
    void playInterstitialAds();
    void showIndicatorView();
    void hideIndicatorView();
    
    void showRateAppView();
    
    std::string generateUUID();
private:
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    RootViewController* mViewController;
#endif
};

#endif /* defined(__MazeJump__NativeBridge__) */
