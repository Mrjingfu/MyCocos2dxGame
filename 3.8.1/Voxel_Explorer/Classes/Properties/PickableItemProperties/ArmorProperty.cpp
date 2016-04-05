//
//  ArmorProperty.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/24.
//
//

#include "ArmorProperty.hpp"
#include "UtilityHelper.h"
#include "AlisaMethod.h"
#include "PlayerProperty.hpp"
USING_NS_CC;
static std::vector<ADDED_EFFECT> sArmorAddedEffects =
{
    AE_LIGHT_DISTANCE,
    AE_SEARCH_DISTANCE,
    AE_MAX_HP,
    AE_MAX_MP,
    AE_DODGE_RATE,
    AE_MAGICITEM_FIND_RATE,
};
ArmorProperty::ArmorProperty(unsigned int instanceID, PickableItem::PickableItemType type, CChaosNumber level, bool identified)
    :PickableItemProperty(instanceID, type)
{
    m_PropertyType = PIPT_ARMOR;
    m_bIdentified = identified;
    m_bStackable = false;
    m_bEquipable = true;
    m_bCombinable = false;
    m_bDiscardable = true;
    
    m_nLevel = level;
    m_bHasEquiped = false;
    
    m_nAddedLightDistance       =0;
    m_nAddedSearchDistance      =0;
    m_nAddedMaxHP               =0;
    m_nAddedMaxMP               =0;
    m_nAddedArmorClass          =0;
    m_fAddedDodgeRate           =0;
    m_fAddedMagicItemFindRate   =0;
    
    m_strBeforeIndentifyDesc = UtilityHelper::getLocalString(PICKABLE_ITEM_NAMES[type] + "_BIDESC");
    m_strPropertyTypeName = UtilityHelper::getLocalString(PICKABLE_ITEM_PROPERTY_TYPE_NAMES[m_PropertyType]);

    if(type >= PickableItem::PIT_CLOTH_PRO_SHOES && type <= PickableItem::PIT_CLOTH_PRO_STEELARMOR)
        m_bIdentified = false;
    else
        m_bIdentified = identified;
}

