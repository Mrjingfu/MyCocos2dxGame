//
//  PotionsProperty.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/24.
//
//

#include "PotionsProperty.hpp"

USING_NS_CC;
PotionsProperty::PotionsProperty(unsigned int instanceID, PickableItem::PickableItemType type, bool identified)
    :PickableItemProperty(instanceID, type)
{
    m_PropertyType = PIPT_POTIONS;
    m_bIdentified = identified;
    m_bStackable = true;
    m_bEquipable = false;
    m_bCombinable = false;
    m_bDiscardable = true;
}