//
//  GlobalPromptLayer.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/12/15.
//
//

#include "GlobalPromptLayer.hpp"
#include "UtilityHelper.h"
USING_NS_CC;
GlobalPromptLayer::GlobalPromptLayer()
{
}
GlobalPromptLayer::~GlobalPromptLayer()
{
    
}
bool GlobalPromptLayer::initUi()
{
    if (!WrapperUILayer::initUi())
        return false;
    
    setAnchorPoint(cocos2d::Vec2::ZERO);
//    setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
//    setBackGroundColor(Color3B::ORANGE);
    setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    return true;
        
}
void GlobalPromptLayer::refreshUIView()
{
    CCLOG("prompt:%ld",m_vPrompts.size());
    cocos2d::Vec2 moveToPos = cocos2d::Vec2::ZERO;
    float labelHeight=0.0f;
    for (int i=0; i<m_vPrompts.size(); i++) {
        
         ui::Text* m_pLabel = m_vPrompts.at(i);
        if (i==0) {
             labelHeight = m_pLabel->getContentSize().height*m_pLabel->getScale();
        }
        if (m_pLabel && m_pLabel->getParent()) {
            m_pLabel->stopAllActions();
            labelHeight = m_pLabel->getContentSize().height*m_pLabel->getScale();
            int tag = std::min(m_pLabel->getTag(),i);
            moveToPos = Vec2(getContentSize().width*0.5,getContentSize().height*0.75-tag*labelHeight);
        }
         CCLOG("i:%d,labelHeight:%f",i,labelHeight);
        if (m_pLabel && !m_pLabel->getParent() )
        {
            addChild(m_pLabel);
            m_pLabel->setTag(i);
            m_pLabel->setVisible(true);
            m_pLabel->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
            m_pLabel->setPosition(cocos2d::Vec2(getContentSize().width*0.5,getContentSize().height*0.65-i*labelHeight));
            
            moveToPos = Vec2(getContentSize().width*0.5,getContentSize().height*0.75-i*labelHeight);
         }
        if (m_pLabel) {
            cocos2d::MoveTo*  moveTo = cocos2d::MoveTo::create(0.2,moveToPos);
            cocos2d::DelayTime* delay = cocos2d::DelayTime::create(1.2f);
            cocos2d::FadeOut* fadeOut = cocos2d::FadeOut::create(0.5);
            CallFunc* callfunN = CallFunc::create(CC_CALLBACK_0(GlobalPromptLayer::removePrompt, this,m_pLabel));
            m_pLabel->runAction(cocos2d::Sequence::create(moveTo,delay,fadeOut,callfunN,nullptr));
        }
    }
    if (m_vPrompts.size()>2)
    {
        for (int i=0; i<=m_vPrompts.size()-1; i++) {
            ui::Text* m_pLabel = m_vPrompts.at(i);
            if (m_pLabel) {
                m_pLabel->removeFromParentAndCleanup(true);
                m_vPrompts.eraseObject(m_pLabel);
            }
        }
        refreshUIView();
    }
    
}
void GlobalPromptLayer::removePrompt(cocos2d::Node* node)
{
    CCLOG("removePrompt");
    ui::Text* m_pLabel = static_cast<ui::Text*>(node);
    if (m_pLabel)
    {
            m_pLabel->removeFromParentAndCleanup(false);
            m_vPrompts.eraseObject(m_pLabel);
    }
}
void GlobalPromptLayer::clearGlobalPrompt()
{
    for (auto iter = m_vPrompts.begin(); iter!=m_vPrompts.end(); iter++) {
        if (*iter) {
            (*iter)->removeFromParentAndCleanup(true);
        }
    }
    m_vPrompts.clear();
}
void GlobalPromptLayer::shwoGlobalPrompt(TipTypes tipType, std::string text)
{
    CCLOG("shwoGlobalPrompt");
    ui::Text* m_pLabel = ui::Text::create();
    m_pLabel->setFontSize(36);
    m_pLabel->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_TOP);
    m_pLabel->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pLabel->setScale(0.55);
    m_pLabel->enableGlow(Color4B(Color3B::GREEN));
//    m_pLabel->enableShadow(Color4B::BLUE);
//    m_pLabel->enableOutline(cocos2d::Color4B::BLUE);
    m_pLabel->setTextColor(cocos2d::Color4B(PopupUILayerManager::getInstance()->getTipsColor(tipType)));
    cocos2d::Size fonSize = UtilityHelper::getSingleStrFontSize(m_pLabel, text);
    int charCount  = (int)(getContentSize().width/fonSize.width);
    UtilityHelper::getLineStr(text, charCount);
    m_pLabel->setString(text);
    m_pLabel->setVisible(false);
    m_vPrompts.pushBack(m_pLabel);
    refreshUIView();

}