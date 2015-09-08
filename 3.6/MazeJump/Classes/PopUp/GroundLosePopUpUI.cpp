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
#include "SdkBoxManager.h"
#include "NativeBridge.h"
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
    
    NativeBridge::getInstance()->showAdsView();
}
void GroundLosePopUpUI::onExit()
{
    NativeBridge::getInstance()->hideAdsView();
    BasePopUpUI::onExit();
}
bool GroundLosePopUpUI::init()
{

    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.width /640.0f;
    
    m_popupBgLayer = cocos2d::ui::ImageView::create(UtilityHelper::getLocalString("UI_GROUND_FAILED_PANEL"),cocos2d::ui::TextureResType::PLIST);
    m_popupBgLayer->setPosition(Vec2(size.width*0.5,size.height*0.5));
    m_popupBgLayer->setScale(scale);

    m_dialogLayer->addChild(m_popupBgLayer);
    ui::Button* backtn = nullptr;
    if (GameController::getInstance()->getMazeMode() == GameController::MAZE) {
        backtn = cocos2d::ui::Button::create(UtilityHelper::getLocalString("UI_GROUND_FAILED_RESTART_BTN"),"","",cocos2d::ui::TextureResType::PLIST);
        backtn->setScale(scale);
        backtn->setPosition(Vec2(size.width*0.5,size.height*0.55));
        m_dialogLayer->addChild(backtn);
    }else if (GameController::getInstance()->getMazeMode() == GameController::NORAML)
    {
        backtn = cocos2d::ui::Button::create(UtilityHelper::getLocalString("UI_GROUND_BTN_FAILED_BACK"),"","",cocos2d::ui::TextureResType::PLIST);
        backtn->setScale(scale);
        backtn->setPosition(Vec2(size.width*0.5,size.height*0.55));
        m_dialogLayer->addChild(backtn);
        
    }
    
    

    
    ui::Button* reviveBtn = cocos2d::ui::Button::create(UtilityHelper::getLocalString("UI_GROUND_BTN_FAILED_HELP"),"","",cocos2d::ui::TextureResType::PLIST);
    reviveBtn->setScale(scale);
    reviveBtn->setPosition(Vec2(size.width*0.5,size.height*0.4));
    m_dialogLayer->addChild(reviveBtn);

    
    backtn->addClickEventListener(CC_CALLBACK_1(GroundLosePopUpUI::onBack, this));
    reviveBtn->addClickEventListener(CC_CALLBACK_1(GroundLosePopUpUI::onHelpRecover, this));
    
    
    
    
    return true;
}
void GroundLosePopUpUI::onHelpRecover(cocos2d::Ref *ref)
{
     UIManager::getInstance()->playBtnSound();
    int goldNum = Value(localStorageGetItem(USER_GOLD_NUM)).asInt();
    if (goldNum >= 320) {
        
        localStorageSetItem(USER_GOLD_NUM, Value(Value(localStorageGetItem(USER_GOLD_NUM)).asInt() - 320).asString());
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_GOLD_CHANGE);
        UIManager::getInstance()->hidePopUp(false);
        GameController::getInstance()->createMap(true,GameController::getInstance()->getCurrentLevel());
    #if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
        SdkBoxManager::getInstance()->logEvent("MazeJump", "Game Result", "Help", 1);
    #endif

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
     UIManager::getInstance()->playBtnSound();
    UIManager::getInstance()->hidePopUp(true,CC_CALLBACK_0(GroundLosePopUpUI::onHidePopUpEnd, this));
}
void GroundLosePopUpUI::onHidePopUpEnd()
{
    if (GameController::getInstance()->getMazeMode() == GameController::MAZE) {
        GameController::getInstance()->createMap(false, Value(localStorageGetItem(USER_MAZE_LEVEL)).asInt());
    }else if (GameController::getInstance()->getMazeMode() == GameController::NORAML)
    {
         GameController::getInstance()->switchToRainbowRun();
    }
   
}