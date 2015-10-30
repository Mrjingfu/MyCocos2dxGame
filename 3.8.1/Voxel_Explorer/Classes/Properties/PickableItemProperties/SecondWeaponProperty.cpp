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
    m_fAddedMagicItemFindRate        =0;
    
    
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