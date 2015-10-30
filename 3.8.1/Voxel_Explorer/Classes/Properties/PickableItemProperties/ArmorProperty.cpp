//
//  ArmorProperty.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/24.
//
//

#include "ArmorProperty.hpp"
USING_NS_CC;
ArmorProperty::ArmorProperty(unsigned int instanceID, PickableItem::PickableItemType type, bool identified)
    :PickableItemProperty(instanceID, type)
{
    m_PropertyType = PIPT_ARMOR;
    m_bIdentified = identified;
    m_bStackable = false;
    m_bEquipable = true;
    m_bCombinable = false;
    m_bDiscardable = true;
    
    m_bHasEquiped = false;
    
    m_nAddedLightDistance       =0;
    m_nAddedSearchDistance      =0;
    m_nAddedMaxHP               =0;
    m_nAddedMaxMP               =0;
    m_nAddedArmorClass          =0;
    m_fAddedDodgeRate           =0;
    m_fAddedMagicItemFindRate   =0;
}

void ArmorProperty::adjustByDC()
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