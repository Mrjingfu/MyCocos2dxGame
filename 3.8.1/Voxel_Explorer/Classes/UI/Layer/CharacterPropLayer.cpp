//
//  CharacterPropLayer.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/27.
//
//

#include "CharacterPropLayer.hpp"
#include "UtilityHelper.h"
#include "TGridView.h"
#include "PlayerProperty.hpp"
USING_NS_CC;

CharacterPropLayer::CharacterPropLayer()
{
    m_pCharacterBufferList       = nullptr;
   m_pCharacterHpBar             = nullptr;
   m_pCharacterCurHp             = nullptr;
   m_pCharacterMaxHp             = nullptr;
   m_pCharacterMpBar             = nullptr;
   m_pCharacterCurMp             = nullptr;
   m_pCharacterMaxMp             = nullptr;
   m_pCharacterLevel             = nullptr;
   m_pCharacterName              = nullptr;
   m_pCharacterIcon              = nullptr;
   m_pCharacterIconFrame         = nullptr;
   
}
CharacterPropLayer::~CharacterPropLayer()
{
    
}
bool CharacterPropLayer::initUi()
{
    if (!load("characterInfoLayer.csb",false))
        return false;
    setContentSize(m_pRootNode->getContentSize());
    m_pRootNode->setPosition(getContentSize()*0.5);
    return true;
}
bool CharacterPropLayer::addEvents()
{
    
    m_pCharacterName =dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_name"));
    if (!m_pCharacterName)
        return false;
    
    m_pCharacterHpBar = dynamic_cast<ui::LoadingBar*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_role_blood"));
    if (!m_pCharacterHpBar)
        return false;
    m_pCharacterMpBar = dynamic_cast<ui::LoadingBar*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_role_margic"));
    if (!m_pCharacterMpBar)
        return false;
    
    m_pCharacterCurHp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_role_blood_num"));
    if (!m_pCharacterCurHp)
        return false;
    
    m_pCharacterMaxHp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_role_blood_maxnum"));
    if(!m_pCharacterMaxHp)
        return false;
    
    m_pCharacterCurMp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_role_margic_num"));
    if (!m_pCharacterCurMp)
        return false;
    
    
    m_pCharacterMaxMp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_role_margic_maxnum"));
    if(!m_pCharacterMaxMp)
        return false;
    
    m_pCharacterLevel = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_lv_num"));
    if (!m_pCharacterLevel)
        return false;
    
    m_pCharacterIconFrame = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "btn_character"));
    if (!m_pCharacterIconFrame)
        return false;
    
    m_pCharacterIcon = ImageView::create();
    m_pCharacterIcon->setScale(0.27);
    m_pCharacterIcon->setPosition(m_pCharacterIconFrame->getContentSize()*0.5);
    m_pCharacterIconFrame->addChild(m_pCharacterIcon);
    
    m_pCharacterBufferList = TGridView::create();
//  m_pRoleBufferList->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
//  m_pRoleBufferList->setBackGroundColor(Color3B::YELLOW);
    m_pCharacterBufferList->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    m_pCharacterBufferList->setContentSize(m_pCharacterMpBar->getContentSize());
    m_pCharacterBufferList->setCol(5);
    m_pCharacterBufferList->setPosition(cocos2d::Vec2(m_pCharacterName->getPositionX(),m_pCharacterName->getPositionY()-m_pCharacterMpBar->getContentSize().height*4.5));
    m_pCharacterBufferList->setScrollBarEnabled(false);
    m_pCharacterBufferList->setItemsMargin(cocos2d::Size(1.5,2));
    m_pCharacterBufferList->setFrameMargin(cocos2d::Size(1,1));
    m_pCharacterBufferList->setClippingEnabled(false);
    m_pRootNode->addChild(m_pCharacterBufferList);
    
    m_pCharacterName->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pCharacterCurHp->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pCharacterMaxHp->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pCharacterCurMp->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pCharacterMaxMp->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
//  m_pCharacterLevel->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    
    return true;
}
void CharacterPropLayer::refreshUIView()
{
    updateCharacterBuff();
    updateCharacterProp();
}