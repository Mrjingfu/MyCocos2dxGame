//
//  GlobalPromptLayer.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/12/15.
//
//

#include "AchieveItemLayer.hpp"
#include "UtilityHelper.h"
#include "AchieveItemUI.hpp"
#include "AchieveEnItemUI.hpp"
#include "ConfigManager.hpp"
USING_NS_CC;
AchieveItemLayer::AchieveItemLayer()
{
}
AchieveItemLayer::~AchieveItemLayer()
{
    
}
bool AchieveItemLayer::initUi()
{
    if (!WrapperUILayer::initUi())
        return false;
    
    setAnchorPoint(cocos2d::Vec2::ZERO);
//    setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
//    setBackGroundColor(Color3B::ORANGE);
    setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    return true;
        
}
void AchieveItemLayer::refreshUIView()
{
    CCLOG("prompt:%ld",m_vAchieves.size());
    float itemHeight = 0.0f;
    for (int i=0; i<m_vAchieves.size(); i++) {

        AchieveItemUI* itemUi = m_vAchieves.at(i);
        if (i==0 && itemUi) {
            itemHeight = itemUi->getRootNode()->getContentSize().height+3;
        }
        if (itemUi && itemUi->getParent()) {
            itemHeight = itemUi->getRootNode()->getContentSize().height+3;
            int tag = std::min(itemUi->getTag(),i);
            cocos2d::Vec2 moveToPos = cocos2d::Vec2(getContentSize().width*0.5,getContentSize().height*0.8-tag*itemHeight);
            itemUi->stopAllActions();
            moveAction(itemUi,moveToPos);
        }
        
        if (itemUi && !itemUi->getParent() )
        {
            addChild(itemUi);
            itemUi->setTag(i);
            itemUi->setVisible(true);
            itemUi->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
            itemUi->getRootNode()->setPosition(cocos2d::Vec2(getContentSize().width*0.5,getContentSize().height*0.8-i*itemHeight));
            inAction(itemUi);
         }
    }
}
void AchieveItemLayer::removeAchieveItem(cocos2d::Node* node)
{
    CCLOG("removePrompt");
    AchieveItemUI* itemUi = static_cast<AchieveItemUI*>(node);
    if (itemUi)
    {
        itemUi->removeFromParentAndCleanup(false);
        m_vAchieves.eraseObject(itemUi);
    }
}
void AchieveItemLayer::clearAchieveItem()
{
    for (auto iter = m_vAchieves.begin(); iter!=m_vAchieves.end(); iter++) {
        if (*iter) {
            (*iter)->removeFromParentAndCleanup(true);
        }
    }
    m_vAchieves.clear();
}
void AchieveItemLayer::inAction(AchieveItemUI* itemUi)
{
    Node* itemRootNode = nullptr;
    if (itemUi)
        itemRootNode = itemUi->getRootNode();
    
    if (itemRootNode) {
        itemRootNode->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
        itemRootNode->setScale(0.001f);
        EaseIn* scale1 = EaseIn::create(ScaleTo::create(0.3f,1.1f *1),0.3f);
        ScaleTo* scale2 = ScaleTo::create(0.1f,1.0f * 1);
        DelayTime* delaytime =  DelayTime::create(1.5);
        CallFunc* func = CallFunc::create(CC_CALLBACK_0(AchieveItemLayer::outAction, this,itemUi));
        itemRootNode->runAction(Sequence::create(scale1,scale2,delaytime,func,nullptr));
    }
    
}
void AchieveItemLayer::outAction(AchieveItemUI* itemUi)
{
    Node* itemRootNode = nullptr;
    if (itemUi)
        itemRootNode = itemUi->getRootNode();

    if (itemRootNode) {
        ScaleTo* scale1 = ScaleTo::create(0.1f,1.1f * 1);
        EaseOut* scale2 = EaseOut::create(ScaleTo::create(0.4f,0.001f * 1),0.3f);
        CallFunc* func = CallFunc::create(CC_CALLBACK_0(AchieveItemLayer::removeAchieveItem, this,itemUi));
        itemRootNode->runAction(Sequence::create(scale1,scale2,func,nullptr));
    }
}
void AchieveItemLayer::moveAction(AchieveItemUI* itemUi,cocos2d::Vec2 pt)
{
    Node* itemRootNode = nullptr;
    if (itemUi)
        itemRootNode = itemUi->getRootNode();
    if (itemRootNode) {
        MoveTo* moveTo = MoveTo::create(0.5, pt);
        DelayTime* delaytime =  DelayTime::create(1.5);
        CallFunc* func = CallFunc::create(CC_CALLBACK_0(AchieveItemLayer::outAction, this,itemUi));
        itemRootNode->runAction(Sequence::create(moveTo,delaytime,func,nullptr));
    }
}
void AchieveItemLayer::showAchieveItem(const std::string icon, const std::string name, const std::string targetDesc)
{
    CCLOG("shwoGlobalPrompt");
    AchieveItemUI* itemUi = nullptr;
    if (ConfigManager::getInstance()->getLanguageType()!= cocos2d::LanguageType::CHINESE)
        itemUi = AchieveEnItemUI::create();
    else
        itemUi = AchieveItemUI::create();
    itemUi->setAchieveDatas(icon, name, targetDesc);
    m_vAchieves.pushBack(itemUi);
    refreshUIView();

}