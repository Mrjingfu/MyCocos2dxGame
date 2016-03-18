//
//  ItemShopPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/26.
//
//

#include "ItemWashPopupUI.hpp"
#include "UtilityHelper.h"
#include "PlayerProperty.hpp"
#include "AlertPopupUI.hpp"
#include "PopupUILayerManager.h"
#include "WeaponProperty.hpp"
#include "ArmorProperty.hpp"
#include "MagicOrnamentProperty.hpp"
#include "SecondWeaponProperty.hpp"
#include "NoteUi.h"
USING_NS_CC;
ItemWashPopupUI::ItemWashPopupUI()
{
    m_nIsBlankClose     = false;
}
ItemWashPopupUI::~ItemWashPopupUI()
{
    
}

void ItemWashPopupUI::setOldItemProp( PickableItemProperty* itemProp)
{
    m_pOldItemProp = itemProp;
//    refreshUIView();
}

void ItemWashPopupUI::refreshUIView()
{
    ItemPopupUI::refreshUIView();
    
    
    m_pBtnDiscard->setVisible(false);
    m_pBtnEquip->setPosition(m_pBottomFrame->getContentSize()*0.5);
    m_pBtnEquip->setTitleText(UtilityHelper::getLocalStringForUi("BTN_TEXT_OK"));
   
    
    m_pBtnEquip->addClickEventListener(CC_CALLBACK_1(ItemWashPopupUI::onClickConfirm, this));
 }
