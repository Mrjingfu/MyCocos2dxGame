//
//  TinyFlare.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/3/12.
//
//

#include "TinyFlare.h"
#include "GameController.h"
#include "NativeBridge.h"
#include "StoreEventHandler.h"
USING_NS_CC;
using namespace soomla;

Scene* TinyFlare::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TinyFlare::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
TinyFlare::TinyFlare()
{
}
// on "init" you need to initialize your instance
bool TinyFlare::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto keyboardListener=EventListenerKeyboard::create();
    keyboardListener->onKeyReleased=CC_CALLBACK_2(TinyFlare::onKeyReleased,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener,this);
    
    return true;
}

void TinyFlare::onEnter()
{
    Layer::onEnter();
    NativeBridge::getInstance()->logWithUserData();
    NativeBridge::getInstance()->showRateAppView();
    NativeBridge::getInstance()->showAdsView();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCSoomlaStore::getInstance()->startIabServiceInBg();
#endif
    
    scheduleUpdate();
    if(!GameController::getInstance()->init(this))
        CCLOGERROR("GameController init failed!");
    ////lwwhb add for debug
    //GameController::getInstance()->resetData();
    ////
}
void TinyFlare::onExit()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCSoomlaStore::getInstance()->stopIabServiceInBg();
#endif
    NativeBridge::getInstance()->hideAdsView();
    GameController::getInstance()->destroy();
    unscheduleUpdate();
    Layer::onExit();
}
void TinyFlare::update(float delta)
{
    GameController::getInstance()->update(delta);
}
void TinyFlare::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *unused_event)
{
    Director::getInstance()->end();
}