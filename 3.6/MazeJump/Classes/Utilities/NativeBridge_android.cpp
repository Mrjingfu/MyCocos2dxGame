//
//  NativeBridge_android.cpp
//  MazeJump
//
//  Created by wang haibo on 15/8/21.
//
//

#include <stdio.h>
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
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "showRateAppView", "()V")) {
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        
        if (t.env->ExceptionOccurred()) {
            
            t.env->ExceptionDescribe();
            
            t.env->ExceptionClear();
            
            return;
        }
        t.env->DeleteLocalRef(t.classID);
    }
    
}
void NativeBridge::playInterstitialAds()
{
    log("playInterstitialAds");
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "playInterstitialAds", "()V")) {
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        
        if (t.env->ExceptionOccurred()) {
            
            t.env->ExceptionDescribe();
            
            t.env->ExceptionClear();
            
            return;
        }
        t.env->DeleteLocalRef(t.classID);
    }
    
}
void NativeBridge::showIndicatorView()
{
    log("showIndicatorView");
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "setIndicatorViewVisible", "(Z)V")) {
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID, true);
        
        if (t.env->ExceptionOccurred()) {
            
            t.env->ExceptionDescribe();
            
            t.env->ExceptionClear();
            
            return;
        }
        t.env->DeleteLocalRef(t.classID);
    }
    
}
void NativeBridge::hideIndicatorView()
{
    log("hideIndicatorView");
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "setIndicatorViewVisible", "(Z)V")) {
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID, false);
        
        if (t.env->ExceptionOccurred()) {
            
            t.env->ExceptionDescribe();
            
            t.env->ExceptionClear();
            
            return;
        }
        t.env->DeleteLocalRef(t.classID);
    }
}
std::string NativeBridge::generateUUID()
{
    log("generateUUID");
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "generateUUID", "(Z)Ljava/lang/String;")) {
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID, false);
        
        if (t.env->ExceptionOccurred()) {
            
            t.env->ExceptionDescribe();
            
            t.env->ExceptionClear();
            
            return "";
        }
        t.env->DeleteLocalRef(t.classID);
    }
}
void NativeBridge::initAdmob()
{
}