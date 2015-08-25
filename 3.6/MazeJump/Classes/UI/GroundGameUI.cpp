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
#include "NativeBridge.h"
#include "ShopPopUpUI.h"
#include "RegionButton.h"
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
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_MAZEJUMP_SHOW_ADA, std::bind(&GroundGameUI::onShowAda, this, std::placeholders::_1));
}
void GroundGameUI::onExit()
{
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_MAZEJUMP_WIN);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_MAZEJUMP_LOSE);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_MAZEJUMP_RECORD_END);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_MAZEJUMP_SHOW_ADA);
}
void GroundGameUI::onShowAda(cocos2d::EventCustom *sender)
{
    runAction(Sequence::create(DelayTime::create(0.3), CallFunc::create(CC_CALLBACK_0(GroundGameUI::onShowAdaDelayTime, this)),NULL));
}
void GroundGameUI::onShowAdaDelayTime()
{
    NativeBridge::getInstance()->playInterstitialAds();
}
bool GroundGameUI::init()
{
    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.width /640.f;
    
    
    
    RegionButton* goldBuyBtn = RegionButton::create("btn_plus_normal.png","btn_plus_pressed.png","",cocos2d::ui::TextureResType::PLIST);
    goldBuyBtn->setTouchRegionSize(cocos2d::Size(150*scale, goldBuyBtn->getContentSize().width*scale));
    goldBuyBtn->setPosition(Vec2(25*scale, size.height*0.95));
    goldBuyBtn->setScale(scale);
    addChild(goldBuyBtn);
    
    
    RegionButton* heartBuyBtn = RegionButton::create("btn_plus_normal.png","btn_plus_pressed.png","",cocos2d::ui::TextureResType::PLIST);
    heartBuyBtn->setTouchRegionSize(cocos2d::Size(150*scale, heartBuyBtn->getContentSize().width*scale));
    heartBuyBtn->setPosition(Vec2(25*scale, size.height*0.95-50*scale));
    heartBuyBtn->setScale(scale);
    addChild(heartBuyBtn);
    
    
    goldBuyBtn->addClickEventListener(CC_CALLBACK_1(GroundGameUI::onShopBuyGold, this));
    
    heartBuyBtn->addClickEventListener(CC_CALLBACK_1(GroundGameUI::onShopBuyHeart, this));
    
    
    cocos2d::ui::ImageView* awardImg = cocos2d::ui::ImageView::create(UtilityHelper::getLocalString("UI_GROUND_AWARD_TV"),cocos2d::ui::TextureResType::PLIST);
    awardImg->setScale(scale);
    awardImg->setPosition(Vec2(size.width*0.5, size.height*0.23));
    addChild(awardImg);
    
    cocos2d::ui::ImageView* goldAni = cocos2d::ui::ImageView::create("ui_gold.png",cocos2d::ui::TextureResType::PLIST);
    goldAni->setPosition(Vec2(size.width*0.32, size.height*0.16));
    goldAni->setScale(scale);
    addChild(goldAni);
    
    
   cocos2d::ui::ImageView*  heartAni = cocos2d::ui::ImageView::create("ui_heart.png",cocos2d::ui::TextureResType::PLIST);
    heartAni->setPosition(Vec2(size.width*0.32, size.height*0.065));
    heartAni->setScale(scale);
    addChild(heartAni);
    
  
    Label* goldRewardTv = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),Value(GameController::getInstance()->getCurrentGoldReward()).asString());
    goldRewardTv->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    goldRewardTv->setPosition(Vec2(size.width*0.71, size.height*0.165));
    goldRewardTv->setScale(scale);
    goldRewardTv->setHorizontalAlignment(TextHAlignment::RIGHT);
    addChild(goldRewardTv);
    
    Label* heartRewardTv = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),Value(GameController::getInstance()->getCurrentHeartReward()).asString());
    heartRewardTv->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    heartRewardTv->setPosition(Vec2(size.width*0.71, size.height*0.067));
    heartRewardTv->setScale(scale);
    heartRewardTv->setHorizontalAlignment(TextHAlignment::RIGHT);
    addChild(heartRewardTv);

    RegionButton* helpBtn = RegionButton::create("ui_question.png","","",cocos2d::ui::TextureResType::PLIST);
    helpBtn->setTouchRegionSize(cocos2d::Size(130*scale, helpBtn->getContentSize().height*scale+15*scale));
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
void GroundGameUI::onShopBuyGold(cocos2d::Ref *ref)
{

    UIManager::getInstance()->playBtnSound();
    UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_SHOP);
    ShopPopUpUI* shopPopUi = static_cast<ShopPopUpUI*>(UIManager::getInstance()->getPopUpUI(BasePopUpUI::POPUP_SHOP));
    if (shopPopUi) {
        shopPopUi->setShopDisplay(ShopPopUpUI::SHOP_GOLD);
    }
    UIManager::getInstance()->showPopUp();
    
}
void GroundGameUI::onShopBuyHeart(cocos2d::Ref *ref)
{

    UIManager::getInstance()->playBtnSound();
    UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_SHOP);
    ShopPopUpUI* shopPopUi = static_cast<ShopPopUpUI*>(UIManager::getInstance()->getPopUpUI(BasePopUpUI::POPUP_SHOP));
    if (shopPopUi) {
        shopPopUi->setShopDisplay(ShopPopUpUI::SHOP_HEART);
    }
    UIManager::getInstance()->showPopUp();
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

