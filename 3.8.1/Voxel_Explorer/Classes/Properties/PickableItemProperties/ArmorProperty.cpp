//
//  ArmorProperty.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/24.
//
//

#include "ArmorProperty.hpp"
#include "UtilityHelper.h"
#include "AlisaMethod.h"
USING_NS_CC;
static std::vector<ADDED_EFFECT> sArmorAddedEffects =
{
    AE_LIGHT_DISTANCE,
    AE_SEARCH_DISTANCE,
    AE_MAX_HP,
    AE_MAX_MP,
    AE_DODGE_RATE,
    AE_MAGICITEM_FIND_RATE,
};
ArmorProperty::ArmorProperty(unsigned int instanceID, PickableItem::PickableItemType type, CChaosNumber level, bool identified)
    :PickableItemProperty(instanceID, type)
{
    m_PropertyType = PIPT_ARMOR;
    m_bIdentified = identified;
    m_bStackable = false;
    m_bEquipable = true;
    m_bCombinable = false;
    m_bDiscardable = true;
    
    m_nLevel = level;
    m_bHasEquiped = false;
    
    m_nAddedLightDistance       =0;
    m_nAddedSearchDistance      =0;
    m_nAddedMaxHP               =0;
    m_nAddedMaxMP               =0;
    m_nAddedArmorClass          =0;
    m_fAddedDodgeRate           =0;
    m_fAddedMagicItemFindRate   =0;
    
    m_strBeforeIndentifyDesc = UtilityHelper::getLocalString(PICKABLE_ITEM_NAMES[type] + "_BIDESC");
    m_strPropertyTypeName = UtilityHelper::getLocalString(PICKABLE_ITEM_PROPERTY_TYPE_NAMES[m_PropertyType]);

    if(type >= PickableItem::PIT_CLOTH_PRO_SHOES && type <= PickableItem::PIT_CLOTH_PRO_STEELARMOR)
        m_bIdentified = false;
    else
        m_bIdentified = identified;
}

void ArmorProperty::adjustByLevel()
{
    if(m_nLevel <= 15)
    {
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_LIGHT_DISTANCE) != m_AddedEffectList.end())
            m_nAddedLightDistance = 1;
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_LIGHT_DISTANCE) != m_AddedEffectList.end())
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
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_DODGE_RATE) != m_AddedEffectList.end())
            m_fAddedDodgeRate = cocos2d::random(0.01f, 0.02f);
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MAGICITEM_FIND_RATE) != m_AddedEffectList.end())
            m_fAddedMagicItemFindRate = cocos2d::random(0.05f, 0.2f);
        
        if (m_nLevel <= 5)
            m_nAddedArmorClass = cocos2d::random(-2, -1);
        else if(m_nLevel <= 10)
            m_nAddedArmorClass = cocos2d::random(-8, -4);
        else
            m_nAddedArmorClass = cocos2d::random(-12, -8);
    }
    else if(m_nLevel <= 30)
    {
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_LIGHT_DISTANCE) != m_AddedEffectList.end())
            m_nAddedLightDistance = cocos2d::random(1, 2);
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_LIGHT_DISTANCE) != m_AddedEffectList.end())
            m_nAddedSearchDistance = cocos2d::random(1, 2);
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
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_DODGE_RATE) != m_AddedEffectList.end())
            m_fAddedDodgeRate = cocos2d::random(0.01f, 0.03f);
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MAGICITEM_FIND_RATE) != m_AddedEffectList.end())
            m_fAddedMagicItemFindRate = cocos2d::random(0.1f, 0.3f);
        
        if (m_nLevel <= 20)
            m_nAddedArmorClass = cocos2d::random(-16, -12);
        else if(m_nLevel <= 25)
            m_nAddedArmorClass = cocos2d::random(-20, -16);
        else
            m_nAddedArmorClass = cocos2d::random(-24, -20);
    }
    else
    {
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_LIGHT_DISTANCE) != m_AddedEffectList.end())
            m_nAddedLightDistance = cocos2d::random(1, 3);
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_LIGHT_DISTANCE) != m_AddedEffectList.end())
            m_nAddedSearchDistance = cocos2d::random(1, 3);
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MAX_HP) != m_AddedEffectList.end())
            m_nAddedMaxHP = cocos2d::random(300, 550);
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MAX_MP) != m_AddedEffectList.end())
            m_nAddedMaxMP = cocos2d::random(300, 550);
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_DODGE_RATE) != m_AddedEffectList.end())
            m_fAddedDodgeRate = cocos2d::random(0.02f, 0.05f);
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MAGICITEM_FIND_RATE) != m_AddedEffectList.end())
            m_fAddedMagicItemFindRate = cocos2d::random(0.15f, 0.45f);
        
        if (m_nLevel <= 35)
            m_nAddedArmorClass = cocos2d::random(-30, -24);
        else if(m_nLevel <= 40)
            m_nAddedArmorClass = cocos2d::random(-40, -30);
        else
            m_nAddedArmorClass = cocos2d::random(-50, -40);
    }
}
void ArmorProperty::handleIdentify()
{
    if(m_bIdentified)
        return;
    m_bIdentified = true;
    m_nLevel = m_nLevel + cocos2d::random(-2, 2);
    m_nLevel = MAX(1, m_nLevel.GetLongValue());
    
    CChaosNumber addedEffectCount = 0;
    
    if(m_ItemType >= PickableItem::PIT_CLOTH_PRO_SHOES && m_ItemType <= PickableItem::PIT_CLOTH_PRO_STEELARMOR)
        addedEffectCount = cocos2d::random(5, 6);
    else
    {
        float percent1 = 0.75f;
        float percent2 = 1.0 - percent1;
        AlisaMethod* am = AlisaMethod::create(percent1, percent2, -1.0, NULL);
        if(am)
        {
            if(am->getRandomIndex() == 0)
                addedEffectCount = cocos2d::random(1, 2);
            else
                addedEffectCount = cocos2d::random(3, 4);
        }
    }
    
    while (m_AddedEffectList.size() < addedEffectCount.GetLongValue()) {
        int index = cocos2d::random(0, int(sArmorAddedEffects.size()-1));
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), sArmorAddedEffects[index]) != m_AddedEffectList.end())
            continue;
        else
            m_AddedEffectList.push_back(sArmorAddedEffects[index]);
    }
    adjustByLevel();
}
CChaosNumber ArmorProperty::getAddedDefense()
{
    return -m_nAddedArmorClass.GetLongValue();
}