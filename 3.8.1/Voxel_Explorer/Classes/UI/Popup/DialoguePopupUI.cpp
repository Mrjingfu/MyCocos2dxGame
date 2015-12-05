//
//  DialoguePopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/12/4.
//
//

#include "DialoguePopupUI.hpp"
#include "UtilityHelper.h"
USING_NS_CC;
DialoguePopupUI::DialoguePopupUI()
{
    m_pBtnNext              = nullptr;
    m_pTextInfo             = nullptr;
    m_pTextTitle            = nullptr;
    m_pCharIcon             = nullptr;

}
DialoguePopupUI::~DialoguePopupUI()
{
    
}
bool DialoguePopupUI::initUi()
{
    if (!PopupUILayer::initUi())
        return false;
    if(!load("dialogueLayer.csb",false))
        return false;
    return true;
}
bool DialoguePopupUI::addEvents()
{
    if (!PopupUILayer::addEvents())
        return false;
    m_pBtnNext= dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "dialogue_btn_next"));
    if (!m_pBtnNext)
        return false;
    m_pTextInfo= dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "dialogue_info_text"));
    if (!m_pTextInfo)
        return false;
    m_pTextTitle= dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "dialogue_title_text"));
    if (!m_pTextTitle)
        return false;
    m_pCharIcon= dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "dialogue_char_icon"));
    if (!m_pCharIcon)
        return false;
    
    m_pTextInfo->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pTextTitle->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    
    MoveBy* moveByNext = MoveBy::create(0.5, cocos2d::Vec2(0,-5));
    
    m_pBtnNext->runAction(RepeatForever::create(Sequence::create(moveByNext,moveByNext->reverse(), nil)));
    m_pBtnNext->resume();
    return true;
}
void DialoguePopupUI::refreshUIView()
{
    
}