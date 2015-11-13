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
    
    switch (type) {
        case PickableItem::PIT_POTION_MINORHEALTH:
        case PickableItem::PIT_POTION_MINORMANA:
        case PickableItem::PIT_POTION_MINORRECOVERY:
            m_nValue = 50;
            break;
        case PickableItem::PIT_POTION_LESSERHEALTH:
        case PickableItem::PIT_POTION_LESSERMANA:
        case PickableItem::PIT_POTION_LESSERRECOVERY:
            m_nValue = 150;
            break;
        case PickableItem::PIT_POTION_HEALTH:
        case PickableItem::PIT_POTION_MANA:
        case PickableItem::PIT_POTION_RECOVERY:
            m_nValue = 250;
            break;
        default:
            m_nValue = 0;
            break;
    }
}

void PotionsProperty::adjustByLevel()
{
}
void PotionsProperty::handleIdentify()
{
}