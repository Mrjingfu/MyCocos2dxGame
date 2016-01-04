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
    
    switch (type) {
        case PickableItem::PIT_SCROLL_INDENTIFY:
        case PickableItem::PIT_SCROLL_DESTINY:
            {
                m_nValueCopper = 100;
            }
            break;
        case PickableItem::PIT_SCROLL_TELEPORT:
            {
                m_nValueCopper = 200;
            }
            break;
        case PickableItem::PIT_SCROLL_SPEED:
        case PickableItem::PIT_SCROLL_STEALTH:
        case PickableItem::PIT_SCROLL_STRONGER:
            {
                m_nValueCopper = 500;
            }
            break;
        default:
            break;
    }
    m_nCopperWhenBuy = m_nValueCopper * 1.5f;
}

void ScrollProperty::adjustByLevel()
{
}
void ScrollProperty::handleIdentify()
{
    if(m_bIdentified)
        return;
}
bool ScrollProperty::load(const cocos2d::ValueMap& data)
{
    m_PropertyType = (PickableItemPropertyType)data.at("PropertyType").asInt();
    m_nInstanceID = data.at("InstanceID").asInt();
    m_ItemType = (PickableItem::PickableItemType)data.at("ItemType").asInt();
    m_nLevel = (PickableItem::PickableItemType)data.at("Level").asInt();
    m_nValueCopper = data.at("ValueCopper").asInt();
    m_nCopperWhenBuy = data.at("CopperWhenBuy").asInt();
    
    m_nCount = data.at("Count").asInt();
    return true;
}
bool ScrollProperty::save(cocos2d::ValueMap& data)
{
    data["PropertyType"] = (int)m_PropertyType;
    data["InstanceID"] = (int)m_nInstanceID;
    data["ItemType"] = (int)m_ItemType;
    data["Level"] = (int)m_nLevel.GetLongValue();
    data["ValueCopper"] = (int)m_nValueCopper.GetLongValue();
    data["CopperWhenBuy"] = (int)m_nCopperWhenBuy.GetLongValue();
    
    data["Count"] = (int)m_nCount;
    return true;

}