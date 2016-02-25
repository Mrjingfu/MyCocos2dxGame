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

#define CLASS_NAME "com/plugin/wanax/util/ChannelOpe"

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
   log("isNetworkAvailable");
   bool result = false;
   JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "isNetworkAvailable", "()Z")) {

        result = t.env->CallStaticBooleanMethod(t.classID,t.methodID);

        if (t.env->ExceptionOccurred()) {

            t.env->ExceptionDescribe();

            t.env->ExceptionClear();
        }
        t.env->DeleteLocalRef(t.classID);
    }

    return result;
}
void NativeBridge::initAdmob()
{
}
void NativeBridge::playInterstitialAds()
{

    log("playInterstitialAds");
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "playInterstitialAds", "()V")) {

        t.env->CallStaticVoidMethod(t.classID, t.methodID);

        if (t.env->ExceptionOccurred()) {

            t.env->ExceptionDescribe();

            t.env->ExceptionClear();

            return;
        }
        t.env->DeleteLocalRef(t.classID);
    }

}
bool NativeBridge::isInterstitialAdsReady()
{
   log("isInterstitialAdsReady");
   bool result = false;
   JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "isInterstitialAdsReady", "()Z")) {

        result = t.env->CallStaticBooleanMethod(t.classID,t.methodID);

        if (t.env->ExceptionOccurred()) {

            t.env->ExceptionDescribe();

            t.env->ExceptionClear();
        }
        t.env->DeleteLocalRef(t.classID);
    }

    return result;
}
void NativeBridge::requestAndLoadInterstitialAds()
{
    log("requestAndLoadInterstitialAds");
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "requestAndLoadInterstitialAds", "()V")) {

        t.env->CallStaticVoidMethod(t.classID, t.methodID);

        if (t.env->ExceptionOccurred()) {

            t.env->ExceptionDescribe();

            t.env->ExceptionClear();

            return;
        }
        t.env->DeleteLocalRef(t.classID);
    }
}
void NativeBridge::exitGame()
{
    log("exitGame");
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "exitGame", "()V")) {

       t.env->CallStaticVoidMethod(t.classID, t.methodID);

        if (t.env->ExceptionOccurred()) {

            t.env->ExceptionDescribe();

            t.env->ExceptionClear();

            return;
        }
        t.env->DeleteLocalRef(t.classID);
    }

}
void NativeBridge::openGooglePlay()
{
    log("openGooglePlay");
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "openGooglePlay", "()V")) {

       t.env->CallStaticVoidMethod(t.classID, t.methodID);

        if (t.env->ExceptionOccurred()) {

            t.env->ExceptionDescribe();

            t.env->ExceptionClear();

            return;
        }
        t.env->DeleteLocalRef(t.classID);
    }

}
