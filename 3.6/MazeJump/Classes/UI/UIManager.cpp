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
#include "GameConst.h"
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
void UIManager::addPopUp(BasePopUpUI::PopUp_UI popid)
{
    BasePopUpUI* popUp = createPopUp(popid);
    if (popUp) {
        for (int i=0; i<m_popUps.size();i++) {
             BasePopUpUI* lpopUp = m_popUps.at(i);
            if (lpopUp->getPopUpId() == popUp->getPopUpId()) {
                return;
            }
        }
        m_popUps.pushBack(popUp);
        
    }

}

UIManager::UIManager()
{
    m_maskLayer = nullptr;
    m_dialogLayer = nullptr;
    m_gameInfoLayer = nullptr;
    m_isShowDialog = false;
    m_parent = nullptr;
}
UIManager::~UIManager()
{
}
void UIManager::init(cocos2d::Layer* layer)
{
    m_parent = layer;
    m_gameUiId = UI_UNKOWN;
    auto size = Director::getInstance()->getVisibleSize();
    
    m_gameLayer = cocos2d::Layer::create();
    m_gameLayer->setName(LAYER_NAME_UI);
    m_parent->addChild(m_gameLayer,LAYER_UI,LAYER_NAME_UI);
    
    m_maskLayer = cocos2d::Layer::create();
    m_maskLayer->setName(LAYER_NAME_MASK);
    m_parent->addChild(m_maskLayer,LAYER_MASK,LAYER_MASK);
    
    
    m_maskLayerBg = cocos2d::LayerColor::create(cocos2d::Color4B(0, 0, 0, 150));
    m_maskLayerBg->setContentSize(size);
    m_maskLayer->addChild(m_maskLayerBg);
    m_maskLayerBg->setVisible(false);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan =  [this](Touch * ,Event *)
    {
        if (m_isShowDialog) {
            return true;
        }else{
            return false;
        }
        
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,m_maskLayer);
    
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
        default:
            break;
    }
    if (m_dialogLayer) {
        m_dialogLayer->addChild(popUp);
    }
    popUp->setPopUpId(popid);
    m_gameInfoLayer->setPopUpId(popid);
    return popUp;
}

void UIManager::showPopUp(BasePopUpUI::Popup_Show popupShow,bool isShowMask, const std::function<void()> &func )
{
    BasePopUpUI* popUi = m_popUps.front();
    if (popUi) {
        m_isShowDialog = true;
        m_dialogLayer->setVisible(true);
        m_maskLayer->setVisible(true);
        if (isShowMask) {
            m_maskLayerBg->setVisible(true);
        }else
        {
            m_maskLayerBg->setVisible(false);
        }
        popUi->showPopUp(popupShow,func);
        CCLOG("showPopUp");
    }
}
void UIManager::hidePopUp(const std::function<void()> &func)
{
    BasePopUpUI* popUi = m_popUps.front();
    if (popUi) {
        popUi->hidePopUp(func);
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
    m_isShowDialog = false;
    m_maskLayer->setVisible(false);
    
    popUi->setPopUpId(BasePopUpUI::POPUP_UNKOWN);
    m_gameInfoLayer->setPopUpId(BasePopUpUI::POPUP_UNKOWN);
    
    m_popUps.eraseObject(popUi);
    if(popUi->getReferenceCount() > 0)
        popUi->removeFromParentAndCleanup(true);
    popUi = nullptr;
}
void UIManager::destory()
{
    m_parent->removeAllChildren();
    m_parent = nullptr;
}
