//
//  SettingUILayer.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/26.
//
//

#include "InformationPopupUI.h"
#include "UtilityHelper.h"
#include "VoxelExplorer.h"
USING_NS_CC;
InformationPopupUI::InformationPopupUI()
{
    m_cActionType = eNone;
    m_pInfoIcon = nullptr;
    m_pInfoDesc = nullptr;
}
InformationPopupUI::~InformationPopupUI()
{
    
}


bool InformationPopupUI::initUi()
{
    if (!PopupUILayer::initUi())
        return false;
    if(!load("",false))
        return false;
    return true;
}

bool InformationPopupUI::addEvents()
{
    if(!PopupUILayer::addEvents())
        return false;
    m_pInfoIcon =   dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "info_img_icon"));
    if (!m_pInfoIcon)
        return false;
    
    m_pInfoDesc = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "info_text_message"));
    if (!m_pInfoDesc)
        return false;
    
    m_pBtnNext = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_icon"));
    if (!m_pBtnNext)
        return false;
    
    m_pInfoTitle =   dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "info_title_text"));
    if (!m_pInfoTitle)
        return false;
    
    m_pInfoDesc->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pInfoTitle->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    
    m_pBtnNext->setVisible(false);
    return true;
}
void InformationPopupUI::refreshUIView()
{
    
}
void InformationPopupUI::setInfoData(const std::string& infoRes, std::string& infoDesc)
{
    int charCount = 0;
    if(cocos2d::Application::getInstance()->getCurrentLanguage() ==cocos2d::LanguageType::CHINESE)
    {
        charCount =20;
    }else{
        charCount = 40;
    }
    int count = UtilityHelper::getLineStr(infoDesc, charCount);

    if (nullptr != m_pInfoIcon) {
        if (infoRes.empty()) {
            m_pInfoIcon->setVisible(false);
            m_pInfoDesc->setPosition(m_pRootNode->getContentSize()*0.5);
        }else{
            m_pInfoIcon->loadTexture(infoRes,TextureResType::PLIST);
            m_pInfoIcon->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
            m_pInfoDesc->setPosition(cocos2d::Vec2(m_pInfoIcon->getPositionX()+m_pInfoIcon->getContentSize().width*0.5,m_pRootNode->getContentSize().height*0.5));
        }
   }
    if (nullptr!= m_pInfoDesc) {
        m_pInfoDesc->setString(infoDesc);
        m_pInfoDesc->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    }
}
