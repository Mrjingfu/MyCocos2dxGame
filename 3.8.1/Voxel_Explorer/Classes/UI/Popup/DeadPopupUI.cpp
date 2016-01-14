//
//  DeadPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/26.
//
//

#include "DeadPopupUI.h"
#include "UtilityHelper.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "ArchiveManager.h"
#include "VoxelExplorer.h"
#include "GameUILayer.h"
USING_NS_CC;
DeadPopupUI::DeadPopupUI()
{
    m_pBtnMenu      = nullptr;
    m_pBtnRestart  = nullptr;
    m_nIsPause = false;
//    m_cActionType = eCenterScale;
}
DeadPopupUI::~DeadPopupUI()
{
    
}

bool DeadPopupUI::initUi()
{
    if (!PopupUILayer::initUi())
        return false;
    
    return load("deadLayer.csb",false);
    
}
bool DeadPopupUI::addEvents()
{
    
    
    m_pBtnMenu = dynamic_cast<cocos2d::ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode,"dead_btn_menu"));
    if (!m_pBtnMenu)
        return false;
    
    m_pBtnRestart = dynamic_cast<cocos2d::ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode,"dead_btn_restart"));
    if (!m_pBtnRestart)
        return false;
    ui::ImageView* title = dynamic_cast<cocos2d::ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode,"dead_title"));
    if (!title)
        return false;
    title->loadTexture(UtilityHelper::getLocalStringForUi("DEAD_RES"),TextureResType::PLIST);
    
    m_pBtnMenu->setTitleFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pBtnMenu->setTitleFontSize(36);
    m_pBtnMenu->getTitleRenderer()->setScale(0.4);
    m_pBtnMenu->setTitleText(UtilityHelper::getLocalStringForUi("BTN_TEXT_MAINMENU"));
    
    
    m_pBtnRestart->setTitleFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pBtnRestart->setTitleFontSize(36);
    m_pBtnRestart->getTitleRenderer()->setScale(0.4);
    m_pBtnRestart->setTitleText(UtilityHelper::getLocalStringForUi("BTN_TEXT_RESTART"));

    m_pBtnMenu->addClickEventListener(CC_CALLBACK_1(DeadPopupUI::onClickMainMenu, this));
    m_pBtnRestart->addClickEventListener(CC_CALLBACK_1(DeadPopupUI::onClickRestart, this));
    
    return true;
}
void DeadPopupUI::onClickMainMenu(cocos2d::Ref *ref)
{
    if(!ArchiveManager::getInstance()->saveGame())
        CCLOGERROR("Save Game failed!");
    closePopup();
    VoxelExplorer::getInstance()->getUILayer()->switchToMenuScene();
}
void DeadPopupUI::onClickRestart(cocos2d::Ref *ref)
{
//    cocos2d::Scene* scene = GameScene::createScene();
//    Director::getInstance()->replaceScene(scene);
    
}
