//
//  NativeBridge_android.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/5/25.
//
//

#include "NativeBridge.h"
#include "jni/JniHelper.h"
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
void NativeBridge::showAdsView()
{
    log("showAdsView");
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "setAdVisible", "(Z)V")) {
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID, true);
        
        if (t.env->ExceptionOccurred()) {
            
            t.env->ExceptionDescribe();
            
            t.env->ExceptionClear();
            
            return;
        }
        t.env->DeleteLocalRef(t.classID);
    }
    
}
void NativeBridge::hideAdsView()
{
    log("hideAdsView");
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "setAdVisible", "(Z)V")) {
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID, false);
        
        if (t.env->ExceptionOccurred()) {
            
            t.env->ExceptionDescribe();
            
            t.env->ExceptionClear();
            
            return;
        }
        t.env->DeleteLocalRef(t.classID);
    }
    
}
void NativeBridge::showRateAppView()
{
    log("showRateAppView");
}
void NativeBridge::playInterstitialAds()
{
    log("playInterstitialAds");
}
void NativeBridge::showIndicatorView()
{
    log("showIndicatorView");
}
void NativeBridge::hideIndicatorView()
{
    log("hideIndicatorView");
}
void NativeBridge::logWithUserData()
{
    log("logWithUserData");
}