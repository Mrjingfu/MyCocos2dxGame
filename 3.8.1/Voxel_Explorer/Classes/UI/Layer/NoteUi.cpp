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
   
//    setBackGroundImageScale9Enabled(true);
//    setBackGroundColorType(BackGroundColorType::SOLID);
//    setBackGroundColor(Color3B::BLUE);
    setContentSize(cocos2d::Size(Director::getInstance()->getVisibleSize().width,10));

    setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_pLabel = cocos2d::ui::TextBMFont::create();
    m_pLabel->setFntFile(UtilityHelper::getLocalStringForUi("FONT_NAME"));
    m_pLabel->setScale(0.7);
    m_pLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    m_pLabel->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    addChild(m_pLabel);
    
    return true;
}


void NoteUi::setMsg(std::string msg,cocos2d::Color3B fontColor /*= cocos2d::Color3B::WHITE*/)
{
    if (m_pLabel)
    {

        UtilityHelper::getLineForText(m_pLabel, msg,this->getParent()->getContentSize().width-10);
        m_pLabel->setScale(0.5);
        m_pLabel->setString(msg);
        float lableSizeHeight = m_pLabel->getContentSize().height*m_pLabel->getScale();
        CCLOG("lableSize:%f",lableSizeHeight);
        if(lableSizeHeight>this->getContentSize().height)
            setContentSize(cocos2d::Size(getContentSize().width,lableSizeHeight+10));
        
        CCLOG("m_pLabel:%zd msg:%lu",m_pLabel->getStringLength(),msg.length());
        m_pLabel->setColor(fontColor);
        m_pLabel->setPosition(Vec2(0,getContentSize().height*0.5));
        m_pLabel->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    }
}
void NoteUi::setItemText(std::string msg,cocos2d::Color3B fontColor /*= cocos2d::Color3B::WHITE*/)
{
    if (m_pLabel)
    {
        float width = this->getParent()->getContentSize().width -14;

        UtilityHelper::getLineForText(m_pLabel, msg,width);
        m_pLabel->setString(msg);
        float lableSizeHeight = m_pLabel->getContentSize().height*m_pLabel->getScale();
        CCLOG("lableSize:%f",lableSizeHeight);
        if(lableSizeHeight>this->getContentSize().height)
            setContentSize(cocos2d::Size(getContentSize().width,lableSizeHeight+10));

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
