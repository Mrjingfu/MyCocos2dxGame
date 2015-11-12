//
//  ScrollProperty.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/24.
//
//

#include "ScrollProperty.hpp"
#include "UtilityHelper.h"
USING_NS_CC;
ScrollProperty::ScrollProperty(unsigned int instanceID, PickableItem::PickableItemType type)
    :PickableItemProperty(instanceID, type)
{
    m_PropertyType = PIPT_SCROLL;
    m_bIdentified = true;
    m_bStackable = true;
    m_bEquipable = false;
    m_bCombinable = false;
    m_bDiscardable = true;
    
    m_strPropertyTypeName = UtilityHelper::getLocalString(PICKABLE_ITEM_PROPERTY_TYPE_NAMES[m_PropertyType]);
}

void ScrollProperty::adjustByLevel()
{
}
void ScrollProperty::handleIdentify()
{
}