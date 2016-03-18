//
//  LangugaePopup.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 16/3/9.
//
//

#include "LangugaePopup.hpp"
#include "UtilityHelper.h"
#include "ConfigManager.hpp"
#include "EventConst.h"
#include "PopupUILayerManager.h"
#include "AlertPopupUI.hpp"
#include "LogoScene.h"
#include "ArchiveManager.h"
USING_NS_CC;
LangugaePopup::LangugaePopup()
{
    m_pRadioGroup = nullptr;
}
LangugaePopup::~LangugaePopup()
{
    
}
bool LangugaePopup::initUi()
{
    if (!PopupUILayer::initUi())
        return false;
    
    return load("langugaeLayer.csb",false);
}

bool LangugaePopup::addEvents()
{
    ui::TextBMFont* chText = dynamic_cast<ui::TextBMFont*>(UtilityHelper::seekNodeByName(m_pRootNode, "langugae_zh_text"));
    if (!chText)
        return false;
    
    ui::TextBMFont* enText = dynamic_cast<ui::TextBMFont*>(UtilityHelper::seekNodeByName(m_pRootNode, "langugae_en_text"));
    if (!enText)
        return false;
    
    ui::CheckBox*  zhCheckBox = dynamic_cast<ui::CheckBox*>(UtilityHelper::seekNodeByName(m_pRootNode, "langugae_zh_radio"));
    if (!zhCheckBox)
        return false;
    
    ui::CheckBox*  enCheckBox = dynamic_cast<ui::CheckBox*>(UtilityHelper::seekNodeByName(m_pRootNode, "langugae_en_radio"));
    if (!enCheckBox)
        return false;
    
    chText->setFntFile(UtilityHelper::getLocalStringForUi("FONT_NAME"));
    chText->setString(UtilityHelper::getLocalStringForUi("LANGUGAE_TEXT_ZH"));
    
    enText->setFntFile(UtilityHelper::getLocalStringForUi("FONT_NAME"));
    enText->setString(UtilityHelper::getLocalStringForUi("LANGUGAE_TEXT_EN"));
    
    m_pRadioGroup = ui::RadioButtonGroup::create();
    
    
    ui::RadioButton* zhRadio = cocos2d::ui::RadioButton::create("ui_radio_off.png", "ui_radio_on.png",TextureResType::PLIST);
    zhRadio->setPosition(zhCheckBox->getPosition());
    zhRadio->setScale(0.6);
    zhCheckBox->setVisible(false);
    m_pRootNode->addChild(zhRadio);
    m_pRadioGroup->addRadioButton(zhRadio);
    zhRadio->addEventListener(CC_CALLBACK_2(LangugaePopup::onSelectRadioZh,this));
    
    ui::RadioButton* enRadio = cocos2d::ui::RadioButton::create("ui_radio_off.png", "ui_radio_on.png",TextureResType::PLIST);
    enRadio->setPosition(enCheckBox->getPosition());
    enRadio->setScale(0.6);
    enCheckBox->setVisible(false);
    m_pRootNode->addChild(enRadio);
    m_pRadioGroup->addRadioButton(enRadio);
    enRadio->addEventListener(CC_CALLBACK_2(LangugaePopup::onSelectRadioEn,this));
    
    m_pRootNode->addChild(m_pRadioGroup);
    
    refreshUIView();
    return true;
}
void LangugaePopup::refreshUIView()
{
    if (ConfigManager::getInstance()->getLanguageType() == LanguageType::CHINESE)
        m_pRadioGroup->setSelectedButton(0);
    else
        m_pRadioGroup->setSelectedButton(1);
}
void LangugaePopup::onSelectRadioZh(cocos2d::ui::RadioButton* radioButton, cocos2d::ui::RadioButton::EventType type)
{
    if (type == cocos2d::ui::RadioButton::EventType::SELECTED) {
        
        this->m_pRootNode->setVisible(false);
        
        AlertPopupUI* alertPopup =  static_cast<AlertPopupUI*>(PopupUILayerManager::getInstance()->openPopup(ePopupAlert));
        if (alertPopup) {
            alertPopup->setMessage(UtilityHelper::getLocalStringForUi("LANGUGAE_CHANGE_TIPS"));
            alertPopup->setPositiveListerner([this](Ref* ref){
                ConfigManager::getInstance()->setLanguageType(LanguageType::CHINESE);
                this->swtichToLogoScene();
                
            });
            alertPopup->setNegativeListerner([this](Ref* ref){
                 this->m_pRootNode->setVisible(true);
                 m_pRadioGroup->setSelectedButton(1);
                 this->closePopup();
            });
        }
        
    }
 }
void LangugaePopup::onSelectRadioEn(cocos2d::ui::RadioButton* radioButton, cocos2d::ui::RadioButton::EventType type)
{
    if (type == cocos2d::ui::RadioButton::EventType::SELECTED) {
        this->m_pRootNode->setVisible(false);
        AlertPopupUI* alertPopup =  static_cast<AlertPopupUI*>(PopupUILayerManager::getInstance()->openPopup(ePopupAlert));
        if (alertPopup)
        {
            alertPopup->setMessage(UtilityHelper::getLocalStringForUi("LANGUGAE_CHANGE_TIPS"));
            alertPopup->setPositiveListerner([this](Ref* ref){
                ConfigManager::getInstance()->setLanguageType(LanguageType::ENGLISH);
                this->swtichToLogoScene();
            });
            alertPopup->setNegativeListerner([this](Ref* ref){
                this->m_pRootNode->setVisible(true);
                m_pRadioGroup->setSelectedButton(0);
                this->closePopup();
            });
        
        }
    }
}
void LangugaePopup::swtichToLogoScene()
{
    ArchiveManager::getInstance()->saveGameAchieve();
    
    Scene* logoScene = LogoScene::createScene();
    Director::getInstance()->replaceScene(logoScene);
}
