//
//  LogoScene.cpp
//  MazeJump
//
//  Created by wang haibo on 15/6/23.
//
//

#include "LogoScene.h"
#include "GroundLayer.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "MainScene.h"
#include "LevelsManager.h"
#include "PatternsManager.h"
#include "SimpleAudioEngine.h"
#include "RoleManager.h"
#include "GameCenterController.h"
#include "SdkBoxManager.h"
#include "NativeBridge.h"
#include "GameConst.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;
using namespace CocosDenshion;
Scene* LogoScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LogoScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
LogoScene::LogoScene()
{
    m_pLogoSprite = nullptr;
    m_pWhiteLayer = nullptr;
}
// on "init" you need to initialize your instance
bool LogoScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    auto size = Director::getInstance()->getVisibleSize();
    m_pLogoSprite = Sprite::create("logo.png");
    if(!m_pLogoSprite)
        return false;
    float scale = size.width / 960.0f;
    m_pLogoSprite->setPosition(size.width*0.5f, size.height*0.5f);
    m_pLogoSprite->setOpacity(0);
    m_pLogoSprite->setScale(scale);
    addChild(m_pLogoSprite);
    
    EaseSineOut* easeOut = EaseSineOut::create(FadeIn::create(1.0f));
    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LogoScene::precache, this));
    
    Sequence* sequence = Sequence::create( easeOut, callFunc, NULL);
    m_pLogoSprite->runAction(sequence);
    
    m_pWhiteLayer = LayerColor::create(Color4B::WHITE);
    if(!m_pWhiteLayer)
        return false;
    this->addChild(m_pWhiteLayer);
    EaseExponentialIn* fadeOut = EaseExponentialIn::create(FadeOut::create(1.0f));
    m_pWhiteLayer->runAction(fadeOut);
    
    NativeBridge::getInstance()->showIndicatorView();
    
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
    SdkBoxManager::getInstance()->logScreen("LogoScene");
#endif
    return true;
}
void LogoScene::precache()
{
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
    GameCenterController::getInstance()->registerGameCenterController();
#endif
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
    SdkBoxManager::getInstance()->registerIAPListener();
    SdkBoxManager::getInstance()->registerGoogleAnalytics();
    NativeBridge::getInstance()->initAdmob();
    
    int gold = Value(localStorageGetItem(USER_GOLD_NUM)).asInt();
    int heart = Value(localStorageGetItem(USER_HEART_NUM)).asInt();
    int maxlevel = Value(localStorageGetItem(USER_MAX_LEVEL)).asInt();
    
    
    if(gold >= 10000)
        SdkBoxManager::getInstance()->logEvent("Game UserInfo", USER_GOLD_NUM, "more than 10000", gold);
    else if(gold >= 3000)
        SdkBoxManager::getInstance()->logEvent("Game UserInfo", USER_GOLD_NUM, "more than 3000", gold);
    else if(gold >= 450)
        SdkBoxManager::getInstance()->logEvent("Game UserInfo", USER_GOLD_NUM, "more than 450", gold);
    
    if(heart >= 100)
        SdkBoxManager::getInstance()->logEvent("Game UserInfo", USER_HEART_NUM, "more than 100", heart);
    else if(heart >= 50)
        SdkBoxManager::getInstance()->logEvent("Game UserInfo", USER_HEART_NUM, "more than 50", heart);
    else if(heart >= 10)
        SdkBoxManager::getInstance()->logEvent("Game UserInfo", USER_HEART_NUM, "more than 10", heart);
    
    if(maxlevel >= 1000)
        SdkBoxManager::getInstance()->logEvent("Game UserInfo", USER_MAX_LEVEL, "more than 1000", maxlevel);
    else if(maxlevel >= 800)
        SdkBoxManager::getInstance()->logEvent("Game UserInfo", USER_MAX_LEVEL, "more than 800", maxlevel);
    else if(maxlevel >= 600)
        SdkBoxManager::getInstance()->logEvent("Game UserInfo", USER_MAX_LEVEL, "more than 600", maxlevel);
    else if(maxlevel >= 500)
        SdkBoxManager::getInstance()->logEvent("Game UserInfo", USER_MAX_LEVEL, "more than 500", maxlevel);
    else if(maxlevel >= 400)
        SdkBoxManager::getInstance()->logEvent("Game UserInfo", USER_MAX_LEVEL, "more than 400", maxlevel);
    else if(maxlevel >= 300)
        SdkBoxManager::getInstance()->logEvent("Game UserInfo", USER_MAX_LEVEL, "more than 300", maxlevel);
    else if(maxlevel >= 250)
        SdkBoxManager::getInstance()->logEvent("Game UserInfo", USER_MAX_LEVEL, "more than 250", maxlevel);
    else if(maxlevel >= 200)
        SdkBoxManager::getInstance()->logEvent("Game UserInfo", USER_MAX_LEVEL, "more than 200", maxlevel);
    else if(maxlevel >= 150)
        SdkBoxManager::getInstance()->logEvent("Game UserInfo", USER_MAX_LEVEL, "more than 150", maxlevel);
    else if(maxlevel >= 100)
        SdkBoxManager::getInstance()->logEvent("Game UserInfo", USER_MAX_LEVEL, "more than 100", maxlevel);
    else if(maxlevel >= 50)
        SdkBoxManager::getInstance()->logEvent("Game UserInfo", USER_MAX_LEVEL, "more than 50", maxlevel);
    else if(maxlevel >= 30)
        SdkBoxManager::getInstance()->logEvent("Game UserInfo", USER_MAX_LEVEL, "more than 30", maxlevel);
    else if(maxlevel >= 20)
        SdkBoxManager::getInstance()->logEvent("Game UserInfo", USER_MAX_LEVEL, "more than 20", maxlevel);
    else if(maxlevel >= 10)
        SdkBoxManager::getInstance()->logEvent("Game UserInfo", USER_MAX_LEVEL, "more than 10", maxlevel);
#endif
    
    if(!PatternsManager::getInstance()->init("patterns.plist"))
        CCLOGERROR("no patterns file!");
    
    if(!LevelsManager::getInstance()->init("levels.plist"))
        CCLOGERROR("no levels file!");
    if (!RoleManager::getInstance()->init())
        CCLOGERROR("role init error!");

    if(m_pWhiteLayer)
    {
        EaseExponentialOut* fadeIn = EaseExponentialOut::create(FadeIn::create(1.0f));
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LogoScene::endcache, this));
        Sequence* sequence = Sequence::create(fadeIn, callFunc, NULL);
        m_pWhiteLayer->runAction(sequence);
    }
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common_ui.plist", "common_ui.png");
    NativeBridge::getInstance()->hideIndicatorView();
}
void LogoScene::endcache()
{
    m_pLogoSprite->setVisible(false);
    auto scene = MenuScene::createScene();
    Director::getInstance()->replaceScene(scene);
}