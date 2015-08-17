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
}
void GroundWinPopUpUI::onExit()
{
    BasePopUpUI::onExit();
}
bool GroundWinPopUpUI::init()
{

    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.width /640.0f;

    m_popupBgLayer = ui::ImageView::create(UtilityHelper::getLocalString("UI_GROUND_SUC_PANEL"));
    m_popupBgLayer->setPosition(Vec2(size.width*0.5,size.height*0.5));
    m_popupBgLayer->setScale(scale);
    m_dialogLayer->addChild(m_popupBgLayer);
    
    ui::ImageView* glodView = ui::ImageView::create("ui_gold.png");
    glodView->setPosition(Vec2(size.width*0.3,size.height*0.56));
    glodView->setScale(scale);
    m_dialogLayer->addChild(glodView);
    
    ui::ImageView* heartView = ui::ImageView::create("ui_heart.png");
    heartView->setPosition(Vec2(size.width*0.3,size.height*0.48));
    heartView->setScale(scale);
    m_dialogLayer->addChild(heartView);
    
    
    
    Label* goldRewardTv = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),Value(GameController::getInstance()->getCurrentGoldReward()).asString());
    goldRewardTv->setAnchorPoint(Vec2(1, 0.5));
    goldRewardTv->setPosition(Vec2(size.width*0.7, size.height*0.56));
    goldRewardTv->setScale(scale*0.5);
    goldRewardTv->setHorizontalAlignment(TextHAlignment::RIGHT);
    m_dialogLayer->addChild(goldRewardTv);
    
    Label* heartRewardTv = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),Value(GameController::getInstance()->getCurrentHeartReward()).asString());
    heartRewardTv->setAnchorPoint(Vec2(1, 0.5));
    heartRewardTv->setPosition(Vec2(size.width*0.7, size.height*0.48));
    heartRewardTv->setScale(scale*0.5);
    heartRewardTv->setHorizontalAlignment(TextHAlignment::RIGHT);
    m_dialogLayer->addChild(heartRewardTv);
    
    ui::Button* reviveBtn = ui::Button::create(UtilityHelper::getLocalString("UI_GROUND_BTN_SUC_BACK"));
    reviveBtn->setScale(scale);
    reviveBtn->setPosition(Vec2(size.width*0.5,size.height*0.4));
    m_dialogLayer->addChild(reviveBtn);
    
    reviveBtn->addClickEventListener(CC_CALLBACK_1(GroundWinPopUpUI::onBack, this));
    return true;
    

}
void GroundWinPopUpUI::onBack(cocos2d::Ref *ref)
{
     UIManager::getInstance()->playSound();
    UIManager::getInstance()->hidePopUp(true,CC_CALLBACK_0(GroundWinPopUpUI::onHidePopUpEnd, this));
}
void GroundWinPopUpUI::onHidePopUpEnd()
{
    GameController::getInstance()->switchToRainbowRun();
}
