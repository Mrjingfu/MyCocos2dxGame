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
#include "NoteUi.h"
#include "GameFormula.hpp"
#include "PopupUILayerManager.h"
USING_NS_CC;
ItemPopupUI::ItemPopupUI()
{
    
    m_cActionType = eNone;
    m_pItemIcon    =nullptr;
    m_pItemName    =nullptr;
    m_pItemlv      =nullptr;
    m_pItemDesc    =nullptr;
    m_pItemType = nullptr;
    m_pItemGoldNum= nullptr;
    m_pItemSilverNum= nullptr;
    m_pItemCopperNum= nullptr;
    m_pItemIdentifyDesc= nullptr;;
    
    m_pMoneyFrame = nullptr;
    m_pAttrFrame    =nullptr;
    m_pItemPropFrame = nullptr;
    m_pBtnDiscard    =nullptr;
    m_pBtnEquip    =nullptr;
    m_pBackGround    =nullptr;

    
    m_pItemGoldIcon = nullptr;
    m_pItemSilverIcon= nullptr;
    m_pItemCopperIcon= nullptr;
    m_nItemId = -2;
    
}
ItemPopupUI::~ItemPopupUI()
{
    
}
bool ItemPopupUI::initUi()
{
    return this->load("itemPopupLayer.csb",false);
}
bool ItemPopupUI::addEvents()
{
    
    m_pAttrFrame = dynamic_cast<ui::Layout*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_attr_layer"));
    if (!m_pAttrFrame)
        return false;
    m_pMoneyFrame= dynamic_cast<ui::Layout*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_money_frame"));
    if (!m_pAttrFrame)
        return false;
    m_pItemPropFrame= dynamic_cast<ui::Layout*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_prop_layer"));
    if (!m_pItemPropFrame)
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
    
    m_pItemGoldIcon =   dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_gold_icon"));
    if (!m_pItemGoldIcon)
        return false;
    
    m_pItemSilverIcon =   dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_silver_icon"));
    if (!m_pItemSilverIcon)
        return false;
    
    m_pItemCopperIcon =   dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_copper_icon"));
    if (!m_pItemCopperIcon)
        return false;
 
    m_pItemName = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_name_text"));
    if (!m_pItemName)
        return false;
    m_pItemlv = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_lv_num_text"));
    if (!m_pItemlv)
        return false;
   
    m_pItemType = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_prop_type"));
    if (!m_pItemType)
        return false;
    
    m_pItemGoldNum = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_gold_num"));
    if (!m_pItemGoldNum)
        return false;
    
    m_pItemSilverNum = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_silver_num"));
    if (!m_pItemSilverNum)
        return false;
    
    m_pItemCopperNum = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_copper_num"));
    if (!m_pItemCopperNum)
        return false;
    
    ui::Text* m_pItemMoneyDesc = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_money_desc"));
    if (!m_pItemMoneyDesc)
        return false;
    m_pItemMoneyDesc->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemMoneyDesc->setString(UtilityHelper::getLocalStringForUi("ITEM_MONEY_DESC"));
    
    
    m_pItemEquipDist = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_equip_dist"));
    if (!m_pItemEquipDist)
        return false;
    
    m_pItemNotIden = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_prop_not_idn"));
    if (!m_pItemNotIden)
        return false;
    m_pItemDesc = NoteUi::create();
    if (!m_pItemDesc)
        return false;
    m_pAttrFrame->setLayoutType(ui::Layout::Type::VERTICAL);
    m_pItemDesc->setFontScale(0.25);
    m_pItemDesc->setContentSize(cocos2d::Size(m_pAttrFrame->getContentSize().width,20));

    
    m_pItemName->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemlv->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemType->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemlv->setVisible(false);
    m_pItemEquipDist->setVisible(false);
    m_pItemNotIden->setVisible(false);
    m_pItemEquipDist->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemNotIden->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemNotIden->setString(UtilityHelper::getLocalStringForUi("ITEM_NOT_IDENTIFY"));
    
    
    m_pItemGoldIcon->setVisible(false);
    m_pItemSilverIcon->setVisible(false);
    m_pItemCopperIcon->setVisible(false);
    
    m_pBtnDiscard->addClickEventListener(CC_CALLBACK_1(ItemPopupUI::onClickDiscard, this));
    

  
    return true;
}
void ItemPopupUI::noEquipFrame(bool isEquip)
{
    if(isEquip)
    {
//      m_pBtnDiscard->setPosition(cocos2d::Vec2(m_pRootNode->getContentSize().width*0.5,0));
//      m_pBtnEquip->setVisible(false);
        m_pBtnEquip->setBright(true);
        m_pBtnEquip->setTouchEnabled(false);
        
    }else
    {
        m_pBtnEquip->setVisible(false);
        m_pBtnDiscard->setVisible(false);
        
        m_pRootNode->setContentSize(cocos2d::Size(m_pRootNode->getContentSize().width,m_pRootNode->getContentSize().height-m_pBtnDiscard->getContentSize().height));
        m_pBackGround->setContentSize(m_pRootNode->getContentSize());
        m_pBackGround->setPosition(m_pRootNode->getContentSize()*0.5);
        m_pItemPropFrame->setPosition(Vec2(m_pItemPropFrame->getPositionX(), m_pRootNode->getContentSize().height));
        
        m_pMoneyFrame->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
        m_pMoneyFrame->setPosition(cocos2d::Vec2(m_pMoneyFrame->getPositionX(),5));
    }
}
void ItemPopupUI::itemFrame()
{
    PickableItemProperty* itemprop = PlayerProperty::getInstance()->getItemFromBag(CChaosNumber(m_nItemId));
    std::string str = itemprop->getDesc();
    ui::LinearLayoutParameter* linerParmter = ui::LinearLayoutParameter::create();
    linerParmter->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
    linerParmter->setMargin(ui::Margin(5,15,0,0));
    
    m_pItemDesc->setItemText(str);
    m_pItemDesc->setLayoutParameter(linerParmter);
    m_pAttrFrame->addChild(m_pItemDesc);
}

