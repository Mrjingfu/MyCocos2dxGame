//
//  DialoguePopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/12/4.
//
//

#include "DialoguePopupUI.hpp"
#include "UtilityHelper.h"
#include "NpcDataManager.hpp"
USING_NS_CC;
DialoguePopupUI::DialoguePopupUI()
{
    m_nIsPause              = false;
    m_bPartEnd              = false;
    m_nPart                 = 0;
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
    m_pDialogueLayout = dynamic_cast<ui::Layout*>(UtilityHelper::seekNodeByName(m_pRootNode, "dialogue_layer_frame"));
    if (!m_pDialogueLayout)
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
    MoveBy* moveByNext = MoveBy::create(0.5, cocos2d::Vec2(0,-2));
    m_pBtnNext->runAction(RepeatForever::create(Sequence::create(moveByNext,moveByNext->reverse(), nil)));
    m_pDialogueLayout->setTouchEnabled(true);
    m_pDialogueLayout->addClickEventListener(CC_CALLBACK_1(DialoguePopupUI::onClickNext, this));
    refreshUIView();
    return true;
}


void DialoguePopupUI::refreshUIView()
{

   
    std::string str = NpcDataManager::getInstance()->getOldManRoomInfoByPart(m_nPart, m_bPartEnd);
    if (!str.empty()) {
        m_pTextInfo->setString(str);
         m_nPart++;
    }
    
    if (m_bPartEnd){
        m_nPart=0;
        CCLOG("对话完毕");
    }
}
void DialoguePopupUI::onClickNext(cocos2d::Ref *ref)
{
    if (!m_bPartEnd) {
         refreshUIView();
    }
   
}
