//
//  Archivelayer.cpp
//  lichuang
//
//  Created by lichuang on 2016/01/11.
//
//

#include "ArchiveLayer.hpp"
#include "UtilityHelper.h"


ArchiveLayer::ArchiveLayer()
{
    m_pArchiveImg       = nullptr;
    m_pArchiveDesc      = nullptr;
    m_pArchiveBtnDel    = nullptr;
    m_bisArchive = false;
}

ArchiveLayer::~ArchiveLayer()
{
    
}

bool ArchiveLayer::initUi()
{
    if (!WrapperUILayer::initUi())
            return false;
    return load("archivelayer.csb",false);
}
bool ArchiveLayer::addEvents()
{
    m_pArchiveImg = dynamic_cast<cocos2d::ui::ImageView *>(UtilityHelper::seekNodeByName(m_pRootNode, "menu_archive_item"));
    if(!m_pArchiveImg)
          return false;
    m_pArchiveDesc = dynamic_cast<cocos2d::ui::Text *>(UtilityHelper::seekNodeByName(m_pRootNode, "menu_archive_item_text"));
    if(!m_pArchiveDesc)
          return false;
    m_pArchiveBtnDel = dynamic_cast<cocos2d::ui::Button *>(UtilityHelper::seekNodeByName(m_pRootNode, "menu_archive_item_del"));
    if(!m_pArchiveBtnDel)
          return false;
    
    m_pArchiveImg->setTouchEnabled(true);
    m_pArchiveImg->setVisible(false);
    m_pArchiveDesc->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pArchiveBtnDel->addClickEventListener(CC_CALLBACK_1(ArchiveLayer::onClickDelGame, this));
    m_pArchiveImg->addClickEventListener(CC_CALLBACK_1(ArchiveLayer::onClickStarGame, this));
     return true;
}
void ArchiveLayer::setArchiveDesc(const std::string& desc)
{
    if (!desc.empty()) {
        m_pArchiveDesc->setString(desc);
    }
}
void ArchiveLayer::onClickStarGame(Ref* ref)
{
    CCLOG("onClickStarGame");
    CHECK_ACTION(ref);
    clickEffect();
    
}
void ArchiveLayer::onClickDelGame(Ref* ref)
{
     CCLOG("onClickDelGame");
    CHECK_ACTION(ref);
    clickEffect();
}


