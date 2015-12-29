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
USING_NS_CC;
PausePopupUI::PausePopupUI()
{
    m_bIsSoundOn = true;
    m_bIsMuiscOn = true;
    m_pSoundImg = nullptr;
    m_pMuiscImg = nullptr;
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
    ui::Text* soundText = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "pause_sound_text"));
    if (!soundText)
        return false;
    
    ui::Text* musicText = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "pause_music_text"));
    if (!musicText)
        return false;
    
    m_pSoundImg = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "pause_sound_img"));
    if (!m_pSoundImg)
        return false;
    
    m_pMuiscImg = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "pause_music_img"));
    if (!m_pMuiscImg)
        return false;
    
    ui::Button* m_pBtnMainMenu= dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "pause_btn_mianmenu"));
    if (!m_pBtnMainMenu)
        return false;
    
    ui::Button* m_pBtnHelp =  dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "pause_btn_help"));
    if (!m_pBtnHelp)
        return false;
    
    ui::Button* m_pBtnAchieve= dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "pause_btn_achieve"));
    if (!m_pBtnAchieve)
        return false;
    
   
    
    soundText->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    soundText->setScale(0.4);
    soundText->setFontSize(36);
    soundText->setString(UtilityHelper::getLocalStringForUi("BTN_TEXT_SOUND"));
    
    musicText->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    musicText->setScale(0.4);
    musicText->setFontSize(36);
    musicText->setString(UtilityHelper::getLocalStringForUi("BTN_TEXT_MUSIC"));
    
    m_pSoundImg->setTouchEnabled(true);
    m_pSoundImg->addClickEventListener(CC_CALLBACK_1(PausePopupUI::onClickSound, this));
    
    m_pMuiscImg->setTouchEnabled(true);
    m_pMuiscImg->addClickEventListener(CC_CALLBACK_1(PausePopupUI::onClickMuisc, this));

    
    m_pBtnMainMenu->setTitleFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pBtnMainMenu->setTitleFontSize(36);
    m_pBtnMainMenu->getTitleRenderer()->setScale(0.4);
    m_pBtnMainMenu->setTitleText(UtilityHelper::getLocalStringForUi("BTN_TEXT_MAINMENU"));
    
    m_pBtnHelp->setTitleFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pBtnHelp->setTitleFontSize(36);
    m_pBtnHelp->getTitleRenderer()->setScale(0.4);
    m_pBtnHelp->setTitleText(UtilityHelper::getLocalStringForUi("BTN_TEXT_HELP"));
    
    m_pBtnAchieve->setTitleFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pBtnAchieve->setTitleFontSize(36);
    m_pBtnAchieve->getTitleRenderer()->setScale(0.4);
    m_pBtnAchieve->setTitleText(UtilityHelper::getLocalStringForUi("TITLE_ACHIEVE"));
    
    
    m_pBtnMainMenu->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_pBtnHelp->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_pBtnAchieve->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    
    m_pBtnMainMenu->addClickEventListener(CC_CALLBACK_1(PausePopupUI::onClickMainMenu, this));
    m_pBtnHelp->addClickEventListener(CC_CALLBACK_1(PausePopupUI::onClickHelp, this));
    m_pBtnAchieve->addClickEventListener(CC_CALLBACK_1(PausePopupUI::onClickAchieve, this));
    
    
    return true;

}
void PausePopupUI::onClickSound(Ref* ref)
{
    if (!m_pSoundImg)
        return ;
    if (m_bIsSoundOn)
    {
        m_pSoundImg->loadTexture("ui_sound_off.png",TextureResType::PLIST);
        m_bIsSoundOn =false;
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
    }else
    {
        m_pSoundImg->loadTexture("ui_sound_on.png",TextureResType::PLIST);
        m_bIsSoundOn =true;
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
    }
    m_pSoundImg->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
}
void PausePopupUI::onClickMuisc(cocos2d::Ref *ref)
{
    if (!m_pMuiscImg)
        return ;
    if (m_bIsMuiscOn)
    {
        m_pMuiscImg->loadTexture("ui_sound_off.png",TextureResType::PLIST);
        m_bIsMuiscOn =false;
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    }else
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        m_pMuiscImg->loadTexture("ui_sound_on.png",TextureResType::PLIST);
        m_bIsMuiscOn =true;
    }
    m_pMuiscImg->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    
}
void PausePopupUI::onClickHelp(cocos2d::Ref *ref)
{
 
    
}
void PausePopupUI::onClickMainMenu(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onClickMainMenu");
    Scene* menuScene = MenuScene::createScene();
    Director::getInstance()->replaceScene(menuScene);
    
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
}
