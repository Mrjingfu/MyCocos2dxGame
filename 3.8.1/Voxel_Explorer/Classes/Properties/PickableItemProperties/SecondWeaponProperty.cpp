//
//  SecondWeaponProperty.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/26.
//
//

#include "SecondWeaponProperty.hpp"
#include "PickableItem.hpp"
USING_NS_CC;

SecondWeaponProperty::SecondWeaponProperty(unsigned int instanceID, PickableItem::PickableItemType type, bool identified)
:PickableItemProperty(instanceID, type)
{
    m_PropertyType = PIPT_SECOND_WEAPON;
    m_bIdentified = identified;
    m_bStackable = false;
    m_bEquipable = true;
    m_bCombinable = false;
    m_bDiscardable = true;
    
    m_bHasEquiped = false;
    
    if(type > PickableItem::PIT_BOW_SHORTBOW && type < PickableItem::PIT_BOW_PRO_GOLDENBOW)
        m_SWPType = SWPT_BOW;
    else if(type > PickableItem::PIT_STAFF_OAKSTAFF && type < PickableItem::PIT_STAFF_PRO_MONKSTAFF)
        m_SWPType = SWPT_STAFF;
    else if(type > PickableItem::PIT_SHIELD_WOODENSHIELD && type < PickableItem::PIT_SHIELD_PRO_TOWERSHIELD)
        m_SWPType = SWPT_SHIELD;
    else
        m_SWPType = SWPT_UNKNOWN;
}


void SecondWeaponProperty::adjustByDC()
{
    
}
void SecondWeaponProperty::handleIdentify()
{
    if(m_bIdentified)
        return;
}
CChaosNumber SecondWeaponProperty::getAddedDefense()
{
    return -m_nAddedArmorClass.GetLongValue();
}