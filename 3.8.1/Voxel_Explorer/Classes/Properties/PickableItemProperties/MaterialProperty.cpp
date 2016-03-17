//
//  MaterialProperty.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/24.
//
//

#include "MaterialProperty.hpp"
#include "UtilityHelper.h"
USING_NS_CC;
std::map<PickableItem::PickableItemType, int> MaterialProperty::WASH_PIQ_RARE=
{
    std::map<PickableItem::PickableItemType, int>::value_type(PickableItem::PIT_MATERIAL_WHITE,1),
    std::map<PickableItem::PickableItemType, int>::value_type(PickableItem::PIT_MATERIAL_GREEN,1),
};
std::map<PickableItem::PickableItemType, int> MaterialProperty::WASH_PIQ_EPIC =
{
    std::map<PickableItem::PickableItemType, int>::value_type(PickableItem::PIT_MATERIAL_WHITE,1),
    std::map<PickableItem::PickableItemType, int>::value_type(PickableItem::PIT_MATERIAL_GREEN,1),
    std::map<PickableItem::PickableItemType, int>::value_type(PickableItem::PIT_MATERIAL_BLUE,1),
};
std::map<PickableItem::PickableItemType, int> MaterialProperty::WASH_PIQ_LEGEND=
{
    std::map<PickableItem::PickableItemType, int>::value_type(PickableItem::PIT_MATERIAL_WHITE,1),
    std::map<PickableItem::PickableItemType, int>::value_type(PickableItem::PIT_MATERIAL_GREEN,1),
    std::map<PickableItem::PickableItemType, int>::value_type(PickableItem::PIT_MATERIAL_BLUE,1),
    std::map<PickableItem::PickableItemType, int>::value_type(PickableItem::PIT_MATERIAL_PURPLE,1)
};
MaterialProperty::MaterialProperty(unsigned int instanceID, PickableItem::PickableItemType type)
    :PickableItemProperty(instanceID, type)
{
    m_PropertyType = PIPT_MATERIAL;
    m_bIdentified = true;
    m_bStackable = true;
    m_bEquipable = false;
    m_bCombinable = true;
    m_bDiscardable = true;
    
    m_strPropertyTypeName = UtilityHelper::getLocalString(PICKABLE_ITEM_PROPERTY_TYPE_NAMES[m_PropertyType]);
    
    switch (type) {
        case PickableItem::PIT_MATERIAL_WHITE:
        {
            m_nValueCopper = 30;
        }
            break;
        case PickableItem::PIT_MATERIAL_GREEN:
        {
            m_nValueCopper = 100;
        }
            break;
        case PickableItem::PIT_MATERIAL_BLUE:
        {
            m_nValueCopper = 300;
        }
            break;
        case PickableItem::PIT_MATERIAL_PURPLE:
        {
            m_nValueCopper = 1000;
        }
            break;
        default:
            break;
    }
     m_nCopperWhenBuy = m_nValueCopper * 2.0f;
    
}
void MaterialProperty::adjustByLevel()
{
    
}
void MaterialProperty::handleIdentify()
{
    if (m_bIdentified)
        return;
}
bool MaterialProperty::load(const cocos2d::ValueMap& data)
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
bool MaterialProperty::save(cocos2d::ValueMap& data)
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
