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
    
    if(type > PickableItem::PIT_BOW_BEGIN && type < PickableItem::PIT_BOW_END)
        m_SWPType = SWPT_BOW;
    else if(type > PickableItem::PIT_STAFF_BEGIN && type < PickableItem::PIT_STAFF_END)
        m_SWPType = SWPT_STAFF;
    else if(type > PickableItem::PIT_SHIELD_BEGIN && type < PickableItem::PIT_SHIELD_END)
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