//
//  NativeBridge_android.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/5/25.
//
//

#include "NativeBridge.h"
#include "EncrytionUtility.h"
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
void NativeBridge::logWithUserData()
{
    log("logWithUserData");
    cocos2d::Value currentStage(EncrytionUtility::getIntegerForKey("CurrentStage", 1));
    cocos2d::Value currentStardustNum(EncrytionUtility::getIntegerForKey("CurStardustNum", 0));
    cocos2d::Value stardustDropLevel(EncrytionUtility::getIntegerForKey("StardustDropLevel", 1));
    cocos2d::Value itemDropLevel(EncrytionUtility::getIntegerForKey("ItemDropLevel", 1));
    cocos2d::Value itemEffectLevel(EncrytionUtility::getIntegerForKey("ItemEffectLevel", 1));
    
    JNIEnv* env = JniHelper::getEnv();
    jclass class_HashMap = env->FindClass("java/util/Hashtable");
    jmethodID construct_method = env->GetMethodID( class_HashMap, "<init>","()V");
    jobject obj_Map = env->NewObject( class_HashMap, construct_method, "");

    jmethodID add_method= env->GetMethodID( class_HashMap,"put","(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
        
    jstring first = env->NewStringUTF("CurrentStage");
    jstring second = env->NewStringUTF(currentStage.asString().c_str());
    env->CallObjectMethod(obj_Map, add_method, first, second);
    env->DeleteLocalRef(first);
    env->DeleteLocalRef(second);
        
    first = env->NewStringUTF("CurStardustNum");
    second = env->NewStringUTF(currentStardustNum.asString().c_str());
    env->CallObjectMethod(obj_Map, add_method, first, second);
    env->DeleteLocalRef(first);
    env->DeleteLocalRef(second);
        
    first = env->NewStringUTF("StardustDropLevel");
    second = env->NewStringUTF(stardustDropLevel.asString().c_str());
    env->CallObjectMethod(obj_Map, add_method, first, second);
    env->DeleteLocalRef(first);
    env->DeleteLocalRef(second);
        
    first = env->NewStringUTF("ItemDropLevel");
    second = env->NewStringUTF(itemDropLevel.asString().c_str());
    env->CallObjectMethod(obj_Map, add_method, first, second);
    env->DeleteLocalRef(first);
    env->DeleteLocalRef(second);
        
    first = env->NewStringUTF("ItemEffectLevel");
    second = env->NewStringUTF(itemEffectLevel.asString().c_str());
    env->CallObjectMethod(obj_Map, add_method, first, second);
    env->DeleteLocalRef(first);
    env->DeleteLocalRef(second);

    env->DeleteLocalRef(class_HashMap);
    
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "logWithUserData", "(Ljava/util/Hashtable;)V")) {
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID, obj_Map);
        
        if (t.env->ExceptionOccurred()) {
            
            t.env->ExceptionDescribe();
            
            t.env->ExceptionClear();
            
            return;
        }
        env->DeleteLocalRef(obj_Map);
        t.env->DeleteLocalRef(t.classID);
    }
}