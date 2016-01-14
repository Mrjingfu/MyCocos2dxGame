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
#include "PopupUILayerManager.h"
USING_NS_CC;
DeadPopupUI::DeadPopupUI()
{
    m_nIsBlankClose = false;
    m_nIsPause = false;
}
DeadPopupUI::~DeadPopupUI()
{
    
}

bool DeadPopupUI::initUi()
{
    ui::ImageView* titleImg = ui::ImageView::create("ui_gameover.png",TextureResType::PLIST);
    titleImg->setScale(2.0);
    titleImg->setPosition(cocos2d::Vec2(m_pRootLayer->getContentSize().width*0.5,m_pRootLayer->getContentSize().height*0.8));
    titleImg->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_pRootLayer->addChild(titleImg);
    
    ui::Button*  btnMainMenu = ui::Button::create("ui_frame_10.png","ui_frame_11.png","ui_frame_11.png",TextureResType::PLIST);
    btnMainMenu->setScale9Enabled(true);
    btnMainMenu->setContentSize(cocos2d::Size(100,40));
    btnMainMenu->setTitleFontName(UtilityHelper::getLocalString("FONT_NAME"));
    btnMainMenu->setTitleFontSize(36);
    btnMainMenu->getTitleRenderer()->setScale(0.4);
    btnMainMenu->setTitleText(UtilityHelper::getLocalStringForUi("BTN_TEXT_MAINMENU"));
    btnMainMenu->setPosition(cocos2d::Vec2(m_pRootLayer->getContentSize().width*0.3,m_pRootLayer->getContentSize().height*0.3));
     m_pRootLayer->addChild(btnMainMenu);
    
    ui::Button*  btnRestart = ui::Button::create("ui_frame_10.png","ui_frame_11.png","ui_frame_11.png",TextureResType::PLIST);
    btnRestart->setScale9Enabled(true);
    btnRestart->setContentSize(cocos2d::Size(100,40));
    btnRestart->setTitleFontName(UtilityHelper::getLocalString("FONT_NAME"));
    btnRestart->setTitleFontSize(36);
    btnRestart->getTitleRenderer()->setScale(0.4);
    btnRestart->setTitleText(UtilityHelper::getLocalStringForUi("BTN_TEXT_RESTART"));
    btnRestart->setPosition(cocos2d::Vec2(m_pRootLayer->getContentSize().width*0.7,m_pRootLayer->getContentSize().height*0.3));
    m_pRootLayer->addChild(btnRestart);
    
    btnMainMenu->addClickEventListener(CC_CALLBACK_1( DeadPopupUI::onClickMainMenu, this));
    btnRestart->addClickEventListener(CC_CALLBACK_1( DeadPopupUI::onClickRestart, this));
    
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
    
    ///for debug
    PopupUILayerManager::getInstance()->closeCurrentPopup();
    VoxelExplorer::getInstance()->respawnPlayer();
}
