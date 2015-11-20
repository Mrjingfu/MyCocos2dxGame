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

    m_pItemBasicAtk = nullptr;
    m_pItemBasicDef = nullptr;
    m_pItemHp = nullptr;
    m_pItemMp = nullptr;
    m_pItemLightDis = nullptr;
    m_pItemSearchDis = nullptr;
    m_pItemMargicFind = nullptr;
    m_pItemCriticalStrike = nullptr;
    m_pItemBlock = nullptr;
    m_pItemDodge = nullptr;
    m_pItemMinHurt = nullptr;
    m_pItemMaxHurt = nullptr;
    
    m_pItemGoldIcon = nullptr;
    m_pItemSilverIcon= nullptr;
    m_pItemCopperIcon= nullptr;
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
        return true;
    }
    return false;
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
    
       m_pItemBasicAtk = NoteUi::create();
    if (!m_pItemBasicAtk)
        return false;
    
    m_pItemBasicDef = NoteUi::create();
    if (!m_pItemBasicDef)
        return false;
    
    m_pItemDesc = NoteUi::create();
    if (!m_pItemDesc)
        return false;
    
    m_pItemHp = NoteUi::create();
    if (!m_pItemHp)
        return false;

    m_pItemMp = NoteUi::create();
    if (!m_pItemMp)
        return false;
    
    m_pItemLightDis =NoteUi::create();
    if (!m_pItemLightDis)
        return false;
    
    m_pItemSearchDis = NoteUi::create();
    if (!m_pItemSearchDis)
        return false;

    m_pItemMargicFind = NoteUi::create();
    if (!m_pItemMargicFind)
        return false;

    m_pItemCriticalStrike =NoteUi::create();
    if (!m_pItemCriticalStrike)
        return false;
    
    m_pItemBlock = NoteUi::create();
    if (!m_pItemBlock)
        return false;

    m_pItemDodge = NoteUi::create();
    if (!m_pItemDodge)
        return false;
    m_pItemMinHurt = NoteUi::create();
    if (!m_pItemMinHurt)
        return false;
    m_pItemMaxHurt = NoteUi::create();
    if (!m_pItemMaxHurt)
        return false;
   
    m_pItemBasicAtk->setFontScale(0.25);
    m_pItemBasicAtk->setFontScale(0.25);
    
    m_pItemDesc->setFontScale(0.25);
    m_pItemBasicAtk->setFontScale(0.25);
    m_pItemBasicDef ->setFontScale(0.25);
    m_pItemHp->setFontScale(0.25);
    m_pItemMp->setFontScale(0.25);
    m_pItemLightDis->setFontScale(0.25);
    m_pItemSearchDis->setFontScale(0.25);
    m_pItemMargicFind ->setFontScale(0.25);
    m_pItemCriticalStrike ->setFontScale(0.25);
    m_pItemBlock->setFontScale(0.25);
    m_pItemDodge->setFontScale(0.25);
    m_pItemMinHurt->setFontScale(0.25);
    m_pItemMaxHurt->setFontScale(0.25);


    m_pAttrFrame->setLayoutType(ui::Layout::Type::VERTICAL);
    m_pItemDesc->setContentSize(cocos2d::Size(m_pAttrFrame->getContentSize().width,20));
    m_pItemBasicAtk->setContentSize(cocos2d::Size(m_pAttrFrame->getContentSize().width,20));
    m_pItemBasicDef ->setContentSize(cocos2d::Size(m_pAttrFrame->getContentSize().width,20));
    m_pItemHp->setContentSize(cocos2d::Size(m_pAttrFrame->getContentSize().width,20));
    m_pItemMp->setContentSize(cocos2d::Size(m_pAttrFrame->getContentSize().width,20));
    m_pItemLightDis->setContentSize(cocos2d::Size(m_pAttrFrame->getContentSize().width,20));
    m_pItemSearchDis ->setContentSize(cocos2d::Size(m_pAttrFrame->getContentSize().width,20));
    m_pItemMargicFind ->setContentSize(cocos2d::Size(m_pAttrFrame->getContentSize().width,20));
    m_pItemCriticalStrike ->setContentSize(cocos2d::Size(m_pAttrFrame->getContentSize().width,20));
    m_pItemBlock ->setContentSize(cocos2d::Size(m_pAttrFrame->getContentSize().width,20));
    m_pItemDodge ->setContentSize(cocos2d::Size(m_pAttrFrame->getContentSize().width,20));
    m_pItemMinHurt ->setContentSize(cocos2d::Size(m_pAttrFrame->getContentSize().width,20));
    m_pItemMaxHurt ->setContentSize(cocos2d::Size(m_pAttrFrame->getContentSize().width,20));
    
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
    linerParmter->setMargin(ui::Margin(0,15,0,0));
    
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
        
        m_pItemBasicAtk->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_ATTACK").c_str(),int(itemproperty->getMinAttack()),int(itemproperty->getMaxAttack())));
        m_pItemBasicAtk->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pAttrFrame->addChild(m_pItemBasicAtk);

        ui::LinearLayoutParameter* linerParmter = ui::LinearLayoutParameter::create();
        linerParmter->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
        linerParmter->setMargin(ui::Margin(0,-5,0,0));
        
        
        
        for (int i = 0 ; i<size; i++) {
            ADDED_EFFECT effect = effectList.at(i);
            if(effect ==AE_LIGHT_DISTANCE)
            {
                m_pItemLightDis->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_LIGHT").c_str(),int(itemproperty->getAddedLightDistance())),effectColor);
                m_pItemLightDis->setLayoutParameter(linerParmter);
                m_pItemLightDis->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemLightDis);
            }else if(effect ==AE_MAX_HP)
            {
                m_pItemHp->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_HP").c_str(),int(itemproperty->getAddedMaxHp())),effectColor);
                m_pItemHp->setLayoutParameter(linerParmter);
                m_pItemHp->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemHp);
                
            }else if(effect ==AE_MAX_MP)
            {
                m_pItemMp->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MP").c_str(),int(itemproperty->getAddedMaxMp())),effectColor);
                m_pItemMp->setLayoutParameter(linerParmter);
                m_pItemMp->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemMp);
            }else if(effect ==AE_MIN_ATTACK)
            {
                m_pItemMinHurt->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MIN_HURT").c_str(),int(itemproperty->getMinAttack())),effectColor);
                m_pItemMinHurt->setLayoutParameter(linerParmter);
                m_pItemMinHurt->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemMinHurt);
            }else if(effect ==AE_MAX_ATTACK)
            {
                m_pItemMaxHurt->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MAX_HURT").c_str(),int(itemproperty->getAddedMaxAttack())),effectColor);
                m_pItemMaxHurt->setLayoutParameter(linerParmter);
                m_pItemMaxHurt->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemMaxHurt);
            }else if(effect ==AE_MAGICITEM_FIND_RATE){
                m_pItemMargicFind->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MAGIC").c_str(),int(itemproperty->getAddedMagicItemFindRate())),effectColor);
                m_pItemMargicFind->setLayoutParameter(linerParmter);
                m_pItemMargicFind->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemMargicFind);
            }
        }

        m_pItemDesc->setLayoutParameter(linerParmter);
        m_pItemDesc->setItemText(str);
        m_pAttrFrame->addChild(m_pItemDesc);
        
    }else if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_ARMOR)
    {
        ArmorProperty* itemproperty = static_cast<ArmorProperty*>(itemprop);
        
        m_pItemBasicDef->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_DEFENSE").c_str(),int(itemproperty->getAddedDefense())));
        m_pItemBasicDef->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pAttrFrame->addChild(m_pItemBasicDef);
        
        ui::LinearLayoutParameter* linerParmter = ui::LinearLayoutParameter::create();
        linerParmter->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
        linerParmter->setMargin(ui::Margin(0,-5,0,0));
        
        for (int i = 0 ; i<size; i++) {
            ADDED_EFFECT effect = effectList.at(i);
            if(effect ==AE_LIGHT_DISTANCE)
            {
                m_pItemLightDis->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_LIGHT").c_str(),int(itemproperty->getAddedLightDistance())),effectColor);
                m_pItemLightDis->setLayoutParameter(linerParmter);
                m_pItemLightDis->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemLightDis);
            }else if(effect ==AE_MAX_HP)
            {
                m_pItemHp->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_HP").c_str(),int(itemproperty->getAddedMaxHp())),effectColor);
                m_pItemHp->setLayoutParameter(linerParmter);
                m_pItemHp->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemHp);
                
            }else if(effect ==AE_MAX_MP)
            {
                m_pItemMp->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MP").c_str(),int(itemproperty->getAddedMaxMp())),effectColor);
                m_pItemMp->setLayoutParameter(linerParmter);
                m_pItemMp->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemMp);
            }else if(effect ==AE_MAGICITEM_FIND_RATE){
                m_pItemMargicFind->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MAGIC").c_str(),int(itemproperty->getAddedMagicItemFindRate())),effectColor);
                m_pItemMargicFind->setLayoutParameter(linerParmter);
                m_pItemMargicFind->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemMargicFind);
            }else if (effect ==AE_SEARCH_DISTANCE)
            {
                m_pItemSearchDis->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_SEQRCH").c_str(),int(itemproperty->getAddedSearchDistance())),effectColor);
                m_pItemSearchDis->setLayoutParameter(linerParmter);
                m_pItemSearchDis->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemSearchDis);
            }else if (effect == AE_DODGE_RATE)
            {
                m_pItemDodge->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_DODGE").c_str(),int(itemproperty->getAddedMagicItemFindRate())),effectColor);
                m_pItemDodge->setLayoutParameter(linerParmter);
                m_pItemDodge->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemDodge);
            }
        }
        
        m_pItemDesc->setLayoutParameter(linerParmter);
        m_pItemDesc->setItemText(str);
        m_pAttrFrame->addChild(m_pItemDesc);
        
        
    }else if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_MAGIC_ORNAMENT)
    {
        MagicOrnamentProperty* itemproperty = static_cast<MagicOrnamentProperty*>(itemprop);

        ui::LinearLayoutParameter* linerParmter = ui::LinearLayoutParameter::create();
        linerParmter->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
        linerParmter->setMargin(ui::Margin(0,-5,0,0));
        
        for (int i = 0 ; i<size; i++) {
            ADDED_EFFECT effect = effectList.at(i);
            if(effect ==AE_LIGHT_DISTANCE)
            {
                m_pItemLightDis->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_LIGHT").c_str(),int(itemproperty->getAddedLightDistance())),effectColor);
                if (i!=0)
                    m_pItemLightDis->setLayoutParameter(linerParmter);
                m_pItemLightDis->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemLightDis);
            }else if(effect ==AE_MAX_HP)
            {
                m_pItemHp->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_HP").c_str(),int(itemproperty->getAddedMaxHp())),effectColor);
                m_pItemHp->setLayoutParameter(linerParmter);
                m_pItemHp->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemHp);
                
            }else if(effect ==AE_MAX_MP)
            {
                m_pItemMp->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MP").c_str(),int(itemproperty->getAddedMaxMp())),effectColor);
                if (i!=0)
                    m_pItemMp->setLayoutParameter(linerParmter);
                m_pItemMp->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemMp);
            }else if(effect ==AE_MIN_ATTACK)
            {
                m_pItemMinHurt->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MIN_HURT").c_str(),int(itemproperty->getAddedMinAttack())),effectColor);
                if (i!=0)
                    m_pItemMinHurt->setLayoutParameter(linerParmter);
                m_pItemMinHurt->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemMinHurt);
            }else if(effect ==AE_MAX_ATTACK)
            {
                m_pItemMaxHurt->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MAX_HURT").c_str(),int(itemproperty->getAddedMaxAttack())),effectColor);
                if (i!=0)
                    m_pItemMaxHurt->setLayoutParameter(linerParmter);
                m_pItemMaxHurt->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemMaxHurt);
            }else if(effect ==AE_MAGICITEM_FIND_RATE){
                m_pItemMargicFind->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MAGIC").c_str(),int(itemproperty->getAddedMagicItemFindRate())),effectColor);
                if (i!=0)
                    m_pItemMargicFind->setLayoutParameter(linerParmter);
                m_pItemMargicFind->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemMargicFind);
            }else if (effect ==AE_SEARCH_DISTANCE)
            {
                m_pItemSearchDis->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_SEQRCH").c_str(),int(itemproperty->getAddedSearchDistance())),effectColor);
                if (i!=0)
                    m_pItemSearchDis->setLayoutParameter(linerParmter);
                m_pItemSearchDis->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemSearchDis);
            }else if (effect == AE_DODGE_RATE)
            {
                m_pItemDodge->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_DODGE").c_str(),int(itemproperty->getAddedMagicItemFindRate())),effectColor);
                if (i!=0)
                    m_pItemDodge->setLayoutParameter(linerParmter);
                m_pItemDodge->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemDodge);
            }else if (effect == AE_BLOCK_RATE)
            {
                m_pItemBlock->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_BLOCK").c_str(),int(itemproperty->getAddedMagicItemFindRate())),effectColor);
                if (i!=0)
                    m_pItemBlock->setLayoutParameter(linerParmter);
                m_pItemBlock->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemBlock);
            }else if (effect == AE_CRITICALSTRICK_RATE)
            {
                m_pItemCriticalStrike->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_CRITICAL_STRIKE").c_str(),int(itemproperty->getAddedMagicItemFindRate())),effectColor);
                if (i!=0)
                    m_pItemCriticalStrike->setLayoutParameter(linerParmter);
                m_pItemCriticalStrike->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemCriticalStrike);
            }
        }
        
        m_pItemDesc->setItemText(str);
        m_pAttrFrame->addChild(m_pItemDesc);

        
    }else if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_SECOND_WEAPON)
    {
        SecondWeaponProperty* itemproperty = static_cast<SecondWeaponProperty*>(itemprop);
        
        ui::LinearLayoutParameter* linerParmter = ui::LinearLayoutParameter::create();
        linerParmter->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
        linerParmter->setMargin(ui::Margin(0,-5,0,0));
        
        for (int i = 0 ; i<size; i++) {
            ADDED_EFFECT effect = effectList.at(i);
            if(effect ==AE_LIGHT_DISTANCE)
            {
                m_pItemLightDis->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_LIGHT").c_str(),int(itemproperty->getAddedLightDistance())),effectColor);
                if (i!=0)
                    m_pItemLightDis->setLayoutParameter(linerParmter);
                m_pItemLightDis->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemLightDis);
            }else if(effect ==AE_MAX_HP)
            {
                m_pItemHp->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_HP").c_str(),int(itemproperty->getAddedMaxHp())),effectColor);
                if (i!=0)
                    m_pItemHp->setLayoutParameter(linerParmter);
                m_pItemHp->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemHp);
                
            }else if(effect ==AE_MAX_MP)
            {
                m_pItemMp->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MP").c_str(),int(itemproperty->getAddedMaxMp())),effectColor);
                if (i!=0)
                    m_pItemMp->setLayoutParameter(linerParmter);
                m_pItemMp->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemMp);
            }else if(effect ==AE_MIN_ATTACK)
            {
                m_pItemMinHurt->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MIN_HURT").c_str(),int(itemproperty->getAddedMinAttack())),effectColor);
                if (i!=0)
                    m_pItemMinHurt->setLayoutParameter(linerParmter);
                m_pItemMinHurt->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemMinHurt);
            }else if(effect ==AE_MAX_ATTACK)
            {
                m_pItemMaxHurt->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MAX_HURT").c_str(),int(itemproperty->getAddedMaxAttack())),effectColor);
                if (i!=0)
                    m_pItemMaxHurt->setLayoutParameter(linerParmter);
                m_pItemMaxHurt->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemMaxHurt);
            }else if(effect ==AE_MAGICITEM_FIND_RATE){
                m_pItemMargicFind->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MAGIC").c_str(),int(itemproperty->getAddedMagicItemFindRate())),effectColor);
                if (i!=0)
                    m_pItemMargicFind->setLayoutParameter(linerParmter);
                m_pItemMargicFind->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemMargicFind);
            }else if (effect ==AE_SEARCH_DISTANCE)
            {
                m_pItemSearchDis->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_SEQRCH").c_str(),int(itemproperty->getAddedSearchDistance())),effectColor);
                if (i!=0)
                    m_pItemSearchDis->setLayoutParameter(linerParmter);
                m_pItemSearchDis->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemSearchDis);
            }else if (effect == AE_DODGE_RATE)
            {
                m_pItemDodge->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_DODGE").c_str(),int(itemproperty->getAddedMagicItemFindRate())),effectColor);
                if (i!=0)
                    m_pItemDodge->setLayoutParameter(linerParmter);
                m_pItemDodge->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemDodge);
            }else if (effect == AE_BLOCK_RATE)
            {
                m_pItemBlock->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_BLOCK").c_str(),int(itemproperty->getAddedMagicItemFindRate())),effectColor);
                if (i!=0)
                    m_pItemBlock->setLayoutParameter(linerParmter);
                m_pItemBlock->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemBlock);
            }else if (effect == AE_CRITICALSTRICK_RATE)
            {
                m_pItemCriticalStrike->setItemText(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_CRITICAL_STRIKE").c_str(),int(itemproperty->getAddedMagicItemFindRate())),effectColor);
                if (i!=0)
                    m_pItemCriticalStrike->setLayoutParameter(linerParmter);
                m_pItemCriticalStrike->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
                m_pAttrFrame->addChild(m_pItemCriticalStrike);
            }
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
    m_pItemIcon->loadTexture(itemprop->getIconRes());
    m_pItemName->setString(itemprop->getName());
    
    CChaosNumber goldNum = 0;
    CChaosNumber silverNum = 0;
    CChaosNumber copperNum = 0;
    GameFormula::exchangeMoney(itemprop->getValueCopper(), goldNum, silverNum, copperNum);
    
    if (goldNum > 0) {
        m_pItemGoldIcon->setVisible(true);
        m_pItemGoldNum->setString(StringUtils::format("%d",int(goldNum)));
    }
    if (silverNum > 0) {
        m_pItemSilverIcon->setVisible(true);
        m_pItemGoldNum->setString(StringUtils::format("%d",int(silverNum)));
    }
    if (copperNum > 0) {
        m_pItemCopperIcon->setVisible(true);
        m_pItemGoldNum->setString(StringUtils::format("%d",int(copperNum)));
    }
    
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
    if(PlayerProperty::getInstance()->removeItemFromBag(CChaosNumber(m_nItemId)))
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
        CCLOG("装备失败 ");
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
