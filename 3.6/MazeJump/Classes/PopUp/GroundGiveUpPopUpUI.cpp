//
//  GroundGiveUpPopUpUI.cpp
//
//
//
//

#include "GroundGiveUpPopUpUI.h"
#include "UtilityHelper.h"
#include "GameConst.h"
#include "UIManager.h"
#include "MainScene.h"
#include "ShopPopUpUI.h"
#include "GameController.h"
#include "SdkBoxManager.h"
#include "NativeBridge.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;

GroundGiveUpPopUpUI* GroundGiveUpPopUpUI::create()
{
    GroundGiveUpPopUpUI *pRet = new(std::nothrow) GroundGiveUpPopUpUI();
    if (pRet)
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

GroundGiveUpPopUpUI::GroundGiveUpPopUpUI()
{
}
GroundGiveUpPopUpUI::~GroundGiveUpPopUpUI()
{
}
void GroundGiveUpPopUpUI::onEnter()
{
    BasePopUpUI::onEnter();
    init();
    
    NativeBridge::getInstance()->showAdsView();
}
void GroundGiveUpPopUpUI::onExit()
{
    NativeBridge::getInstance()->hideAdsView();
    BasePopUpUI::onExit();
}
bool GroundGiveUpPopUpUI::init()
{

    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.width /640.0f;
    
    m_popupBgLayer = cocos2d::ui::ImageView::create(UtilityHelper::getLocalString("UI_GROUND_GIVEUP_PANEL"),cocos2d::ui::TextureResType::PLIST);
    m_popupBgLayer->setPosition(Vec2(size.width*0.5,size.height*0.5));
    m_popupBgLayer->setScale(scale);

    m_dialogLayer->addChild(m_popupBgLayer);
    
    ui::Button* oKtn = cocos2d::ui::Button::create(UtilityHelper::getLocalString("UI_GROUND_BTN_GIVEUP_OK"),"","",cocos2d::ui::TextureResType::PLIST);
    oKtn->setScale(scale);
    oKtn->setPosition(Vec2(size.width*0.5,size.height*0.53));
    m_dialogLayer->addChild(oKtn);

    
    ui::Button* cancelBtn = cocos2d::ui::Button::create(UtilityHelper::getLocalString("UI_GROUND_BTN_GIVEUP_CANCEL"),"","",cocos2d::ui::TextureResType::PLIST);
    cancelBtn->setScale(scale);
    cancelBtn->setPosition(Vec2(size.width*0.5,size.height*0.43));
    m_dialogLayer->addChild(cancelBtn);

    
    oKtn->addClickEventListener(CC_CALLBACK_1(GroundGiveUpPopUpUI::onOK, this));
    cancelBtn->addClickEventListener(CC_CALLBACK_1(GroundGiveUpPopUpUI::onBack, this));
    
    return true;
}

void GroundGiveUpPopUpUI::onBack(cocos2d::Ref *ref)
{
     UIManager::getInstance()->playBtnSound();
    UIManager::getInstance()->hidePopUp();
}
void GroundGiveUpPopUpUI::onOK(cocos2d::Ref *ref)
{
    GameController::getInstance()->switchToRainbowRun();
}