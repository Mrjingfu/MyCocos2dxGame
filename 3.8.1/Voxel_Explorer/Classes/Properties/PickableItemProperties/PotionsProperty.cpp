//
//  PotionsProperty.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/24.
//
//

#include "PotionsProperty.hpp"
#include "UtilityHelper.h"
USING_NS_CC;
PotionsProperty::PotionsProperty(unsigned int instanceID, PickableItem::PickableItemType type)
    :PickableItemProperty(instanceID, type)
{
    m_PropertyType = PIPT_POTIONS;
    m_bIdentified = true;
    m_bStackable = true;
    m_bEquipable = false;
    m_bCombinable = true;
    m_bDiscardable = true;
    
    m_strPropertyTypeName = UtilityHelper::getLocalString(PICKABLE_ITEM_PROPERTY_TYPE_NAMES[m_PropertyType]);
}

void PotionsProperty::adjustByLevel()
{
}
void PotionsProperty::handleIdentify()
{
}