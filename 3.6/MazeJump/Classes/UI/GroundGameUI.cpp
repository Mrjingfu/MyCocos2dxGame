//
//  GroundGameUI.cpp
//
//
//
//

#include "GroundGameUI.h"
#include "GameController.h"
#include "GameConst.h"
#include "UtilityHelper.h"
#include "UIManager.h"
#include "storage/local-storage/LocalStorage.h"
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
    float scale = size.width /640.f;
    
    
    ui::ImageView* awardImg = ui::ImageView::create(UtilityHelper::getLocalString("UI_GROUND_AWARD_TV"));
    awardImg->setScale(scale);
    awardImg->setPosition(Vec2(size.width*0.5, size.height*0.15));
    addChild(awardImg);
  
    Label* goldRewardTv = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),Value(Value(localStorageGetItem(USER_GOLD_NUM)).asInt()).asString());
    goldRewardTv->setAnchorPoint(Vec2(1, 0.5));
    goldRewardTv->setPosition(Vec2(size.width*0.6, size.height*0.16));
    goldRewardTv->setScale(scale*0.5);
    goldRewardTv->setHorizontalAlignment(TextHAlignment::RIGHT);
   addChild(goldRewardTv);
    
    Label* heartRewardTv = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),Value(Value(localStorageGetItem(USER_GOLD_NUM)).asInt()).asString());
    heartRewardTv->setAnchorPoint(Vec2(1, 0.5));
    heartRewardTv->setPosition(Vec2(size.width*0.6, size.height*0.07));
    heartRewardTv->setScale(scale*0.5);
    heartRewardTv->setHorizontalAlignment(TextHAlignment::RIGHT);
   addChild(heartRewardTv);

    return true;
}
void GroundGameUI::onMazeJumpWin(cocos2d::EventCustom *sender)
{
    CCLOG("onMazeJumpWin");
    UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_GROUND_WIN);
    UIManager::getInstance()->showPopUp();
    
}
void GroundGameUI::onMazeJumpLose(cocos2d::EventCustom *sender)
{
    CCLOG("onMazeJumpLose");
    UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_GROUND_LOSE);
    UIManager::getInstance()->showPopUp();
}
void GroundGameUI::onGroundRecordEnd(cocos2d::EventCustom *sender)
{
    CCLOG("onGroundRecordEnd");
    UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_GROUND_RECOVER);
    UIManager::getInstance()->showPopUp();
}

