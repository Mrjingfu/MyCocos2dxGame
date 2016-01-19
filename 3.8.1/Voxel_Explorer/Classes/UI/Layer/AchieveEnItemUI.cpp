//
//  AchieveItemPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/12/17.
//
//

#include "AchieveEnItemUI.hpp"
#include "UtilityHelper.h"
USING_NS_CC;

bool AchieveEnItemUI::initUi()
{
    if (!WrapperUILayer::initUi())
        return false;
    return load("achieveEnItemLayer.csb",false);
}

void AchieveEnItemUI::setAchieveDatas(const std::string icon,  std::string name,  std::string targetDesc)
{
    if (m_pAchieveIcon) {
        m_pAchieveIcon->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_RIGHT);
        m_pAchieveIcon->loadTexture(icon,TextureResType::PLIST);
        m_pAchieveIcon->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    }
   
    if (m_pAchieveName && m_pAchieveTargetDesc) {
        
        UtilityHelper::getLineForText(m_pAchieveName, name,m_pRootNode->getContentSize().width - m_pAchieveIcon->getPositionX()-15);
        m_pAchieveName->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_LEFT);
        m_pAchieveName->setString(name);
        float textHeight =m_pAchieveName->getContentSize().height*m_pAchieveName->getScale();
   
        
      UtilityHelper::getLineForText(m_pAchieveTargetDesc, targetDesc,m_pRootNode->getContentSize().width - m_pAchieveIcon->getPositionX()-15);
      m_pAchieveTargetDesc->setString(targetDesc);
      m_pAchieveTargetDesc->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
      m_pAchieveTargetDesc->setPosition(cocos2d::Vec2(m_pAchieveName->getPositionX(),m_pAchieveName->getPositionY()-textHeight*0.5));
   
      float heigth = m_pRootNode->getContentSize().height -10;
      float descWidth = m_pAchieveTargetDesc->getContentSize().height* m_pAchieveTargetDesc->getScale() + textHeight;
        
    if (descWidth > heigth) {
        m_pRootNode->setContentSize(cocos2d::Size(m_pRootNode->getContentSize().width,descWidth+10));
        m_pAchieveIcon->setPosition(cocos2d::Vec2(m_pRootNode->getContentSize().width*0.3,m_pRootNode->getContentSize().height));
        m_pAchieveName->setPosition(cocos2d::Vec2(m_pRootNode->getContentSize().width*0.32,m_pRootNode->getContentSize().height*0.66));
        m_pAchieveTargetDesc->setPosition(cocos2d::Vec2(m_pAchieveName->getPositionX(),m_pAchieveName->getPositionY()+textHeight));
    }
       
    }
}
