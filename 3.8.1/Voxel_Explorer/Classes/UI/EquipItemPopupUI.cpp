//
//  ItemPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/26.
//
//

#include "EquipItemPopupUI.h"
#include "UtilityHelper.h"
#include "PlayerProperty.hpp"
#include "WeaponProperty.hpp"
#include "ArmorProperty.hpp"
#include "MagicOrnamentProperty.hpp"
#include "SecondWeaponProperty.hpp"
#include "EventConst.h"
USING_NS_CC;
EquipItemPopupUI::EquipItemPopupUI()
{
    
    m_cActionType = eNone;
    m_pItemIcon    =nullptr;
    m_pItemName    =nullptr;
    m_pItemlv      =nullptr;
    m_pItemDesc    =nullptr;
    m_pBtnItemFrame    =nullptr;
    m_pPropFrame    =nullptr;
    m_pDescItemFrame    =nullptr;
    m_pBtnDiscard    =nullptr;
    m_pBtnEquip    =nullptr;
    m_pBackGround    =nullptr;

    m_pItemType = nullptr;
    m_pItemValueNum = nullptr;
    m_pItemHp = nullptr;
    m_pItemMp = nullptr;
    m_pItemLightDis = nullptr;
    m_pItemSearchDis = nullptr;
    m_pItemMargicFind = nullptr;
    m_pItemCriticalStrike = nullptr;
    m_pItemBlock = nullptr;
    m_pItemDodge = nullptr;
    m_nItemId = -2;
}
EquipItemPopupUI::~EquipItemPopupUI()
{
    
}
bool EquipItemPopupUI::init()
{
    if (PopupUILayer::init())
    {
        this->load("equipitemPopupLayer.csb",false);
        enableDarkLayer(false);
        return true;
    }
    return false;
}
bool EquipItemPopupUI::addEvents()
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
     m_pBtnEquip = dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_btn_equip"));
    if (!m_pBtnEquip)
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
    m_pItemHp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_prop_hp"));
    if (!m_pItemHp)
        return false;
    m_pItemMp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_prop_mp"));
    if (!m_pItemMp)
        return false;
    m_pItemLightDis = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_prop_light"));
    if (!m_pItemLightDis)
        return false;
    m_pItemSearchDis = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_prop_search"));
    if (!m_pItemSearchDis)
        return false;
    m_pItemMargicFind = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_prop_magic"));
    if (!m_pItemMargicFind)
        return false;
    m_pItemCriticalStrike = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_prop_critical_strike"));
    if (!m_pItemCriticalStrike)
        return false;
    m_pItemBlock = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_prop_block"));
    if (!m_pItemBlock)
        return false;
    m_pItemDodge = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_prop_dodge"));
    if (!m_pItemDodge)
        return false;
    
    
    m_pItemCount->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemCount->setVisible(false);
    m_pItemName->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemlv->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemDesc->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemType->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemValueNum->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemHp->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemMp->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemLightDis->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemSearchDis->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemMargicFind->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemCriticalStrike->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemBlock->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemDodge->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    
    m_pBtnDiscard->addClickEventListener(CC_CALLBACK_1(EquipItemPopupUI::onClickDiscard, this));
    m_pBtnEquip->addClickEventListener(CC_CALLBACK_1(EquipItemPopupUI::onClickEquip, this));

  
    return true;
}

