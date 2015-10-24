//
//  MagicOrnamentProperty.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/24.
//
//

#include "MagicOrnamentProperty.hpp"
USING_NS_CC;

MagicOrnamentProperty::MagicOrnamentProperty(unsigned int instanceID, PickableItem::PickableItemType type, bool identified)
    :PickableItemProperty(instanceID, type)
{
    m_PropertyType = PIPT_MAGIC_ORNAMENT;
    m_bIdentified = identified;
    m_bStackable = false;
    m_bEquipable = true;
    m_bCombinable = false;
    m_bDiscardable = true;
    
    m_bHasEquiped = false;
}