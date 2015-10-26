//
//  PickableItemProperty.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/24.
//
//

#include "PickableItemProperty.hpp"
#include "UtilityHelper.h"
#include "LevelResourceManager.h"
USING_NS_CC;

PickableItemProperty::PickableItemProperty(unsigned int instanceID, PickableItem::PickableItemType type)
{
    m_nInstanceID = instanceID;
    m_PropertyType = PIPT_UNKNOWN;
    m_ItemType = type;
    m_nLevel = 0;
    m_nValueCopper = 0;
    m_strName = UtilityHelper::getLocalString(PICKABLE_ITEM_NAMES[type]);
    m_strDesc = UtilityHelper::getLocalString(PICKABLE_ITEM_NAMES[type] + "_DESC");
    m_strIconRes = LevelResourceManager::getInstance()->getItemIconRes(PICKABLE_ITEM_NAMES[type]);
    m_bIdentified = true;
    m_bStackable = false;
    m_bEquipable = true;
    m_bCombinable = false;
    m_bDiscardable = true;
    m_bCursed = false;
}

