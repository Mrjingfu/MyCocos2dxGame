//
//  GlobalPromptLayer.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/12/15.
//
//

#include "HudPromptLayer.hpp"
#include "UtilityHelper.h"
#include "Actor.hpp"
#include "VoxelExplorer.h"
USING_NS_CC;
HudPromptLayer::HudPromptLayer()
{
    m_vPos = cocos2d::Vec2::ZERO;
}
HudPromptLayer::~HudPromptLayer()
{
    
}
bool HudPromptLayer::initUi()
{
    if (!WrapperUILayer::initUi())
        return false;
    
    setAnchorPoint(cocos2d::Vec2::ZERO);
//    setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
//    setBackGroundColor(Color3B::ORANGE);
    setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    return true;
        
}
void HudPromptLayer::refreshUIView()
{
    CCLOG("prompt:%ld",m_vPrompts.size());

 
    for (int i=0; i<m_vPrompts.size(); i++) {
        
         ui::TextBMFont* m_pLabel = m_vPrompts.at(i);
        if (m_pLabel && !m_pLabel->getParent() )
        {
            addChild(m_pLabel);
            m_pLabel->setVisible(true);
            m_pLabel->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
            float labelHeight = m_pLabel->getContentSize().height*m_pLabel->getScale();
            CCLOG("i:%d,labelHeight:%f",i,labelHeight);
            m_pLabel->setPosition(m_vPos-cocos2d::Vec2(0,i*labelHeight));
            
            if (m_eTipType == TIP_ROLE_CRITICAL_STRIKE || m_eTipType == TIP_MONSTER_CRITICAL_STRIKE) {
                cocos2d::ScaleTo* ScaleTo1 = cocos2d::ScaleTo::create(0.3, 0.8);
                cocos2d::MoveBy* moveBy = cocos2d::MoveBy::create(0.3, Vec2(0, 40.0f));
                cocos2d::DelayTime* delay = cocos2d::DelayTime::create(0.2);
                cocos2d::FadeOut* fadeOut = cocos2d::FadeOut::create(0.2);
                CallFunc* callfunN = CallFunc::create(CC_CALLBACK_0(HudPromptLayer::removePrompt, this,m_pLabel));
                m_pLabel->runAction(cocos2d::Sequence::create(cocos2d::Spawn::createWithTwoActions(moveBy, ScaleTo1),delay,fadeOut,callfunN, nullptr));
            }
            else
            {
                cocos2d::MoveBy* moveBy = cocos2d::MoveBy::create(0.5, cocos2d::Vec2(0,30.0f));
                cocos2d::DelayTime* delay = cocos2d::DelayTime::create(0.2);
                cocos2d::FadeOut* fadeOut = cocos2d::FadeOut::create(0.2);
                CallFunc* callfunN = CallFunc::create(CC_CALLBACK_0(HudPromptLayer::removePrompt, this,m_pLabel));
                m_pLabel->runAction(cocos2d::Sequence::create(moveBy,delay,fadeOut,callfunN, nullptr));
                
            }
            
        }
    }
    
    if (m_vPrompts.size() >1) {
        m_vPrompts.clear();
    }
}
void HudPromptLayer::removePrompt(cocos2d::Node* node)
{
    CCLOG("removePrompt");
    ui::TextBMFont* m_pLabel = static_cast<ui::TextBMFont*>(node);
    if (m_pLabel) {
        m_pLabel->removeFromParentAndCleanup(false);
    }
}
void HudPromptLayer::shwoPrompt(cocos2d::Vec2 pos,TipTypes tipType, std::string text)
{
     CCLOG("shwoGlobalPrompt");
    m_eTipType = tipType;
    m_vPos = pos;
    ui::TextBMFont* m_pLabel = ui::TextBMFont::create();
    m_pLabel->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
    m_pLabel->setFntFile(UtilityHelper::getLocalStringForUi("FONT_NAME"));
    m_pLabel->setScale(0.55);
    m_pLabel->setColor(PopupUILayerManager::getInstance()->getTipsColor(tipType));

    UtilityHelper::getLineForText(m_pLabel, text,getContentSize().width-10);
    m_pLabel->setString(text);
    m_pLabel->setVisible(false);
    m_vPrompts.pushBack(m_pLabel);
    refreshUIView();

}