void ArmorProperty::adjustByLevel()
{
    if(m_nLevel <= 15)
    {
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_LIGHT_DISTANCE) != m_AddedEffectList.end())
            m_nAddedLightDistance = 1;
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_SEARCH_DISTANCE) != m_AddedEffectList.end())
            m_nAddedSearchDistance = 1;
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MAX_HP) != m_AddedEffectList.end())
        {
            if (m_nLevel <= 5)
                m_nAddedMaxHP = cocos2d::random(5, 20);
            else if(m_nLevel <= 10)
                m_nAddedMaxHP = cocos2d::random(15, 50);
            else
                m_nAddedMaxHP = cocos2d::random(40, 100);
        }
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MAX_MP) != m_AddedEffectList.end())
        {
            if (m_nLevel <= 5)
                m_nAddedMaxMP = cocos2d::random(5, 20);
            else if(m_nLevel <= 10)
                m_nAddedMaxMP = cocos2d::random(15, 50);
            else
                m_nAddedMaxMP = cocos2d::random(40, 100);
        }
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_DODGE_RATE) != m_AddedEffectList.end())
            m_fAddedDodgeRate = cocos2d::random(0.01f, 0.02f);
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MAGICITEM_FIND_RATE) != m_AddedEffectList.end())
            m_fAddedMagicItemFindRate = cocos2d::random(0.05f, 0.2f);
        
        if (m_nLevel <= 5)
            m_nAddedArmorClass = MIN((int)m_nAddedArmorClass.GetLongValue(), cocos2d::random(-2, -1));
        else if(m_nLevel <= 10)
            m_nAddedArmorClass = MIN((int)m_nAddedArmorClass.GetLongValue(),cocos2d::random(-8, -4));
        else
            m_nAddedArmorClass = MIN((int)m_nAddedArmorClass.GetLongValue(),cocos2d::random(-12, -8));
    }
    else if(m_nLevel <= 30)
    {
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_LIGHT_DISTANCE) != m_AddedEffectList.end())
            m_nAddedLightDistance = cocos2d::random(1, 2);
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_SEARCH_DISTANCE) != m_AddedEffectList.end())
            m_nAddedSearchDistance = 1;
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MAX_HP) != m_AddedEffectList.end())
        {
            if (m_nLevel <= 20)
                m_nAddedMaxHP = cocos2d::random(80, 150);
            else if(m_nLevel <= 25)
                m_nAddedMaxHP = cocos2d::random(120, 200);
            else
                m_nAddedMaxHP = cocos2d::random(180, 300);
        }
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MAX_MP) != m_AddedEffectList.end())
        {
            if (m_nLevel <= 20)
                m_nAddedMaxMP = cocos2d::random(80, 150);
            else if(m_nLevel <= 25)
                m_nAddedMaxMP = cocos2d::random(120, 200);
            else
                m_nAddedMaxMP = cocos2d::random(180, 300);
        }
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_DODGE_RATE) != m_AddedEffectList.end())
            m_fAddedDodgeRate = cocos2d::random(0.01f, 0.03f);
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MAGICITEM_FIND_RATE) != m_AddedEffectList.end())
            m_fAddedMagicItemFindRate = cocos2d::random(0.1f, 0.3f);
        
        if (m_nLevel <= 20)
            m_nAddedArmorClass = MIN((int)m_nAddedArmorClass.GetLongValue(),cocos2d::random(-16, -12));
        else if(m_nLevel <= 25)
            m_nAddedArmorClass = MIN((int)m_nAddedArmorClass.GetLongValue(),cocos2d::random(-20, -16));
        else
            m_nAddedArmorClass = MIN((int)m_nAddedArmorClass.GetLongValue(),cocos2d::random(-24, -20));
    }
    else
    {
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_LIGHT_DISTANCE) != m_AddedEffectList.end())
            m_nAddedLightDistance = cocos2d::random(1, 2);
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_SEARCH_DISTANCE) != m_AddedEffectList.end())
            m_nAddedSearchDistance = 1;
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MAX_HP) != m_AddedEffectList.end())
        {
            if (m_nLevel <= 35)
                m_nAddedMaxHP = cocos2d::random(300, 350);
            else if(m_nLevel <= 40)
                m_nAddedMaxHP = cocos2d::random(350, 400);
            else if(m_nLevel <= 45)
                m_nAddedMaxHP = cocos2d::random(400, 450);
            else if(m_nLevel <= 50)
                m_nAddedMaxHP = cocos2d::random(450, 500);
            else
                m_nAddedMaxHP = cocos2d::random(500, 550);
        }
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MAX_MP) != m_AddedEffectList.end())
        {
            if (m_nLevel <= 35)
                m_nAddedMaxMP = cocos2d::random(300, 350);
            else if(m_nLevel <= 40)
                m_nAddedMaxMP = cocos2d::random(350, 400);
            else if(m_nLevel <= 45)
                m_nAddedMaxMP = cocos2d::random(400, 450);
            else if(m_nLevel <= 50)
                m_nAddedMaxMP = cocos2d::random(450, 500);
            else
                m_nAddedMaxMP = cocos2d::random(500, 550);
        }
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_DODGE_RATE) != m_AddedEffectList.end())
            m_fAddedDodgeRate = cocos2d::random(0.02f, 0.05f);
        
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), AE_MAGICITEM_FIND_RATE) != m_AddedEffectList.end())
            m_fAddedMagicItemFindRate = cocos2d::random(0.15f, 0.45f);
        
        if (m_nLevel <= 35)
            m_nAddedArmorClass = MIN((int)m_nAddedArmorClass.GetLongValue(),cocos2d::random(-30, -24));
        else if(m_nLevel <= 40)
            m_nAddedArmorClass = MIN((int)m_nAddedArmorClass.GetLongValue(),cocos2d::random(-40, -30));
        else if(m_nLevel <= 50)
            m_nAddedArmorClass = MIN((int)m_nAddedArmorClass.GetLongValue(),cocos2d::random(-60, -40));
        else
            m_nAddedArmorClass = MIN((int)m_nAddedArmorClass.GetLongValue(),cocos2d::random(-80, -60));
    }
    
    m_nValueCopper = 250 * (int)(m_AddedEffectList.size())*(int)(m_AddedEffectList.size()) + m_nLevel*50;
    m_nCopperWhenBuy = m_nValueCopper * 2.0f;
}
void ArmorProperty::handleIdentify()
{
    if(m_bIdentified)
        return;
    m_bIdentified = true;
    m_nLevel = m_nLevel + cocos2d::random(-2, 2);
    m_nLevel = MAX(1, m_nLevel.GetLongValue());
    
    CChaosNumber addedEffectCount = 0;
    
    if(m_ItemType >= PickableItem::PIT_CLOTH_PRO_SHOES && m_ItemType <= PickableItem::PIT_CLOTH_PRO_STEELARMOR)
        addedEffectCount = cocos2d::random(5, 6);
    else
    {
        float percent1 = 0.75f;
        float percent2 = 1.0 - percent1;
        AlisaMethod* am = AlisaMethod::create(percent1, percent2, -1.0, NULL);
        if(am)
        {
            int randIndex = am->getRandomIndex();
            if(randIndex == 0)
                addedEffectCount = cocos2d::random(1, 2);
            else
                addedEffectCount = cocos2d::random(3, 4);
        }
    }
    if(addedEffectCount >= 5)
        m_Quality = PIQ_LEGEND;
    else if(addedEffectCount >= 3)
        m_Quality = PIQ_EPIC;
    else if(addedEffectCount >= 1)
        m_Quality = PIQ_RARE;
    else
        m_Quality = PIQ_GENERAL;
    while (m_AddedEffectList.size() < addedEffectCount.GetLongValue()) {
        int index = cocos2d::random(0, int(sArmorAddedEffects.size()-1));
        if(std::find(m_AddedEffectList.begin(), m_AddedEffectList.end(), sArmorAddedEffects[index]) != m_AddedEffectList.end())
            continue;
        else
            m_AddedEffectList.push_back(sArmorAddedEffects[index]);
    }
    adjustByLevel();
}
CChaosNumber ArmorProperty::getAddedDefense()
{
    return -m_nAddedArmorClass.GetLongValue();
}
ArmorProperty* ArmorProperty::clone() const
{
    ArmorProperty* prop = new (std::nothrow) ArmorProperty(PlayerProperty::m_snItemInstanceIDCounter++,this->m_ItemType,this->m_nLevel,this->m_bIdentified);
    
    prop->m_PropertyType = this->m_PropertyType;
    prop->m_nValueCopper = this->m_nValueCopper.GetLongValue();
    prop->m_nCopperWhenBuy = this->m_nCopperWhenBuy.GetLongValue();
    prop->m_Quality = this->m_Quality;
    prop->m_AddedEffectList.assign(this->m_AddedEffectList.begin(), this->m_AddedEffectList.end());
    prop->m_nAddedLightDistance = this->m_nAddedLightDistance.GetLongValue();
    prop->m_nAddedSearchDistance = this->m_nAddedSearchDistance.GetLongValue();
    prop->m_nAddedMaxHP = this->m_nAddedMaxHP.GetLongValue();
    prop->m_nAddedMaxMP = this->m_nAddedMaxMP.GetLongValue();
    prop->m_nAddedArmorClass =this->m_nAddedArmorClass.GetLongValue();
    prop->m_fAddedDodgeRate = this->m_fAddedDodgeRate.GetFloatValue();
    prop->m_fAddedMagicItemFindRate = this->m_fAddedMagicItemFindRate.GetFloatValue();
    
    return prop;
}

