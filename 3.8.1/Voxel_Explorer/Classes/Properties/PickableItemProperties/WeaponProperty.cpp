//
//  WeaponProperty.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/24.
//
//

#include "WeaponProperty.hpp"
#include "RandomDungeon.hpp"
#include "UtilityHelper.h"
#include "AlisaMethod.h"
USING_NS_CC;
static std::vector<ADDED_EFFECT> sWeaponAddedEffects =
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
WeaponProperty::WeaponProperty(unsigned int instanceID, PickableItem::PickableItemType type,  CChaosNumber level, bool identified)
    :PickableItemProperty(instanceID, type)
{
    m_PropertyType = PIPT_WEAPON;
    m_bStackable = false;
    m_bEquipable = true;
    m_bCombinable = false;
    m_bDiscardable = true;
    
    m_nLevel = level;
    m_bHasEquiped = false;
    m_nAddedLightDistance       = 0;
    m_nAddedSearchDistance      = 0;
    m_nAddedMaxHP               = 0;
    m_nAddedMaxMP               = 0;
    m_nAddedMinAttack           = 0;
    m_nAddedMaxAttack           = 0;
    m_nAttackDiceNum            = 0;
    m_nAttackDiceFaceNum        = 0;
    m_fAddedCriticalStrikeRate  = 0;
    m_fAddedMagicItemFindRate   = 0;
    
    m_strBeforeIndentifyDesc = UtilityHelper::getLocalString(PICKABLE_ITEM_NAMES[type] + "_BIDESC");
    m_strPropertyTypeName = UtilityHelper::getLocalString(PICKABLE_ITEM_PROPERTY_TYPE_NAMES[m_PropertyType]);
    
    if(type > PickableItem::PIT_DAGGER_DAGGER && type < PickableItem::PIT_DAGGER_PRO_RUBYDAGGER)
        m_WPType = WPT_DAGGER;
    else if(type > PickableItem::PIT_AXE_HATCHET && type < PickableItem::PIT_AXE_PRO_DOUBLEBITAX)
        m_WPType = WPT_AXE;
    else if(type > PickableItem::PIT_SWORD_SWORD && type < PickableItem::PIT_SWORD_PRO_CRYSTALSWORD)
        m_WPType = WPT_SWORD;
    else if(type > PickableItem::PIT_MACE_ROLLINGPIN && type < PickableItem::PIT_MACE_PRO_SLEDGEHAMMER)
        m_WPType = WPT_MACE;
    else
        m_WPType = WPT_UNKNOWN;
    
    if((type >= PickableItem::PIT_DAGGER_PRO_DAGGER && type <= PickableItem::PIT_DAGGER_PRO_RUBYDAGGER) ||
       (type >= PickableItem::PIT_AXE_PRO_HATCHET && type <= PickableItem::PIT_AXE_PRO_DOUBLEBITAX) ||
       (type >= PickableItem::PIT_SWORD_PRO_SWORD && type <= PickableItem::PIT_SWORD_PRO_CRYSTALSWORD) ||
       (type >= PickableItem::PIT_MACE_PRO_ROLLINGPIN && type <= PickableItem::PIT_MACE_PRO_SLEDGEHAMMER)
       )
        m_bIdentified = false;
    else
        m_bIdentified = identified;
}


