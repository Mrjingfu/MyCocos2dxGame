//
//  DeathPopUpUI.cpp
//
//
//
//

#include "DeathPopUpUI.h"
#include "UtilityHelper.h"
#include "GameConst.h"
#include "MainScene.h"
#include "MenuScene.h"
#include "RunController.h"
#include "UIManager.h"
#include "ShopPopUpUI.h"
#include "SdkBoxManager.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;

DeathPopUpUI* DeathPopUpUI::create()
{
    DeathPopUpUI *pRet = new(std::nothrow) DeathPopUpUI();
    if (pRet )
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

DeathPopUpUI::DeathPopUpUI()
{
}
DeathPopUpUI::~DeathPopUpUI()
{
}
void DeathPopUpUI::onEnter()
{
    BasePopUpUI::onEnter();
    init();
}
void DeathPopUpUI::onExit()
{
    BasePopUpUI::onExit();
}
bool DeathPopUpUI::init()
{

    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.width /640.0f;
    m_popupBgLayer = ui::ImageView::create(UtilityHelper::getLocalString("UI_DEATH_PANEL"));
    m_popupBgLayer->setPosition(Vec2(size.width*0.5,size.height*0.5));
    m_popupBgLayer->setScale(scale);
    
    m_dialogLayer->addChild(m_popupBgLayer);
    
    ui::Button* homeBtn = cocos2d::ui::Button::create("btn_home_normal.png","btn_home_pressed.png");
    homeBtn->setScale(scale);
    homeBtn->setPosition(Vec2(size.width*0.33,size.height*0.53));
    m_dialogLayer->addChild(homeBtn);
    
    ui::Button* shopBtn = cocos2d::ui::Button::create("btn_shop_normal.png","btn_shop_pressed.png");
    shopBtn->setScale(scale);
    shopBtn->setPosition(Vec2(size.width*0.33+homeBtn->getContentSize().width*scale+35*scale,size.height*0.53));
    m_dialogLayer->addChild(shopBtn);
    
    ui::Button* agiainBtn = cocos2d::ui::Button::create("btn_agiain_normal.png","btn_agiain_pressed.png");
    agiainBtn->setScale(scale);
    agiainBtn->setPosition(Vec2(size.width*0.33+shopBtn->getContentSize().width*2*scale+70*scale,size.height*0.53));
    m_dialogLayer->addChild(agiainBtn);
    
    ui::Button* reviveBtn = cocos2d::ui::Button::create(UtilityHelper::getLocalString("UI_DEATH_BTN_REVICE"));
    reviveBtn->setScale(scale);
    reviveBtn->setPosition(Vec2(size.width*0.5,size.height*0.38));
    m_dialogLayer->addChild(reviveBtn);
    
    
    homeBtn->addClickEventListener(CC_CALLBACK_1(DeathPopUpUI::onHome, this));
    shopBtn->addClickEventListener(CC_CALLBACK_1(DeathPopUpUI::onShop, this));
    agiainBtn->addClickEventListener(CC_CALLBACK_1(DeathPopUpUI::onAgiain, this));
    reviveBtn->addClickEventListener(CC_CALLBACK_1(DeathPopUpUI::onRevive, this));
    return true;
}
void DeathPopUpUI::onHome(cocos2d::Ref *ref)
{
     UIManager::getInstance()->playBtnSound();
    UIManager::getInstance()->hidePopUp(false);
    RunController::getInstance()->switchToMenu();

}
void DeathPopUpUI::onShop(cocos2d::Ref *ref)
{
     UIManager::getInstance()->playBtnSound();
    UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_SHOP);
    UIManager::getInstance()->showPopUp(false);
}
void DeathPopUpUI::onAgiain(cocos2d::Ref *ref)
{
    UIManager::getInstance()->hidePopUp(false);
    localStorageSetItem(USER_LAST_LEVEL,"0");
    auto scene = MainScene::createScene();
    Director::getInstance()->replaceScene(scene);
}
void DeathPopUpUI::onRevive(cocos2d::Ref *ref)
{
   
     UIManager::getInstance()->playBtnSound();
    int heartNum = Value(localStorageGetItem(USER_HEART_NUM)).asInt();
    if (heartNum >=1) {
         UIManager::getInstance()->hidePopUp(false);
        localStorageSetItem(USER_HEART_NUM, Value(Value(localStorageGetItem(USER_HEART_NUM)).asInt()-1).asString());
        auto scene = MainScene::createScene();
        Director::getInstance()->replaceScene(scene);
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
        SdkBoxManager::getInstance()->logEvent("Game Continue", "Revive", "Heart cost", 1);
#endif
    }else
    {
        UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_SHOP);
        ShopPopUpUI* shopPopup = static_cast<ShopPopUpUI*>(UIManager::getInstance()->getPopUpUI(BasePopUpUI::POPUP_SHOP));
        if (shopPopup) {
            shopPopup->setShopDisplay(ShopPopUpUI::SHOP_HEART);
        }
        UIManager::getInstance()->showPopUp(false);
    }
    

}