//
//  GameCenterController.cpp
//  MazeJump
//
//  Created by wang haibo on 15/8/17.
//
//

#include "GameCenterController.h"
#include <stdio.h>
#include "jni/JniHelper.h"
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
#include "NCSGameCenter.h"
#endif
USING_NS_CC;
#define CLASS_NAME "com/plugin/wanax/util/ChannelOpe"


GameCenterController* g_pGameCenterControllerInstance = nullptr;
GameCenterController* GameCenterController::getInstance()
{
    if( g_pGameCenterControllerInstance == nullptr )
        g_pGameCenterControllerInstance = new GameCenterController();

    return g_pGameCenterControllerInstance;
}

GameCenterController::GameCenterController()
{
//#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
//    m_AchievementDict = FileUtils::getInstance()->getValueMapFromFile("achievement.plist");
//#endif
}

GameCenterController::~GameCenterController()
{
}
void GameCenterController::registerGameCenterController()
{
    log("registerGameCenterController");
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "googleGameConnect", "()V")) {

       t.env->CallStaticVoidMethod(t.classID, t.methodID);

        if (t.env->ExceptionOccurred()) {

            t.env->ExceptionDescribe();

            t.env->ExceptionClear();

            return;
        }
        t.env->DeleteLocalRef(t.classID);
    }
}

void GameCenterController::openLeaderBoard()
{
    log("openLeaderBoard");
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "openLeaderBoard", "()V")) {

       t.env->CallStaticVoidMethod(t.classID, t.methodID);

        if (t.env->ExceptionOccurred()) {

            t.env->ExceptionDescribe();

            t.env->ExceptionClear();

            return;
        }
        t.env->DeleteLocalRef(t.classID);
    }
}
void GameCenterController::reportScore(const std::string& rank_id, const cocos2d::Value& value)
{
// (Ljava/lang/String;F)V


}
void GameCenterController::reportCachedScores()
{

}
void GameCenterController::retrieveTopXScores(const std::string& rank_id, int num)
{

}

// 打开成就页。
void GameCenterController::openAchievementBoard()
{
    log("openLeaderBoard");
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "openAchievementBoard", "()V")) {

       t.env->CallStaticVoidMethod(t.classID, t.methodID);

        if (t.env->ExceptionOccurred()) {

            t.env->ExceptionDescribe();

            t.env->ExceptionClear();

            return;
        }
        t.env->DeleteLocalRef(t.classID);
    }
}

void GameCenterController::reportAchievement(const std::string& strId, float percent)
{
    //log("reportAchievement");
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "reportAchievement", "(Ljava/lang/String;I)V")) {

        jstring jstr = t.env->NewStringUTF(strId.c_str());

        t.env->CallStaticVoidMethod(t.classID, t.methodID, jstr,(int)percent);

        if (t.env->ExceptionOccurred()) {

            t.env->ExceptionDescribe();

            t.env->ExceptionClear();

            return;
        }
        t.env->DeleteLocalRef(jstr);
        t.env->DeleteLocalRef(t.classID);
    }
}

void GameCenterController::reportLevel(int level)
{
    log("reportLevel");
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "reportLevel", "(I)V")) {

        t.env->CallStaticVoidMethod(t.classID, t.methodID, level);

        if (t.env->ExceptionOccurred()) {

            t.env->ExceptionDescribe();

            t.env->ExceptionClear();

            return;
        }
        t.env->DeleteLocalRef(t.classID);
    }
}
void GameCenterController::reportMoney(float goldcoins)
{
    log("reportLevel");
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "reportMoney", "(I)V")) {

        t.env->CallStaticVoidMethod(t.classID, t.methodID, (int)goldcoins);

        if (t.env->ExceptionOccurred()) {

            t.env->ExceptionDescribe();

            t.env->ExceptionClear();

            return;
        }
        t.env->DeleteLocalRef(t.classID);
    }
}
void GameCenterController::retrieveTopXLevel(int num)
{

}
void GameCenterController::retrieveTopXMoney(int num)
{

}