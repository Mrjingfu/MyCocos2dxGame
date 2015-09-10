//
//  GroundWinPopUpUI.cpp
//
//
//
//

#include "GroundWinPopUpUI.h"
#include "UtilityHelper.h"
#include "GameConst.h"
#include "MainScene.h"
#include "UIManager.h"
#include "GameController.h"
#include "NativeBridge.h"
#include "LevelsManager.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;

GroundWinPopUpUI* GroundWinPopUpUI::create()
{
    GroundWinPopUpUI *pRet = new(std::nothrow) GroundWinPopUpUI();
    if (pRet)
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

GroundWinPopUpUI::GroundWinPopUpUI()
{
}
GroundWinPopUpUI::~GroundWinPopUpUI()
{
}

void GroundWinPopUpUI::onEnter()
{
    BasePopUpUI::onEnter();
    init();
    
    NativeBridge::getInstance()->showAdsView();
}
void GroundWinPopUpUI::onExit()
{
    NativeBridge::getInstance()->hideAdsView();
    BasePopUpUI::onExit();
}
bool GroundWinPopUpUI::init()
{

    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.width /640.0f;

    m_popupBgLayer = cocos2d::ui::ImageView::create(UtilityHelper::getLocalString("UI_GROUND_SUC_PANEL"),cocos2d::ui::TextureResType::PLIST);
    m_popupBgLayer->setPosition(Vec2(size.width*0.5,size.height*0.5));
    m_popupBgLayer->setScale(scale);
    m_dialogLayer->addChild(m_popupBgLayer);
    
    cocos2d::ui::ImageView* glodView = cocos2d::ui::ImageView::create("ui_gold.png",cocos2d::ui::TextureResType::PLIST);
    glodView->setPosition(Vec2(size.width*0.3,size.height*0.56));
    glodView->setScale(scale);
    m_dialogLayer->addChild(glodView);
    
    cocos2d::ui::ImageView* heartView = cocos2d::ui::ImageView::create("ui_heart.png",cocos2d::ui::TextureResType::PLIST);
    heartView->setPosition(Vec2(size.width*0.3,size.height*0.48));
    heartView->setScale(scale);
    m_dialogLayer->addChild(heartView);
    
    
    
    Label* goldRewardTv = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),Value(GameController::getInstance()->getCurrentGoldReward()).asString());
    goldRewardTv->setAnchorPoint(Vec2(1, 0.5));
    goldRewardTv->setPosition(Vec2(size.width*0.7, size.height*0.56));
    goldRewardTv->setScale(scale);
    goldRewardTv->setHorizontalAlignment(TextHAlignment::RIGHT);
    m_dialogLayer->addChild(goldRewardTv);
    
    Label* heartRewardTv = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),Value(GameController::getInstance()->getCurrentHeartReward()).asString());
    heartRewardTv->setAnchorPoint(Vec2(1, 0.5));
    heartRewardTv->setPosition(Vec2(size.width*0.7, size.height*0.48));
    heartRewardTv->setScale(scale);
    heartRewardTv->setHorizontalAlignment(TextHAlignment::RIGHT);
    m_dialogLayer->addChild(heartRewardTv);
    
    cocos2d::ui::Button* nextBtn = cocos2d::ui::Button::create(UtilityHelper::getLocalString("UI_GROUND_SUC_NEXT_BTN"),"","",cocos2d::ui::TextureResType::PLIST);
    nextBtn->setScale(scale);
    nextBtn->setPosition(Vec2(size.width*0.5,size.height*0.55));
    m_dialogLayer->addChild(nextBtn);
    
    
   cocos2d::ui::Button* reviveBtn = cocos2d::ui::Button::create(UtilityHelper::getLocalString("UI_GROUND_BTN_SUC_BACK"),"","",cocos2d::ui::TextureResType::PLIST);
    reviveBtn->setScale(scale);
    reviveBtn->setPosition(Vec2(size.width*0.5,size.height*0.38));
    m_dialogLayer->addChild(reviveBtn);
    
    nextBtn->addClickEventListener(CC_CALLBACK_1(GroundWinPopUpUI::onNext, this));
    reviveBtn->addClickEventListener(CC_CALLBACK_1(GroundWinPopUpUI::onBack, this));
    
    
    
    if (GameController::getInstance()->getMazeMode() == GameController::MAZE) {
        glodView->setVisible(false);
        heartView->setVisible(false);
        goldRewardTv->setVisible(false);
        heartRewardTv->setVisible(false);
        reviveBtn->setPosition(Vec2(size.width*0.5,size.height*0.45));
        int level = Value(localStorageGetItem(USER_MAZE_LEVEL)).asInt();
        int maxLevel = LevelsManager::getInstance()->getMaxLevels();
        if (level>=maxLevel) {
            nextBtn->setVisible(false);
            reviveBtn->setPosition(Vec2(size.width*0.5,size.height*0.5));
        }
        
        
    }else if (GameController::getInstance()->getMazeMode() == GameController::NORAML)
    {
        nextBtn->setVisible(false);
    }
    return true;

    
}
void GroundWinPopUpUI::onNext(cocos2d::Ref *ref)
{
    UIManager::getInstance()->playBtnSound();
    UIManager::getInstance()->hidePopUp(true,CC_CALLBACK_0(GroundWinPopUpUI::onHideNextPopUpEnd, this));

}
void GroundWinPopUpUI::onHideNextPopUpEnd()
{
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_MAZE_CHANAGE_LEVEL);
    GameController::getInstance()->changeToMap(false, Value(localStorageGetItem(USER_MAZE_LEVEL)).asInt());
}
void GroundWinPopUpUI::onBack(cocos2d::Ref *ref)
{
    UIManager::getInstance()->playBtnSound();
    UIManager::getInstance()->hidePopUp(true,CC_CALLBACK_0(GroundWinPopUpUI::onHideBackPopUpEnd, this));
}
void GroundWinPopUpUI::onHideBackPopUpEnd()
{
    if (GameController::getInstance()->getMazeMode() == GameController::MAZE) {
        GameController::getInstance()->switchToMenu();
    }else if (GameController::getInstance()->getMazeMode() == GameController::NORAML)
    {
        GameController::getInstance()->switchToRainbowRun();
    }
}