void WeaponProperty::adjustByLevel()
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
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_CRITICALSTRICK_RATE) != m_AddedEffectList.end())
            m_fAddedCriticalStrikeRate = cocos2d::random(0.02f, 0.04f);
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MAGICITEM_FIND_RATE) != m_AddedEffectList.end())
            m_fAddedMagicItemFindRate = cocos2d::random(0.05f, 0.2f);
        
        if (m_nLevel <= 5)
        {
            if(m_WPType == WPT_DAGGER)
            {
                m_nAttackDiceNum = 1;
                m_nAttackDiceFaceNum = 4;
            }
            else if(m_WPType == WPT_AXE)
            {
                m_nAttackDiceNum = 1;
                m_nAttackDiceFaceNum = 8;
            }
            else if (m_WPType == WPT_SWORD)
            {
                m_nAttackDiceNum = 1;
                m_nAttackDiceFaceNum = 6;
            }
            else if(m_WPType == WPT_MACE)
            {
                m_nAttackDiceNum = 1;
                m_nAttackDiceFaceNum = 6;
            }
        }
        else if(m_nLevel <= 10)
        {
            if(m_WPType == WPT_DAGGER)
            {
                m_nAttackDiceNum = 6;
                m_nAttackDiceFaceNum = 2;
            }
            else if(m_WPType == WPT_AXE)
            {
                m_nAttackDiceNum = 2;
                m_nAttackDiceFaceNum = 10;
            }
            else if (m_WPType == WPT_SWORD)
            {
                m_nAttackDiceNum = 3;
                m_nAttackDiceFaceNum = 6;
            }
            else if(m_WPType == WPT_MACE)
            {
                m_nAttackDiceNum = 5;
                m_nAttackDiceFaceNum = 4;
            }
        }
        else
        {
            if(m_WPType == WPT_DAGGER)
            {
                m_nAttackDiceNum = 6;
                m_nAttackDiceFaceNum = 4;
            }
            else if(m_WPType == WPT_AXE)
            {
                m_nAttackDiceNum = 3;
                m_nAttackDiceFaceNum = 10;
            }
            else if (m_WPType == WPT_SWORD)
            {
                m_nAttackDiceNum = 4;
                m_nAttackDiceFaceNum = 8;
            }
            else if(m_WPType == WPT_MACE)
            {
                m_nAttackDiceNum = 5;
                m_nAttackDiceFaceNum = 6;
            }
        }
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
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_CRITICALSTRICK_RATE) != m_AddedEffectList.end())
            m_fAddedCriticalStrikeRate = cocos2d::random(0.02f, 0.06f);
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MAGICITEM_FIND_RATE) != m_AddedEffectList.end())
            m_fAddedMagicItemFindRate = cocos2d::random(0.1f, 0.3f);
        
        if (m_nLevel <= 20)
        {
            if(m_WPType == WPT_DAGGER)
            {
                m_nAttackDiceNum = 10;
                m_nAttackDiceFaceNum = 4;
            }
            else if(m_WPType == WPT_AXE)
            {
                m_nAttackDiceNum = 4;
                m_nAttackDiceFaceNum = 10;
            }
            else if (m_WPType == WPT_SWORD)
            {
                m_nAttackDiceNum = 5;
                m_nAttackDiceFaceNum = 8;
            }
            else if(m_WPType == WPT_MACE)
            {
                m_nAttackDiceNum = 6;
                m_nAttackDiceFaceNum = 8;
            }
        }
        else if(m_nLevel <= 25)
        {
            if(m_WPType == WPT_DAGGER)
            {
                m_nAttackDiceNum = 12;
                m_nAttackDiceFaceNum = 4;
            }
            else if(m_WPType == WPT_AXE)
            {
                m_nAttackDiceNum = 5;
                m_nAttackDiceFaceNum = 10;
            }
            else if (m_WPType == WPT_SWORD)
            {
                m_nAttackDiceNum = 6;
                m_nAttackDiceFaceNum = 8;
            }
            else if(m_WPType == WPT_MACE)
            {
                m_nAttackDiceNum = 8;
                m_nAttackDiceFaceNum = 6;
            }
        }
        else
        {
            if(m_WPType == WPT_DAGGER)
            {
                m_nAttackDiceNum = 12;
                m_nAttackDiceFaceNum = 6;
            }
            else if(m_WPType == WPT_AXE)
            {
                m_nAttackDiceNum = 6;
                m_nAttackDiceFaceNum = 14;
            }
            else if (m_WPType == WPT_SWORD)
            {
                m_nAttackDiceNum = 10;
                m_nAttackDiceFaceNum = 8;
            }
            else if(m_WPType == WPT_MACE)
            {
                m_nAttackDiceNum = 8;
                m_nAttackDiceFaceNum = 10;
            }
        }
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
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MIN_ATTACK) != m_AddedEffectList.end())
            m_nAddedMinAttack = cocos2d::random(45, 60);
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MAX_ATTACK) != m_AddedEffectList.end())
            m_nAddedMaxAttack = cocos2d::random(100, 150);
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_CRITICALSTRICK_RATE) != m_AddedEffectList.end())
            m_fAddedCriticalStrikeRate = cocos2d::random(0.04f, 0.1f);
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MAGICITEM_FIND_RATE) != m_AddedEffectList.end())
            m_fAddedMagicItemFindRate = cocos2d::random(0.15f, 0.45f);
        
        if (m_nLevel <= 35)
        {
            if(m_WPType == WPT_DAGGER)
            {
                m_nAttackDiceNum = 14;
                m_nAttackDiceFaceNum = 8;
            }
            else if(m_WPType == WPT_AXE)
            {
                m_nAttackDiceNum = 6;
                m_nAttackDiceFaceNum = 20;
            }
            else if (m_WPType == WPT_SWORD)
            {
                m_nAttackDiceNum = 8;
                m_nAttackDiceFaceNum = 14;
            }
            else if(m_WPType == WPT_MACE)
            {
                m_nAttackDiceNum = 10;
                m_nAttackDiceFaceNum = 12;
            }
        }
        else if(m_nLevel <= 40)
        {
            if(m_WPType == WPT_DAGGER)
            {
                m_nAttackDiceNum = 16;
                m_nAttackDiceFaceNum = 8;
            }
            else if(m_WPType == WPT_AXE)
            {
                m_nAttackDiceNum = 8;
                m_nAttackDiceFaceNum = 20;
            }
            else if (m_WPType == WPT_SWORD)
            {
                m_nAttackDiceNum = 10;
                m_nAttackDiceFaceNum = 14;
            }
            else if(m_WPType == WPT_MACE)
            {
                m_nAttackDiceNum = 10;
                m_nAttackDiceFaceNum = 14;
            }
        }
        else
        {
            if(m_WPType == WPT_DAGGER)
            {
                m_nAttackDiceNum = 16;
                m_nAttackDiceFaceNum = 10;
            }
            else if(m_WPType == WPT_AXE)
            {
                m_nAttackDiceNum = 10;
                m_nAttackDiceFaceNum = 20;
            }
            else if (m_WPType == WPT_SWORD)
            {
                m_nAttackDiceNum = 10;
                m_nAttackDiceFaceNum = 16;
            }
            else if(m_WPType == WPT_MACE)
            {
                m_nAttackDiceNum = 10;
                m_nAttackDiceFaceNum = 18;
            }
        }
    }
}
void WeaponProperty::handleIdentify()
{
    if(m_bIdentified)
        return;
    m_bIdentified = true;
    m_nLevel = m_nLevel + cocos2d::random(-2, 2);
    m_nLevel = MAX(1, m_nLevel.GetLongValue());
    
    CChaosNumber addedEffectCount = 0;
    
    if((m_ItemType >= PickableItem::PIT_DAGGER_PRO_DAGGER && m_ItemType <= PickableItem::PIT_DAGGER_PRO_RUBYDAGGER) ||
       (m_ItemType >= PickableItem::PIT_AXE_PRO_HATCHET && m_ItemType <= PickableItem::PIT_AXE_PRO_DOUBLEBITAX) ||
       (m_ItemType >= PickableItem::PIT_SWORD_PRO_SWORD && m_ItemType <= PickableItem::PIT_SWORD_PRO_CRYSTALSWORD) ||
       (m_ItemType >= PickableItem::PIT_MACE_PRO_ROLLINGPIN && m_ItemType <= PickableItem::PIT_MACE_PRO_SLEDGEHAMMER)
       )
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
    int index = cocos2d::random(0, int(sWeaponAddedEffects.size()-1));
    while (m_AddedEffectList.size() < addedEffectCount.GetLongValue()) {
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), sWeaponAddedEffects[index]) != m_AddedEffectList.end())
            continue;
        else
            m_AddedEffectList.push_back(sWeaponAddedEffects[index]);
    }
    adjustByLevel();
}
CChaosNumber WeaponProperty::getMinAttack()
{
    return m_nAttackDiceNum + m_nAddedMinAttack.GetLongValue();
}
CChaosNumber WeaponProperty::getMaxAttack()
{
    return m_nAttackDiceNum*m_nAttackDiceFaceNum.GetLongValue() + m_nAddedMaxAttack.GetLongValue();
}