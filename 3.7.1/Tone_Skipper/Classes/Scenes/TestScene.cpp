//
//  TestScene.cpp
//  Tone_Skipper
//
//  Created by wang haibo on 15/8/26.
//
//

#include "TestScene.h"
#include "JoyStick.h"
#include "MapMgrs.h"
#include "PopupUILayerManager.h"
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
    
    if(!MapMgrs::getInstance()->init(this))
        return false;
    if(!MapMgrs::getInstance()->loadMap("testmap.tmx"))
        return false;
    
    JoyStick* joystick = JoyStick::create();
    if(joystick)
    {
        joystick->addJoystickListener(MapMgrs::getInstance()->getNilo());
        addChild(joystick);
    }
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("joystick.plist");
    ui::Button* testABtn = ui::Button::create("a_normal.png", "a_clicked.png", "", ui::TextureResType::PLIST);
    if(!testABtn)
        return false;
    
    PopupUILayerManager::getInstance()->setParentLayer(this);
    
    
    testABtn->setPosition(Vec2(size.width*0.3,size.height*0.8));
    testABtn->addClickEventListener([this](Ref* ref)
                                    {
                                        PopupUILayerManager::getInstance()->openPopup(ePopupTest);
                                    });
    addChild(testABtn);
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
    MapMgrs::getInstance()->update(delta);
}