void ItemPopupUI::IdentifyEquiipFrame()
{
    PickableItemProperty* itemprop = PlayerProperty::getInstance()->getItemFromBag(CChaosNumber(m_nItemId));
    std::string str = "传说由来自天魔星的魔矿打造，会逐渐控制主人的心智，使之入魔。";
    if (itemprop->isIdentified()) {
        str = itemprop->getDesc();
    }else
    {
        str= itemprop->getBeforeIndentifyDesc();
    }
    
    std::vector<ADDED_EFFECT> effectList = itemprop->getAddedEffectList();
//     std::vector<ADDED_EFFECT> effectList ={
//        AE_LIGHT_DISTANCE,
//        AE_SEARCH_DISTANCE,
//        AE_MAX_HP,
//        AE_MAX_MP,
//        AE_MIN_ATTACK,
//        AE_MAX_ATTACK,
//        AE_BLOCK_RATE,
//        AE_CRITICALSTRICK_RATE,
//        AE_DODGE_RATE,
//        AE_MAGICITEM_FIND_RATE,
//    };
    int size = effectList.size();
    cocos2d::Size addSize = cocos2d::Size(0,10*size);
    m_pAttrFrame->setContentSize(cocos2d::Size(m_pAttrFrame->getContentSize() + addSize));
    m_pRootNode->setContentSize(m_pRootNode->getContentSize()+addSize);
    m_pBackGround->setContentSize(m_pRootNode->getContentSize());
    m_pBackGround->setPosition(m_pRootNode->getContentSize()*0.5);
    m_pItemPropFrame->setPosition(Vec2(m_pItemPropFrame->getPositionX(), m_pRootNode->getContentSize().height));

    std::sort(effectList.begin(),effectList.end(),std::less<ADDED_EFFECT>());
    Color3B effectColor = PopupUILayerManager::getInstance()->getTipsColor(TIP_EFFECT);
    if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_WEAPON)
    {
        WeaponProperty* itemproperty = static_cast<WeaponProperty*>(itemprop);
        
        addItemProp(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_ATTACK").c_str(),int(itemproperty->getMinAttack()),int(itemproperty->getMaxAttack())));
      

        ui::LinearLayoutParameter* linerParmter = ui::LinearLayoutParameter::create();
        linerParmter->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
        linerParmter->setMargin(ui::Margin(0,-5,0,0));
        
        
         std::string itemPropStr;
        for (int i = 0 ; i<size; i++) {
            ADDED_EFFECT effect = effectList.at(i);
            if(effect ==AE_LIGHT_DISTANCE)
            {
                itemPropStr =  StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_LIGHT").c_str(),int(itemproperty->getAddedLightDistance()));
                
            }else if(effect ==AE_MAX_HP)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_HP").c_str(),int(itemproperty->getAddedMaxHp()));
             }else if(effect ==AE_MAX_MP)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MP").c_str(),int(itemproperty->getAddedMaxMp()));
                
            }else if(effect ==AE_MIN_ATTACK)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MIN_HURT").c_str(),int(itemproperty->getMinAttack()));
                
            }else if(effect ==AE_MAX_ATTACK)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MAX_HURT").c_str(),int(itemproperty->getAddedMaxAttack()));
                
            }else if(effect ==AE_MAGICITEM_FIND_RATE){
                
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MAGIC").c_str(),int(itemproperty->getAddedMagicItemFindRate()));
            }
            
            addItemProp(itemPropStr,effectColor,linerParmter);
        }

        m_pItemDesc->setLayoutParameter(linerParmter);
        m_pItemDesc->setItemText(str);
        m_pAttrFrame->addChild(m_pItemDesc);
        
    }else if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_ARMOR)
    {
        ArmorProperty* itemproperty = static_cast<ArmorProperty*>(itemprop);
        
        addItemProp(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_DEFENSE").c_str(),int(itemproperty->getAddedDefense())), effectColor);
        
        
        ui::LinearLayoutParameter* linerParmter = ui::LinearLayoutParameter::create();
        linerParmter->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
        linerParmter->setMargin(ui::Margin(0,-5,0,0));
        std::string itemPropStr;
        for (int i = 0 ; i<size; i++) {
            ADDED_EFFECT effect = effectList.at(i);
            if(effect ==AE_LIGHT_DISTANCE)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_LIGHT").c_str(),int(itemproperty->getAddedLightDistance()));
              
                
            }else if(effect ==AE_MAX_HP)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_HP").c_str(),int(itemproperty->getAddedMaxHp()));

             }else if(effect ==AE_MAX_MP)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MP").c_str(),int(itemproperty->getAddedMaxMp()));
 
            }else if(effect ==AE_MAGICITEM_FIND_RATE){
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MAGIC").c_str(),int(itemproperty->getAddedMagicItemFindRate()));
                
            }else if (effect ==AE_SEARCH_DISTANCE)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_SEQRCH").c_str(),int(itemproperty->getAddedSearchDistance()));
            }
            else if (effect == AE_DODGE_RATE)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_DODGE").c_str(),int(itemproperty->getAddedMagicItemFindRate()));
                
            }
        }
        addItemProp(itemPropStr,effectColor,linerParmter);
        m_pItemDesc->setLayoutParameter(linerParmter);
        m_pItemDesc->setItemText(str);
        m_pAttrFrame->addChild(m_pItemDesc);
        
        
    }else if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_MAGIC_ORNAMENT)
    {
        MagicOrnamentProperty* itemproperty = static_cast<MagicOrnamentProperty*>(itemprop);

        ui::LinearLayoutParameter* linerParmter = ui::LinearLayoutParameter::create();
        linerParmter->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
        linerParmter->setMargin(ui::Margin(0,-5,0,0));
        
        std::string itemPropStr;
        for (int i = 0 ; i<size; i++) {
            ADDED_EFFECT effect = effectList.at(i);
            if(effect ==AE_LIGHT_DISTANCE)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_LIGHT").c_str(),int(itemproperty->getAddedLightDistance()));
 
            }else if(effect ==AE_MAX_HP)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_HP").c_str(),int(itemproperty->getAddedMaxHp()));
                
            }else if(effect ==AE_MAX_MP)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MP").c_str(),int(itemproperty->getAddedMaxMp()));
               
            }else if(effect ==AE_MIN_ATTACK)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MIN_HURT").c_str(),int(itemproperty->getAddedMinAttack()));
            }else if(effect ==AE_MAX_ATTACK)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MAX_HURT").c_str(),int(itemproperty->getAddedMaxAttack()));
                
            }else if(effect ==AE_MAGICITEM_FIND_RATE){
                
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MAGIC").c_str(),int(itemproperty->getAddedMagicItemFindRate()));
               
            }else if (effect ==AE_SEARCH_DISTANCE)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_SEQRCH").c_str(),int(itemproperty->getAddedSearchDistance()));
                
            }else if (effect == AE_DODGE_RATE)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_DODGE").c_str(),int(itemproperty->getAddedMagicItemFindRate()));
            }else if (effect == AE_BLOCK_RATE)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_BLOCK").c_str(),int(itemproperty->getAddedMagicItemFindRate()));
                
            }else if (effect == AE_CRITICALSTRICK_RATE)
            {
                
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_CRITICAL_STRIKE").c_str(),int(itemproperty->getAddedMagicItemFindRate()));
            }
            
            if (i!=0)
                addItemProp(itemPropStr,effectColor,linerParmter);
            else
                addItemProp(itemPropStr,effectColor);
        }
        
        m_pItemDesc->setItemText(str);
        m_pAttrFrame->addChild(m_pItemDesc);

        
    }else if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_SECOND_WEAPON)
    {
        SecondWeaponProperty* itemproperty = static_cast<SecondWeaponProperty*>(itemprop);
        
        ui::LinearLayoutParameter* linerParmter = ui::LinearLayoutParameter::create();
        linerParmter->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
        linerParmter->setMargin(ui::Margin(0,-5,0,0));
        std::string itemPropStr;
        for (int i = 0 ; i<size; i++) {
            ADDED_EFFECT effect = effectList.at(i);
            if(effect ==AE_LIGHT_DISTANCE)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_LIGHT").c_str(),int(itemproperty->getAddedLightDistance()));
                
            }else if(effect ==AE_MAX_HP)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_HP").c_str(),int(itemproperty->getAddedMaxHp()));
                
            }else if(effect ==AE_MAX_MP)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MP").c_str(),int(itemproperty->getAddedMaxMp()));
                
            }else if(effect ==AE_MIN_ATTACK)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MIN_HURT").c_str(),int(itemproperty->getAddedMinAttack()));
            }else if(effect ==AE_MAX_ATTACK)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MAX_HURT").c_str(),int(itemproperty->getAddedMaxAttack()));
                
            }else if(effect ==AE_MAGICITEM_FIND_RATE){
                
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MAGIC").c_str(),int(itemproperty->getAddedMagicItemFindRate()));
                
            }else if (effect ==AE_SEARCH_DISTANCE)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_SEQRCH").c_str(),int(itemproperty->getAddedSearchDistance()));
                
            }else if (effect == AE_DODGE_RATE)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_DODGE").c_str(),int(itemproperty->getAddedMagicItemFindRate()));
            }else if (effect == AE_BLOCK_RATE)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_BLOCK").c_str(),int(itemproperty->getAddedMagicItemFindRate()));
                
            }else if (effect == AE_CRITICALSTRICK_RATE)
            {
                
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_CRITICAL_STRIKE").c_str(),int(itemproperty->getAddedMagicItemFindRate()));
            }
            
            if (i!=0)
                addItemProp(itemPropStr,effectColor,linerParmter);
            else
                addItemProp(itemPropStr,effectColor);
    
        }
        
        m_pItemDesc->setItemText(str);
        m_pAttrFrame->addChild(m_pItemDesc);

    }
}

