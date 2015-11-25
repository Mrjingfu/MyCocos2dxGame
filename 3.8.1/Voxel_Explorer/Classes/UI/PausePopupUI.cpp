//
//  SettingUILayer.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/26.
//
//

#include "PausePopupUI.h"
#include "UtilityHelper.h"
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
    
    m_pBtnMainMenu->loadTextureNormal(UtilityHelper::getLocalStringForUi("PAUSE_BTN_MAIN_MENU"),cocos2d::ui::TextureResType::PLIST);
    m_pBtnSetting->loadTextureNormal(UtilityHelper::getLocalStringForUi("PAUSE_BTN_SETTING"),cocos2d::ui::TextureResType::PLIST);
    m_pBtnExitGame->loadTextureNormal(UtilityHelper::getLocalStringForUi("PAUSE_BTN_EXIT_GAME"),cocos2d::ui::TextureResType::PLIST);
    
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
}
void PausePopupUI::onClickMainMenu(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickMainMenu");
}
void PausePopupUI::onClickSetting(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickSetting");
}
