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


void AchieveItemUI::setAchieveDatas(const std::string icon, const std::string name, const std::string targetDesc)
{
    if (m_pAchieveIcon) {
        m_pAchieveIcon->loadTexture(icon,TextureResType::PLIST);
        m_pAchieveIcon->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    }
    if (m_pAchieveName) {
        m_pAchieveName->setString(name);
    }
    if (m_pAchieveTargetDesc) {
        m_pAchieveTargetDesc->setString(targetDesc);
    }
}