void ItemPopupUI::updateItemPopup(int itemId)
{
    m_nItemId = itemId;
    CCLOG("m_nItemId:%d",m_nItemId);
    
    PickableItemProperty* itemprop = PlayerProperty::getInstance()->getItemFromBag(CChaosNumber(m_nItemId));
    m_pItemIcon->loadTexture(itemprop->getIconRes(),cocos2d::ui::Widget::TextureResType::PLIST);
    m_pItemName->setString(itemprop->getName());
    
    updateItemMoney(itemprop->getValueCopper());
    
    PickableItemProperty::PickableItemPropertyType itemtype =itemprop->getPickableItemPropertyType();
    std::string str;
    if (itemtype == ArmorProperty::PIPT_KEY) {
        str = UtilityHelper::getLocalStringForUi("ITEM_PROP_TYPE_KEY");
    }else if (itemtype == ArmorProperty::PIPT_WEAPON)
    {
         str = UtilityHelper::getLocalStringForUi("ITEM_PROP_TYPE_WEAPON");
    }else if (itemtype == ArmorProperty::PIPT_SECOND_WEAPON)
    {
         str = UtilityHelper::getLocalStringForUi("ITEM_PROP_TYPE_SECOND_WEAPON");
    }else if (itemtype == ArmorProperty::PIPT_MAGIC_ORNAMENT)
    {
         str = UtilityHelper::getLocalStringForUi("ITEM_PROP_TYPE_MAGIC_ORNAMENT");
    }else if (itemtype == ArmorProperty::PIPT_SCROLL)
    {
         str = UtilityHelper::getLocalStringForUi("ITEM_PROP_TYPE_SCROLL");
    }else if (itemtype == ArmorProperty::PIPT_POTIONS)
    {
         str = UtilityHelper::getLocalStringForUi("ITEM_PROP_TYPE_POTIONS");
    }else if (itemtype == ArmorProperty::PIPT_MATERIAL)
    {
         str = UtilityHelper::getLocalStringForUi("ITEM_PROP_TYPE_MATERIAL");
    }else if (itemtype == ArmorProperty::PIPT_QUEST)
    {
         str = UtilityHelper::getLocalStringForUi("ITEM_PROP_TYPE_QUEST");
    }else if (itemtype == ArmorProperty::PIPT_SUNDRIES)
    {
         str = UtilityHelper::getLocalStringForUi("ITEM_PROP_TYPE_SUNDRIES");
    }
    
    m_pItemType->setString(str);
    
    if (itemtype ==PickableItemProperty::PIPT_WEAPON ||itemtype ==PickableItemProperty::PIPT_SECOND_WEAPON||
        itemtype ==PickableItemProperty::PIPT_ARMOR ||itemtype ==PickableItemProperty::PIPT_MAGIC_ORNAMENT ) {
        
        m_pBtnEquip->addClickEventListener(CC_CALLBACK_1(ItemPopupUI::onClickEquip, this));
        m_pItemlv->setVisible(true);
        m_pItemlv->setString(StringUtils::format("LV.%ld",itemprop->getLevel().GetLongValue()));
        
        if (itemprop->isEquipable() ) {
            if (PlayerProperty::getInstance()->getEquipedWeaponID() == m_nItemId ||
                PlayerProperty::getInstance()->getEquipedArmorID() == m_nItemId ||
                PlayerProperty::getInstance()->getEquipedOrnamentsID() == m_nItemId||
                PlayerProperty::getInstance()->getEquipedSecondWeaponID() == m_nItemId){
                m_pItemEquipDist->setVisible(true);
                m_pItemEquipDist->setString(UtilityHelper::getLocalStringForUi("ITEM_ALREDY_EQUIP"));
                
                noEquipFrame(false);
            }
        }else
        {
            m_pItemEquipDist->setString(UtilityHelper::getLocalStringForUi("ITEM_NOT_EQUIP"));
            m_pItemEquipDist->setColor(PopupUILayerManager::getInstance()->getTipsColor(TIP_WARNING));
             noEquipFrame(true);
        }
        
        if (itemprop->isIdentified()) {
            m_pItemNotIden->setVisible(false);
        }else
        {
            m_pItemNotIden->setVisible(true);
            
        }
        IdentifyEquiipFrame();
    }else{
         m_pBtnEquip->addClickEventListener(CC_CALLBACK_1(ItemPopupUI::onClickUser, this));
         itemFrame();
    }
    
    m_pItemIcon->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
}
void ItemPopupUI::onClickDiscard(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickDiscard");
    PickableItemProperty* itemprop = PlayerProperty::getInstance()->getItemFromBag(CChaosNumber(m_nItemId));
    bool isSuccess = false;
    if (itemprop->isStackable()) {
        isSuccess = PlayerProperty::getInstance()->removeStackableItemFromBag(itemprop->getPickableItemType(), 1);
    }else{
        isSuccess = PlayerProperty::getInstance()->removeItemFromBag(CChaosNumber(m_nItemId));
    }
    
    if(isSuccess)
        closePopup();
    
}
void ItemPopupUI::onClickUser(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickUser");
    PickableItemProperty* itemprop = PlayerProperty::getInstance()->getItemFromBag(CChaosNumber(m_nItemId));
    PickableItemProperty::PickableItemPropertyType itemtype =itemprop->getPickableItemPropertyType();
     bool isItemUse = false;
    if (itemtype == PickableItemProperty::PIPT_POTIONS)
    {
        isItemUse = PlayerProperty::getInstance()->usePotion(CChaosNumber(m_nItemId));
    }else if (itemtype == PickableItemProperty::PIPT_SCROLL)
    {
        isItemUse = PlayerProperty::getInstance()->useScroll(CChaosNumber(m_nItemId));
    }else if (itemtype == PickableItemProperty::PIPT_KEY)
    {
         PlayerProperty::getInstance()->useKey(itemprop->getPickableItemType());
    }
    if (!isItemUse) {
      
        CCLOG("使用道具失败");
    }

}
void ItemPopupUI::onClickEquip(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);

    PickableItemProperty* itemprop = PlayerProperty::getInstance()->getItemFromBag(CChaosNumber(m_nItemId));
    bool isEquipSuccess = false;
    if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_WEAPON) {
        
        isEquipSuccess = PlayerProperty::getInstance()->equipWeapon(CChaosNumber(m_nItemId));
        
    }else if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_ARMOR){
        
        isEquipSuccess = PlayerProperty::getInstance()->equipArmor(CChaosNumber(m_nItemId));
        
    }else if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_MAGIC_ORNAMENT)
    {
        isEquipSuccess = PlayerProperty::getInstance()->equipOrnaments(CChaosNumber(m_nItemId));
        
    }else if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_SECOND_WEAPON)
    {
        isEquipSuccess = PlayerProperty::getInstance()->equipSecondWeapon(CChaosNumber(m_nItemId));
    }
    if (isEquipSuccess) {
        closePopup();
    }else{
        //装备失败 或者提前给出提示
        CCLOG("装备失败 ");
    }
}
void ItemPopupUI::addItemProp(std::string propStr,cocos2d::Color3B fontColor,cocos2d::ui::LinearLayoutParameter* paramLayout)
{
    NoteUi* itemNote = NoteUi::create();
    itemNote->setFontScale(0.25);
    itemNote->setContentSize(cocos2d::Size(m_pAttrFrame->getContentSize().width,20));
    itemNote->setItemText(propStr,fontColor);
    if (paramLayout)
        itemNote->setLayoutParameter(paramLayout);
    itemNote->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_pAttrFrame->addChild(itemNote);
}
void ItemPopupUI::updateItemMoney(CChaosNumber money)
{
    CChaosNumber goldNum = 0;
    CChaosNumber silverNum = 0;
    CChaosNumber copperNum = 0;
    GameFormula::exchangeMoney(money, goldNum, silverNum, copperNum);
    CCLOG("=======%d=====, %d, %d, %d", (int)(money), (int)(goldNum.GetLongValue()), (int)(silverNum.GetLongValue()), (int)(copperNum.GetLongValue()));
    
    if (goldNum > 0) {
        m_pItemGoldIcon->setVisible(true);
        m_pItemGoldNum->setString(StringUtils::format("%d",int(goldNum)));
        m_pItemSilverIcon->setVisible(true);
        m_pItemSilverNum->setString(StringUtils::format("%d",int(silverNum)));
        m_pItemCopperIcon->setVisible(true);
        m_pItemCopperNum->setString(StringUtils::format("%d",int(copperNum)));
    }
    else if (silverNum > 0) {
        m_pItemSilverIcon->setVisible(true);
        m_pItemSilverNum->setString(StringUtils::format("%d",int(silverNum)));
        m_pItemCopperIcon->setVisible(true);
        m_pItemCopperNum->setString(StringUtils::format("%d",int(copperNum)));
    }
    else if (copperNum > 0) {
        m_pItemCopperIcon->setVisible(true);
        m_pItemCopperNum->setString(StringUtils::format("%d",int(copperNum)));
    }

}
void ItemPopupUI::closePopup()
{
    
    if(m_pPopupType == ePopupItem)
    {
        PopupUILayer* pLayer = nullptr;
        if (PopupUILayerManager::getInstance()->isOpenPopup(ePopupEquipItem,pLayer)) {
            ItemPopupUI* itemPopupUi = static_cast<ItemPopupUI*>(pLayer);
            if (itemPopupUi) {
                itemPopupUi->closePopup();
            }
        }
        
    }
    outAction();
   
    
}
