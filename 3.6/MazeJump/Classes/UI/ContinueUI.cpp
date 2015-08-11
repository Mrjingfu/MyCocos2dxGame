//
//  DeathUI.cpp
//
//
//
//

#include "ContinueUI.h"
#include "UtilityHelper.h"
#include "GameConst.h"
#include "MainScene.h"
#include "UIManager.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;

ContinueUI* ContinueUI::create()
{
    ContinueUI *pRet = new(std::nothrow) ContinueUI();
    if (pRet )
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

ContinueUI::ContinueUI()
{
}
ContinueUI::~ContinueUI()
{
}
void ContinueUI::onEnter()
{
    BasePopUpUI::onEnter();
    init();
}
void ContinueUI::onExit()
{
    BasePopUpUI::onExit();
}
bool ContinueUI::init()
{

    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.width /640.0f;
    
    ui::ImageView* bgView = ui::ImageView::create("ui_continue_bg.png");
    bgView->setPosition(Vec2(size.width*0.5, size.height*0.45));
    bgView->setScale(scale);
    m_dialogLayer->addChild(bgView);
    
    ui::Text* tv = ui::Text::create(UtilityHelper::getLocalString("CONTINUE_GAME"), FONT_FXZS, 30);
    tv->setPosition(Vec2(size.width*0.5, size.height*0.50));
    tv->setScale(scale);
    m_dialogLayer->addChild(tv);
    
    auto saveBtn = ui::Button::create("btn_heart1_normal.png","btn_heart1_press.png");
    saveBtn->setScale(scale);
    saveBtn->setPosition(Vec2(size.width*0.5, size.height*0.41));
    m_dialogLayer->addChild(saveBtn);
    
    saveBtn->addClickEventListener(CC_CALLBACK_1(ContinueUI::onContinueGame,this));
    return true;
}
void ContinueUI::onContinueGame(cocos2d::Ref *ref)
{
    int heartNum = Value(localStorageGetItem(USER_HEART_NUM)).asInt();
    if (heartNum>=1) {
        localStorageSetItem(USER_HEART_NUM, Value(heartNum-1).asString());
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_HEART_CHANGE);
        localStorageSetItem(USER_LAST_LEVEL, localStorageGetItem(USER_LAST_LEVEL));
        UIManager::getInstance()->hidePopUp(CC_CALLBACK_0(ContinueUI::onHideEndPopUp, this));
    }else
    {
         UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_HEART_NOT_ENOUGT);
         UIManager::getInstance()->showPopUp(false);
    }
}
void ContinueUI::onHideEndPopUp()
{
    auto scene = MainScene::createScene();
    Director::getInstance()->replaceScene(scene);
}