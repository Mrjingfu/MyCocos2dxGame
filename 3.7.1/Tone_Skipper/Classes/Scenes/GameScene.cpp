//
//  GameScene.cpp
//  Tone_Skipper
//
//  Created by wang haibo on 15/9/18.
//
//

#include "GameScene.h"
#include "JoyStick.h"
#include "MapMgrs.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
GameScene::GameScene()
{
}
// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    cocos2d::Size size = Director::getInstance()->getWinSize();
    
    if(!MapMgrs::getInstance()->init(this))
        return false;
    if(!MapMgrs::getInstance()->loadMap("1-1.tmx"))
        return false;
    
    JoyStick* joystick = JoyStick::create();
    if(joystick)
    {
        joystick->addJoystickListener(MapMgrs::getInstance()->getNilo());
        joystick->setEnableJoyStick(true);
        addChild(joystick);
    }
    return true;
}

void GameScene::onEnter()
{
    Layer::onEnter();
    scheduleUpdate();
}
void GameScene::onExit()
{
    unscheduleUpdate();
    Layer::onExit();
}
void GameScene::update(float delta)
{
    MapMgrs::getInstance()->update(delta);
}