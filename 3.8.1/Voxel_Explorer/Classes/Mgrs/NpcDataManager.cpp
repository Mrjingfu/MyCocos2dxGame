//
//  NpcDataManager.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/11/26.
//
//

#include "NpcDataManager.hpp"
#include "PickableItemProperty.hpp"
#include "PlayerProperty.hpp"
#include "WeaponProperty.hpp"
#include "SecondWeaponProperty.hpp"
#include "ArmorProperty.hpp"
#include "MagicOrnamentProperty.hpp"
#include "ScrollProperty.hpp"
#include "PotionsProperty.hpp"
#include "KeyProperty.hpp"
#include "ScrollProperty.hpp"
#include "PotionsProperty.hpp"
#include "EventConst.h"
USING_NS_CC;
NpcDataManager* g_pNpcDataManagerInstance = nullptr;
NpcDataManager* NpcDataManager::getInstance()
{
    if( g_pNpcDataManagerInstance == nullptr )
        g_pNpcDataManagerInstance = new NpcDataManager();
    
    return g_pNpcDataManagerInstance;
}
NpcDataManager::NpcDataManager()
{
    m_bDirty = false;
}
NpcDataManager::~NpcDataManager()
{
}
bool NpcDataManager::initNpcData()
{
    m_EquipmentShop.clear();
    m_MagicShop.clear();
    m_AlchemistRoom.clear();
    m_TheifRoom.clear();
    
    if(!initEquipmentShop())
    {
        CCLOG("initEquipmentShop failed!");
        return false;
    }
    if(!initMagicShop())
    {
        CCLOG("initMagicShop failed!");
        return false;
    }
    if(!initAlchemistShop())
    {
        CCLOG("initAlchemistShop failed!");
        return false;
    }
    if(!initTheifRoom())
    {
        CCLOG("initTheifRoom failed!");
        return false;
    }
    if(!initOldManRoom())
    {
        CCLOG("initOldManRoom failed!");
        return false;
    }
    m_bDirty = true;
    return true;
}
void NpcDataManager::update(float delta)
{
    if(m_bDirty)
    {
        m_bDirty = false;
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_NPC_DATA_DIRTY);
    }
}
bool NpcDataManager::removeItemFromEquipmentShopList(CChaosNumber id)
{
    std::vector<PickableItemProperty*>::iterator iter;
    for (iter = m_EquipmentShop.begin(); iter != m_EquipmentShop.end(); iter++) {
        if((*iter) != nullptr && (*iter)->getInstanceID() == id.GetLongValue())
        {
            PickableItemProperty* property = static_cast<PickableItemProperty*>(*iter);
            CC_SAFE_RELEASE(property);
            m_EquipmentShop.erase(iter);
            m_bDirty = true;
            return true;
        }
    }
    return false;
}
bool NpcDataManager::removeItemFromMagicShopList(CChaosNumber id)
{
    std::vector<PickableItemProperty*>::iterator iter;
    for (iter = m_MagicShop.begin(); iter != m_MagicShop.end(); iter++) {
        if((*iter) != nullptr && (*iter)->getInstanceID() == id.GetLongValue())
        {
            PickableItemProperty* property = static_cast<PickableItemProperty*>(*iter);
            CC_SAFE_RELEASE(property);
            m_MagicShop.erase(iter);
            m_bDirty = true;
            return true;
        }
    }
    return false;
}
bool NpcDataManager::removeItemFromAlchemistRoomList(CChaosNumber id)
{
    std::vector<PickableItemProperty*>::iterator iter;
    for (iter = m_AlchemistRoom.begin(); iter != m_AlchemistRoom.end(); iter++) {
        if((*iter) != nullptr && (*iter)->getInstanceID() == id.GetLongValue())
        {
            PickableItemProperty* property = static_cast<PickableItemProperty*>(*iter);
            CC_SAFE_RELEASE(property);
            m_AlchemistRoom.erase(iter);
            m_bDirty = true;
            return true;
        }
    }
    return false;

}
bool NpcDataManager::removeItemFromTheifRoomList(CChaosNumber id)
{
    std::vector<PickableItemProperty*>::iterator iter;
    for (iter = m_TheifRoom.begin(); iter != m_TheifRoom.end(); iter++) {
        if((*iter) != nullptr && (*iter)->getInstanceID() == id.GetLongValue())
        {
            PickableItemProperty* property = static_cast<PickableItemProperty*>(*iter);
            CC_SAFE_RELEASE(property);
            m_TheifRoom.erase(iter);
            m_bDirty = true;
            return true;
        }
    }
    return false;
}
std::string NpcDataManager::getOldManRoomInfoByPart(int part, bool& atEnd)
{
    std::string retStr;
    atEnd = true;
    int randIndex = cocos2d::random(0, (int)(m_OldManRoom.size()-1));
    ValueVector infos = m_OldManRoom[randIndex].asValueVector();
    if(!infos.empty() && part < infos.size())
    {
        retStr = infos[part].asString();
        if(part == (int)(infos.size() - 1))
            atEnd = true;
        else
            atEnd = false;
    }
    return retStr;
}
bool NpcDataManager::initEquipmentShop()
{
    int level = PlayerProperty::getInstance()->getLevel().GetLongValue();
    PickableItem::PickableItemType type = PickableItem::PIT_UNKNOWN;
    int count = cocos2d::random(8, 12);
    int itemLevel = 1;
    
    PickableItemProperty* itemProperty = nullptr;
    for (int i = 0; i<count; ++i) {
        if(level <= 5)
        {
            type = PickableItem::generate1_5EquipmentShopItemType();
            itemLevel = cocos2d::random(1, 7);
        }
        else if(level <= 10)
        {
            type = PickableItem::generate6_10EquipmentShopItemType();
            itemLevel = cocos2d::random(8, 12);
        }
        else if(level <=15)
        {
            type = PickableItem::generate11_15EquipmentShopItemType();
            itemLevel = cocos2d::random(13, 17);
        }
        else if(level <= 20)
        {
            type = PickableItem::generate16_20EquipmentShopItemType();
            itemLevel = cocos2d::random(18, 22);
        }
        else if(level <= 25)
        {
            type = PickableItem::generate21_25EquipmentShopItemType();
            itemLevel = cocos2d::random(23, 27);
        }
        else if(level <= 30)
        {
            type = PickableItem::generate26_30EquipmentShopItemType();
            itemLevel = cocos2d::random(28, 32);
        }
        else
        {
            type = PickableItem::generate31_35EquipmentShopItemType();
            itemLevel = cocos2d::random(33, 40);
        }
        
        if(type >= PickableItem::PIT_DAGGER_DAGGER && type <= PickableItem::PIT_MACE_SLEDGEHAMMER)
            itemProperty = new (std::nothrow) WeaponProperty(PlayerProperty::m_snItemInstanceIDCounter++,type, itemLevel, false);
        else if (type >= PickableItem::PIT_BOW_SHORTBOW && type <=PickableItem::PIT_SHIELD_TOWERSHIELD)
            itemProperty = new (std::nothrow) SecondWeaponProperty(PlayerProperty::m_snItemInstanceIDCounter++,type, itemLevel, false);
        if(itemProperty)
        {
            itemProperty->adjustByLevel();
            itemProperty->handleIdentify();
            m_EquipmentShop.push_back(itemProperty);
        }
    }
    return true;
}
bool NpcDataManager::initMagicShop()
{
    int level = PlayerProperty::getInstance()->getLevel().GetLongValue();
    PickableItem::PickableItemType type = PickableItem::PIT_UNKNOWN;
    int count = cocos2d::random(8, 12);
    int itemLevel = 1;
    PickableItemProperty* itemProperty = nullptr;
    for (int i = 0; i<count; ++i) {
        if(level <= 5)
        {
            type = PickableItem::generate1_5MagicShopItemType();
            itemLevel = cocos2d::random(1, 7);
        }
        else if(level <= 10)
        {
            type = PickableItem::generate6_10MagicShopItemType();
            itemLevel = cocos2d::random(8, 12);
        }
        else if(level <=15)
        {
            type = PickableItem::generate11_15MagicShopItemType();
            itemLevel = cocos2d::random(13, 17);
        }
        else if(level <= 20)
        {
            type = PickableItem::generate16_20MagicShopItemType();
            itemLevel = cocos2d::random(18, 22);
        }
        else if(level <= 25)
        {
            type = PickableItem::generate21_25MagicShopItemType();
            itemLevel = cocos2d::random(23, 27);
        }
        else if(level <= 30)
        {
            type = PickableItem::generate26_30MagicShopItemType();
            itemLevel = cocos2d::random(28, 32);
        }
        else
        {
            type = PickableItem::generate31_35MagicShopItemType();
            itemLevel = cocos2d::random(33, 40);
        }
        if(type >= PickableItem::PIT_CLOTH_SHOES && type <= PickableItem::PIT_CLOTH_STEELARMOR)
            itemProperty = new (std::nothrow) ArmorProperty(PlayerProperty::m_snItemInstanceIDCounter++,type, level, false);
        else if(type >= PickableItem::PIT_ORNAMENT_RING && type <= PickableItem::PIT_ORNAMENT_JEWELS)
            itemProperty = new (std::nothrow) MagicOrnamentProperty(PlayerProperty::m_snItemInstanceIDCounter++,type, level, false);
        if(itemProperty)
        {
            itemProperty->adjustByLevel();
            itemProperty->handleIdentify();
            m_MagicShop.push_back(itemProperty);
        }
    }
    return true;
}
bool NpcDataManager::initAlchemistShop()
{
    int level = PlayerProperty::getInstance()->getLevel().GetLongValue();
    PickableItem::PickableItemType type = PickableItem::PIT_UNKNOWN;
    PickableItemProperty* itemProperty = nullptr;
    std::vector<PickableItem::PickableItemType> types;
    if(level <= 15)
    {
        types = { PickableItem::PIT_SCROLL_INDENTIFY, PickableItem::PIT_SCROLL_TELEPORT, PickableItem::PIT_SCROLL_DESTINY, PickableItem::PIT_POTION_MINORHEALTH, PickableItem::PIT_POTION_MINORMANA, PickableItem::PIT_POTION_DETOXIFICATION, PickableItem::PIT_POTION_HEALING };
        
    }
    else if(level <= 30)
    {
        types = { PickableItem::PIT_SCROLL_INDENTIFY, PickableItem::PIT_SCROLL_TELEPORT, PickableItem::PIT_SCROLL_DESTINY, PickableItem::PIT_POTION_LESSERHEALTH, PickableItem::PIT_POTION_LESSERMANA, PickableItem::PIT_POTION_DETOXIFICATION, PickableItem::PIT_POTION_HEALING, PickableItem::PIT_POTION_SPECIFIC };
    }
    else
    {
        types = { PickableItem::PIT_SCROLL_INDENTIFY, PickableItem::PIT_SCROLL_TELEPORT, PickableItem::PIT_SCROLL_DESTINY, PickableItem::PIT_POTION_HEALTH, PickableItem::PIT_POTION_MANA, PickableItem::PIT_POTION_DETOXIFICATION, PickableItem::PIT_POTION_HEALING, PickableItem::PIT_POTION_SPECIFIC, PickableItem::PIT_POTION_UNIVERSAL };
    }
    for (int i = 0; i< types.size()-1; ++i) {
        type = types[i];
        if(type >= PickableItem::PIT_KEY_COPPER && type <= PickableItem::PIT_KEY_GOLD)
            itemProperty = new (std::nothrow) KeyProperty(PlayerProperty::m_snItemInstanceIDCounter++,type);
        else if(type >= PickableItem::PIT_SCROLL_INDENTIFY && type <= PickableItem::PIT_SCROLL_DESTINY)
            itemProperty = new (std::nothrow) ScrollProperty(PlayerProperty::m_snItemInstanceIDCounter++,type);
        else if(type >= PickableItem::PIT_POTION_MINORHEALTH && type <= PickableItem::PIT_POTION_UNIVERSAL)
            itemProperty = new (std::nothrow) PotionsProperty(PlayerProperty::m_snItemInstanceIDCounter++,type);
        if(itemProperty)
        {
            itemProperty->adjustByLevel();
            m_AlchemistRoom.push_back(itemProperty);
        }
    }
    return true;
}
bool NpcDataManager::initTheifRoom()
{
    int level = PlayerProperty::getInstance()->getLevel().GetLongValue();
    PickableItem::PickableItemType type = PickableItem::PIT_UNKNOWN;
    int count = cocos2d::random(8, 12);
    int itemLevel = 1;
    
    PickableItemProperty* itemProperty = nullptr;
    for (int i = 0; i<count; ++i) {
        if(level <= 15)
        {
            type = PickableItem::generatePickItemByUseableLevel(level, UseableItem::UIT_CHEST_COPPER);
            itemLevel = cocos2d::random(1, 7);
        }
        else if(level <= 30)
        {
            type = PickableItem::generatePickItemByUseableLevel(level, UseableItem::UIT_CHEST_SILVER);
            itemLevel = cocos2d::random(8, 12);
        }
        else
        {
            type = PickableItem::generatePickItemByUseableLevel(level, UseableItem::UIT_CHEST_GOLD);
            itemLevel = cocos2d::random(13, 17);
        }
        if (type >= PickableItem::PIT_DAGGER_DAGGER && type <= PickableItem::PIT_MACE_PRO_SLEDGEHAMMER)
            itemProperty = new (std::nothrow) WeaponProperty(PlayerProperty::m_snItemInstanceIDCounter++,type, level, true);
        else if (type >= PickableItem::PIT_BOW_SHORTBOW && type <=PickableItem::PIT_SHIELD_PRO_TOWERSHIELD)
            itemProperty = new (std::nothrow) SecondWeaponProperty(PlayerProperty::m_snItemInstanceIDCounter++,type, level, true);
        else if(type >= PickableItem::PIT_CLOTH_SHOES && type <= PickableItem::PIT_CLOTH_PRO_STEELARMOR)
            itemProperty = new (std::nothrow) ArmorProperty(PlayerProperty::m_snItemInstanceIDCounter++,type, level, true);
        else if(type >= PickableItem::PIT_ORNAMENT_RING && type <= PickableItem::PIT_ORNAMENT_PRO_JEWELS)
            itemProperty = new (std::nothrow) MagicOrnamentProperty(PlayerProperty::m_snItemInstanceIDCounter++,type, level, true);
        if(itemProperty)
        {
            itemProperty->adjustByLevel();
            int mul = (int)(itemLevel / 5) + 1;
            itemProperty->setCopperWhenBuy(mul*20000);
            m_TheifRoom.push_back(itemProperty);
        }
    }
    return true;
}
bool NpcDataManager::initOldManRoom()
{
    LanguageType lt= Application::getInstance()->getCurrentLanguage();
    switch (lt) {
        case LanguageType::CHINESE:
            m_OldManRoom = FileUtils::getInstance()->getValueVectorFromFile("npc_info_chinese.plist");
            break;
            
        default:
            m_OldManRoom = FileUtils::getInstance()->getValueVectorFromFile("npc_info_english.plish");
            break;
    }
    if(m_OldManRoom.empty())
        return false;
    return true;
}
PickableItemProperty* NpcDataManager::getItemFromEquipMentShop(CChaosNumber id) const
{
    return getItemFormVector(m_EquipmentShop,id);
}
PickableItemProperty* NpcDataManager::getItemFromMagicShop(CChaosNumber id) const
{
    return getItemFormVector(m_MagicShop,id);
}
PickableItemProperty* NpcDataManager::getItemFromAlchemistRoom(CChaosNumber id) const
{
    return getItemFormVector(m_AlchemistRoom,id);
}
PickableItemProperty* NpcDataManager::getItemFromTheifRoom(CChaosNumber id) const
{
    return getItemFormVector(m_TheifRoom,id);
}
PickableItemProperty* NpcDataManager::getItemFormVector(const std::vector<PickableItemProperty*>& datas,CChaosNumber id) const
{
    std::vector<PickableItemProperty*>::const_iterator iter;
    for (iter = datas.begin(); iter != datas.end(); iter++) {
        if((*iter) != nullptr && (*iter)->getInstanceID() == id.GetLongValue())
            return (*iter);
    }
    return nullptr;
}