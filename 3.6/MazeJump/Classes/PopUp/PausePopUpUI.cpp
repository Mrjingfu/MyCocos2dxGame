//
//  PausePopUpUI.cpp
//
//
//
//

#include "PausePopUpUI.h"
#include "UtilityHelper.h"
#include "GameConst.h"
#include "MenuScene.h"
#include "UIManager.h"
#include "RunController.h"
#include "NativeBridge.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;

PausePopUpUI* PausePopUpUI::create()
{
    PausePopUpUI *pRet = new(std::nothrow) PausePopUpUI();
    if (pRet )
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

PausePopUpUI::PausePopUpUI()
{
}
PausePopUpUI::~PausePopUpUI()
{
}
void PausePopUpUI::onEnter()
{
    BasePopUpUI::onEnter();
    init();
    NativeBridge::getInstance()->playInterstitialAds();
}
void PausePopUpUI::onExit()
{
    BasePopUpUI::onExit();
}
bool PausePopUpUI::init()
{

    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.width /640.0f;
    m_popupBgLayer = ui::ImageView::create(UtilityHelper::getLocalString("UI_PASUE_PANEL"));
    m_popupBgLayer->setPosition(Vec2(size.width*0.5,size.height*0.5));
    m_popupBgLayer->setScale(scale);
    
    m_dialogLayer->addChild(m_popupBgLayer);
    
    ui::Button* homeBtn = cocos2d::ui::Button::create("btn_home_normal.png","btn_home_pressed.png");
    homeBtn->setScale(scale);
    homeBtn->setPosition(Vec2(size.width*0.35,size.height*0.48));
    m_dialogLayer->addChild(homeBtn);
    
    ui::Button* shopBtn = cocos2d::ui::Button::create("btn_shop_normal.png","btn_shop_pressed.png");
    shopBtn->setScale(scale);
    shopBtn->setPosition(Vec2(size.width*0.35+homeBtn->getContentSize().width*scale+35*scale,size.height*0.48));
    m_dialogLayer->addChild(shopBtn);
    
    ui::Button* playnBtn = cocos2d::ui::Button::create("btn_play_normal.png","btn_play_pressed.png");
    playnBtn->setScale(scale);
    playnBtn->setPosition(Vec2(size.width*0.35+shopBtn->getContentSize().width*2*scale+70*scale,size.height*0.48));
    m_dialogLayer->addChild(playnBtn);

    homeBtn->addClickEventListener(CC_CALLBACK_1(PausePopUpUI::onHome, this));
    shopBtn->addClickEventListener(CC_CALLBACK_1(PausePopUpUI::onShop, this));
    playnBtn->addClickEventListener(CC_CALLBACK_1(PausePopUpUI::onContinue, this));
    
    return true;
}
void PausePopUpUI::onHome(cocos2d::Ref *ref)
{
     UIManager::getInstance()->playBtnSound();
    UIManager::getInstance()->hidePopUp(false);
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_RUNNER_PAUSE_RESUME);
//    auto scene = MenuScene::createScene();
//    Director::getInstance()->replaceScene(scene);
    RunController::getInstance()->switchToMenu();
}
void PausePopUpUI::onShop(cocos2d::Ref *ref)
{
     UIManager::getInstance()->playBtnSound();
    UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_SHOP);
    UIManager::getInstance()->showPopUp(false);
}
void PausePopUpUI::onContinue(cocos2d::Ref *ref)
{
     UIManager::getInstance()->playBtnSound();
    UIManager::getInstance()->hidePopUp(false);
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_RUNNER_RECOVER_PAUSE);
}

