//
//  TestScene.cpp
//  Tone_Skipper
//
//  Created by wang haibo on 15/8/26.
//
//

#include "TestScene.h"
#include "ActorMgr.h"
#include "JoyStick.h"
USING_NS_CC;

Scene* TestScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TestScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
TestScene::TestScene()
{
}
// on "init" you need to initialize your instance
bool TestScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    cocos2d::Size size = Director::getInstance()->getWinSize();
    Player* nilo = ActorMgr::getInstance()->createPlayer(Player::PT_NILO);
    if(nilo)
    {
        nilo->setPosition(Vec2(size.width*0.5f, size.height*0.5f));
        this->addChild(nilo);
    }
    JoyStick* joystick = JoyStick::create();
    if(joystick)
    {
        joystick->addJoystickListener(nilo);
        addChild(joystick);
    }
    return true;
}

void TestScene::onEnter()
{
    Layer::onEnter();
    scheduleUpdate();
}
void TestScene::onExit()
{
    unscheduleUpdate();
    Layer::onExit();
}
void TestScene::update(float delta)
{
    
}