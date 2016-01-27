//
//  SecondWeaponProperty.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/26.
//
//

#include "SecondWeaponProperty.hpp"
#include "PickableItem.hpp"
#include "UtilityHelper.h"
#include "AlisaMethod.h"
#include "PlayerProperty.hpp"
USING_NS_CC;
static std::vector<ADDED_EFFECT> sBowAddedEffects =
{
    AE_LIGHT_DISTANCE,
    AE_SEARCH_DISTANCE,
    AE_MIN_ATTACK,
    AE_MAX_ATTACK,
    AE_CRITICALSTRICK_RATE,
    AE_DODGE_RATE,
    AE_MAGICITEM_FIND_RATE,
};
static std::vector<ADDED_EFFECT> sStaffAddedEffects =
{
    AE_LIGHT_DISTANCE,
    AE_SEARCH_DISTANCE,
    AE_MAX_HP,
    AE_MAX_MP,
    AE_MIN_ATTACK,
    AE_MAX_ATTACK,
    AE_CRITICALSTRICK_RATE,
    AE_MAGICITEM_FIND_RATE,
};
static std::vector<ADDED_EFFECT> sShieldAddedEffects =
{
    AE_LIGHT_DISTANCE,
    AE_SEARCH_DISTANCE,
    AE_MAX_HP,
    AE_MAX_MP,
    AE_BLOCK_RATE,
    AE_MAGICITEM_FIND_RATE,
};
SecondWeaponProperty::SecondWeaponProperty(unsigned int instanceID, PickableItem::PickableItemType type, CChaosNumber level, bool identified)
:PickableItemProperty(instanceID, type)
{
    m_PropertyType = PIPT_SECOND_WEAPON;
    m_bIdentified = identified;
    m_bStackable = false;
    m_bEquipable = true;
    m_bCombinable = false;
    m_bDiscardable = true;
    
    m_nLevel = level;
    m_bHasEquiped = false;
    
    m_nAddedLightDistance           =0;
     m_nAddedSearchDistance         =0;
    m_nAddedMaxHP                   =0;
    m_nAddedMaxMP                   =0;
    m_nAddedMinAttack               =0;
    m_nAddedMaxAttack               =0;
    m_nAddedArmorClass              =0;
    m_fAddedBlockRate               =0;
    m_fAddedCriticalStrikeRate      =0;
    m_fAddedDodgeRate               =0;
    m_fAddedMagicItemFindRate       =0;
    
    m_strBeforeIndentifyDesc = UtilityHelper::getLocalString(PICKABLE_ITEM_NAMES[type] + "_BIDESC");
    m_strPropertyTypeName = UtilityHelper::getLocalString(PICKABLE_ITEM_PROPERTY_TYPE_NAMES[m_PropertyType]);
    
    if(type >= PickableItem::PIT_BOW_SHORTBOW && type <= PickableItem::PIT_BOW_PRO_GOLDENBOW)
    {
        m_SWPType = SWPT_BOW;
        m_PlayerSkill = PS_MAGICARROW;
    }
    else if(type >= PickableItem::PIT_STAFF_OAKSTAFF && type <= PickableItem::PIT_STAFF_PRO_MONKSTAFF)
    {
        m_SWPType = SWPT_STAFF;
        m_PlayerSkill = PS_FIREBALL;
    }
    else if(type >= PickableItem::PIT_SHIELD_WOODENSHIELD && type <= PickableItem::PIT_SHIELD_PRO_TOWERSHIELD)
    {
        m_SWPType = SWPT_SHIELD;
        m_PlayerSkill = PS_BLOCKRATEUP;
    }
    else
    {
        m_SWPType = SWPT_UNKNOWN;
        m_PlayerSkill = PS_NONE;
    }
    
    if((type >= PickableItem::PIT_BOW_PRO_SHORTBOW && type <= PickableItem::PIT_BOW_PRO_GOLDENBOW) ||
       (type >= PickableItem::PIT_STAFF_PRO_OAKSTAFF && type <= PickableItem::PIT_STAFF_PRO_MONKSTAFF) ||
       (type >= PickableItem::PIT_SHIELD_PRO_WOODENSHIELD && type <= PickableItem::PIT_SHIELD_PRO_TOWERSHIELD))
        m_bIdentified = false;
    else
        m_bIdentified = identified;
}


