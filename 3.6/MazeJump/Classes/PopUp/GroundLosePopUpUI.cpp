//
//  GroundLosePopUpUI.cpp
//
//
//
//

#include "GroundLosePopUpUI.h"
#include "UtilityHelper.h"
#include "GameConst.h"
#include "UIManager.h"
#include "MainScene.h"
#include "ShopPopUpUI.h"
#include "GameController.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;

GroundLosePopUpUI* GroundLosePopUpUI::create()
{
    GroundLosePopUpUI *pRet = new(std::nothrow) GroundLosePopUpUI();
    if (pRet)
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

GroundLosePopUpUI::GroundLosePopUpUI()
{
}
GroundLosePopUpUI::~GroundLosePopUpUI()
{
}
void GroundLosePopUpUI::onEnter()
{
    BasePopUpUI::onEnter();
    init();
}
void GroundLosePopUpUI::onExit()
{
    BasePopUpUI::onExit();
}
bool GroundLosePopUpUI::init()
{

    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.width /640.0f;
    
    m_popupBgLayer = ui::ImageView::create(UtilityHelper::getLocalString("UI_GROUND_FAILED_PANEL"));
    m_popupBgLayer->setPosition(Vec2(size.width*0.5,size.height*0.5));
    m_popupBgLayer->setScale(scale);

    m_dialogLayer->addChild(m_popupBgLayer);
    
    ui::Button* backtn = ui::Button::create(UtilityHelper::getLocalString("UI_GROUND_BTN_FAILED_BACK"));
    backtn->setScale(scale);
    backtn->setPosition(Vec2(size.width*0.5,size.height*0.55));
    m_dialogLayer->addChild(backtn);

    
    ui::Button* reviveBtn = ui::Button::create(UtilityHelper::getLocalString("UI_GROUND_BTN_FAILED_HELP"));
    reviveBtn->setScale(scale);
    reviveBtn->setPosition(Vec2(size.width*0.5,size.height*0.4));
    m_dialogLayer->addChild(reviveBtn);

    
    backtn->addClickEventListener(CC_CALLBACK_1(GroundLosePopUpUI::onBack, this));
    reviveBtn->addClickEventListener(CC_CALLBACK_1(GroundLosePopUpUI::onHelpRecover, this));
    
    return true;
}
void GroundLosePopUpUI::onHelpRecover(cocos2d::Ref *ref)
{
     UIManager::getInstance()->playSound();
    int goldNum = Value(localStorageGetItem(USER_GOLD_NUM)).asInt();
    if (goldNum >= 80) {
        
        localStorageSetItem(USER_GOLD_NUM, Value(Value(localStorageGetItem(USER_GOLD_NUM)).asInt() - 80).asString());
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_GOLD_CHANGE);
        UIManager::getInstance()->hidePopUp(false);
        GameController::getInstance()->createMap(true,GameController::getInstance()->getCurrentLevel());

    }else
    {
        UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_SHOP);
        ShopPopUpUI* popUpShop = static_cast<ShopPopUpUI*>(UIManager::getInstance()->getPopUpUI(BasePopUpUI::POPUP_SHOP));
        if (popUpShop) {
            popUpShop->setShopDisplay(ShopPopUpUI::SHOP_GOLD);
        }
        UIManager::getInstance()->showPopUp(false);
    }

}
void GroundLosePopUpUI::onBack(cocos2d::Ref *ref)
{
     UIManager::getInstance()->playSound();
    UIManager::getInstance()->hidePopUp(true,CC_CALLBACK_0(GroundLosePopUpUI::onHidePopUpEnd, this));
}
void GroundLosePopUpUI::onHidePopUpEnd()
{
    GameController::getInstance()->switchToRainbowRun();
}