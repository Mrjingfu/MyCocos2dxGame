//
//  MenuUILayer.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/20.
//
//

#include "MenuUILayer.h"
#include "UtilityHelper.h"
#include "GameConfig.h"
#include "GameScene.h"
#include "PopupUILayerManager.h"
#include "AchievePopupUI.h"
#include "ArchiveManager.h"
USING_NS_CC;

MenuUILayer::MenuUILayer()
{
    m_pAchievePopupUI = nullptr;
}
MenuUILayer::~MenuUILayer()
{
    
}
bool MenuUILayer::addEvents()
{
    
    
    cocos2d::ui::Button* btn_achieve = dynamic_cast<cocos2d::ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode,"btn_achieve"));
    if (!btn_achieve)
        return false;
    cocos2d::ui::Button* btn_setting = dynamic_cast<cocos2d::ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode,"btn_setting"));
    if (!btn_setting)
        return false;
    cocos2d::ui::Button* btn_rank = dynamic_cast<cocos2d::ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode,"btn_rank"));
    if (!btn_rank)
        return false;
    cocos2d::ui::Button* btn_rate = dynamic_cast<cocos2d::ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode,"btn_rate"));
    if (!btn_rate)
        return false;
    cocos2d::ui::Button* btn_start = dynamic_cast<cocos2d::ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode,"btn_start"));
    if (!btn_start)
        return false;
    
    m_pEyes = dynamic_cast<cocos2d::Sprite*>(UtilityHelper::seekNodeByName(m_pRootNode,"menu_eyes"));
    if (!m_pEyes)
        return false;
    
    cocos2d::ui::ImageView* splash = dynamic_cast<cocos2d::ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode,"menu_bg"));
    if (!splash)
        return false;
    std::string splashTxName = UtilityHelper::getLocalStringForUi("SPLASH_RES");
    splash->loadTexture(splashTxName);
    
    m_pAchievePopupUI = AchievePopupUI::create();
    m_pAchievePopupUI->setVisible(false);
    m_pRootNode->addChild(m_pAchievePopupUI,eZOrderPopupUILayer);
    m_pAchievePopupUI->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    
    btn_achieve->addClickEventListener(CC_CALLBACK_1(MenuUILayer::onClickAchieve, this));
    btn_setting->addClickEventListener(CC_CALLBACK_1(MenuUILayer::onClickSetting, this));
    btn_rank->addClickEventListener(CC_CALLBACK_1(MenuUILayer::onClickRank, this));
    btn_start->addClickEventListener(CC_CALLBACK_1(MenuUILayer::onClickStart, this));
    btn_rate->addClickEventListener(CC_CALLBACK_1(MenuUILayer::onClickRate, this));


    return true;
}

void MenuUILayer::onClickAchieve(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onTouchAchieve");
    if (m_pAchievePopupUI)
    {
        if (m_pAchievePopupUI->isVisible())
        {
            m_pAchievePopupUI->setVisible(false);
        }
        else
        {
            m_pAchievePopupUI->setVisible(true);
            m_pAchievePopupUI->refreshUIView();
        }
        
    }

}
void MenuUILayer::onClickSetting(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onTouchSetting");
}
void MenuUILayer::onClickRank(cocos2d::Ref *ref)
{
    
    CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onTouchRank");
    ArchiveManager::getInstance()->saveGame();
//    PopupUILayerManager::getInstance()->openPopup(ePopupInfo);
}
void MenuUILayer::onClickStart(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onTouchStart");
    ui::Button* startBtn = static_cast<ui::Button*>(ref);
    if (startBtn) {
        startBtn->setVisible(false);
        
        EaseSineOut* fadein = EaseSineOut::create(FadeIn::create(0.5));
        EaseSineOut* fadeout = EaseSineOut::create(FadeOut::create(0.5));
        CallFunc* func = CallFunc::create([](){
            
            auto scene = GameScene::createScene();
            Director::getInstance()->replaceScene(scene);
        });
        
        m_pEyes->runAction(Sequence::create(fadein, fadeout,func,nullptr));
    }
    
    
}

void MenuUILayer::onClickRate(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onTouchRate");
}