bool ArmorProperty::load(const cocos2d::ValueMap& data)
{
    m_PropertyType = (PickableItemPropertyType)data.at("PropertyType").asInt();
    m_nInstanceID = data.at("InstanceID").asInt();
    m_ItemType = (PickableItem::PickableItemType)data.at("ItemType").asInt();
    m_nLevel = (PickableItem::PickableItemType)data.at("Level").asInt();
    m_nValueCopper = data.at("ValueCopper").asInt();
    m_nCopperWhenBuy = data.at("CopperWhenBuy").asInt();
    
    m_bIdentified = data.at("Identified").asBool();
    
    if(m_bIdentified)
    {
        m_Quality = (PICKABLEITEM_QUALITY)data.at("Quality").asInt();
        
        ValueVector addedEffectList = data.at("AddedEffectList").asValueVector();
        for (Value value : addedEffectList) {
            m_AddedEffectList.push_back((ADDED_EFFECT)value.asInt());
        }
        
        m_nAddedLightDistance = data.at("AddedLightDistance").asInt();
        m_nAddedSearchDistance = data.at("AddedSearchDistance").asInt();
        m_nAddedMaxHP = data.at("AddedMaxHP").asInt();
        m_nAddedMaxMP = data.at("AddedMaxMP").asInt();
        
        m_nAddedArmorClass = data.at("AddedArmorClass").asInt();
        
        m_fAddedDodgeRate = data.at("AddedDodgeRate").asFloat();
        m_fAddedMagicItemFindRate = data.at("AddedMagicItemFindRate").asFloat();
    }
    else
    {
        if(data.find("AddedArmorClass") != data.end())
            m_nAddedArmorClass = data.at("AddedArmorClass").asInt();
    }

    return true;
}
bool ArmorProperty::save(cocos2d::ValueMap& data)
{
    data["PropertyType"] = (int)m_PropertyType;
    data["InstanceID"] = (int)m_nInstanceID;
    data["ItemType"] = (int)m_ItemType;
    data["Level"] = (int)m_nLevel.GetLongValue();
    data["ValueCopper"] = (int)m_nValueCopper.GetLongValue();
    data["CopperWhenBuy"] = (int)m_nCopperWhenBuy.GetLongValue();
    
    data["Identified"] = m_bIdentified;
    
    if(m_bIdentified)
    {
        data["Quality"] = (int)m_Quality;
        
        ValueVector addedEffectList;
        for (ADDED_EFFECT effectType : m_AddedEffectList) {
            addedEffectList.push_back(Value((int)effectType));
        }
        data["AddedEffectList"] = addedEffectList;
        
        data["AddedLightDistance"] = (int)m_nAddedLightDistance.GetLongValue();
        data["AddedSearchDistance"] = (int)m_nAddedSearchDistance.GetLongValue();
        data["AddedMaxHP"] = (int)m_nAddedMaxHP.GetLongValue();
        data["AddedMaxMP"] = (int)m_nAddedMaxMP.GetLongValue();
        
        data["AddedArmorClass"] = (int)m_nAddedArmorClass.GetLongValue();

        data["AddedDodgeRate"] = m_fAddedDodgeRate.GetFloatValue();
        data["AddedMagicItemFindRate"] = m_fAddedMagicItemFindRate.GetFloatValue();
    }
    else
        data["AddedArmorClass"] = (int)m_nAddedArmorClass.GetLongValue();
    return true;
}