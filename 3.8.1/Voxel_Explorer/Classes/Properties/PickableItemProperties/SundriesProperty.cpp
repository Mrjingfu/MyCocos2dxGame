//
//  SundriesProperty.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/24.
//
//

#include "SundriesProperty.hpp"
#include "UtilityHelper.h"
USING_NS_CC;
SundriesProperty::SundriesProperty(unsigned int instanceID, PickableItem::PickableItemType type)
    :PickableItemProperty(instanceID, type)
{
    m_PropertyType = PIPT_SUNDRIES;
    m_bStackable = true;
    m_bEquipable = false;
    m_bCombinable = false;
    m_bDiscardable = true;
    
    m_strPropertyTypeName = UtilityHelper::getLocalString(PICKABLE_ITEM_PROPERTY_TYPE_NAMES[m_PropertyType]);
}

bool SundriesProperty::load(const cocos2d::ValueMap& data)
{
    return true;
}
bool SundriesProperty::save(cocos2d::ValueMap& data)
{
    return true;
}