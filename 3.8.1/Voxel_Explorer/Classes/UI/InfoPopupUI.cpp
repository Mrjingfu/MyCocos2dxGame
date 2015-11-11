//
//  SettingUILayer.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/26.
//
//

#include "InfoPopupUI.h"
#include "UtilityHelper.h"
#include "VoxelExplorer.h"
USING_NS_CC;
InfoPopupUI::InfoPopupUI()
{
    m_cActionType = eNone;
    m_pInfoIcon = nullptr;
    m_pInfoDesc = nullptr;
}
InfoPopupUI::~InfoPopupUI()
{
    
}



bool InfoPopupUI::initUi()
{
    if (!this->load("infoPopupLayer.csb",false))
        return false;
    setDarkLayerVisble(false);
    return true;
}
bool InfoPopupUI::addEvents()
{
    m_pInfoIcon =   dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "info_popup_icon"));
    if (!m_pInfoIcon)
        return false;
    
    m_pInfoDesc = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "info_popup_desc"));
    if (!m_pInfoDesc)
        return false;

    m_pInfoDesc->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    
    return true;
}

void InfoPopupUI::setInfoData(std::string infoRes, std::string infoDesKey)
{
    if (nullptr != m_pInfoIcon) {
        m_pInfoIcon->loadTexture(infoRes);
        m_pInfoIcon->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    }
    if (nullptr!= m_pInfoDesc) {
        m_pInfoDesc->setString(UtilityHelper::getLocalStringForUi(infoDesKey));
    }
}
