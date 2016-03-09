//
//  Archivelayer.cpp
//  lichuang
//
//  Created by lichuang on 2016/01/11.
//
//

#include "LoadingLayer.hpp"
#include "UtilityHelper.h"
#include "VoxelExplorer.h"
#include "ConfigManager.hpp"
USING_NS_CC;
LoadingLayer::LoadingLayer()
{
    m_nCamerFlag = cocos2d::CameraFlag::DEFAULT;
}

LoadingLayer::~LoadingLayer()
{
    
}

bool LoadingLayer::initUi()
{
    if (!WrapperUILayer::initUi())
            return false;
    return load("loadingLayer.csb",false);
}
bool LoadingLayer::addEvents()
{
    m_LoadingIcon = dynamic_cast<cocos2d::ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "loading_bar"));
    if (!m_LoadingIcon)
        return false;
    
    ui::TextBMFont* tips = dynamic_cast<cocos2d::ui::TextBMFont*>(UtilityHelper::seekNodeByName(m_pRootNode, "loading_tips"));
    if (!tips)
        return false;
        
    m_pTipDesc = dynamic_cast<cocos2d::ui::TextBMFont*>(UtilityHelper::seekNodeByName(m_pRootNode, "loading_tips_desc"));
    if (!m_pTipDesc)
        return false;
    
    tips->setFntFile(UtilityHelper::getLocalStringForUi("FONT_NAME"));
    tips->setString(UtilityHelper::getLocalStringForUi("LOAGING_TIPS"));
    m_pTipDesc->setFntFile(UtilityHelper::getLocalStringForUi("FONT_NAME"));
    cocos2d::Label* tipDescLabel =static_cast<Label*>(m_pTipDesc->getVirtualRenderer());
    tipDescLabel->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
    
    refreshUIView();
    
    return true;
}
void LoadingLayer::refreshUIView()
{
    
    EaseSineOut* fadeIn = EaseSineOut::create(FadeIn::create(0.5f));
    EaseSineIn* moveUp = EaseSineIn::create(MoveBy::create(0.5,cocos2d::Vec2(0,12)));
    EaseSineIn* moveLeft = EaseSineIn::create(MoveBy::create(0.3,cocos2d::Vec2(-12,0)));
    EaseSineIn* moveRight = EaseSineIn::create(MoveBy::create(0.6,cocos2d::Vec2(15,0)));
    m_LoadingIcon->runAction(RepeatForever::create(Spawn::create(fadeIn, moveUp,moveLeft,moveRight,nullptr)));
    
    std::string tipFileName ="tips_chinese.plist";
    if (ConfigManager::getInstance()->getLanguageType()!=LanguageType::CHINESE)
        tipFileName = "tips_english.plist";
    
    cocos2d::ValueVector tipVector = cocos2d::FileUtils::getInstance()->getValueVectorFromFile(tipFileName);
    int count = cocos2d::random(0,(int)(tipVector.size()-1));
    std::string tipDesc = tipVector.at(count).asString();
    CCLOG("tipDesc source:%s",tipDesc.c_str());
    UtilityHelper::getLineForText(m_pTipDesc,tipDesc,getContentSize().width-20);
    CCLOG("tipDesc target:%s",tipDesc.c_str());
    m_pTipDesc->setString(tipDesc);
    
}
void LoadingLayer::testDesc(std::string tipDesc)
{
    EaseSineOut* fadeIn = EaseSineOut::create(FadeIn::create(0.5f));
    EaseSineIn* moveUp = EaseSineIn::create(MoveBy::create(0.5,cocos2d::Vec2(0,12)));
    EaseSineIn* moveLeft = EaseSineIn::create(MoveBy::create(0.3,cocos2d::Vec2(-12,0)));
    EaseSineIn* moveRight = EaseSineIn::create(MoveBy::create(0.6,cocos2d::Vec2(15,0)));
    m_LoadingIcon->runAction(RepeatForever::create(Spawn::create(fadeIn, moveUp,moveLeft,moveRight,nullptr)));
    
    CCLOG("tipDesc source:%s",tipDesc.c_str());
    UtilityHelper::getLineForText(m_pTipDesc,tipDesc,getContentSize().width-20);
    CCLOG("tipDesc target:%s",tipDesc.c_str());
    m_pTipDesc->setString(tipDesc);
}