void EquipItemPopupUI::itemProperty()
{
    PickableItemProperty* itemprop = PlayerProperty::getInstance()->getItemFromBag(CChaosNumber(m_nItemId));
    if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_WEAPON)
    {
        WeaponProperty* itemproperty = static_cast<WeaponProperty*>(itemprop);
        m_pItemHp->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_HP").c_str(),int(itemproperty->getAddedMaxHp())));
        m_pItemMp->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_MP").c_str(),int(itemproperty->getAddedMaxMp())));
        m_pItemLightDis->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_LIGHT_DIS").c_str(),int(itemproperty->getAddedLightDistance())));
        m_pItemSearchDis->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_SEARCH_DIS").c_str(),int(itemproperty->getAddedSearchDistance())));
        m_pItemCriticalStrike ->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_CRITICAL_STRIKE").c_str(),int(itemproperty->getAddedCriticalStrikeRate())));
        m_pItemMargicFind->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_MARGIC_FIND").c_str(),int(itemproperty->getAddedMagicItemFindRate())));
        
        m_pItemBlock->setVisible(false);
        m_pItemDodge->setVisible(false);
        
    }else if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_ARMOR)
    {
        ArmorProperty* itemproperty = static_cast<ArmorProperty*>(itemprop);
        m_pItemHp->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_HP").c_str(),int(itemproperty->getAddedMaxHp())));
        m_pItemMp->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_MP").c_str(),int(itemproperty->getAddedMaxMp())));
        m_pItemLightDis->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_LIGHT_DIS").c_str(),int(itemproperty->getAddedLightDistance())));
        m_pItemSearchDis->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_SEARCH_DIS").c_str(),int(itemproperty->getAddedSearchDistance())));
        m_pItemMargicFind->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_MARGIC_FIND").c_str(),int(itemproperty->getAddedMagicItemFindRate())));
        m_pItemDodge->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_DODGE").c_str(),int(itemproperty->getAddedDodgeRate())));
        m_pItemDodge->setPosition(m_pItemCriticalStrike->getPosition());
        
        m_pItemCriticalStrike->setVisible(false);
        m_pItemBlock->setVisible(false);
        
    }else if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_MAGIC_ORNAMENT)
    {
        MagicOrnamentProperty* itemproperty = static_cast<MagicOrnamentProperty*>(itemprop);
        m_pItemHp->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_HP").c_str(),int(itemproperty->getAddedMaxHp())));
        m_pItemMp->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_MP").c_str(),int(itemproperty->getAddedMaxMp())));
        m_pItemLightDis->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_LIGHT_DIS").c_str(),int(itemproperty->getAddedLightDistance())));
        m_pItemSearchDis->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_SEARCH_DIS").c_str(),int(itemproperty->getAddedSearchDistance())));
        m_pItemCriticalStrike ->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_CRITICAL_STRIKE").c_str(),int(itemproperty->getAddedCriticalStrikeRate())));
        m_pItemMargicFind->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_MARGIC_FIND").c_str(),int(itemproperty->getAddedMagicItemFindRate())));
        m_pItemBlock->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_BLOCK").c_str(),int(itemproperty->getAddedBlockRate())));
        m_pItemDodge->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_DODGE").c_str(),int(itemproperty->getAddedDodgeRate())));
        
        
    }else if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_SECOND_WEAPON)
    {
        SecondWeaponProperty* itemproperty = static_cast<SecondWeaponProperty*>(itemprop);
        m_pItemHp->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_HP").c_str(),int(itemproperty->getAddedMaxHp())));
        m_pItemMp->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_MP").c_str(),int(itemproperty->getAddedMaxMp())));
        m_pItemLightDis->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_LIGHT_DIS").c_str(),int(itemproperty->getAddedLightDistance())));
        m_pItemSearchDis->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_SEARCH_DIS").c_str(),int(itemproperty->getAddedSearchDistance())));
        m_pItemCriticalStrike ->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_CRITICAL_STRIKE").c_str(),int(itemproperty->getAddedCriticalStrikeRate())));
        m_pItemMargicFind->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_MARGIC_FIND").c_str(),int(itemproperty->getAddedMagicItemFindRate())));
        m_pItemBlock->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_BLOCK").c_str(),int(itemproperty->getAddedBlockRate())));
        m_pItemDodge->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_DODGE").c_str(),int(itemproperty->getAddedDodgeRate())));
    }
}

void EquipItemPopupUI::displayFrame()
{
    m_pBtnItemFrame->setVisible(false);
    m_pRootNode->setContentSize(cocos2d::Size(m_pRootNode->getContentSize().width,m_pRootNode->getContentSize().height-m_pBtnItemFrame->getContentSize().height));
    m_pBackGround->setContentSize(m_pRootNode->getContentSize());
    m_pBackGround->setPosition(m_pBackGround->getContentSize()*0.5);
    m_pPropFrame->setPosition(Vec2(0, m_pRootNode->getContentSize().height));
    m_pDescItemFrame->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    m_pDescItemFrame->setPosition(Vec2::ZERO);
     itemProperty();
}
void EquipItemPopupUI::updateItemPopup(int itemId)
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
    
    if (itemprop->isEquipable() ) {
        if (!(PlayerProperty::getInstance()->getEquipedWeaponID() == m_nItemId ||
            PlayerProperty::getInstance()->getEquipedArmorID() == m_nItemId ||
            PlayerProperty::getInstance()->getEquipedOrnamentsID() == m_nItemId||
              PlayerProperty::getInstance()->getEquipedSecondWeaponID() == m_nItemId)){
            itemProperty();
        }else
        {
            displayFrame();
        }
    }else
    {
        m_pBtnItemFrame->setVisible(true);
    }
    
    m_pItemIcon->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
}
void EquipItemPopupUI::onClickDiscard(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickDiscard");
    if(PlayerProperty::getInstance()->removeItemFromBag(CChaosNumber(m_nItemId)))
        closePopup();
    
}
void EquipItemPopupUI::onClickEquip(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);

    PickableItemProperty* itemprop = PlayerProperty::getInstance()->getItemFromBag(CChaosNumber(m_nItemId));
    bool isEquipSucess = false;
    if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_WEAPON) {
        
        isEquipSucess = PlayerProperty::getInstance()->equipWeapon(CChaosNumber(m_nItemId));
        
    }else if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_ARMOR){
        
        isEquipSucess = PlayerProperty::getInstance()->equipArmor(CChaosNumber(m_nItemId));
        
    }else if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_MAGIC_ORNAMENT)
    {
        isEquipSucess = PlayerProperty::getInstance()->equipOrnaments(CChaosNumber(m_nItemId));
        
    }else if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_SECOND_WEAPON)
    {
        isEquipSucess = PlayerProperty::getInstance()->equipSecondWeapon(CChaosNumber(m_nItemId));
    }
    if (isEquipSucess) {
        closePopup();
    }else{
        //装备失败 或者提前给出提示
    }
}
