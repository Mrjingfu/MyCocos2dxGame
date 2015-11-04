//
//  ItemPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/26.
//
//

#include "ItemPopupUI.h"
#include "UtilityHelper.h"
#include "PlayerProperty.hpp"
#include "WeaponProperty.hpp"
#include "ArmorProperty.hpp"
#include "MagicOrnamentProperty.hpp"
#include "SecondWeaponProperty.hpp"
#include "EventConst.h"
USING_NS_CC;
ItemPopupUI::ItemPopupUI()
{
    
    m_cActionType = eNone;
    m_pItemIcon         =nullptr;
    m_pItemName         =nullptr;
    m_pItemlv           =nullptr;
    m_pItemDesc         =nullptr;
    m_pBtnItemFrame     =nullptr;
    m_pPropFrame        =nullptr;
    m_pDescItemFrame    =nullptr;
    m_pBtnDiscard       =nullptr;
    m_pBtnUse           =nullptr;
    m_pBackGround       =nullptr;
    m_pItemType         =nullptr;
    m_pItemValueNum     =nullptr;

    m_nItemId = -2;
}
ItemPopupUI::~ItemPopupUI()
{
    
}
bool ItemPopupUI::init()
{
    if (PopupUILayer::init())
    {
        this->load("itemPopupLayer.csb",false);
        enableDarkLayer(false);
        return true;
    }
    return false;
}
bool ItemPopupUI::addEvents()
{
    
    m_pBtnItemFrame = dynamic_cast<ui::Layout*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_event__layer"));
    if (!m_pBtnItemFrame)
        return false;
    m_pPropFrame = dynamic_cast<ui::Layout*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_prop_layer"));
    if (!m_pBtnItemFrame)
        return false;
    m_pDescItemFrame = dynamic_cast<ui::Layout*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_desc_layer"));
    if (!m_pBtnItemFrame)
        return false;
    
     m_pBtnDiscard = dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_btn_discard"));
    if (!m_pBtnDiscard)
        return false;
    m_pBtnUse = dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_btn_use"));
    if (!m_pBtnUse)
        return false;
    
    m_pBackGround =   dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_background"));
    if (!m_pBackGround)
        return false;

    m_pItemIcon =   dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_icon"));
    if (!m_pItemIcon)
        return false;
 
    m_pItemName = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_name_text"));
    if (!m_pItemName)
        return false;
    m_pItemlv = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_lv_num_text"));
    if (!m_pItemlv)
        return false;
    m_pItemDesc = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_desc_text"));
    if (!m_pItemDesc)
        return false;
    m_pItemCount = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_count_text"));
    if (!m_pItemCount)
        return false;

    m_pItemType = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_prop_type"));
    if (!m_pItemType)
        return false;
    m_pItemValueNum = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_value_num"));
    if (!m_pItemValueNum)
        return false;

    
    
    m_pItemCount->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemCount->setVisible(false);
    
    m_pItemName->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemlv->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemDesc->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemType->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemValueNum->setFontName(UtilityHelper::getLocalString("FONT_NAME"));

    
    m_pBtnDiscard->addClickEventListener(CC_CALLBACK_1(ItemPopupUI::onClickDiscard, this));
    m_pBtnUse->addClickEventListener(CC_CALLBACK_1(ItemPopupUI::onClickUser, this));

    return true;
}


void ItemPopupUI::updateItemPopup(int itemId)
{
    m_nItemId = itemId;
    CCLOG("m_nItemId:%d",m_nItemId);
    
    PickableItemProperty* itemprop = PlayerProperty::getInstance()->getItemFromBag(CChaosNumber(m_nItemId));
    m_pItemIcon->loadTexture(itemprop->getIconRes());
    m_pItemName->setString(itemprop->getName());
    std::string str = "传说由来自天魔星的魔矿打造，会逐渐控制主人的心智，使之入魔。";
    m_pItemDesc->setString(str);
    m_pItemlv->setString(StringUtils::format("LV.%ld",itemprop->getLevel().GetLongValue()));
    m_pItemValueNum->setString(StringUtils::format("%d",int(itemprop->getValueCopper())));
    
    if (itemprop->isStackable()) {
        m_pItemCount->setVisible(true);
        PickableItemProperty::PickableItemPropertyType itemtype =itemprop->getPickableItemPropertyType() ;
        if ( itemtype == PickableItemProperty::PIPT_KEY) {
            
            CCLOG("合并 PIPT_KEY");
            
        }else if (itemtype == PickableItemProperty::PIPT_MATERIAL){
            
            CCLOG("合并 PIPT_MATERIAL");
            
        }else if(itemtype == PickableItemProperty::PIPT_POTIONS)
        {
            CCLOG("合并 PIPT_POTIONS");
        }
    }
    
    m_pItemIcon->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
}
void ItemPopupUI::onClickDiscard(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickDiscard");
    if(PlayerProperty::getInstance()->removeItemFromBag(CChaosNumber(m_nItemId)))
        closePopup();
}

void ItemPopupUI::onClickUser(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickUser");
}
