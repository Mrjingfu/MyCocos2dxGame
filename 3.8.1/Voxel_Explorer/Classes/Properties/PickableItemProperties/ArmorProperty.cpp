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
}

void ArmorProperty::adjustByDC()
{
}
void ArmorProperty::handleIdentify()
{
    if(m_bIdentified)
        return;
}
CChaosNumber ArmorProperty::getDefense()
{
    return -m_nArmorClass.GetLongValue();
}