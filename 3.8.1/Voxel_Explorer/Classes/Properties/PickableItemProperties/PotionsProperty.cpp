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
            {
                m_nValue = 50;
                m_nValueCopper = 40;
            }
            break;
        case PickableItem::PIT_POTION_MINORRECOVERY:
            {
                m_nValue = 0.25f;
                m_nValueCopper = 300;
            }
            break;
        case PickableItem::PIT_POTION_LESSERHEALTH:
        case PickableItem::PIT_POTION_LESSERMANA:
            {
                m_nValue = 150;
                m_nValueCopper = 200;
            }
            break;
        case PickableItem::PIT_POTION_LESSERRECOVERY:
            {
                m_nValue = 0.5f;
                m_nValueCopper = 1800;
            }
            break;
        case PickableItem::PIT_POTION_HEALTH:
        case PickableItem::PIT_POTION_MANA:
            {
                m_nValue = 250;
                m_nValueCopper = 350;
            }
            break;
        case PickableItem::PIT_POTION_RECOVERY:
            {
                m_nValue = 0.75f;
                m_nValueCopper = 3000;
            }
            break;
        case PickableItem::PIT_POTION_DETOXIFICATION:
            {
                m_nValue = 0;
                m_nValueCopper = 200;
            }
            break;
        case PickableItem::PIT_POTION_SPECIFIC:
            {
                m_nValue = 0;
                m_nValueCopper = 200;
            }
            break;
        case PickableItem::PIT_POTION_HEALING:
            {
                m_nValue = 0;
                m_nValueCopper = 200;
            }
            break;
        case PickableItem::PIT_POTION_UNIVERSAL:
            {
                m_nValue = 0;
                m_nValueCopper = 1000;
            }
        default:
            break;
    }
    m_nCopperWhenBuy = m_nValueCopper * 2.0f;
}

void PotionsProperty::adjustByLevel()
{
}
void PotionsProperty::handleIdentify()
{
    if(m_bIdentified)
        return;
}
bool PotionsProperty::load(const cocos2d::ValueMap& data)
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
bool PotionsProperty::save(cocos2d::ValueMap& data)
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