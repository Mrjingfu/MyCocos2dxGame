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
bool NativeBridge::isNetworkAvailable()
{
    return false;
}
void NativeBridge::initAdmob()
{
}
void NativeBridge::playInterstitialAds()
{
    // bool removeAds = Value(localStorageGetItem("RemoveAds")).asBool();
    // if (removeAds)
    //     return;
    // log("playInterstitialAds");
    // JniMethodInfo t;

    // if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "playInterstitialAds", "()V")) {

    //     t.env->CallStaticVoidMethod(t.classID, t.methodID);

    //     if (t.env->ExceptionOccurred()) {

    //         t.env->ExceptionDescribe();

    //         t.env->ExceptionClear();

    //         return;
    //     }
    //     t.env->DeleteLocalRef(t.classID);
    // }

}
bool NativeBridge::isInterstitialAdsReady()
{
    return false;
}
void NativeBridge::exitGame()
{
    // log("exitGame");
    // JniMethodInfo t;

    // if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "exitGame", "()V")) {

    //    t.env->CallStaticVoidMethod(t.classID, t.methodID);

    //     if (t.env->ExceptionOccurred()) {

    //         t.env->ExceptionDescribe();

    //         t.env->ExceptionClear();

    //         return;
    //     }
    //     t.env->DeleteLocalRef(t.classID);
    // }

}
void NativeBridge::openGooglePlay()
{
    // log("openGooglePlay");
    // JniMethodInfo t;

    // if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "openGooglePlay", "()V")) {

    //    t.env->CallStaticVoidMethod(t.classID, t.methodID);

    //     if (t.env->ExceptionOccurred()) {

    //         t.env->ExceptionDescribe();

    //         t.env->ExceptionClear();

    //         return;
    //     }
    //     t.env->DeleteLocalRef(t.classID);
    // }

}
