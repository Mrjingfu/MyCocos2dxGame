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
    setBackGroundImageScale9Enabled(true);
    setBackGroundColorType(BackGroundColorType::SOLID);
    setContentSize(cocos2d::Size(Director::getInstance()->getVisibleSize().width,20));
    setBackGroundImageColor(Color3B::RED);
    
    m_pLabel = cocos2d::Label::createWithSystemFont("",UtilityHelper::getLocalString("FONT_NAME"),36);
    m_pLabel->setColor(Color3B::RED);
    m_pLabel->setScale(0.3);
    m_pLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    m_pLabel->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    addChild(m_pLabel);
    
    return true;
}
void NoteUi::setMsg(std::string msg)
{
    if (m_pLabel)
    {
        m_pLabel->setString(msg);
        m_pLabel->setPosition(Vec2(0,getContentSize().height*0.5));
    }
    
    
    
}