//
//  ArmorProperty.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/24.
//
//

#include "ArmorProperty.hpp"
USING_NS_CC;
static std::vector<ADDED_EFFECT> sArmorAddedEffects =
{
    AE_LIGHT_DISTANCE,
    AE_SEARCH_DISTANCE,
    AE_MAX_HP,
    AE_MAX_MP,
    AE_ARMOR_CLASS,
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
}

void ArmorProperty::adjustByLevel()
{
}
void ArmorProperty::handleIdentify()
{
    if(m_bIdentified)
        return;
}
CChaosNumber ArmorProperty::getAddedDefense()
{
    return -m_nAddedArmorClass.GetLongValue();
}