void SecondWeaponProperty::adjustByLevel()
{
    if(m_nLevel <= 15)
    {
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_LIGHT_DISTANCE) != m_AddedEffectList.end())
            m_nAddedLightDistance = 1;
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_SEARCH_DISTANCE) != m_AddedEffectList.end())
            m_nAddedSearchDistance = 1;
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MAX_HP) != m_AddedEffectList.end())
        {
            if (m_nLevel <= 5)
                m_nAddedMaxHP = cocos2d::random(5, 20);
            else if(m_nLevel <= 10)
                m_nAddedMaxHP = cocos2d::random(15, 50);
            else
                m_nAddedMaxHP = cocos2d::random(40, 100);
        }
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MAX_MP) != m_AddedEffectList.end())
        {
            if (m_nLevel <= 5)
                m_nAddedMaxMP = cocos2d::random(5, 20);
            else if(m_nLevel <= 10)
                m_nAddedMaxMP = cocos2d::random(15, 50);
            else
                m_nAddedMaxMP = cocos2d::random(40, 100);
        }
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MIN_ATTACK) != m_AddedEffectList.end())
        {
            if (m_nLevel <= 5)
                m_nAddedMinAttack = cocos2d::random(1, 3);
            else if(m_nLevel <= 10)
                m_nAddedMinAttack = cocos2d::random(3, 9);
            else
                m_nAddedMinAttack = cocos2d::random(10, 15);
        }
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MAX_ATTACK) != m_AddedEffectList.end())
        {
            if (m_nLevel <= 5)
                m_nAddedMaxAttack = cocos2d::random(2, 6);
            else if(m_nLevel <= 10)
                m_nAddedMaxAttack = cocos2d::random(6, 18);
            else
                m_nAddedMaxAttack = cocos2d::random(20, 30);
        }
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_BLOCK_RATE) != m_AddedEffectList.end())
            m_fAddedBlockRate = cocos2d::random(0.01f, 0.02f);
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_CRITICALSTRICK_RATE) != m_AddedEffectList.end())
            m_fAddedCriticalStrikeRate = cocos2d::random(0.02f, 0.04f);
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_DODGE_RATE) != m_AddedEffectList.end())
            m_fAddedDodgeRate = cocos2d::random(0.01f, 0.02f);
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MAGICITEM_FIND_RATE) != m_AddedEffectList.end())
            m_fAddedMagicItemFindRate = cocos2d::random(0.05f, 0.2f);
        
        if(m_SWPType == SWPT_SHIELD)
        {
            if (m_nLevel <= 5)
                m_nAddedArmorClass = m_nAddedArmorClass = MIN((int)m_nAddedArmorClass.GetLongValue(), cocos2d::random(-2, -1));
            else if(m_nLevel <= 10)
                m_nAddedArmorClass = m_nAddedArmorClass = MIN((int)m_nAddedArmorClass.GetLongValue(), cocos2d::random(-8, -4));
            else
                m_nAddedArmorClass = m_nAddedArmorClass = MIN((int)m_nAddedArmorClass.GetLongValue(), cocos2d::random(-12, -8));
        }
    }
    else if(m_nLevel <= 30)
    {
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_LIGHT_DISTANCE) != m_AddedEffectList.end())
            m_nAddedLightDistance = cocos2d::random(1, 2);
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_SEARCH_DISTANCE) != m_AddedEffectList.end())
            m_nAddedSearchDistance = 1;
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MAX_HP) != m_AddedEffectList.end())
        {
            if (m_nLevel <= 20)
                m_nAddedMaxHP = cocos2d::random(80, 150);
            else if(m_nLevel <= 25)
                m_nAddedMaxHP = cocos2d::random(120, 200);
            else
                m_nAddedMaxHP = cocos2d::random(180, 300);
        }
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MAX_MP) != m_AddedEffectList.end())
        {
            if (m_nLevel <= 20)
                m_nAddedMaxMP = cocos2d::random(80, 150);
            else if(m_nLevel <= 25)
                m_nAddedMaxMP = cocos2d::random(120, 200);
            else
                m_nAddedMaxMP = cocos2d::random(180, 300);
        }
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MIN_ATTACK) != m_AddedEffectList.end())
        {
            if (m_nLevel <= 20)
                m_nAddedMinAttack = cocos2d::random(16, 20);
            else if(m_nLevel <= 25)
                m_nAddedMinAttack = cocos2d::random(21, 30);
            else
                m_nAddedMinAttack = cocos2d::random(31, 45);
        }
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MAX_ATTACK) != m_AddedEffectList.end())
        {
            if (m_nLevel <= 20)
                m_nAddedMaxAttack = cocos2d::random(30, 40);
            else if(m_nLevel <= 25)
                m_nAddedMaxAttack = cocos2d::random(40, 60);
            else
                m_nAddedMaxAttack = cocos2d::random(60, 90);
        }
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_BLOCK_RATE) != m_AddedEffectList.end())
            m_fAddedBlockRate = cocos2d::random(0.01f, 0.03f);
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_CRITICALSTRICK_RATE) != m_AddedEffectList.end())
            m_fAddedCriticalStrikeRate = cocos2d::random(0.02f, 0.06f);
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_DODGE_RATE) != m_AddedEffectList.end())
            m_fAddedDodgeRate = cocos2d::random(0.01f, 0.03f);
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MAGICITEM_FIND_RATE) != m_AddedEffectList.end())
            m_fAddedMagicItemFindRate = cocos2d::random(0.1f, 0.3f);
        
        if(m_SWPType == SWPT_SHIELD)
        {
            if (m_nLevel <= 20)
                m_nAddedArmorClass = m_nAddedArmorClass = MIN((int)m_nAddedArmorClass.GetLongValue(), cocos2d::random(-16, -12));
            else if(m_nLevel <= 25)
                m_nAddedArmorClass = m_nAddedArmorClass = MIN((int)m_nAddedArmorClass.GetLongValue(), cocos2d::random(-20, -16));
            else
                m_nAddedArmorClass = m_nAddedArmorClass = MIN((int)m_nAddedArmorClass.GetLongValue(), cocos2d::random(-24, -20));
        }
    }
    else
    {
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_LIGHT_DISTANCE) != m_AddedEffectList.end())
            m_nAddedLightDistance = cocos2d::random(1, 2);
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_SEARCH_DISTANCE) != m_AddedEffectList.end())
            m_nAddedSearchDistance = 1;
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MAX_HP) != m_AddedEffectList.end())
            m_nAddedMaxHP = cocos2d::random(300, 550);
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MAX_MP) != m_AddedEffectList.end())
            m_nAddedMaxMP = cocos2d::random(300, 550);
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MIN_ATTACK) != m_AddedEffectList.end())
            m_nAddedMinAttack = cocos2d::random(45, 60);
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MAX_ATTACK) != m_AddedEffectList.end())
            m_nAddedMaxAttack = cocos2d::random(100, 150);
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_BLOCK_RATE) != m_AddedEffectList.end())
            m_fAddedBlockRate = cocos2d::random(0.02f, 0.05f);
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_CRITICALSTRICK_RATE) != m_AddedEffectList.end())
            m_fAddedCriticalStrikeRate = cocos2d::random(0.04f, 0.1f);
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_DODGE_RATE) != m_AddedEffectList.end())
            m_fAddedDodgeRate = cocos2d::random(0.02f, 0.05f);
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MAGICITEM_FIND_RATE) != m_AddedEffectList.end())
            m_fAddedMagicItemFindRate = cocos2d::random(0.15f, 0.45f);
        
        if(m_SWPType == SWPT_SHIELD)
        {
            if (m_nLevel <= 35)
                m_nAddedArmorClass = m_nAddedArmorClass = MIN((int)m_nAddedArmorClass.GetLongValue(), cocos2d::random(-30, -24));
            else if(m_nLevel <= 40)
                m_nAddedArmorClass = m_nAddedArmorClass = MIN((int)m_nAddedArmorClass.GetLongValue(), cocos2d::random(-40, -30));
            else
                m_nAddedArmorClass = m_nAddedArmorClass = MIN((int)m_nAddedArmorClass.GetLongValue(), cocos2d::random(-50, -40));
        }
    }
    
    m_nValueCopper = 150 * (int)(m_AddedEffectList.size())*(int)(m_AddedEffectList.size()) + m_nLevel*50;
    m_nCopperWhenBuy = m_nValueCopper * 2.0f;
}
void SecondWeaponProperty::handleIdentify()
{
    if(m_bIdentified)
        return;
    m_bIdentified = true;
    m_nLevel = m_nLevel + cocos2d::random(-2, 2);
    m_nLevel = MAX(1, m_nLevel.GetLongValue());
    
    CChaosNumber addedEffectCount = 0;
    
    if((m_ItemType >= PickableItem::PIT_BOW_PRO_SHORTBOW && m_ItemType <= PickableItem::PIT_BOW_PRO_GOLDENBOW) ||
       (m_ItemType >= PickableItem::PIT_STAFF_PRO_OAKSTAFF && m_ItemType <= PickableItem::PIT_STAFF_PRO_MONKSTAFF) ||
       (m_ItemType >= PickableItem::PIT_SHIELD_PRO_WOODENSHIELD && m_ItemType <= PickableItem::PIT_SHIELD_PRO_TOWERSHIELD))
        addedEffectCount = cocos2d::random(5, 6);
    else
    {
        float percent1 = 0.75f;
        float percent2 = 1.0 - percent1;
        AlisaMethod* am = AlisaMethod::create(percent1, percent2, -1.0, NULL);
        if(am)
        {
            int randIndex = am->getRandomIndex();
            if(randIndex == 0)
                addedEffectCount = cocos2d::random(1, 2);
            else
                addedEffectCount = cocos2d::random(3, 4);
        }
    }
    if(addedEffectCount >= 5)
        m_Quality = PIQ_LEGEND;
    else if(addedEffectCount >= 3)
        m_Quality = PIQ_EPIC;
    else if(addedEffectCount >= 1)
        m_Quality = PIQ_RARE;
    else
        m_Quality = PIQ_GENERAL;
    if(m_ItemType >= PickableItem::PIT_BOW_SHORTBOW && m_ItemType <= PickableItem::PIT_BOW_PRO_GOLDENBOW)
    {
        while (m_AddedEffectList.size() < addedEffectCount.GetLongValue()) {
            int index = cocos2d::random(0, int(sBowAddedEffects.size()-1));
            if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), sBowAddedEffects[index]) != m_AddedEffectList.end())
                continue;
            else
                m_AddedEffectList.push_back(sBowAddedEffects[index]);
        }
    }
    else if(m_ItemType >= PickableItem::PIT_STAFF_OAKSTAFF && m_ItemType <= PickableItem::PIT_STAFF_PRO_MONKSTAFF)
    {
        while (m_AddedEffectList.size() < addedEffectCount.GetLongValue()) {
            int index = cocos2d::random(0, int(sStaffAddedEffects.size()-1));
            if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), sStaffAddedEffects[index]) != m_AddedEffectList.end())
                continue;
            else
                m_AddedEffectList.push_back(sStaffAddedEffects[index]);
        }
    }
    else if(m_ItemType >= PickableItem::PIT_SHIELD_WOODENSHIELD && m_ItemType <= PickableItem::PIT_SHIELD_PRO_TOWERSHIELD)
    {
        while (m_AddedEffectList.size() < addedEffectCount.GetLongValue()) {
            int index = cocos2d::random(0, int(sShieldAddedEffects.size()-1));
            if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), sShieldAddedEffects[index]) != m_AddedEffectList.end())
                continue;
            else
                m_AddedEffectList.push_back(sShieldAddedEffects[index]);
        }

    }
    adjustByLevel();
}
CChaosNumber SecondWeaponProperty::getAddedDefense()
{
    return -m_nAddedArmorClass.GetLongValue();
}
bool SecondWeaponProperty::load(const cocos2d::ValueMap& data)
{
    m_PropertyType = (PickableItemPropertyType)data.at("PropertyType").asInt();
    m_nInstanceID = data.at("InstanceID").asInt();
    m_ItemType = (PickableItem::PickableItemType)data.at("ItemType").asInt();
    m_nLevel = (PickableItem::PickableItemType)data.at("Level").asInt();
    m_nValueCopper = data.at("ValueCopper").asInt();
    m_nCopperWhenBuy = data.at("CopperWhenBuy").asInt();
    m_PlayerSkill = (PlayerSkill)data.at("PlayerSkill").asInt();
    
    m_bIdentified = data.at("Identified").asBool();
    
    if(m_bIdentified)
    {
        m_Quality = (PICKABLEITEM_QUALITY)data.at("Quality").asInt();
        
        ValueVector addedEffectList = data.at("AddedEffectList").asValueVector();
        for (Value value : addedEffectList) {
            m_AddedEffectList.push_back((ADDED_EFFECT)value.asInt());
        }
        
        m_nAddedLightDistance = data.at("AddedLightDistance").asInt();
        m_nAddedSearchDistance = data.at("AddedSearchDistance").asInt();
        m_nAddedMaxHP = data.at("AddedMaxHP").asInt();
        m_nAddedMaxMP = data.at("AddedMaxMP").asInt();
        
        m_nAddedMinAttack = data.at("AddedMinAttack").asInt();
        m_nAddedMaxAttack = data.at("AddedMaxAttack").asInt();

        m_nAddedArmorClass = data.at("AddedArmorClass").asInt();
        
        m_fAddedBlockRate = data.at("AddedBlockRate").asFloat();
        m_fAddedCriticalStrikeRate = data.at("AddedCriticalStrikeRate").asFloat();
        m_fAddedDodgeRate = data.at("AddedDodgeRate").asFloat();
        m_fAddedMagicItemFindRate = data.at("AddedMagicItemFindRate").asFloat();
    }
    return true;
}
bool SecondWeaponProperty::save(cocos2d::ValueMap& data)
{
    data["PropertyType"] = (int)m_PropertyType;
    data["InstanceID"] = (int)m_nInstanceID;
    data["ItemType"] = (int)m_ItemType;
    data["Level"] = (int)m_nLevel.GetLongValue();
    data["ValueCopper"] = (int)m_nValueCopper.GetLongValue();
    data["CopperWhenBuy"] = (int)m_nCopperWhenBuy.GetLongValue();
    data["PlayerSkill"] = (int)m_PlayerSkill;
    
    data["Identified"] = m_bIdentified;
    
    if(m_bIdentified)
    {
        data["Quality"] = (int)m_Quality;
        
        ValueVector addedEffectList;
        for (ADDED_EFFECT effectType : m_AddedEffectList) {
            addedEffectList.push_back(Value((int)effectType));
        }
        data["AddedEffectList"] = addedEffectList;
        
        data["AddedLightDistance"] = (int)m_nAddedLightDistance.GetLongValue();
        data["AddedSearchDistance"] = (int)m_nAddedSearchDistance.GetLongValue();
        data["AddedMaxHP"] = (int)m_nAddedMaxHP.GetLongValue();
        data["AddedMaxMP"] = (int)m_nAddedMaxMP.GetLongValue();
        
        data["AddedMinAttack"] = (int)m_nAddedMinAttack.GetLongValue();
        data["AddedMaxAttack"] = (int)m_nAddedMaxAttack.GetLongValue();
        
        data["AddedArmorClass"] = (int)m_nAddedArmorClass.GetLongValue();
        
        data["AddedBlockRate"] = m_fAddedBlockRate.GetFloatValue();
        data["AddedCriticalStrikeRate"] = m_fAddedCriticalStrikeRate.GetFloatValue();
        data["AddedDodgeRate"] = m_fAddedDodgeRate.GetFloatValue();
        data["AddedMagicItemFindRate"] = m_fAddedMagicItemFindRate.GetFloatValue();
    }
    return true;
}