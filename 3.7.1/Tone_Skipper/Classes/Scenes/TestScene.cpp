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
    
    testABtn->setPosition(Vec2(size.width*0.3,size.height*0.8));
    testABtn->addClickEventListener([this,joystick](Ref* ref)
                                    {
                                            Player* nilo =MapMgrs::getInstance()->getNilo();
                                            Player* pudge =MapMgrs::getInstance()->getPudge();
                                        if (pudge && !pudge->isVisible()) {
                                            pudge->setVisible(true);
                                            joystick->removeJoyStickListener(MapMgrs::getInstance()->getNilo());
                                            joystick->addJoystickListener(MapMgrs::getInstance()->getPudge());
                                        }else
                                        {
                                            joystick->addJoystickListener(MapMgrs::getInstance()->getNilo());
                                            joystick->removeJoyStickListener(MapMgrs::getInstance()->getPudge());
                                             MapMgrs::getInstance()->getPudge()->setPlayerState(Player::PlayerState::PS_IDLE);
                                            pudge->setVisible(false);
                                        }
                                        pudge->setPosition(Vec2(nilo->getPosition().x+15 ,nilo->getPosition().y));
                                        
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