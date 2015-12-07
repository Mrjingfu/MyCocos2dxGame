//
//  NoteUi.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/3.
//
//

#include "NoteUi.h"
#include "cocos2d.h"
#include "UtilityHelper.h"

USING_NS_CC;
NoteUi::NoteUi()
{
    
}
NoteUi::~NoteUi()
{
    
}
bool NoteUi::init()
{
    if (!Layout::init())
        return false;
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    setTouchEnabled(true);
//    setBackGroundImageScale9Enabled(true);
//    setBackGroundColorType(BackGroundColorType::SOLID);
//    setBackGroundColor(Color3B::BLUE);
    setContentSize(cocos2d::Size(Director::getInstance()->getVisibleSize().width,10));

    setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_pLabel = cocos2d::Label::createWithTTF("",UtilityHelper::getLocalString("FONT_NAME"),36);
    m_pLabel->setScale(0.4);
    m_pLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    m_pLabel->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    addChild(m_pLabel);
    
    return true;
}


void NoteUi::setMsg(std::string msg,cocos2d::Color3B fontColor /*= cocos2d::Color3B::WHITE*/)
{
    if (m_pLabel)
    {
        int charCount = 0;
        if(cocos2d::Application::getInstance()->getCurrentLanguage() ==cocos2d::LanguageType::CHINESE)
        {
            charCount =20;
        }else{
            charCount = 40;
        }
        int count = UtilityHelper::getLineStr(msg, charCount);
        m_pLabel->setString(msg);
        float lableSizeHeight = m_pLabel->getContentSize().height*m_pLabel->getScale();
        CCLOG("lableSize:%f",lableSizeHeight);
        if(count>1)
            setContentSize(cocos2d::Size(getContentSize().width,lableSizeHeight+getContentSize().height));
        
        CCLOG("m_pLabel:%d msg:%lu",m_pLabel->getStringLength(),msg.length());
        m_pLabel->setColor(fontColor);
        m_pLabel->setPosition(Vec2(0,getContentSize().height*0.5));
        m_pLabel->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    }
}
void NoteUi::setItemText(std::string msg,cocos2d::Color3B fontColor /*= cocos2d::Color3B::WHITE*/)
{
    if (m_pLabel)
    {
        int charCount = 0;
        if(cocos2d::Application::getInstance()->getCurrentLanguage() ==cocos2d::LanguageType::CHINESE)
        {
            charCount =13;
        }else{
            charCount = 23;
        }
        int count = UtilityHelper::getLineStr(msg, charCount);
        m_pLabel->setString(msg);
        float lableSizeHeight = m_pLabel->getContentSize().height*m_pLabel->getScale();
        CCLOG("lableSize:%f",lableSizeHeight);
        if(count>1)
            setContentSize(cocos2d::Size(getContentSize().width,lableSizeHeight+getContentSize().height));
        
        CCLOG("m_pLabel:%d msg:%lu",m_pLabel->getStringLength(),msg.length());
        m_pLabel->setColor(fontColor);
        m_pLabel->setPosition(Vec2(0,getContentSize().height*0.5));
        m_pLabel->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    }
}
void NoteUi::setFontScale(float scale)
{
    if (m_pLabel) {
        m_pLabel->setScale(scale);
    }
}
