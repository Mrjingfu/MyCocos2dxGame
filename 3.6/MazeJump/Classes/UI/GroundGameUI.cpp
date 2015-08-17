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
    isShwoHelp = false;

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
  
    Label* goldRewardTv = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),Value(GameController::getInstance()->getCurrentGoldReward()).asString());
    goldRewardTv->setAnchorPoint(Vec2(1, 0.5));
    goldRewardTv->setPosition(Vec2(size.width*0.6, size.height*0.16));
    goldRewardTv->setScale(scale*0.5);
    goldRewardTv->setHorizontalAlignment(TextHAlignment::RIGHT);
   addChild(goldRewardTv);
    
    Label* heartRewardTv = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),Value(GameController::getInstance()->getCurrentHeartReward()).asString());
    heartRewardTv->setAnchorPoint(Vec2(1, 0.5));
    heartRewardTv->setPosition(Vec2(size.width*0.6, size.height*0.07));
    heartRewardTv->setScale(scale*0.5);
    heartRewardTv->setHorizontalAlignment(TextHAlignment::RIGHT);
   addChild(heartRewardTv);

    ui::Button* helpBtn = ui::Button::create("question.png");
    helpBtn->setPosition(Vec2(size.width*0.93, size.height*0.05));
    helpBtn->setScale(scale);
    addChild(helpBtn);
    
    helpLayer = cocos2d::LayerColor::create(cocos2d::Color4B(0, 0, 0, 150));
    helpLayer->setContentSize(size);
    addChild(helpLayer);
    auto helplistener = EventListenerTouchOneByOne::create();
    helplistener->setSwallowTouches(true);
    helplistener->onTouchBegan =  [this](Touch * ,Event *)
    {
        if (isShwoHelp) {
            UIManager::getInstance()->playSound();
            isShwoHelp = false;
            helpLayer->setVisible(false);
            return true;
        }else{
            return false;
        }
        
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(helplistener,helpLayer);
    
    
    cocos2d::ui::ImageView* handleTipsImg = ui::ImageView::create(UtilityHelper::getLocalString("UI_GROUND_HANDLE_TIPS"));
    handleTipsImg->setPosition(Vec2(size.width*0.5, size.height*0.25));
    handleTipsImg->setScale(scale);
    helpLayer->addChild(handleTipsImg);
    
    cocos2d::ui::ImageView* ruleTipsImg = ui::ImageView::create(UtilityHelper::getLocalString("UI_GROUND_RULE_TIPS"));
    ruleTipsImg->setPosition(Vec2(size.width*0.5, size.height*0.65));
    ruleTipsImg->setScale(scale);
    helpLayer->addChild(ruleTipsImg);


    
    helpBtn->addClickEventListener(CC_CALLBACK_1(GroundGameUI::onHelp, this));
    
    
    int parrentIndex = GameController::getInstance()->getDifficultLevel();
    if (parrentIndex<=1) {
        isShwoHelp=true;
        helpLayer->setVisible(true);

    }else
    {
        helpLayer ->setVisible(false);
    }
    
    return true;
}
void GroundGameUI::onHelp(Ref* ref)
{
     UIManager::getInstance()->playSound();
    if (!isShwoHelp) {
        isShwoHelp = true;
         helpLayer->setVisible(true);
    }
    
}
void GroundGameUI::onMazeJumpWin(cocos2d::EventCustom *sender)
{
    CCLOG("onMazeJumpWin");
    localStorageSetItem(USER_GOLD_NUM, Value(Value(localStorageGetItem(USER_GOLD_NUM)).asInt()+ GameController::getInstance()->getCurrentGoldReward()).asString());
        localStorageSetItem(USER_GOLD_NUM, Value(Value(localStorageGetItem(USER_HEART_NUM)).asInt()+ GameController::getInstance()->getCurrentHeartReward()).asString());
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_GOLD_CHANGE);
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_HEART_CHANGE);
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

