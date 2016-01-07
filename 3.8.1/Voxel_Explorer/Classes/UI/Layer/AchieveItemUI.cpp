//
//  AchieveItemPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/12/17.
//
//

#include "AchieveItemUI.hpp"
#include "UtilityHelper.h"
USING_NS_CC;
AchieveItemUI::AchieveItemUI()
{
    m_pAchieveIcon  = nullptr;
    m_pAchieveName  = nullptr;
    m_pAchieveTargetDesc = nullptr;

}
AchieveItemUI::~AchieveItemUI()
{
    
}
bool AchieveItemUI::initUi()
{
    if (!WrapperUILayer::initUi())
        return false;
    return load("achieveItemLayer.csb",false);
}
bool AchieveItemUI::addEvents()
{
    m_pAchieveIcon = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "achieveitem_icon"));
    if(!m_pAchieveIcon)
        return false;
    m_pAchieveTargetDesc = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "achieveitem_target_desc"));
    if(!m_pAchieveTargetDesc)
        return false;
    m_pAchieveName = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "achieveitem_name"));
    if(!m_pAchieveName)
        return false;
    
    m_pAchieveTargetDesc->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pAchieveName->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pAchieveTargetDesc->setColor(Color3B(185, 153, 109));
    m_pAchieveName->setColor(Color3B(241, 222, 188));
    return true;
}


void AchieveItemUI::setAchieveDatas(const std::string icon,  std::string name,  std::string targetDesc)
{
    if (m_pAchieveIcon) {
        m_pAchieveIcon->loadTexture(icon,TextureResType::PLIST);
        m_pAchieveIcon->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    }
    float width = m_pRootNode->getContentSize().width*0.75;
    if (m_pAchieveName) {
        
        cocos2d::Size fontsize = UtilityHelper::getSingleStrFontSize(m_pAchieveName, name);
        int count = width/fontsize.width;
        UtilityHelper::getLineStr(name, count);
        m_pAchieveName->setString(name);
    }
    if (m_pAchieveTargetDesc) {
        
        cocos2d::Size fontsize = UtilityHelper::getSingleStrFontSize(m_pAchieveTargetDesc, targetDesc);
        int xCount = width/fontsize.width;
        UtilityHelper::getLineStr(targetDesc, xCount);
        m_pAchieveTargetDesc->setString(targetDesc);
        float heigth = m_pRootNode->getContentSize().height*0.5;
        float descWidth = m_pAchieveTargetDesc->getContentSize().height* m_pAchieveTargetDesc->getScale();
        if (descWidth > heigth) {
            m_pRootNode->setContentSize(m_pRootNode->getContentSize() + cocos2d::Size(0,descWidth-heigth +10));
            m_pAchieveIcon->setAnchorPoint(cocos2d::Vec2(m_pRootNode->getContentSize().width*0.33,m_pRootNode->getContentSize().height));
            m_pAchieveName->setPosition(cocos2d::Vec2(m_pRootNode->getContentSize().width*0.35,m_pRootNode->getContentSize().height*0.66));
            m_pAchieveTargetDesc->setPosition(cocos2d::Vec2(m_pRootNode->getContentSize().width*0.35,m_pRootNode->getContentSize().height*0.5));
        }
       
    }
}
