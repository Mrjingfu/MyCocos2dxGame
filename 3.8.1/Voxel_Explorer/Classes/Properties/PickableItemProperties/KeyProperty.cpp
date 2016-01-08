//
//  KeyProperty.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/24.
//
//

#include "KeyProperty.hpp"
#include "UtilityHelper.h"
USING_NS_CC;

KeyProperty::KeyProperty(unsigned int instanceID, PickableItem::PickableItemType type)
    :PickableItemProperty(instanceID, type)
{
    m_PropertyType = PIPT_KEY;
    m_bIdentified = true;
    m_bStackable = true;
    m_bEquipable = false;
    m_bCombinable = true;
    m_bDiscardable = true;
    
    m_strPropertyTypeName = UtilityHelper::getLocalString(PICKABLE_ITEM_PROPERTY_TYPE_NAMES[m_PropertyType]);
    
    if(m_ItemType == PickableItem::PIT_KEY_COPPER)
        m_nValueCopper = 50;
    else if(m_ItemType == PickableItem::PIT_KEY_SILVER)
        m_nValueCopper = 150;
    else if(m_ItemType == PickableItem::PIT_KEY_GOLD)
        m_nValueCopper = 500;
    else if(m_ItemType == PickableItem::PIT_KEY_ROOM)
    {
        m_bDiscardable = false;
        m_nValueCopper = 0;
    }
    else if(m_ItemType == PickableItem::PIT_KEY_BOSS)
    {
        m_bStackable = false;
        m_bDiscardable = false;
        m_nValueCopper = 0;
    }
    m_nCopperWhenBuy = m_nValueCopper * 2.0f;
}

void KeyProperty::adjustByLevel()
{
}
void KeyProperty::handleIdentify()
{
    if(m_bIdentified)
        return;
}
bool KeyProperty::load(const cocos2d::ValueMap& data)
{
    m_PropertyType = (PickableItemPropertyType)data.at("PropertyType").asInt();
    m_nInstanceID = data.at("InstanceID").asInt();
    m_ItemType = (PickableItem::PickableItemType)data.at("ItemType").asInt();
    m_nLevel = (PickableItem::PickableItemType)data.at("Level").asInt();
    m_nValueCopper = data.at("ValueCopper").asInt();
    m_nCopperWhenBuy = data.at("CopperWhenBuy").asInt();

    m_bIdentified = data.at("Identified").asBool();
    
    m_nCount = data.at("Count").asInt();
    return true;
}
bool KeyProperty::save(cocos2d::ValueMap& data)
{
    data["PropertyType"] = (int)m_PropertyType;
    data["InstanceID"] = (int)m_nInstanceID;
    data["ItemType"] = (int)m_ItemType;
    data["Level"] = (int)m_nLevel.GetLongValue();
    data["ValueCopper"] = (int)m_nValueCopper.GetLongValue();
    data["CopperWhenBuy"] = (int)m_nCopperWhenBuy.GetLongValue();
    
    data["Identified"] = m_bIdentified;
    
    data["Count"] = (int)m_nCount;
    return true;
}