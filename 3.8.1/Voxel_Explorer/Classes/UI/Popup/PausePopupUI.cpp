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
#include "AchievePopupUI.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "VoxelExplorer.h"
#include "AchievePopupUI.h"
#include "GameUILayer.h"
#include "ArchiveManager.h"
#include "GameCenterController.h"
USING_NS_CC;
PausePopupUI::PausePopupUI()
{
    m_bIsSoundOn = true;
    m_bIsMuiscOn = true;
//    m_pSoundImg = nullptr;
    m_pMuiscImg = nullptr;
}
PausePopupUI::~PausePopupUI()
{
    
}
bool PausePopupUI::initUi()
{
#if (CHINA_CHANEL==0)
    return load("pausenewPopupLayer_abroad.csb",false);
#else
    return load("pausenewPopupLayer.csb",false);
#endif
    
}
bool PausePopupUI::addEvents()
{
    ui::TextBMFont* musicText = dynamic_cast<ui::TextBMFont*>(UtilityHelper::seekNodeByName(m_pRootNode, "pause_music_text"));
    if (!musicText)
        return false;

    
    m_pMuiscImg = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "pause_music_img"));
    if (!m_pMuiscImg)
        return false;
    
    ui::Button* m_pBtnMainMenu= dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "pause_btn_mianmenu"));
    if (!m_pBtnMainMenu)
        return false;
    
    ui::Button* m_pBtnAchieve= dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "pause_btn_achieve"));
    if (m_pBtnAchieve)
    {
        m_pBtnAchieve->setTitleFontName(UtilityHelper::getLocalStringForUi("FONT_NAME"));
        m_pBtnAchieve->setTitleFontSize(36);
        m_pBtnAchieve->getTitleRenderer()->setScale(0.7);
        m_pBtnAchieve->setTitleText(UtilityHelper::getLocalStringForUi("TITLE_ACHIEVE"));
        m_pBtnAchieve->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pBtnAchieve->addClickEventListener(CC_CALLBACK_1(PausePopupUI::onClickAchieve, this));
    }
    
    ui::Button* m_pBtnRank= dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "pause_btn_rank"));
    if (m_pBtnRank)
    {
        m_pBtnRank->setTitleFontName(UtilityHelper::getLocalStringForUi("FONT_NAME"));
        m_pBtnRank->setTitleFontSize(36);
        m_pBtnRank->getTitleRenderer()->setScale(0.7);
        m_pBtnRank->setTitleText(UtilityHelper::getLocalStringForUi("BTN_TEXT_RANK"));
        m_pBtnRank->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pBtnRank->addClickEventListener(CC_CALLBACK_1(PausePopupUI::onClickRank, this));

    }

    
    
    
    musicText->setFntFile(UtilityHelper::getLocalStringForUi("FONT_NAME"));
    musicText->setScale(0.65);
    musicText->setString(UtilityHelper::getLocalStringForUi("BTN_TEXT_MUSIC"));
    
    m_pMuiscImg->setTouchEnabled(true);
    m_pMuiscImg->addClickEventListener(CC_CALLBACK_1(PausePopupUI::onClickMuisc, this));

    
    m_pBtnMainMenu->setTitleFontName(UtilityHelper::getLocalStringForUi("FONT_NAME"));
    m_pBtnMainMenu->getTitleRenderer()->setScale(0.7);
    m_pBtnMainMenu->setTitleText(UtilityHelper::getLocalStringForUi("BTN_TEXT_MAINMENU"));
    m_pBtnMainMenu->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_pBtnMainMenu->addClickEventListener(CC_CALLBACK_1(PausePopupUI::onClickMainMenu, this));
    
    
    refreshUIView();
    
    
    return true;

}

void PausePopupUI::refreshUIView()
{
    if (CocosDenshion::SimpleAudioEngine::getInstance()->getPauseSound())
    {
        m_pMuiscImg->loadTexture("ui_btn_sound_off.png",TextureResType::PLIST);
    }else
    {
        m_pMuiscImg->loadTexture("ui_btn_sound_on.png",TextureResType::PLIST);
    }
    m_pMuiscImg->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
}
void PausePopupUI::onClickMuisc(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    if (!m_pMuiscImg)
        return ;
    if (CocosDenshion::SimpleAudioEngine::getInstance()->getPauseSound())
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->setPauseSound(false);
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
        refreshUIView();
 
    }else
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->setPauseSound(true);
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
        refreshUIView();
    }
    
    
}
void PausePopupUI::onClickHelp(cocos2d::Ref *ref)
{
 
    
}
void PausePopupUI::onClickRank(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onClickRank");
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    GameCenterController::getInstance()->openLeaderBoard();
#endif
}
void PausePopupUI::onClickMainMenu(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onClickMainMenu");
    VoxelExplorer::getInstance()->getCurrentLevel()->showMap(false);
    VoxelExplorer::getInstance()->getUILayer()->switchToMenuScene();
    closePopup();

}
void PausePopupUI::onClickAchieve(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onClickAchieve");
    this->getRootNode()->setVisible(false);
    AchievePopupUI* m_pAchievePopupUI = VoxelExplorer::getInstance()->getUILayer()->getAchievePopupUI();
    
    if (m_pAchievePopupUI && !m_pAchievePopupUI->getParent()) {
        this->addChild(m_pAchievePopupUI);
        m_pAchievePopupUI->setVisible(true);
        m_pAchievePopupUI->refreshUIView();
        
        m_pAchievePopupUI->registerCloseCallback([this,m_pAchievePopupUI](){
             this->getRootNode()->setVisible(true);
             m_pAchievePopupUI->removeFromParentAndCleanup(false);
        });
    }
    GameCenterController::getInstance()->openAchievementBoard();
}
