//
//  PopUpManager.cpp
//
//
//
//

#include "UIManager.h"
#include "StarPopUpUI.h"
#include "ShopPopUpUI.h"
#include "GameInfoUI.h"
#include "MainUI.h"
#include "GameUI.h"
#include "TipsUI.h"
#include "ContinueUI.h"
#include "GameConst.h"
#include "UtilityHelper.h"
USING_NS_CC;

UIManager* g_pPopManagerInstance = nullptr;
UIManager* UIManager::getInstance()
{
    if (g_pPopManagerInstance ==nullptr) {
        g_pPopManagerInstance = new(std::nothrow) UIManager();
        return g_pPopManagerInstance;
    }
    return g_pPopManagerInstance;
}


UIManager::UIManager()
{
    m_dialogLayer = nullptr;
    m_gameInfoLayer = nullptr;
    m_parent = nullptr;
    m_isCancel = false;

}
UIManager::~UIManager()
{
}
void UIManager::init(cocos2d::Layer* layer)
{
    
    m_parent = layer;
    m_gameUiId = UI_UNKOWN;
    m_gameLayer = cocos2d::Layer::create();
    m_gameLayer->setName(LAYER_NAME_UI);
    m_parent->addChild(m_gameLayer,LAYER_UI,LAYER_NAME_UI);
    m_dialogLayer = cocos2d::Layer::create();
    m_dialogLayer->setName(LAYER_NAME_DIALOG);
    m_parent->addChild(m_dialogLayer,LAYER_DIALOG,LAYER_DIALOG);
    m_dialogLayer->setVisible(false);

    
    m_gameInfoLayer = GameInfoUI::create();
    m_parent->addChild(m_gameInfoLayer,LAYER_DIALOG);
    m_gameInfoLayer->setVisible(false);
    
}
void UIManager::setGameUi(Game_UI gameuiStaus)
{
    m_gameUiId = gameuiStaus;
    cocos2d::Layer* gameUi = nullptr;
    switch (m_gameUiId) {
        case UI_MAIN:
            gameUi = MainUI::create();
            break;
        case UI_GAME:
            gameUi = GameUI::create();
            break;
        case UI_GROUND_GAME:
            break;
        default:
            break;
    }
    if (m_parent) {
        m_gameLayer->addChild(gameUi);
    }
    
}
BasePopUpUI* UIManager::getPopUpUI(BasePopUpUI::PopUp_UI popid)
{
    for (int i =0 ; i< m_popUps.size(); i++) {
        BasePopUpUI* popUp = m_popUps.at(i);
        if (popUp->getPopUpId() == popid) {
            return popUp;
        }
    }
    return nullptr;
}
BasePopUpUI* UIManager::createPopUp(BasePopUpUI::PopUp_UI popid)
{
    BasePopUpUI* popUp = nullptr;
    switch (popid) {
        case BasePopUpUI::POPUP_START:
            popUp= StarPopUpUI::create();
            break;
        case BasePopUpUI::POPUP_SHOP:
            popUp = ShopPopUpUI::create();
            break;

        case BasePopUpUI::POPUP_CONTINUE:
            popUp = ContinueUI::create();
            break;
        case BasePopUpUI::POPUP_GLOD_NOT_ENOUGT:
            popUp = TipsUI::create(TipsUI::TIP_GOLD);
            break;
        case BasePopUpUI::POPUP_HEART_NOT_ENOUGT:
            popUp = TipsUI::create(TipsUI::TIP_HEART);
            break;

        default:
            break;
    }
    if (m_dialogLayer) {
        m_dialogLayer->addChild(popUp);
    }
    if(popUp)
        popUp->setPopUpId(popid);
    if (m_gameInfoLayer)
        m_gameInfoLayer->setPopUpId(popid);
    return popUp;
}
void UIManager::addPopUp(BasePopUpUI::PopUp_UI popid)
{

    for(int i=0; i<m_popUps.size();i++)
    {
        BasePopUpUI* lpopUp = m_popUps.at(i);
        if (lpopUp->getPopUpId() == popid) {
            return;
        }
    }
        BasePopUpUI* popUp = createPopUp(popid);
        m_popUps.pushBack(popUp);
 
}
void UIManager::showPopUp(bool isPlayAn,BasePopUpUI::Popup_Show popupShow, const std::function<void()> &endfunc ,cocos2d::Vec2 vt)
{

    if (m_popUps.size() <=0) {
        return;
    }
    
    BasePopUpUI* popUi = m_popUps.back();
    if (popUi) {
        m_dialogLayer->setVisible(true);
        if (m_popUps.size()>1) {
            BasePopUpUI* prePopUi = m_popUps.front();
            prePopUi->setShowMaskBg(false);
        }
        popUi->showPopUp(isPlayAn,vt,popupShow,endfunc);
        
        CCLOG("showPopUp");
    }
}

void UIManager::hidePopUp(const std::function<void()> &endfunc)
{
    BasePopUpUI* popUi = m_popUps.back();
    if (popUi) {
        popUi->hidePopUp(endfunc);
        CCLOG("hidePopUp");

    }
}
void UIManager::showInfo(bool isShowInfo)
{
    if (isShowInfo) {
        m_gameInfoLayer->setVisible(true);
    }else
    {
        m_gameInfoLayer->setVisible(false);
    }
}
void UIManager::removePopUp(BasePopUpUI* popUi)
{
    if (m_popUps.size()>1) {
        BasePopUpUI* prePopUi = m_popUps.front();
        prePopUi->setShowMaskBg(true);
    }
    
    popUi->setPopUpId(BasePopUpUI::POPUP_UNKOWN);
    m_popUps.eraseObject(popUi);
    if(popUi->getReferenceCount() > 0)
        popUi->removeFromParentAndCleanup(true);
    popUi = nullptr;
}
void UIManager::destory()
{
    if (m_popUps.size() > 0) {
        for (int i =0; i< m_popUps.size(); i++) {
            removePopUp(m_popUps.at(i));
        }
    }
    if(m_parent)
    {
        m_parent->removeAllChildren();
        m_parent = nullptr;
    }

}
void UIManager::onGameInfoHidePopUp()
{
    if (m_gameInfoLayer) {
        m_gameInfoLayer->onhideEndPopup();
    }
    
}
