//
//  QuestItemProperty.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/24.
//
//

#include "QuestItemProperty.hpp"

USING_NS_CC;
QuestItemProperty::QuestItemProperty(unsigned int instanceID, PickableItem::PickableItemType type)
    :PickableItemProperty(instanceID, type)
{
    m_PropertyType = PIPT_QUEST;
    m_bStackable = false;
    m_bEquipable = false;
    m_bCombinable = false;
    m_bDiscardable = false;
}