//
//  SettingUILayer.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/26.
//
//

#include "PausePopupUI.h"
#include "UtilityHelper.h"
#include "PopupUILayerManager.h"
#include "SettingPopupUI.hpp"
#include "MenuScene.h"
USING_NS_CC;
PausePopupUI::PausePopupUI()
{
   m_pBtnMainMenu = nullptr;
   m_pBtnSetting = nullptr;
   m_pBtnExitGame = nullptr;
}
PausePopupUI::~PausePopupUI()
{
    
}
bool PausePopupUI::initUi()
{
    return load("pausePopupLayer.csb",false);
}
bool PausePopupUI::addEvents()
{
    m_pBtnMainMenu= dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "pause_btn_mianmenu"));
    if (!m_pBtnMainMenu)
        return false;
    
    m_pBtnSetting= dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "pause_btn_setting"));
    if (!m_pBtnSetting)
        return false;
    
    m_pBtnExitGame= dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "pause_btn_exitgame"));
    if (!m_pBtnExitGame)
        return false;
    m_pBtnMainMenu->setTitleFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pBtnMainMenu->setTitleFontSize(36);
    m_pBtnMainMenu->getTitleRenderer()->setScale(0.4);
    m_pBtnMainMenu->setTitleText(UtilityHelper::getLocalStringForUi("BTN_TEXT_MAINMENU"));
    
    m_pBtnSetting->setTitleFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pBtnSetting->setTitleFontSize(36);
    m_pBtnSetting->getTitleRenderer()->setScale(0.4);
    m_pBtnSetting->setTitleText(UtilityHelper::getLocalStringForUi("BTN_TEXT_SETTING"));
    
    m_pBtnExitGame->setTitleFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pBtnExitGame->setTitleFontSize(36);
    m_pBtnExitGame->getTitleRenderer()->setScale(0.4);
    m_pBtnExitGame->setTitleText(UtilityHelper::getLocalStringForUi("BTN_TEXT_EXITGAME"));
    
    
    m_pBtnMainMenu->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_pBtnSetting->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_pBtnExitGame->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    
    m_pBtnMainMenu->addClickEventListener(CC_CALLBACK_1(PausePopupUI::onClickMainMenu, this));
    m_pBtnSetting->addClickEventListener(CC_CALLBACK_1(PausePopupUI::onClickSetting, this));
    m_pBtnExitGame->addClickEventListener(CC_CALLBACK_1(PausePopupUI::onClickExitGame, this));
    
    return true;

}
void PausePopupUI::onClickExitGame(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickExitGame");
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
}
void PausePopupUI::onClickMainMenu(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickMainMenu");
    Scene* menuScene = MenuScene::createScene();
    Director::getInstance()->replaceScene(menuScene);
    
}
void PausePopupUI::onClickSetting(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickSetting");
    PopupUILayerManager::getInstance()->getCurrentPopUpLayer()->getRootNode()->setVisible(false);
    SettingPopupUI* settingPopup = static_cast<SettingPopupUI*>( PopupUILayerManager::getInstance()->openPopup(ePopupSetting));
    if (settingPopup)
    {
        settingPopup->setDarkLayerVisble(false);
        settingPopup->registerCloseCallback([]()
        {
             PopupUILayerManager::getInstance()->getCurrentPopUpLayer()->getRootNode()->setVisible(true);
        });
    }
}