void ItemWashPopupUI::IdentifyEquiipFrame()
{
    PickableItemProperty* itemprop = getItemIdProperty();
    std::string str;
    if (itemprop->isIdentified()) {
        str = itemprop->getDesc();
    }else
    {
        str= itemprop->getBeforeIndentifyDesc();
    }
    
    int addAttrCount = 0;
    std::vector<ADDED_EFFECT> effectList = itemprop->getAddedEffectList();
    int effectSize = (int)effectList.size();
    
    std::sort(effectList.begin(),effectList.end(),std::less<ADDED_EFFECT>());
    Color3B effectColor = PopupUILayerManager::getInstance()->getTipsColor(TIP_EFFECT);
    Color3B baseColor = Color3B::WHITE;
    ui::LinearLayoutParameter* linerParmter = ui::LinearLayoutParameter::create();
    linerParmter->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
    linerParmter->setMargin(ui::Margin(10,2,0,0));
    
    Color3B upColor = cocos2d::Color3B(0,255,0);
    Color3B downColor = cocos2d::Color3B(255, 80, 31);
    
    CChaosNumber oldNum = 0 ;
    CChaosNumber newNum = 0 ;
    bool isEquipFloat = false;
    
    if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_WEAPON)
    {
        WeaponProperty* itemproperty = static_cast<WeaponProperty*>(itemprop);
        WeaponProperty* olditemproperty = static_cast<WeaponProperty*>(m_pOldItemProp);
        
        ui::LinearLayoutParameter* onelinerParmter = ui::LinearLayoutParameter::create();
        onelinerParmter->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
        onelinerParmter->setMargin(ui::Margin(10,0,0,0));

        addItemProp(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_ATTACK").c_str(),int(itemproperty->getMinAttack()),int(itemproperty->getMaxAttack())),Color3B::WHITE,onelinerParmter);
        ++addAttrCount;
        std::string itemPropStr;
        for (int i = 0 ; i<effectSize; i++) {
            effectColor = PopupUILayerManager::getInstance()->getTipsColor(TIP_EFFECT);
            oldNum = 0 ;
            newNum = 0;
            isEquipFloat = false;
            ADDED_EFFECT effect = effectList.at(i);
            if(effect ==AE_LIGHT_DISTANCE)
            {
                itemPropStr =  StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_LIGHT").c_str(),int(itemproperty->getAddedLightDistance()));
                
                oldNum = olditemproperty->getAddedLightDistance().GetLongValue();
                newNum = itemproperty->getAddedLightDistance().GetLongValue();


            }else if(effect ==AE_MAX_HP)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_HP").c_str(),int(itemproperty->getAddedMaxHp()));
                
                oldNum = olditemproperty->getAddedMaxHp().GetLongValue();
                newNum = itemproperty->getAddedMaxHp().GetLongValue();


            }else if(effect ==AE_MAX_MP)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MP").c_str(),int(itemproperty->getAddedMaxMp()));
                
                oldNum = olditemproperty->getAddedMaxMp().GetLongValue();
                newNum = itemproperty->getAddedMaxMp().GetLongValue();
                
            }else if(effect ==AE_MIN_ATTACK)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MIN_HURT").c_str(),int(itemproperty->getAddedMinAttack()));
                
                oldNum = olditemproperty->getAddedMinAttack().GetLongValue();
                newNum = itemproperty->getAddedMinAttack().GetLongValue();

                
            }else if(effect ==AE_MAX_ATTACK)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MAX_HURT").c_str(),int(itemproperty->getAddedMaxAttack()));
                
                oldNum = olditemproperty->getAddedMaxAttack().GetLongValue();
                newNum = itemproperty->getAddedMaxAttack().GetLongValue();

                
            }else if(effect ==AE_MAGICITEM_FIND_RATE){
                
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MAGIC").c_str(),itemproperty->getAddedMagicItemFindRate().GetFloatValue()*100.0);
                
                oldNum = olditemproperty->getAddedMagicItemFindRate().GetFloatValue();
                newNum = itemproperty->getAddedMagicItemFindRate().GetFloatValue();
                isEquipFloat =true;
                
                
            }else if (effect == AE_CRITICALSTRICK_RATE)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_CRITICAL_STRIKE").c_str(),itemproperty->getAddedCriticalStrikeRate().GetFloatValue()*100.0);
                
                oldNum = olditemproperty->getAddedCriticalStrikeRate().GetFloatValue();
                newNum = itemproperty->getAddedCriticalStrikeRate().GetFloatValue();
                isEquipFloat =true;

                
            }else if (effect == AE_SEARCH_DISTANCE)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_SEQRCH").c_str(),int(itemproperty->getAddedSearchDistance()));
                
                oldNum = olditemproperty->getAddedSearchDistance().GetLongValue();
                newNum = itemproperty->getAddedSearchDistance().GetLongValue();
            }
            
            if (!itemPropStr.empty())
            {
                if (isEquipFloat)
                {
                    if (oldNum > newNum.GetFloatValue())
                    {
                        effectColor = downColor;
                        itemPropStr = itemPropStr.append(StringUtils::format(" (-%.1f%%)",oldNum.GetFloatValue()*100.0f - newNum.GetFloatValue()*100.0f));
                    }else if (oldNum < newNum.GetFloatValue())
                    {
                        effectColor = upColor;
                        itemPropStr = itemPropStr.append(StringUtils::format(" (+%.1f%%)",newNum.GetFloatValue()*100.0f - oldNum.GetFloatValue()*100.0f));
                    }
                }else
                {
                    if (oldNum > newNum.GetLongValue())
                    {
                        effectColor = downColor;
                        itemPropStr = itemPropStr.append(StringUtils::format(" (-%ld)",oldNum.GetLongValue() - newNum.GetLongValue()));
                    }else if (oldNum < newNum.GetLongValue())
                    {
                        effectColor = upColor;
                        itemPropStr = itemPropStr.append(StringUtils::format(" (+%ld)",newNum.GetLongValue() - oldNum.GetLongValue()));
                    }
                 }
                
                
                addItemProp(itemPropStr,effectColor,linerParmter);
                ++addAttrCount;
            }
            
        }
        
        
    }else if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_ARMOR)
    {
        ArmorProperty* itemproperty = static_cast<ArmorProperty*>(itemprop);
        ArmorProperty* olditemproperty = static_cast<ArmorProperty*>(m_pOldItemProp);
        
        ui::LinearLayoutParameter* onelinerParmter = ui::LinearLayoutParameter::create();
        onelinerParmter->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
        onelinerParmter->setMargin(ui::Margin(10,0,0,0));

        oldNum = olditemproperty->getAddedDefense().GetLongValue();
        newNum = itemproperty->getAddedDefense().GetLongValue();
        
        std::string baseStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_DEFENSE").c_str(),int(itemproperty->getAddedDefense()));

        if (oldNum > newNum.GetLongValue())
        {
            effectColor = downColor;
            baseStr = baseStr.append(StringUtils::format(" (-%ld)",oldNum.GetLongValue() - newNum.GetLongValue()));
        }else if (oldNum < newNum.GetLongValue())
        {
            effectColor = upColor;
            baseStr = baseStr.append(StringUtils::format(" (+%ld)",newNum.GetLongValue() - oldNum.GetLongValue()));
        }
    
        
        addItemProp(baseStr, baseColor,onelinerParmter);
        
        ++addAttrCount;
        std::string itemPropStr;
        for (int i = 0 ; i<effectSize; i++) {
            effectColor = PopupUILayerManager::getInstance()->getTipsColor(TIP_EFFECT);
            oldNum = 0 ;
            newNum = 0;
            isEquipFloat = false;
            ADDED_EFFECT effect = effectList.at(i);
            if(effect ==AE_LIGHT_DISTANCE)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_LIGHT").c_str(),int(itemproperty->getAddedLightDistance()));
                
                oldNum = olditemproperty->getAddedLightDistance().GetLongValue();
                newNum = itemproperty->getAddedLightDistance().GetLongValue();

                
            }else if(effect ==AE_MAX_HP)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_HP").c_str(),int(itemproperty->getAddedMaxHp()));
                
                oldNum = olditemproperty->getAddedMaxHp().GetLongValue();
                newNum = itemproperty->getAddedMaxHp().GetLongValue();
                
            }else if(effect ==AE_MAX_MP)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MP").c_str(),int(itemproperty->getAddedMaxMp()));
                
                oldNum = olditemproperty->getAddedMaxMp().GetLongValue();
                newNum = itemproperty->getAddedMaxMp().GetLongValue();
                
            }else if(effect ==AE_MAGICITEM_FIND_RATE){
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MAGIC").c_str(),itemproperty->getAddedMagicItemFindRate().GetFloatValue()*100.0);
                
                oldNum = olditemproperty->getAddedMagicItemFindRate().GetFloatValue();
                newNum = itemproperty->getAddedMagicItemFindRate().GetFloatValue();
                isEquipFloat = true;
                
            }else if (effect ==AE_SEARCH_DISTANCE)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_SEQRCH").c_str(),int(itemproperty->getAddedSearchDistance()));
                
                oldNum = olditemproperty->getAddedSearchDistance().GetLongValue();
                newNum = itemproperty->getAddedSearchDistance().GetLongValue();
            }
            else if (effect == AE_DODGE_RATE)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_DODGE").c_str(),itemproperty->getAddedDodgeRate().GetFloatValue()*100.0);
                
                oldNum = olditemproperty->getAddedDodgeRate().GetFloatValue();
                newNum = itemproperty->getAddedDodgeRate().GetFloatValue();
                isEquipFloat = true;
            }
            
            if (!itemPropStr.empty())
            {
                if (isEquipFloat)
                {
                    if (oldNum > newNum.GetFloatValue())
                    {
                        effectColor = downColor;
                        itemPropStr = itemPropStr.append(StringUtils::format(" (-%.1f%%)",oldNum.GetFloatValue()*100.0f - newNum.GetFloatValue()*100.0f));
                    }else if (oldNum < newNum.GetFloatValue())
                    {
                        effectColor = upColor;
                        itemPropStr = itemPropStr.append(StringUtils::format(" (+%.1f%%)",newNum.GetFloatValue()*100.0f - oldNum.GetFloatValue()*100.0f));
                    }
                }else
                {
                    if (oldNum > newNum.GetLongValue())
                    {
                        effectColor = downColor;
                        itemPropStr = itemPropStr.append(StringUtils::format(" (-%ld)",oldNum.GetLongValue() - newNum.GetLongValue()));
                    }else if (oldNum < newNum.GetLongValue())
                    {
                        effectColor = upColor;
                        itemPropStr = itemPropStr.append(StringUtils::format(" (+%ld)",newNum.GetLongValue() - oldNum.GetLongValue()));
                    }
                }
                
                ++addAttrCount;
                addItemProp(itemPropStr,effectColor,linerParmter);
            }
        }
        
    }else if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_MAGIC_ORNAMENT)
    {
        MagicOrnamentProperty* itemproperty = static_cast<MagicOrnamentProperty*>(itemprop);
        MagicOrnamentProperty* olditemproperty = static_cast<MagicOrnamentProperty*>(m_pOldItemProp);
        
        ui::LinearLayoutParameter* onelinerParmter = ui::LinearLayoutParameter::create();
        onelinerParmter->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
        onelinerParmter->setMargin(ui::Margin(10,0,0,0));
        
        
        oldNum = olditemproperty->getAddedDefense().GetLongValue();
        newNum = itemproperty->getAddedDefense().GetLongValue();
        
        std::string baseStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_DEFENSE").c_str(),int(itemproperty->getAddedDefense()));
        

        if (oldNum > newNum.GetLongValue())
        {
            effectColor = downColor;
            baseStr = baseStr.append(StringUtils::format(" (-%ld)",oldNum.GetLongValue() - newNum.GetLongValue()));
        }else if (oldNum < newNum.GetLongValue())
        {
            effectColor = upColor;
            baseStr = baseStr.append(StringUtils::format(" (+%ld)",newNum.GetLongValue() - oldNum.GetLongValue()));
        }
        addItemProp(baseStr, baseColor,onelinerParmter);
     
        ++addAttrCount;
        
        std::string itemPropStr;
        for (int i = 0 ; i<effectSize; i++) {
            effectColor = PopupUILayerManager::getInstance()->getTipsColor(TIP_EFFECT);
            oldNum = 0 ;
            newNum = 0;
            isEquipFloat = false;
            
            ADDED_EFFECT effect = effectList.at(i);
            if(effect ==AE_LIGHT_DISTANCE)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_LIGHT").c_str(),int(itemproperty->getAddedLightDistance()));
                
                oldNum = olditemproperty->getAddedLightDistance().GetLongValue();
                newNum = itemproperty->getAddedLightDistance().GetLongValue();
                
            }else if(effect ==AE_MAX_HP)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_HP").c_str(),int(itemproperty->getAddedMaxHp()));
                
                oldNum = olditemproperty->getAddedMaxHp().GetLongValue();
                newNum = itemproperty->getAddedMaxHp().GetLongValue();

                
            }else if(effect ==AE_MAX_MP)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MP").c_str(),int(itemproperty->getAddedMaxMp()));
                
                oldNum = olditemproperty->getAddedMaxMp().GetLongValue();
                newNum = itemproperty->getAddedMaxMp().GetLongValue();
                
            }else if(effect ==AE_MIN_ATTACK)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MIN_HURT").c_str(),int(itemproperty->getAddedMinAttack()));
                
                oldNum = olditemproperty->getAddedMinAttack().GetLongValue();
                newNum = itemproperty->getAddedMinAttack().GetLongValue();
                
            }else if(effect ==AE_MAX_ATTACK)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MAX_HURT").c_str(),int(itemproperty->getAddedMaxAttack()));
                
                oldNum = olditemproperty->getAddedMaxAttack().GetLongValue();
                newNum = itemproperty->getAddedMaxAttack().GetLongValue();
                
            }else if(effect ==AE_MAGICITEM_FIND_RATE){
                
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MAGIC").c_str(),itemproperty->getAddedMagicItemFindRate().GetFloatValue()*100.0);
                
                oldNum = olditemproperty->getAddedMagicItemFindRate().GetFloatValue();
                newNum = itemproperty->getAddedMagicItemFindRate().GetFloatValue();
                isEquipFloat = true;
                
            }else if (effect ==AE_SEARCH_DISTANCE)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_SEQRCH").c_str(),int(itemproperty->getAddedSearchDistance()));
                
                oldNum = olditemproperty->getAddedSearchDistance().GetLongValue();
                newNum = itemproperty->getAddedSearchDistance().GetLongValue();
                
            }else if (effect == AE_DODGE_RATE)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_DODGE").c_str(),itemproperty->getAddedDodgeRate().GetFloatValue()*100.0);
                
                oldNum = olditemproperty->getAddedDodgeRate().GetFloatValue();
                newNum = itemproperty->getAddedDodgeRate().GetFloatValue();
                isEquipFloat = true;

                
            }else if (effect == AE_BLOCK_RATE)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_BLOCK").c_str(),itemproperty->getAddedBlockRate().GetFloatValue()*100.0);
                
                oldNum = olditemproperty->getAddedBlockRate().GetFloatValue();
                newNum = itemproperty->getAddedBlockRate().GetFloatValue();
                isEquipFloat = true;
                
            }else if (effect == AE_CRITICALSTRICK_RATE)
            {
                
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_CRITICAL_STRIKE").c_str(),itemproperty->getAddedCriticalStrikeRate().GetFloatValue()*100.0);
                
                oldNum = olditemproperty->getAddedCriticalStrikeRate().GetFloatValue();
                newNum = itemproperty->getAddedCriticalStrikeRate().GetFloatValue();
                isEquipFloat = true;
            }
            if (!itemPropStr.empty())
            {
                if (isEquipFloat)
                {
                    if (oldNum > newNum.GetFloatValue())
                    {
                        effectColor = downColor;
                        itemPropStr = itemPropStr.append(StringUtils::format(" (-%.1f%%)",oldNum.GetFloatValue()*100.0f - newNum.GetFloatValue()*100.0f));
                    }else if (oldNum < newNum.GetFloatValue())
                    {
                        effectColor = upColor;
                        itemPropStr = itemPropStr.append(StringUtils::format(" (+%.1f%%)",newNum.GetFloatValue()*100.0f - oldNum.GetFloatValue()*100.0f));
                    }
                }else
                {
                    if (oldNum > newNum.GetLongValue())
                    {
                        effectColor = downColor;
                        itemPropStr = itemPropStr.append(StringUtils::format(" (-%ld)",oldNum.GetLongValue() - newNum.GetLongValue()));
                    }else if (oldNum < newNum.GetLongValue())
                    {
                        effectColor = upColor;
                        itemPropStr = itemPropStr.append(StringUtils::format(" (+%ld)",newNum.GetLongValue() - oldNum.GetLongValue()));
                    }
                }
                
                
                ++addAttrCount;
                addItemProp(itemPropStr,effectColor,linerParmter);
            }
  
        }
        
        
    }else if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_SECOND_WEAPON)
    {
        SecondWeaponProperty* itemproperty = static_cast<SecondWeaponProperty*>(itemprop);
        SecondWeaponProperty* olditemproperty = static_cast<SecondWeaponProperty*>(m_pOldItemProp);
        
        
        SecondWeaponProperty::SecondWeaponPropertyType secondWtype =itemproperty->getSecondWeaponPropertyType() ;
        if (secondWtype== SecondWeaponProperty::SWPT_SHIELD)
        {
            ui::LinearLayoutParameter* onelinerParmter = ui::LinearLayoutParameter::create();
            onelinerParmter->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
            onelinerParmter->setMargin(ui::Margin(10,0,0,0));
            
            
            oldNum = olditemproperty->getAddedDefense().GetLongValue();
            newNum = itemproperty->getAddedDefense().GetLongValue();
            
            std::string baseStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_DEFENSE").c_str(),int(itemproperty->getAddedDefense()));
            

            if (oldNum > newNum.GetLongValue())
            {
                effectColor = downColor;
                baseStr = baseStr.append(StringUtils::format(" (-%ld)",oldNum.GetLongValue() - newNum.GetLongValue()));
            }else if (oldNum < newNum.GetLongValue())
            {
                effectColor = upColor;
                baseStr = baseStr.append(StringUtils::format(" (+%ld)",newNum.GetLongValue() - oldNum.GetLongValue()));
            }
            
            addItemProp(baseStr, baseColor,onelinerParmter);
        
            ++addAttrCount;
        }
        
        std::string itemPropStr;
        for (int i = 0 ; i<effectSize; i++) {
            effectColor = PopupUILayerManager::getInstance()->getTipsColor(TIP_EFFECT);
            oldNum = 0 ;
            newNum = 0;
            isEquipFloat = false;
            ADDED_EFFECT effect = effectList.at(i);
            if(effect ==AE_LIGHT_DISTANCE)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_LIGHT").c_str(),int(itemproperty->getAddedLightDistance()));
                
                oldNum = olditemproperty->getAddedLightDistance().GetLongValue();
                newNum = itemproperty->getAddedLightDistance().GetLongValue();

                
            }else if(effect ==AE_MAX_HP)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_HP").c_str(),int(itemproperty->getAddedMaxHp()));
                
                oldNum = olditemproperty->getAddedMaxHp().GetLongValue();
                newNum = itemproperty->getAddedMaxHp().GetLongValue();
                
            }else if(effect ==AE_MAX_MP)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MP").c_str(),int(itemproperty->getAddedMaxMp()));
                
                oldNum = olditemproperty->getAddedMaxMp().GetLongValue();
                newNum = itemproperty->getAddedMaxMp().GetLongValue();
                
            }else if(effect ==AE_MIN_ATTACK)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MIN_HURT").c_str(),int(itemproperty->getAddedMinAttack()));
                
                oldNum = olditemproperty->getAddedMinAttack().GetLongValue();
                newNum = itemproperty->getAddedMinAttack().GetLongValue();
                
            }else if(effect ==AE_MAX_ATTACK)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MAX_HURT").c_str(),int(itemproperty->getAddedMaxAttack()));
                
                oldNum = olditemproperty->getAddedMaxAttack().GetLongValue();
                newNum = itemproperty->getAddedMaxAttack().GetLongValue();
                
            }else if(effect ==AE_MAGICITEM_FIND_RATE){
                
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MAGIC").c_str(),itemproperty->getAddedMagicItemFindRate().GetFloatValue()*100.0);
                
                oldNum = olditemproperty->getAddedMagicItemFindRate().GetFloatValue();
                newNum = itemproperty->getAddedMagicItemFindRate().GetFloatValue();
                isEquipFloat =true;
                
            }else if (effect ==AE_SEARCH_DISTANCE)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_SEQRCH").c_str(),int(itemproperty->getAddedSearchDistance()));
                
                oldNum = olditemproperty->getAddedSearchDistance().GetLongValue();
                newNum = itemproperty->getAddedSearchDistance().GetLongValue();;
                
            }else if (effect == AE_DODGE_RATE)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_DODGE").c_str(),itemproperty->getAddedDodgeRate().GetFloatValue()*100.0);
                
                oldNum = olditemproperty->getAddedDodgeRate().GetFloatValue();
                newNum = itemproperty->getAddedDodgeRate().GetFloatValue();
                isEquipFloat =true;
                
            }else if (effect == AE_BLOCK_RATE)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_BLOCK").c_str(),itemproperty->getAddedBlockRate().GetFloatValue()*100.0);
                
                oldNum = olditemproperty->getAddedBlockRate().GetFloatValue();
                newNum = itemproperty->getAddedBlockRate().GetFloatValue();
                isEquipFloat =true;
                
            }else if (effect == AE_CRITICALSTRICK_RATE)
            {
                
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_CRITICAL_STRIKE").c_str(),itemproperty->getAddedCriticalStrikeRate().GetFloatValue()*100.0);
                
                oldNum = olditemproperty->getAddedCriticalStrikeRate().GetFloatValue();
                newNum = itemproperty->getAddedCriticalStrikeRate().GetFloatValue();
                isEquipFloat =true;
                
            }
            if (itemPropStr.empty())
            {
                itemPropStr.clear();
                continue;
            }
            if (isEquipFloat)
            {
                if (oldNum > newNum.GetFloatValue())
                {
                    effectColor = downColor;
                    itemPropStr = itemPropStr.append(StringUtils::format(" (-%.1f%%)",oldNum.GetFloatValue()*100.0f - newNum.GetFloatValue()*100.0f));
                }else if (oldNum < newNum.GetFloatValue())
                {
                    effectColor = upColor;
                    itemPropStr = itemPropStr.append(StringUtils::format(" (+%.1f%%)",newNum.GetFloatValue()*100.0f - oldNum.GetFloatValue()*100.0f));
                }
            }else
            {
                if (oldNum > newNum.GetLongValue())
                {
                    effectColor = downColor;
                    itemPropStr = itemPropStr.append(StringUtils::format(" (-%ld)",oldNum.GetLongValue() - newNum.GetLongValue()));
                }else if (oldNum < newNum.GetLongValue())
                {
                    effectColor = upColor;
                    itemPropStr = itemPropStr.append(StringUtils::format(" (+%ld)",newNum.GetLongValue() - oldNum.GetLongValue()));
                }
            }
            
            if (secondWtype== SecondWeaponProperty::SWPT_SHIELD)
            {
                addItemProp(itemPropStr,effectColor,linerParmter);
                ++addAttrCount;
            }else
            {
                
                if (i!=0)
                {
                    addItemProp(itemPropStr,effectColor,linerParmter);
                    ++addAttrCount;
                }
                else
                {
                    ui::LinearLayoutParameter* onelinerParmter = ui::LinearLayoutParameter::create();
                    onelinerParmter->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
                    onelinerParmter->setMargin(ui::Margin(10,0,0,0));
                    addItemProp(itemPropStr,effectColor,onelinerParmter);
                    ++addAttrCount;
                }
                itemPropStr.clear();
            }
            
            
        }
    }
    
    
    
    cocos2d::Size addSize =cocos2d::Size::ZERO;
    
    if (addAttrCount>=2) {
        addSize = cocos2d::Size(0,m_pItemDesc->getContentSize().height*addAttrCount);
    }
    if (addAttrCount>=7) {
        addSize = addSize +cocos2d::Size(0,10);
    }
    
    if (!str.empty()) {
        
        ui::LinearLayoutParameter* lastlinerParmter = ui::LinearLayoutParameter::create();
        lastlinerParmter->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
        lastlinerParmter->setMargin(ui::Margin(10,2,0,0));
        m_pItemDesc->setLayoutParameter(lastlinerParmter);
        m_pItemDesc->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pAttrFrame->addChild(m_pItemDesc);
        m_pItemDesc->setItemText(str);
        
        addSize = addSize + cocos2d::Size(0,m_pItemDesc->getContentSize().height);
    }
    
    updateItemPopupSize(addSize);
}
void ItemWashPopupUI::updateBottomUi()
{
    //如果当前道具就是装备道具不添加底部UI
    if (PlayerProperty::getInstance()->getEquipedWeaponID() == m_nItemId ||
        PlayerProperty::getInstance()->getEquipedArmorID() == m_nItemId ||
        PlayerProperty::getInstance()->getEquipedOrnamentsID() == m_nItemId||
        PlayerProperty::getInstance()->getEquipedSecondWeaponID() == m_nItemId){
        
        m_pItemEquipDist->setVisible(true);
        m_pItemEquipDist->setString(UtilityHelper::getLocalStringForUi("ITEM_ALREDY_EQUIP"));
        m_pItemEquipDist->setColor(cocos2d::Color3B(144,248,144));
    }
        addBottomUI();
}
void ItemWashPopupUI::onClickConfirm(Ref* ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onClickSelect");
    PickableItemProperty* itemProp =  PlayerProperty::getInstance()->getItemFromBag(m_nItemId);
    if (itemProp)
    {
        setCloseCallbackParamO(itemProp);
        
    }
    closePopup();
    
}
void ItemWashPopupUI::onKeyBackClick()
{
    
}

