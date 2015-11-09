//
//  WeaponProperty.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/24.
//
//

#include "WeaponProperty.hpp"
#include "RandomDungeon.hpp"
USING_NS_CC;
static std::vector<ADDED_EFFECT> sWeaponAddedEffects =
{
    AE_LIGHT_DISTANCE,
    AE_SEARCH_DISTANCE,
    AE_MAX_HP,
    AE_MAX_MP,
    AE_MIN_ATTACK,
    AE_MAX_ATTACK,
    AE_DICE_NUM,
    AE_DICE_FACE_NUM,
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
}
void WeaponProperty::handleIdentify()
{
    if(m_bIdentified)
        return;
    m_bIdentified = true;
    m_nLevel = m_nLevel + cocos2d::random(-2, 2);
    m_nLevel = MAX(1, m_nLevel.GetLongValue());
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