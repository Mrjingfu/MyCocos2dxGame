//
//  GroundGameUI.cpp
//
//
//
//

#include "GroundGameUI.h"
#include "GameController.h"
#include "GameConst.h"
USING_NS_CC;

GroundGameUI* GroundGameUI::create()
{
    GroundGameUI *pRet = new(std::nothrow) GroundGameUI();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

GroundGameUI::GroundGameUI()
{
    

}
GroundGameUI::~GroundGameUI()
{
}
void GroundGameUI::onEnter()
{
    Layer::onEnter();
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_MAZEJUMP_WIN, std::bind(&GroundGameUI::onMazeJumpWin, this, std::placeholders::_1));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_MAZEJUMP_LOSE, std::bind(&GroundGameUI::onMazeJumpLose, this, std::placeholders::_1));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_MAZEJUMP_RECORD_END, std::bind(&GroundGameUI::onGroundRecordEnd, this, std::placeholders::_1));
}
void GroundGameUI::onExit()
{
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_MAZEJUMP_WIN);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_MAZEJUMP_LOSE);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_MAZEJUMP_RECORD_END);
}
bool GroundGameUI::init()
{
    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.height /640.f;
    
    
    cocos2d::ui::Button* button = cocos2d::ui::Button::create("button_retry_up.png",
                                                            "button_retry_down.png");
    button->setScale(scale);
    button->setPosition(Vec2(size.width * 0.8f, size.height * 0.8f));
    button->setPressedActionEnabled(true);
    button->addClickEventListener([=](Ref* sender){
        
        
        GameController::getInstance()->switchToRainbowRun();
        
    });
    addChild(button);
    
    cocos2d::ui::Button* promptBtn = cocos2d::ui::Button::create("button_retry_up.png",
                                                              "button_retry_down.png");
    promptBtn->setPosition(Vec2(size.width * 0.5f, size.height * 0.8f));
    promptBtn->setTitleText("教程");
    promptBtn->setPressedActionEnabled(true);
    promptBtn->addClickEventListener([=](Ref* sender){
        
        
        GameController::getInstance()->createMap(true,GameController::getInstance()->getCurrentLevel());
        
    });
    promptBtn->setScale(scale);
    addChild(promptBtn);
  
    

    return true;
}
void GroundGameUI::onMazeJumpWin(cocos2d::EventCustom *sender)
{
    CCLOG("onMazeJumpWin");
}
void GroundGameUI::onMazeJumpLose(cocos2d::EventCustom *sender)
{
    CCLOG("onMazeJumpLose");
}
void GroundGameUI::onGroundRecordEnd(cocos2d::EventCustom *sender)
{
    CCLOG("onGroundRecordEnd");
}
