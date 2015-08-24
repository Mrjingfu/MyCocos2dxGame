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
#include "AudioEngine.h"
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
    
    
    cocos2d::ui::ImageView* awardImg = cocos2d::ui::ImageView::create(UtilityHelper::getLocalString("UI_GROUND_AWARD_TV"),cocos2d::ui::TextureResType::PLIST);
    awardImg->setScale(scale);
    awardImg->setPosition(Vec2(size.width*0.5, size.height*0.15));
    addChild(awardImg);
  
    Label* goldRewardTv = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),Value(GameController::getInstance()->getCurrentGoldReward()).asString());
    goldRewardTv->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    goldRewardTv->setPosition(Vec2(size.width*0.74, size.height*0.16));
    goldRewardTv->setScale(scale);
    goldRewardTv->setHorizontalAlignment(TextHAlignment::RIGHT);
   addChild(goldRewardTv);
    
    Label* heartRewardTv = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),Value(GameController::getInstance()->getCurrentHeartReward()).asString());
    heartRewardTv->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    heartRewardTv->setPosition(Vec2(size.width*0.74, size.height*0.065));
    heartRewardTv->setScale(scale);
    heartRewardTv->setHorizontalAlignment(TextHAlignment::RIGHT);
    addChild(heartRewardTv);

    cocos2d::ui::Button* helpBtn = cocos2d::ui::Button::create("ui_question.png","","",cocos2d::ui::TextureResType::PLIST);
    helpBtn->setPosition(Vec2(size.width*0.93, size.height*0.03));
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
            UIManager::getInstance()->playBtnSound();
            isShwoHelp = false;
            helpLayer->setVisible(false);
            return true;
        }else{
            return false;
        }
        
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(helplistener,helpLayer);
    
    
    cocos2d::ui::ImageView* handleTipsImg = cocos2d::ui::ImageView::create(UtilityHelper::getLocalString("UI_GROUND_HANDLE_TIPS"),cocos2d::ui::TextureResType::PLIST);
    handleTipsImg->setPosition(Vec2(size.width*0.5, size.height*0.26));
    handleTipsImg->setScale(scale);
    helpLayer->addChild(handleTipsImg);
    
    cocos2d::ui::ImageView* ruleTipsImg = cocos2d::ui::ImageView::create(UtilityHelper::getLocalString("UI_GROUND_RULE_TIPS"),cocos2d::ui::TextureResType::PLIST);
    ruleTipsImg->setPosition(Vec2(size.width*0.5, size.height*0.625));
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
     UIManager::getInstance()->playBtnSound();
    if (!isShwoHelp) {
        isShwoHelp = true;
         helpLayer->setVisible(true);
    }
    
}
void GroundGameUI::onMazeJumpWin(cocos2d::EventCustom *sender)
{
    CCLOG("onMazeJumpWin");
    cocos2d::experimental::AudioEngine::play2d("mazejump_sucess.wav", false, 0.5f);
    int goldReward = GameController::getInstance()->getCurrentGoldReward();
    int heartReward = GameController::getInstance()->getCurrentHeartReward();
    CCLOG("goldreward:%d,heartReward%d",goldReward,heartReward);
    localStorageSetItem(USER_GOLD_NUM, Value(Value(localStorageGetItem(USER_GOLD_NUM)).asInt()+goldReward).asString());
        localStorageSetItem(USER_HEART_NUM, Value(Value(localStorageGetItem(USER_HEART_NUM)).asInt()+ heartReward).asString());
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_GOLD_CHANGE);
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_HEART_CHANGE);
    UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_GROUND_WIN);
    UIManager::getInstance()->showPopUp();
    
}
void GroundGameUI::onMazeJumpLose(cocos2d::EventCustom *sender)
{
    CCLOG("onMazeJumpLose");
    cocos2d::experimental::AudioEngine::play2d("mazejump_failed.wav", false, 0.6f);
    UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_GROUND_LOSE);
    UIManager::getInstance()->showPopUp();
}
void GroundGameUI::onGroundRecordEnd(cocos2d::EventCustom *sender)
{
    CCLOG("onGroundRecordEnd");
    cocos2d::experimental::AudioEngine::play2d("mazejump_sucess.wav", false, 0.5f);
    UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_GROUND_RECOVER);
    UIManager::getInstance()->showPopUp();
}

