//
//  SettingPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/12/19.
//
//

#include "SettingPopupUI.hpp"
#include "UtilityHelper.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
SettingPopupUI::SettingPopupUI()
{
    m_bIsSoundOn = true;
    m_bIsMuiscOn = true;
    m_pSoundImg = nullptr;
    m_pMuiscImg = nullptr;
}
SettingPopupUI::~SettingPopupUI()
{
    
}

bool SettingPopupUI::initUi()
{
    if(!PopupUILayer::initUi())
        return false;
    
    if (!load("settingLayer.csb",false))
        return false;
    
    return true;
}
bool SettingPopupUI::addEvents()
{

    ui::Button* helpBtn = dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "setting_btn_help"));
    if (!helpBtn)
        return false;
    
    ui::Text* soundText = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "setting_sound_text"));
    if (!soundText)
        return false;
    
    ui::Text* musicText = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "setting_music_text"));
    if (!musicText)
        return false;
    
     m_pSoundImg = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "setting_sound_img"));
    if (!m_pSoundImg)
        return false;
    
    m_pMuiscImg = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "setting_music_img"));
    if (!m_pMuiscImg)
        return false;

    helpBtn->setTitleFontName(UtilityHelper::getLocalString("FONT_NAME"));
    helpBtn->setTitleFontSize(36);
    helpBtn->getTitleRenderer()->setScale(0.4);
    helpBtn->setTitleText(UtilityHelper::getLocalStringForUi("BTN_TEXT_HELP"));

    soundText->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    soundText->setScale(0.4);
    soundText->setFontSize(36);
    soundText->setString(UtilityHelper::getLocalStringForUi("BTN_TEXT_SOUND"));
    
    musicText->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    musicText->setScale(0.4);
    musicText->setFontSize(36);
    musicText->setString(UtilityHelper::getLocalStringForUi("BTN_TEXT_MUSIC"));
    
    m_pSoundImg->setTouchEnabled(true);
    m_pSoundImg->addClickEventListener(CC_CALLBACK_1(SettingPopupUI::onClickSound, this));
    
    m_pMuiscImg->setTouchEnabled(true);
    m_pMuiscImg->addClickEventListener(CC_CALLBACK_1(SettingPopupUI::onClickMuisc, this));
    
    helpBtn->addClickEventListener(CC_CALLBACK_1(SettingPopupUI::onClickHelp, this));
    
    return true;
}

void SettingPopupUI::onClickSound(Ref* ref)
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
void SettingPopupUI::onClickMuisc(cocos2d::Ref *ref)
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
void SettingPopupUI::onClickHelp(Ref* ref)
{
    
}