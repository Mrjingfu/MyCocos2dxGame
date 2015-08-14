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
#include "GroundGameUI.h"
#include "TipsPopUpUI.h"
#include "GameInfoUI.h"
#include "ContinuePopUpUI.h"
#include "GameConst.h"
#include "UtilityHelper.h"
#include "PausePopUpUI.h"
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
    m_gameUi = nullptr;
    m_isCancel = false;
    m_gameUiId = UI_UNKOWN;

}
UIManager::~UIManager()
{
}
void UIManager::init(cocos2d::Layer* layer)
{

    
    m_parent = layer;
    
    if (m_dialogLayer) {
        m_dialogLayer->removeFromParentAndCleanup(true);
        m_dialogLayer = nullptr;
    }
    
    
    m_dialogLayer = cocos2d::Layer::create();
    m_parent->addChild(m_dialogLayer,LAYER_DIALOG,LAYER_DIALOG);
    m_dialogLayer->setVisible(false);
    
    
    
    if (m_gameInfoLayer) {
        m_gameInfoLayer->removeFromParentAndCleanup(true);
        m_gameInfoLayer = nullptr;
    }
        m_gameInfoLayer = GameInfoUI::create();
        m_parent->addChild(m_gameInfoLayer,LAYER_DIALOG);
        m_gameInfoLayer->setVisible(false);

    
}
void UIManager::setGameUi(Game_UI gameuiStaus)
{

    switch (m_gameUiId) {
        case UI_MAIN:
            onExitMenu();
            break;
        case UI_GAME:
            onExitGame();
            break;
        case UI_GROUND_GAME:
            onExitGroundGame();
            break;
        default:
            break;
    }
    
    m_gameUiId = gameuiStaus;
    
    switch (m_gameUiId) {
        case UI_MAIN:
            onEnterMenu();
            break;
        case UI_GAME:
            onEnterGame();
            break;
        case UI_GROUND_GAME:
            onEnterGronudGame();
            break;
        default:
            break;
    }
   
}
void UIManager::onExitMenu()
{
    
}
void UIManager::onExitGame()
{
    if (m_gameUi) {
        m_gameUi->setVisible(false);
    }

}
void UIManager::onExitGroundGame()
{
    if (m_gameUi) {
        m_gameUi->setVisible(true);
    }
}
void UIManager::onEnterMenu()
{
    Layer* lLayer = MainUI::create();
    if (m_parent) {
        m_parent->addChild(lLayer);
    }
}

void UIManager::onEnterGame()
{
    if (m_parent && !m_gameUi) {
        
            Layer* lLayer = GameUI::create();
            m_parent->addChild(lLayer);
            m_gameUi = lLayer;
    }
    showInfo(true);
}

void UIManager::onEnterGronudGame()
{
    if (m_parent) {
            Layer* lLayer = GroundGameUI::create();
            m_parent->addChild(lLayer);
            showInfo(true);
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
            popUp = ContinuePopUpUI::create();
            break;
        case BasePopUpUI::POPUP_GLOD_NOT_ENOUGT:
            popUp = TipsPopUpUI::create(TipsPopUpUI::TIP_GOLD);
            break;
        case BasePopUpUI::POPUP_HEART_NOT_ENOUGT:
            popUp = TipsPopUpUI::create(TipsPopUpUI::TIP_HEART);
            break;
        case BasePopUpUI::POPUP_PAUSE:
            popUp = PausePopUpUI::create();
        default:
            break;
    }
    if (m_dialogLayer) {
        m_dialogLayer->addChild(popUp);
    }
    if(popUp)
        popUp->setPopUpId(popid);

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
            prePopUi->setVisible(false);
        }
        popUi->showPopUp(isPlayAn,vt,popupShow,endfunc);
        
        CCLOG("showPopUp");
    }
}

void UIManager::hidePopUp(bool isPlayAn,const std::function<void()> &endfunc)
{
    BasePopUpUI* popUi = m_popUps.back();
    if (popUi) {
        popUi->hidePopUp(isPlayAn,endfunc);
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
void UIManager::removePopUp(bool isCallBack,BasePopUpUI* popUi)
{
    if (isCallBack) {
        if (m_popUps.size()>1) {
            BasePopUpUI* prePopUi = m_popUps.front();
            prePopUi->setVisible(true);
        }
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
            removePopUp(false,m_popUps.at(i));
        }
    }
    
    if (m_gameUiId == UI_GAME) {
        m_gameUi = nullptr;
    }
    
    if(m_parent)
    {
        m_dialogLayer = nullptr;
        m_gameInfoLayer = nullptr;
        m_parent = nullptr;
    }

}

