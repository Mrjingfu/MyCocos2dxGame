//
//  PlayerProperty.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/19.
//
//

#include "PlayerProperty.hpp"
#include "GameFormula.hpp"
#include "EventConst.h"
#include "KeyProperty.hpp"
#include "WeaponProperty.hpp"
#include "SecondWeaponProperty.hpp"
#include "ArmorProperty.hpp"
#include "MagicOrnamentProperty.hpp"
#include "ScrollProperty.hpp"
#include "PotionsProperty.hpp"
#include "MaterialProperty.hpp"
#include "QuestItemProperty.hpp"
#include "SundriesProperty.hpp"
#include "VoxelExplorer.h"
#include "StatisticsManager.hpp"
#include "SimpleAudioEngine.h"
#include "LevelResourceManager.h"
#include "SdkBoxManager.hpp"
#include "GameCenterController.h"
USING_NS_CC;
using namespace CocosDenshion;

unsigned int PlayerProperty::m_snItemInstanceIDCounter = 0;
PlayerProperty* g_pPlayerPropertyInstance = nullptr;
PlayerProperty* PlayerProperty::getInstance()
{
    if( g_pPlayerPropertyInstance == nullptr )
        g_pPlayerPropertyInstance = new PlayerProperty();
    
    return g_pPlayerPropertyInstance;
}
PlayerProperty::PlayerProperty()
{
    reset();
    m_bDirty = false;
    m_bNeedRefreshAfterCreatePlayer = false;
}
PlayerProperty::~PlayerProperty()
{
    reset();
}
bool PlayerProperty::initNewPlayer()   ///新角色初始化
{
    bool ret = false;
    int itemIDCounter = m_snItemInstanceIDCounter;
    WeaponProperty* weaponProperty = new (std::nothrow) WeaponProperty(m_snItemInstanceIDCounter++,PickableItem::PIT_DAGGER_PRO_BLUELIGHTDAGGER, 25, true);
    if(!weaponProperty)
        return ret;
    if(weaponProperty->isIdentified())
        weaponProperty->adjustByLevel();
    m_Bag.push_back(weaponProperty);

    addMoney(90000, false);
    ret = equipWeapon(itemIDCounter, false);
    ret = addItemToBag(PickableItem::PIT_POTION_MINORHEALTH, 1, false);
    ret = addItemToBag(PickableItem::PIT_POTION_MINORHEALTH, 1, false);
    ret = addItemToBag(PickableItem::PIT_POTION_MINORHEALTH, 1, false);
    ret = addItemToBag(PickableItem::PIT_POTION_MINORMANA, 1, false);
    ret = addItemToBag(PickableItem::PIT_POTION_MINORMANA, 1, false);
    ret = addItemToBag(PickableItem::PIT_POTION_MINORMANA, 1, false);
    ret = addItemToBag(PickableItem::PIT_SCROLL_INDENTIFY, 1, false);
    ret = addItemToBag(PickableItem::PIT_SCROLL_INDENTIFY, 1, false);
    ret = addItemToBag(PickableItem::PIT_SCROLL_INDENTIFY, 1, false);
    ret = addItemToBag(PickableItem::PIT_KEY_COPPER, 1, false);
    ret = addItemToBag(PickableItem::PIT_KEY_COPPER, 1, false);
    ret = addItemToBag(PickableItem::PIT_KEY_COPPER, 1, false);
    ret = addItemToBag(PickableItem::PIT_POTION_DETOXIFICATION, 1, false);
    ret = addItemToBag(PickableItem::PIT_POTION_SPECIFIC, 1, false);
    ret = addItemToBag(PickableItem::PIT_POTION_HEALING, 1, false);
    
    return ret;
}
void PlayerProperty::update(float delta)
{
    if(m_bDirty)
    {
        m_bDirty = false;
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_PROPERTY_DIRTY);
    }
}
void PlayerProperty::addPlayerBuffer(PlayerBuffer buff)
{
    if(buff == PB_WEAK)
    {
        m_nMaxHP = m_nMaxHP - m_nLevel*8 - 30;
        m_nMaxMP = m_nMaxMP - m_nLevel*8 - 30;
        m_nCurrentHP = MIN(m_nCurrentHP, m_nMaxHP);
        m_nCurrentMP = MIN(m_nCurrentMP, m_nMaxMP);
        
        m_nBaseArmorClass = m_nBaseArmorClass - m_nLevel.GetLongValue();
        
    }
    else if(buff == PB_STRONGER)
    {
        m_nMaxHP = m_nMaxHP + m_nLevel*8 + 30;
        m_nMaxMP = m_nMaxMP + m_nLevel*8 + 30;
        m_nCurrentHP = m_nCurrentHP + m_nLevel*8 + 30;
        m_nCurrentMP = m_nCurrentMP + m_nLevel*8 + 30;
        m_nCurrentHP = MIN(m_nCurrentHP, m_nMaxHP);
        m_nCurrentMP = MIN(m_nCurrentMP, m_nMaxMP);
        
        m_nBaseArmorClass = m_nBaseArmorClass + m_nLevel.GetLongValue();
    }
    else if(buff == PB_BLOCKRATEUP)
    {
        m_fBlockRate = m_fBlockRate + 0.1f;
        m_fBlockRate = MIN(m_fBlockRate.GetFloatValue(), 0.3f);
    }
    m_BufferFlag = m_BufferFlag | buff;
    m_bDirty = true;
}
void PlayerProperty::removePlayerBuffer(PlayerBuffer buff)
{
    if(buff == PB_WEAK)
    {
        m_nMaxHP = m_nMaxHP + m_nLevel*8 + 30;
        m_nMaxMP = m_nMaxMP + m_nLevel*8 + 30;
        m_nCurrentHP = MIN(m_nCurrentHP, m_nMaxHP);
        m_nCurrentMP = MIN(m_nCurrentMP, m_nMaxMP);
        
        m_nBaseArmorClass = m_nBaseArmorClass + m_nLevel.GetLongValue();
    }
    else if(buff == PB_STRONGER)
    {
        m_nMaxHP = m_nMaxHP - m_nLevel*8 - 30;
        m_nMaxMP = m_nMaxMP - m_nLevel*8 - 30;
        m_nCurrentHP = MIN(m_nCurrentHP, m_nMaxHP);
        m_nCurrentMP = MIN(m_nCurrentMP, m_nMaxMP);
        
        m_nBaseArmorClass = m_nBaseArmorClass - m_nLevel.GetLongValue();
    }
    else if(buff == PB_BLOCKRATEUP)
    {
        m_fBlockRate = m_fBlockRate - 0.1f;
        m_fBlockRate = MAX(0, m_fBlockRate.GetFloatValue());
    }
    m_BufferFlag = m_BufferFlag &~ buff;
    m_bDirty = true;
}
void PlayerProperty::resetPlayerBuffer()
{
    m_BufferFlag = PB_NONE;
    m_bDirty = true;
}
void PlayerProperty::healedbyNurse()
{
    m_nCurrentHP = m_nMaxHP;
    m_nCurrentMP = m_nMaxMP;
    m_bDirty = true;
}
CChaosNumber PlayerProperty::getMinAttack()
{
    return m_nAttackDiceNum + m_nAddedMinAttack.GetLongValue();
}
CChaosNumber PlayerProperty::getMaxAttack()
{
    return m_nAttackDiceNum*m_nAttackDiceFaceNum.GetLongValue() + m_nAddedMaxAttack.GetLongValue();
}
CChaosNumber PlayerProperty::getDefense()
{
    CCLOG("m_nArmorClass = %d  m_nBaseArmorClass = %d", (int)m_nArmorClass.GetLongValue(), (int)m_nBaseArmorClass.GetLongValue());
    return -m_nArmorClass.GetLongValue() + m_nBaseArmorClass.GetLongValue();
}
void PlayerProperty::addMoney( CChaosNumber copper, bool sound)
{
    StatisticsManager::getInstance()->addCopperTotalNum(copper);
    m_nValueCopper = m_nValueCopper + copper.GetLongValue();
    if(sound)
    {
        std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("COIN_DROP");
        SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_PROPERTY_DIRTY);
    GameCenterController::getInstance()->reportMoney((int)m_nValueCopper.GetLongValue());
    m_bDirty = true;
}
bool PlayerProperty::costMoney( CChaosNumber costcopper )
{
   
    if(m_nValueCopper < costcopper)
    {
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_MONEY_NOT_ENOUGH);
        return false;
    }
    m_nValueCopper = m_nValueCopper - costcopper.GetLongValue();
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_PROPERTY_DIRTY);
    
    GameCenterController::getInstance()->reportMoney((int)m_nValueCopper.GetLongValue());
    
    m_bDirty = true;
    return true;
}
void PlayerProperty::setExp(CChaosNumber exp)
{
    int needExp = GameFormula::getNextLevelExp(m_nLevel);
    if(exp >= needExp)
    {
        m_nExp = exp - needExp;
        levelUp();
    }
    else
        m_nExp = exp;
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_PROPERTY_DIRTY);
    m_bDirty = true;
}
void PlayerProperty::setCurrentHP(CChaosNumber hp)
{
    if(hp >= m_nMaxHP)
        m_nCurrentHP = m_nMaxHP;
    else if(hp <= 0)
    {
        m_nCurrentHP = 0;
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_DEATH);
    }
    else
        m_nCurrentHP = hp;
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_PROPERTY_DIRTY);
    m_bDirty = true;
}
void PlayerProperty::setCurrentMP(CChaosNumber mp)
{
    if(mp >= m_nMaxMP)
        m_nCurrentMP = m_nMaxMP;
    else if(mp <= 0)
    {
        m_nCurrentMP = 0;
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_NO_MANA);
    }
    else
        m_nCurrentMP = mp;
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_PROPERTY_DIRTY);
    m_bDirty = true;
}
bool PlayerProperty::equipWeapon(CChaosNumber id, bool sound)
{

    WeaponProperty* weaponProperty = static_cast<WeaponProperty*>(getItemFromBag(id));
    if(weaponProperty)
    {
        ///检查是否可装备
        if(weaponProperty->hasEquiped() || weaponProperty->getLevel() > m_nLevel)
            return false;
        ///卸载旧武器
        WeaponProperty* oldWeaponProperty = static_cast<WeaponProperty*>(getItemFromBag(m_nEquipedWeaponID));
        if(oldWeaponProperty && id.GetLongValue() != m_nEquipedWeaponID.GetLongValue() )
        {
            ///检测旧装备是否可卸载
            if(!oldWeaponProperty->hasEquiped() || oldWeaponProperty->isCursed())
                return false;
            m_nLightDistance = m_nLightDistance - oldWeaponProperty->getAddedLightDistance().GetLongValue();
            m_nLightDistance = MAX(m_nLightDistance.GetLongValue(), 6);
            m_nSearchDistance = m_nSearchDistance - oldWeaponProperty->getAddedSearchDistance().GetLongValue();
            m_nSearchDistance = MAX(m_nSearchDistance.GetLongValue(), 1);
            m_nMaxHP = m_nMaxHP - oldWeaponProperty->getAddedMaxHp().GetLongValue();
            m_nMaxHP = MAX(m_nMaxHP.GetLongValue(), 30);
            m_nMaxMP = m_nMaxMP - oldWeaponProperty->getAddedMaxMp().GetLongValue();
            m_nMaxMP = MAX(m_nMaxMP.GetLongValue(), 30);
            m_nCurrentHP = MIN(m_nCurrentHP, m_nMaxHP);
            m_nCurrentMP = MIN(m_nCurrentMP, m_nMaxMP);
            m_nAddedMinAttack = m_nAddedMinAttack - oldWeaponProperty->getAddedMinAttack().GetLongValue();
            m_nAddedMinAttack = MAX(0, m_nAddedMinAttack.GetLongValue());
            m_nAddedMaxAttack = m_nAddedMaxAttack - oldWeaponProperty->getAddedMaxAttack().GetLongValue();
            m_nAddedMaxAttack = MAX(0, m_nAddedMaxAttack.GetLongValue());
            m_nAttackDiceNum = 0;
            m_nAttackDiceFaceNum = 0;
            m_fCriticalStrikeRate = m_fCriticalStrikeRate - oldWeaponProperty->getAddedCriticalStrikeRate().GetFloatValue();
            m_fCriticalStrikeRate = MAX(0, m_fCriticalStrikeRate.GetFloatValue());
            m_fMagicItemFindRate = m_fMagicItemFindRate - m_fBasicMagicItemFindRate*oldWeaponProperty->getAddedMagicItemFindRate().GetFloatValue();
            m_fMagicItemFindRate = MAX(0, m_fBasicMagicItemFindRate.GetFloatValue());
            oldWeaponProperty->setEquiped(false);
            ///处理灯光
            Color3B color = Color3B::WHITE;
            VoxelExplorer::getInstance()->setPlayerLightColor(color);
        }
        m_nEquipedWeaponID = id;
        
        ///装备新武器
        m_nLightDistance = m_nLightDistance + weaponProperty->getAddedLightDistance().GetLongValue();
        m_nSearchDistance = m_nSearchDistance + weaponProperty->getAddedSearchDistance().GetLongValue();
        m_nSearchDistance = MIN(m_nSearchDistance.GetLongValue(), 5);
        m_nMaxHP = m_nMaxHP + weaponProperty->getAddedMaxHp().GetLongValue();
        m_nMaxMP = m_nMaxMP + weaponProperty->getAddedMaxMp().GetLongValue();
        m_nCurrentHP = MIN(m_nCurrentHP, m_nMaxHP);
        m_nCurrentMP = MIN(m_nCurrentMP, m_nMaxMP);
        m_nAddedMinAttack = m_nAddedMinAttack + weaponProperty->getAddedMinAttack().GetLongValue();
        m_nAddedMaxAttack = m_nAddedMaxAttack + weaponProperty->getAddedMaxAttack().GetLongValue();
        m_nAttackDiceNum = weaponProperty->getAttackDiceNum().GetLongValue();
        m_nAttackDiceFaceNum = weaponProperty->getAttackDiceFaceNum().GetLongValue();
        m_fCriticalStrikeRate = m_fCriticalStrikeRate + weaponProperty->getAddedCriticalStrikeRate().GetFloatValue();
        m_fMagicItemFindRate = m_fMagicItemFindRate + m_fBasicMagicItemFindRate*weaponProperty->getAddedMagicItemFindRate().GetFloatValue();
        m_fMagicItemFindRate = MIN(m_fMagicItemFindRate, m_fMaxMagicItemFindRate);
        weaponProperty->setEquiped(true);
        ///处理灯光
        if(weaponProperty->getPickableItemType() == PickableItem::PIT_DAGGER_PRO_DAGGER)
        {
            ///烛光颜色
            Color3B color = Color3B(252, 225, 90);
            VoxelExplorer::getInstance()->setPlayerLightColor(color);
        }
        else if(weaponProperty->getPickableItemType() == PickableItem::PIT_DAGGER_PRO_RUBYDAGGER
                || weaponProperty->getPickableItemType() == PickableItem::PIT_SWORD_PRO_SWORD || weaponProperty->getPickableItemType() == PickableItem::PIT_SWORD_PRO_HUGESWORD || weaponProperty->getPickableItemType() == PickableItem::PIT_MACE_PRO_MACE)
        {
            ///火焰颜色
            Color3B color = Color3B(252, 152, 126);
            VoxelExplorer::getInstance()->setPlayerLightColor(color);
        }
        else if(weaponProperty->getPickableItemType() == PickableItem::PIT_MACE_PRO_BONEHAMMER || weaponProperty->getPickableItemType() == PickableItem::PIT_SWORD_PRO_CRYSTALSWORD || weaponProperty->getPickableItemType() == PickableItem::PIT_DAGGER_PRO_BLUELIGHTDAGGER)
        {
            ///淡蓝色
            Color3B color = Color3B(126, 235, 251);
            VoxelExplorer::getInstance()->setPlayerLightColor(color);
        }
        else if(weaponProperty->getPickableItemType() == PickableItem::PIT_MACE_PRO_HAMMER || weaponProperty->getPickableItemType() == PickableItem::PIT_AXE_PRO_TOMAHAWK || weaponProperty->getPickableItemType() == PickableItem::PIT_DAGGER_PRO_KNIFE)
        {
            ///金色颜色
            Color3B color = Color3B(251, 250, 126);
            VoxelExplorer::getInstance()->setPlayerLightColor(color);
        }
        StatisticsManager::getInstance()->addRoleAttr();
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_PROPERTY_DIRTY);
        m_bDirty = true;
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_EQUIPED_WEAPON, &m_nEquipedWeaponID);
        if(sound)
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("EQUIP_WEAPON");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
        return true;
    }
    return false;
}
bool PlayerProperty::equipSecondWeapon(CChaosNumber id, bool sound)
{

    SecondWeaponProperty* secondWeaponProperty = static_cast<SecondWeaponProperty*>(getItemFromBag(id));
    if(secondWeaponProperty)
    {
        ///检查是否可装备
        if(secondWeaponProperty->hasEquiped() || secondWeaponProperty->getLevel() > m_nLevel)
            return false;
        ///卸载旧武器
        SecondWeaponProperty* oldSecondWeaponProperty = static_cast<SecondWeaponProperty*>(getItemFromBag(m_nEquipedSecondWeaponID));
        if(oldSecondWeaponProperty && id.GetLongValue() != m_nEquipedSecondWeaponID.GetLongValue() )
        {
            ///检测旧装备是否可卸载
            if(!oldSecondWeaponProperty->hasEquiped() || oldSecondWeaponProperty->isCursed())
                return false;
            m_nLightDistance = m_nLightDistance - oldSecondWeaponProperty->getAddedLightDistance().GetLongValue();
            m_nLightDistance = MAX(m_nLightDistance.GetLongValue(), 6);
            m_nSearchDistance = m_nSearchDistance - oldSecondWeaponProperty->getAddedSearchDistance().GetLongValue();
            m_nSearchDistance = MAX(m_nSearchDistance.GetLongValue(), 1);
            m_nMaxHP = m_nMaxHP - oldSecondWeaponProperty->getAddedMaxHp().GetLongValue();
            m_nMaxHP = MAX(m_nMaxHP.GetLongValue(), 30);
            m_nMaxMP = m_nMaxMP - oldSecondWeaponProperty->getAddedMaxMp().GetLongValue();
            m_nMaxMP = MAX(m_nMaxMP.GetLongValue(), 30);
            m_nCurrentHP = MIN(m_nCurrentHP, m_nMaxHP);
            m_nCurrentMP = MIN(m_nCurrentMP, m_nMaxMP);
            m_nAddedMinAttack = m_nAddedMinAttack - oldSecondWeaponProperty->getAddedMinAttack().GetLongValue();
            m_nAddedMinAttack = MAX(0, m_nAddedMinAttack.GetLongValue());
            m_nAddedMaxAttack = m_nAddedMaxAttack - oldSecondWeaponProperty->getAddedMaxAttack().GetLongValue();
            m_nAddedMaxAttack = MAX(0, m_nAddedMaxAttack.GetLongValue());
            
            m_nArmorClass = m_nArmorClass - oldSecondWeaponProperty->getAddedArmorClass().GetLongValue();
            m_nArmorClass = MIN(m_nBaseArmorClass.GetLongValue(), m_nArmorClass.GetLongValue());
            
            m_fBlockRate = m_fBlockRate - oldSecondWeaponProperty->getAddedBlockRate().GetFloatValue();
            m_fBlockRate = MAX(0, m_fBlockRate.GetFloatValue());
            m_fCriticalStrikeRate = m_fCriticalStrikeRate - oldSecondWeaponProperty->getAddedCriticalStrikeRate().GetFloatValue();
            m_fCriticalStrikeRate = MAX(0, m_fCriticalStrikeRate.GetFloatValue());
            m_fDodgeRate = m_fDodgeRate - oldSecondWeaponProperty->getAddedDodgeRate().GetFloatValue();
            m_fDodgeRate = MAX(0, m_fDodgeRate.GetFloatValue());
            m_fMagicItemFindRate = m_fMagicItemFindRate - m_fBasicMagicItemFindRate*oldSecondWeaponProperty->getAddedMagicItemFindRate().GetFloatValue();
            m_fMagicItemFindRate = MAX(0, m_fBasicMagicItemFindRate.GetFloatValue());
            m_curPlayerSkill = PS_NONE;
            oldSecondWeaponProperty->setEquiped(false);
            ///处理灯光
            Color3B color = Color3B::WHITE;
            VoxelExplorer::getInstance()->setPlayerLightColor(color);
        }
        m_nEquipedSecondWeaponID = id;
        
        ///装备新武器
        m_nLightDistance = m_nLightDistance + secondWeaponProperty->getAddedLightDistance().GetLongValue();
        m_nSearchDistance = m_nSearchDistance + secondWeaponProperty->getAddedSearchDistance().GetLongValue();
        m_nSearchDistance = MIN(m_nSearchDistance.GetLongValue(), 5);
        m_nMaxHP = m_nMaxHP + secondWeaponProperty->getAddedMaxHp().GetLongValue();
        m_nMaxMP = m_nMaxMP + secondWeaponProperty->getAddedMaxMp().GetLongValue();
        m_nAddedMinAttack = m_nAddedMinAttack + secondWeaponProperty->getAddedMinAttack().GetLongValue();
        m_nAddedMaxAttack = m_nAddedMaxAttack + secondWeaponProperty->getAddedMaxAttack().GetLongValue();

        m_nArmorClass = m_nArmorClass + secondWeaponProperty->getAddedArmorClass().GetLongValue();
        
        m_fBlockRate = m_fBlockRate + secondWeaponProperty->getAddedBlockRate().GetFloatValue();
        m_fCriticalStrikeRate = m_fCriticalStrikeRate + secondWeaponProperty->getAddedCriticalStrikeRate().GetFloatValue();
        m_fDodgeRate = m_fDodgeRate + secondWeaponProperty->getAddedDodgeRate().GetFloatValue();
        
        m_fMagicItemFindRate = m_fMagicItemFindRate + m_fBasicMagicItemFindRate*secondWeaponProperty->getAddedMagicItemFindRate().GetFloatValue();
        m_fMagicItemFindRate = MIN(m_fMagicItemFindRate, m_fMaxMagicItemFindRate);
        
        m_curPlayerSkill = secondWeaponProperty->getPlayerSkill();
        secondWeaponProperty->setEquiped(true);
        ///处理灯光
        if(secondWeaponProperty->getPickableItemType() == PickableItem::PIT_STAFF_PRO_OAKSTAFF || secondWeaponProperty->getPickableItemType() == PickableItem::PIT_BOW_PRO_LAMINATEDBOW)
        {
            ///绿光颜色
            Color3B color = Color3B(126, 251, 191);
            VoxelExplorer::getInstance()->setPlayerLightColor(color);
        }
        else if(secondWeaponProperty->getPickableItemType() == PickableItem::PIT_STAFF_PRO_FIRSTAFF)
        {
            ///金色颜色
            Color3B color = Color3B(251, 250, 126);
            VoxelExplorer::getInstance()->setPlayerLightColor(color);
        }
        StatisticsManager::getInstance()->addRoleAttr();
         Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_PROPERTY_DIRTY);
        m_bDirty = true;
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_EQUIPED_SECOND_WEAPON, &m_nEquipedWeaponID);
        
        if(sound)
        {
            PickableItem::PickableItemType type = secondWeaponProperty->getPickableItemType();
            if(type >= PickableItem::PIT_STAFF_OAKSTAFF && type <= PickableItem::PIT_STAFF_PRO_MONKSTAFF)
            {
                std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("EQUIP_STAFF");
                SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
            }
            else if(type >= PickableItem::PIT_BOW_SHORTBOW && type <= PickableItem::PIT_BOW_PRO_GOLDENBOW)
            {
                std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("EQUIP_BOW");
                SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
            }
            else if(type >= PickableItem::PIT_SHIELD_WOODENSHIELD && type <= PickableItem::PIT_SHIELD_PRO_TOWERSHIELD)
            {
                std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("EQUIP_ARMOR");
                SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
            }
        }
        return true;
    }
    return false;
}
bool PlayerProperty::equipArmor(CChaosNumber id, bool sound)
{
    ArmorProperty* armorProperty = static_cast<ArmorProperty*>(getItemFromBag(id));
    if(armorProperty)
    {
        ///检查是否可装备
        if(armorProperty->hasEquiped() || armorProperty->getLevel() > m_nLevel)
            return false;
        ///卸载旧护具
        ArmorProperty* oldArmorProperty = static_cast<ArmorProperty*>(getItemFromBag(m_nEquipedArmorID));
        if(oldArmorProperty && id.GetLongValue() != m_nEquipedArmorID.GetLongValue() )
        {
            ///检测旧装备是否可卸载
            if(!oldArmorProperty->hasEquiped() || oldArmorProperty->isCursed())
                return false;
            m_nLightDistance = m_nLightDistance - oldArmorProperty->getAddedLightDistance().GetLongValue();
            m_nLightDistance = MAX(m_nLightDistance.GetLongValue(), 6);
            m_nSearchDistance = m_nSearchDistance - oldArmorProperty->getAddedSearchDistance().GetLongValue();
            m_nSearchDistance = MAX(m_nSearchDistance.GetLongValue(), 1);
            m_nMaxHP = m_nMaxHP - oldArmorProperty->getAddedMaxHp().GetLongValue();
            m_nMaxHP = MAX(m_nMaxHP.GetLongValue(), 30);
            m_nMaxMP = m_nMaxMP - oldArmorProperty->getAddedMaxMp().GetLongValue();
            m_nMaxMP = MAX(m_nMaxMP.GetLongValue(), 30);
            m_nCurrentHP = MIN(m_nCurrentHP, m_nMaxHP);
            m_nCurrentMP = MIN(m_nCurrentMP, m_nMaxMP);
            
            m_nArmorClass = m_nArmorClass - oldArmorProperty->getAddedArmorClass().GetLongValue();
            m_nArmorClass = MIN(m_nBaseArmorClass.GetLongValue(), m_nArmorClass.GetLongValue());
            
            m_fDodgeRate = m_fDodgeRate - oldArmorProperty->getAddedDodgeRate().GetFloatValue();
            m_fDodgeRate = MIN(0, m_fDodgeRate.GetFloatValue());
            
            m_fMagicItemFindRate = m_fMagicItemFindRate - m_fBasicMagicItemFindRate*oldArmorProperty->getAddedMagicItemFindRate().GetFloatValue();
            m_fMagicItemFindRate = MAX(0, m_fBasicMagicItemFindRate.GetFloatValue());
            oldArmorProperty->setEquiped(false);
        }
        
        m_nEquipedArmorID = id;
        
        ///装备新护具
        m_nLightDistance = m_nLightDistance + armorProperty->getAddedLightDistance().GetLongValue();
        m_nSearchDistance = m_nSearchDistance + armorProperty->getAddedSearchDistance().GetLongValue();
        m_nSearchDistance = MIN(m_nSearchDistance.GetLongValue(), 5);
        m_nMaxHP = m_nMaxHP + armorProperty->getAddedMaxHp().GetLongValue();
        m_nMaxMP = m_nMaxMP + armorProperty->getAddedMaxMp().GetLongValue();
        m_nCurrentHP = MIN(m_nCurrentHP, m_nMaxHP);
        m_nCurrentMP = MIN(m_nCurrentMP, m_nMaxMP);

        m_nArmorClass = m_nArmorClass + armorProperty->getAddedArmorClass().GetFloatValue();
        m_fDodgeRate = m_fDodgeRate + armorProperty->getAddedDodgeRate().GetFloatValue();
        
        m_fMagicItemFindRate = m_fMagicItemFindRate + m_fBasicMagicItemFindRate*armorProperty->getAddedMagicItemFindRate().GetFloatValue();
        m_fMagicItemFindRate = MIN(m_fMagicItemFindRate, m_fMaxMagicItemFindRate);
        armorProperty->setEquiped(true);
        StatisticsManager::getInstance()->addRoleAttr();
         Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_PROPERTY_DIRTY);
        m_bDirty = true;
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_EQUIPED_ARMOR, &m_nEquipedArmorID);
        
        if(sound)
        {
            PickableItem::PickableItemType type = armorProperty->getPickableItemType();
            if((type >= PickableItem::PIT_CLOTH_SHOES && type <= PickableItem::PIT_CLOTH_CHAINSHOES) || (type >= PickableItem::PIT_CLOTH_PRO_SHOES && type <= PickableItem::PIT_CLOTH_PRO_MAGA_CAP))
            {
                std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("EQUIP_CLOTH");
                SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
            }
            else
            {
                std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("EQUIP_ARMOR");
                SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
            }
        }
        return true;
    }
    return false;
}
bool PlayerProperty::equipOrnaments(CChaosNumber id, bool sound)
{

    MagicOrnamentProperty* magicOrnamentProperty = static_cast<MagicOrnamentProperty*>(getItemFromBag(id));
    if(magicOrnamentProperty)
    {
        ///检查是否可装备
        if(magicOrnamentProperty->hasEquiped() || magicOrnamentProperty->getLevel() > m_nLevel)
            return false;
        ///卸载旧饰品
        SecondWeaponProperty* oldMagicOrnamentProperty = static_cast<SecondWeaponProperty*>(getItemFromBag(m_nEquipedOrnamentsID));
        if(oldMagicOrnamentProperty && id.GetLongValue() != m_nEquipedOrnamentsID.GetLongValue() )
        {
            ///检测旧装备是否可卸载
            if(!oldMagicOrnamentProperty->hasEquiped() || oldMagicOrnamentProperty->isCursed())
                return false;
            m_nLightDistance = m_nLightDistance - oldMagicOrnamentProperty->getAddedLightDistance().GetLongValue();
            m_nLightDistance = MAX(m_nLightDistance.GetLongValue(), 6);
            m_nSearchDistance = m_nSearchDistance - oldMagicOrnamentProperty->getAddedSearchDistance().GetLongValue();
            m_nSearchDistance = MAX(m_nSearchDistance.GetLongValue(), 1);
            m_nMaxHP = m_nMaxHP - oldMagicOrnamentProperty->getAddedMaxHp().GetLongValue();
            m_nMaxHP = MAX(m_nMaxHP.GetLongValue(), 30);
            m_nMaxMP = m_nMaxMP - oldMagicOrnamentProperty->getAddedMaxMp().GetLongValue();
            m_nMaxMP = MAX(m_nMaxMP.GetLongValue(), 30);
            m_nCurrentHP = MIN(m_nCurrentHP, m_nMaxHP);
            m_nCurrentMP = MIN(m_nCurrentMP, m_nMaxMP);
            m_nAddedMinAttack = m_nAddedMinAttack - oldMagicOrnamentProperty->getAddedMinAttack().GetLongValue();
            m_nAddedMinAttack = MAX(0, m_nAddedMinAttack.GetLongValue());
            m_nAddedMaxAttack = m_nAddedMaxAttack - oldMagicOrnamentProperty->getAddedMaxAttack().GetLongValue();
            m_nAddedMaxAttack = MAX(0, m_nAddedMaxAttack.GetLongValue());
            
            m_nArmorClass = m_nArmorClass - oldMagicOrnamentProperty->getAddedArmorClass().GetLongValue();
            m_nArmorClass = MIN(m_nBaseArmorClass.GetLongValue(), m_nArmorClass.GetLongValue());
            
            m_fBlockRate = m_fBlockRate - oldMagicOrnamentProperty->getAddedBlockRate().GetFloatValue();
            m_fBlockRate = MAX(0, m_fBlockRate.GetFloatValue());
            m_fCriticalStrikeRate = m_fCriticalStrikeRate - oldMagicOrnamentProperty->getAddedCriticalStrikeRate().GetFloatValue();
            m_fCriticalStrikeRate = MAX(0, m_fCriticalStrikeRate.GetFloatValue());
            m_fDodgeRate = m_fDodgeRate - oldMagicOrnamentProperty->getAddedDodgeRate().GetFloatValue();
            m_fDodgeRate = MAX(0, m_fDodgeRate.GetFloatValue());
            m_fMagicItemFindRate = m_fMagicItemFindRate - m_fBasicMagicItemFindRate*oldMagicOrnamentProperty->getAddedMagicItemFindRate().GetFloatValue();
            m_fMagicItemFindRate = MAX(0, m_fBasicMagicItemFindRate.GetFloatValue());
            oldMagicOrnamentProperty->setEquiped(false);
        }
        m_nEquipedOrnamentsID = id;
        
        ///装备新饰品
        m_nLightDistance = m_nLightDistance + magicOrnamentProperty->getAddedLightDistance().GetLongValue();
        m_nSearchDistance = m_nSearchDistance + magicOrnamentProperty->getAddedSearchDistance().GetLongValue();
        m_nSearchDistance = MIN(m_nSearchDistance.GetLongValue(), 5);
        m_nMaxHP = m_nMaxHP + magicOrnamentProperty->getAddedMaxHp().GetLongValue();
        m_nMaxMP = m_nMaxMP + magicOrnamentProperty->getAddedMaxMp().GetLongValue();
        m_nAddedMinAttack = m_nAddedMinAttack + magicOrnamentProperty->getAddedMinAttack().GetLongValue();
        m_nAddedMaxAttack = m_nAddedMaxAttack + magicOrnamentProperty->getAddedMaxAttack().GetLongValue();
        
        m_nArmorClass = m_nArmorClass + magicOrnamentProperty->getAddedArmorClass().GetLongValue();
        
        m_fBlockRate = m_fBlockRate + magicOrnamentProperty->getAddedBlockRate().GetFloatValue();
        m_fCriticalStrikeRate = m_fCriticalStrikeRate + magicOrnamentProperty->getAddedCriticalStrikeRate().GetFloatValue();
        m_fDodgeRate = m_fDodgeRate + magicOrnamentProperty->getAddedDodgeRate().GetFloatValue();
        
        m_fMagicItemFindRate = m_fMagicItemFindRate + m_fBasicMagicItemFindRate*magicOrnamentProperty->getAddedMagicItemFindRate().GetFloatValue();
        m_fMagicItemFindRate = MIN(m_fMagicItemFindRate, m_fMaxMagicItemFindRate);
        magicOrnamentProperty->setEquiped(true);
        StatisticsManager::getInstance()->addRoleAttr();
         Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_PROPERTY_DIRTY);
        m_bDirty = true;
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_EQUIPED_ORNAMENTS, &m_nEquipedOrnamentsID);
        
        if(sound)
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("EQUIP_ORNAMENT");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
        return true;
    }
    return false;
}
bool PlayerProperty::indentifyItem(CChaosNumber id)
{
    bool hasIndentifyScroll = false;
    std::vector<PickableItemProperty*>::iterator iter;
    for (iter = m_Bag.begin(); iter != m_Bag.end(); iter++) {
        if((*iter) != nullptr)
        {
            ScrollProperty* scrollProperty = dynamic_cast<ScrollProperty*>(*iter);
            if(scrollProperty && (scrollProperty->getPickableItemType() == PickableItem::PIT_SCROLL_INDENTIFY) && (scrollProperty->getCount() >= 1))
            {
                scrollProperty->decreaseCount();
                hasIndentifyScroll = true;
                if(scrollProperty->getCount() == 0)
                {
                    CC_SAFE_DELETE(*iter);
                    m_Bag.erase(iter);
                    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_PROPERTY_DIRTY);
                    m_bDirty = true;
                }
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_BAG_ITEM_UPDATE);
                break;
            }
        }
    }
    if(!hasIndentifyScroll)
    {
        std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("HANDLE_FAILED");
        SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        return false;
    }
    PickableItemProperty* pickableItemProperty = static_cast<PickableItemProperty*>(getItemFromBag(id));
    if(pickableItemProperty && !pickableItemProperty->isIdentified())
    {
        pickableItemProperty->handleIdentify();
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_PROPERTY_DIRTY);
        m_bDirty = true;
        std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("INDENTIFY_OK");
        SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM ==CC_PLATFORM_ANDROID )
        SdkBoxManager::getInstance()->logEvent("Player", "IndentifyItem", "ItemType", (int)(pickableItemProperty->getPickableItemType()));
#endif
        return true;
    }
    std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("HANDLE_FAILED");
    SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    return false;
}
bool PlayerProperty::usePotion(CChaosNumber id)
{
    PotionsProperty* potionsProperty = static_cast<PotionsProperty*>(getItemFromBag(id));
    if(potionsProperty && potionsProperty->getCount() >= 1)
    {
//        PIT_POTION_MINORHEALTH,                  ///小治疗药水 Minor Health Potion
//        PIT_POTION_LESSERHEALTH,                 ///轻微治疗药水 Lesser Health Potion
//        PIT_POTION_HEALTH,                       ///治疗药水 Health Potion
//        PIT_POTION_MINORMANA,                    ///小魔法药水 Minor Mana Potion
//        PIT_POTION_LESSERMANA,                   ///轻微魔法药水 Lesser Mana Potion
//        PIT_POTION_MANA,                         ///魔法药水 Mana Potion
//        PIT_POTION_MINORRECOVERY,                ///小恢复药水 Minor Recovery Potion
//        PIT_POTION_LESSERRECOVERY,               ///轻微恢复药水 Lesser Recovery Potion
//        PIT_POTION_RECOVERY,                     ///恢复药水 Recovery Potion
//        PIT_POTION_DETOXIFICATION,               ///解毒药水 Detoxification Potion
//        PIT_POTION_SPECIFIC,                     ///特效药水 Specific Potion
        potionsProperty->decreaseCount();
        switch (potionsProperty->getPickableItemType()) {
            case PickableItem::PIT_POTION_MINORHEALTH:
            case PickableItem::PIT_POTION_LESSERHEALTH:
            case PickableItem::PIT_POTION_HEALTH:
                {
                    setCurrentHP(getCurrentHP() + potionsProperty->getValue().GetLongValue());
                    std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("USE_POTION");
                    SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
                }
                break;
            case PickableItem::PIT_POTION_MINORMANA:
            case PickableItem::PIT_POTION_LESSERMANA:
            case PickableItem::PIT_POTION_MANA:
                {
                    setCurrentMP(getCurrentMP() + potionsProperty->getValue().GetLongValue());
                    std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("USE_POTION");
                    SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
                }
                break;
            case PickableItem::PIT_POTION_MINORRECOVERY:
            case PickableItem::PIT_POTION_LESSERRECOVERY:
            case PickableItem::PIT_POTION_RECOVERY:
                {
                    setCurrentHP(getCurrentHP() + getMaxHP()*potionsProperty->getValue().GetFloatValue());
                    setCurrentMP(getCurrentMP() + getMaxMP()*potionsProperty->getValue().GetFloatValue());
                    std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("USE_POTION");
                    SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
                }
                break;
            case PickableItem::PIT_POTION_DETOXIFICATION:
            case PickableItem::PIT_POTION_SPECIFIC:
            case PickableItem::PIT_POTION_HEALING:
            case PickableItem::PIT_POTION_UNIVERSAL:
                {
                    VoxelExplorer::getInstance()->handlePlayerUsePotion(potionsProperty->getPickableItemType());
                    std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("USE_POTION_TAKE_EFFECT");
                    SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
                    
                    VoxelExplorer::getInstance()->addParticle3DEffectToPlayer(P3D_PLAYER_USE_POTION_TAKE_EFFECT);
                }
                break;
            default:
                break;
        }
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_USE_POTION, potionsProperty);
        if(potionsProperty->getCount() <= 0)
            removeItemFromBag(id);
        else
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_BAG_ITEM_UPDATE);
        return true;
    }
    return false;
}
bool PlayerProperty::useScroll(CChaosNumber id)
{
    ScrollProperty* scrollProperty = static_cast<ScrollProperty*>(getItemFromBag(id));
    if(scrollProperty && scrollProperty->getCount() >= 1)
    {
//        PIT_SCROLL_INDENTIFY,                    ////辨识卷轴 Scroll of Identify
//        PIT_SCROLL_TELEPORT,                     ////传送卷轴 Scroll of Random Teleport
//        PIT_SCROLL_SPEED,                        ////速度卷轴 Scroll of Speed
//        PIT_SCROLL_STEALTH,                      ////隐身卷轴 Scroll of Stealth
//        PIT_SCROLL_DESTINY,                      ////命运卷轴 Scroll of Destiny
        
        if(scrollProperty->getPickableItemType() == PickableItem::PIT_SCROLL_INDENTIFY)
        {
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_USE_SCROLL, scrollProperty);
        }
        else
        {
            VoxelExplorer::getInstance()->handlePlayerUseScroll(scrollProperty->getPickableItemType());
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_USE_SCROLL, scrollProperty);
            scrollProperty->decreaseCount();
            if(scrollProperty->getCount() <= 0)
                removeItemFromBag(id);
            else
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_BAG_ITEM_UPDATE);
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("USE_SCROLL");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
        return true;
    }
    return false;
}
bool PlayerProperty::useKey(PickableItem::PickableItemType type)
{
    KeyProperty* keyProperty = nullptr;
    for (PickableItemProperty* item : m_Bag) {
        if(item)
        {
            keyProperty = dynamic_cast<KeyProperty*>(item);
            if(keyProperty && keyProperty->getPickableItemType() == type && keyProperty->getCount() >= 1)
                break;
        }
    }
    if(keyProperty && keyProperty->getPickableItemType() == type)
    {
        StatisticsManager::getInstance()->addUseKeyNum();
        keyProperty->decreaseCount();
        if(keyProperty->getCount() <=0 )
            removeItemFromBag((int)(keyProperty->getInstanceID()));
        else
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_BAG_ITEM_UPDATE);
        return true;
    }
    return false;
}
void PlayerProperty::playPickupItemSound(PickableItemProperty* itemProperty)
{
    if(itemProperty)
    {
        if(itemProperty->getPickableItemPropertyType() == PickableItemProperty::PIPT_KEY)
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("PICKUP_KEY");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
        else if(itemProperty->getPickableItemPropertyType() == PickableItemProperty::PIPT_POTIONS)
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("PICKUP_POTION");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
        else if(itemProperty->getPickableItemPropertyType() == PickableItemProperty::PIPT_SCROLL)
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("PICKUP_SCROLL");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
            
        }
        else if(itemProperty->getPickableItemPropertyType() >=PickableItemProperty::PIPT_WEAPON && itemProperty->getPickableItemPropertyType() <=PickableItemProperty::PIPT_MAGIC_ORNAMENT)
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("PICKUP_WEAPON");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
        else
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("PICKUP_OTHER");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
    }
}
bool PlayerProperty::buyItemToBag(PickableItemProperty* buyItemProperty, CChaosNumber count, bool toIndentify, bool sound)
{
    if(!buyItemProperty)
        return false;
    
    CChaosNumber buycopper = buyItemProperty->getCopperWhenBuy() * count.GetLongValue();
    
    if(buyItemProperty->isStackable())
    {
        for (PickableItemProperty* item : m_Bag) {
            if(item && (item->getInstanceID() != buyItemProperty->getInstanceID()))
            {
                if(item->getPickableItemType() == buyItemProperty->getPickableItemType())
                {
                    if(costMoney(buycopper))
                    {
                        IStackable* itemProperty = dynamic_cast<IStackable*>(item);
                        if (itemProperty)
                            itemProperty->addCount(count);
                        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_BAG_ITEM_UPDATE);
                        m_bDirty = true;
                        if(sound)
                            playPickupItemSound(buyItemProperty);
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM ==CC_PLATFORM_ANDROID )
                        SdkBoxManager::getInstance()->logEvent("Player", "BuyItem", "ItemType", (int)(buyItemProperty->getPickableItemType()));
#endif
                        return true;
                    }
                }
            }
        }
        
        if(m_Bag.size() >= m_nBagMaxSpace.GetLongValue())
        {
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_BAG_NO_SPACE);
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM ==CC_PLATFORM_ANDROID )
            SdkBoxManager::getInstance()->logEvent("Player", "BuyItem", "BagNoSpace", 0);
#endif
            return false;
        }
        else
        {
            if(costMoney(buycopper))
            {
                PickableItemProperty::PickableItemPropertyType type = buyItemProperty->getPickableItemPropertyType();
                
                PickableItemProperty* itemProperty = nullptr;
                if(type == PickableItemProperty::PIPT_KEY)
                {
                    itemProperty = new (std::nothrow) KeyProperty(m_snItemInstanceIDCounter++,buyItemProperty->getPickableItemType());
                }
                else if(type == PickableItemProperty::PIPT_POTIONS)
                {
                    itemProperty = new (std::nothrow) PotionsProperty(m_snItemInstanceIDCounter++,buyItemProperty->getPickableItemType());
                }
                else if(type == PickableItemProperty::PIPT_SCROLL)
                {
                    itemProperty = new (std::nothrow) ScrollProperty(m_snItemInstanceIDCounter++,buyItemProperty->getPickableItemType());
                }
                if(itemProperty)
                {
                    itemProperty->setCount(count);
                    m_Bag.push_back(itemProperty);
                    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_BAG_ITEM_UPDATE);
                    StatisticsManager::getInstance()->addBagFullNum();
                    if(sound)
                        playPickupItemSound(itemProperty);
                }
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM ==CC_PLATFORM_ANDROID )
                SdkBoxManager::getInstance()->logEvent("Player", "BuyItem", "ItemType", (int)(itemProperty->getPickableItemType()));
#endif
                return true;
            }
        }
    }
    else
    {
        if(m_Bag.size() >= m_nBagMaxSpace.GetLongValue())
        {
            
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_BAG_NO_SPACE);
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM ==CC_PLATFORM_ANDROID )
            SdkBoxManager::getInstance()->logEvent("Player", "BuyItem", "BagNoSpace", 0);
#endif
            return false;
        }
        
        CCASSERT(count == 1, "UnStackable item count must be 1.");
        if(costMoney(buycopper))
        {
            if(toIndentify)
                buyItemProperty->handleIdentify();
            else
            {
                if(buyItemProperty->isIdentified())
                    buyItemProperty->adjustByLevel();
            }
            buyItemProperty->retain();
            m_Bag.push_back(buyItemProperty);
            StatisticsManager::getInstance()->addBagFullNum();
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_BAG_ITEM_UPDATE);
            m_bDirty = true;
            if(sound)
                playPickupItemSound(buyItemProperty);
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM ==CC_PLATFORM_ANDROID )
            SdkBoxManager::getInstance()->logEvent("Player", "BuyItem", "ItemType", (int)(buyItemProperty->getPickableItemType()));
#endif
            return true;
        }
    }
    return false;
}
bool PlayerProperty::sellItemFromBag(PickableItemProperty* sellItemProperty, CChaosNumber count)
{
    if(!sellItemProperty)
        return false;
    
    CChaosNumber valueCopper = sellItemProperty->getValueCopper()* count.GetLongValue();
    if(sellItemProperty->isStackable())
    {
        if(removeStackableItemFromBag(sellItemProperty->getPickableItemType(), count))
        {
            addMoney(valueCopper);
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM ==CC_PLATFORM_ANDROID )
            SdkBoxManager::getInstance()->logEvent("Player", "SellItem", "ItemType", (int)(sellItemProperty->getPickableItemType()));
#endif
            return true;
        }
    }
    else
    {
        CCASSERT(count == 1, "UnStackable item count must be 1.");
        
        if(removeItemFromBag((int)(sellItemProperty->getInstanceID())))
        {
            addMoney(valueCopper);
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM ==CC_PLATFORM_ANDROID )
            SdkBoxManager::getInstance()->logEvent("Player", "SellItem", "ItemType", (int)(sellItemProperty->getPickableItemType()));
#endif
            return true;
        }
    }
    return false;
}
bool PlayerProperty::addItemToBag(PickableItem::PickableItemType type, CChaosNumber level, bool sound)
{
    for (PickableItemProperty* item : m_Bag) {
        if(item)
        {
            if(item->isStackable() && item->getPickableItemType() == type)
            {
                IStackable* itemProperty = dynamic_cast<IStackable*>(item);
                if (itemProperty)
                {
                    itemProperty->increaseCount();
                    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_BAG_ITEM_UPDATE);
                    if (sound)
                        StatisticsManager::getInstance()->addPickItemNum();
                }
                if(item->isIdentified())
                    item->adjustByLevel();
                
                if(sound)
                    playPickupItemSound(item);
                return true;
            }
        }
    }
    if(m_Bag.size() >= m_nBagMaxSpace.GetLongValue())
    {
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_BAG_NO_SPACE);
        return false;
    }
    PickableItemProperty* itemProperty = nullptr;
    if(type >= PickableItem::PIT_KEY_COPPER && type <= PickableItem::PIT_KEY_ROOM)
        itemProperty = new (std::nothrow) KeyProperty(m_snItemInstanceIDCounter++,type);
    else if (type >= PickableItem::PIT_DAGGER_DAGGER && type <= PickableItem::PIT_MACE_PRO_SLEDGEHAMMER)
    {
        itemProperty = new (std::nothrow) WeaponProperty(m_snItemInstanceIDCounter++,type, level, !GameFormula::generateMagicItem(m_fMagicItemFindRate.GetFloatValue()));
        if (sound && itemProperty&&itemProperty->isIdentified()) {
            StatisticsManager::getInstance()->addPickMagicItemNum();
        }
    }
    else if (type >= PickableItem::PIT_BOW_SHORTBOW && type <=PickableItem::PIT_SHIELD_PRO_TOWERSHIELD)
    {
        itemProperty = new (std::nothrow) SecondWeaponProperty(m_snItemInstanceIDCounter++,type, level, !GameFormula::generateMagicItem(m_fMagicItemFindRate.GetFloatValue()));
        if (sound && itemProperty&&itemProperty->isIdentified()) {
            StatisticsManager::getInstance()->addPickMagicItemNum();
        }
    }
    else if(type >= PickableItem::PIT_CLOTH_SHOES && type <= PickableItem::PIT_CLOTH_PRO_STEELARMOR)
    {
        itemProperty = new (std::nothrow) ArmorProperty(m_snItemInstanceIDCounter++,type, level, !GameFormula::generateMagicItem(m_fMagicItemFindRate.GetFloatValue()));
        if (sound && itemProperty&&itemProperty->isIdentified()) {
            StatisticsManager::getInstance()->addPickMagicItemNum();
        }
    }
    else if(type >= PickableItem::PIT_ORNAMENT_RING && type <= PickableItem::PIT_ORNAMENT_PRO_JEWELS)
    {
        itemProperty = new (std::nothrow) MagicOrnamentProperty(m_snItemInstanceIDCounter++,type, level, !GameFormula::generateMagicItem(m_fMagicItemFindRate.GetFloatValue()));
        if (sound && itemProperty&&itemProperty->isIdentified()) {
            StatisticsManager::getInstance()->addPickMagicItemNum();
        }
    }
    else if(type >= PickableItem::PIT_SCROLL_INDENTIFY && type <= PickableItem::PIT_SCROLL_DESTINY)
        itemProperty = new (std::nothrow) ScrollProperty(m_snItemInstanceIDCounter++,type);
    else if(type >= PickableItem::PIT_POTION_MINORHEALTH && type <= PickableItem::PIT_POTION_UNIVERSAL)
        itemProperty = new (std::nothrow) PotionsProperty(m_snItemInstanceIDCounter++,type);
    if(itemProperty)
    {
        if (sound)
            StatisticsManager::getInstance()->addPickItemNum();
        if(itemProperty->isIdentified())
            itemProperty->adjustByLevel();
        m_Bag.push_back(itemProperty);
        StatisticsManager::getInstance()->addBagFullNum();
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_BAG_ITEM_UPDATE);
        if(sound)
            playPickupItemSound(itemProperty);
        return true;
    }
    return false;
}
bool PlayerProperty::removeStackableItemFromBag(PickableItem::PickableItemType type, CChaosNumber count)
{
    std::vector<PickableItemProperty*>::iterator iter;
    for (iter = m_Bag.begin(); iter != m_Bag.end(); iter++) {
        if((*iter) != nullptr && (*iter)->getPickableItemType() == type)
        {
            if(!(*iter)->isStackable())
                continue;
            if((*iter)->getCount() == count)
            {
                CC_SAFE_DELETE(*iter);
                m_Bag.erase(iter);
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_PROPERTY_DIRTY);
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_BAG_ITEM_UPDATE);
                m_bDirty = true;
                return true;
            }
            else if((*iter)->getCount() > count)
            {
                (*iter)->setCount((*iter)->getCount().GetLongValue() - count.GetLongValue());
                 Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_PROPERTY_DIRTY);
                 Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_BAG_ITEM_UPDATE);
                 m_bDirty = true;
                return true;
            }
            else
                return false;
        }
    }
    return false;
}
bool PlayerProperty::removeItemFromBag(CChaosNumber id)
{
    std::vector<PickableItemProperty*>::iterator iter;
    for (iter = m_Bag.begin(); iter != m_Bag.end(); iter++) {
        if((*iter) != nullptr && (*iter)->getInstanceID() == id.GetLongValue())
        {
            CC_SAFE_DELETE(*iter);
            m_Bag.erase(iter);
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_PROPERTY_DIRTY);
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_BAG_ITEM_UPDATE);
            m_bDirty = true;
            return true;
        }
    }
    return false;
}
void PlayerProperty::extendBagSpace()
{
    if(m_nBagExtendTimes >= m_nBagExtendMaxTimes)
    {
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_BAG_EXTEND_HAS_REACH_MAXTIMES);
        
        std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("HANDLE_FAILED");
        SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM ==CC_PLATFORM_ANDROID )
        SdkBoxManager::getInstance()->logEvent("Player", "ExtendBagSpace", "Failed", 0);
#endif
    }
    else
    {
        m_nBagExtendTimes = m_nBagExtendTimes + 1;
        m_nBagMaxSpace = m_nBagExtendTimes*15;
        StatisticsManager::getInstance()->addBagExtend();
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_BAG_EXTEND_OK);
        
        std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("EXTEND_BAG_OK");
        SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM ==CC_PLATFORM_ANDROID )
        SdkBoxManager::getInstance()->logEvent("Player", "ExtendBagSpaceOK", "Times", m_nBagExtendTimes);
#endif
    }
}
CChaosNumber PlayerProperty::getRandomAttack()
{
    return cocos2d::random(getMinAttack().GetLongValue(), getMaxAttack().GetLongValue());
}
void PlayerProperty::reset()
{
    m_nValueCopper          = 0;                ///价值
    m_nLevel                = 1;                ///等级
    m_nExp                  = 0;                ///经验
    m_nLightDistance        = 6;                ///光照范围
    m_nSearchDistance       = 1;                ///侦查范围
    m_nMaxHP                = 60;               ///最大生命值
    m_nMaxMP                = 60;               ///最大魔法值
    m_nCurrentHP            = 60;               ///当前生命值
    m_nCurrentMP            = 60;               ///当前魔法值
    m_nAddedMinAttack       = 1;                ///额外最小攻击增加值
    m_nAddedMaxAttack       = 4;                ///额外最大攻击增加值
    m_nAttackDiceNum        = 0;                ///攻击骰子数
    m_nAttackDiceFaceNum    = 0;                ///攻击骰子面数
    m_nArmorClass           = 4;                ///防御等级
    m_nBaseArmorClass       = 4;                ///基础防御等级
    m_fBlockRate            = 0.01f;            ///格挡率
    m_fCriticalStrikeRate   = 0.01f;            ///暴击率
    m_fDodgeRate            = 0.02f;            ///闪避率
    m_fBasicMagicItemFindRate = 0.2f;           ///基本魔法物品获得率
    m_fMagicItemFindRate    = m_fBasicMagicItemFindRate;             ///魔法物品获得率
    m_fMaxMagicItemFindRate = 0.8f;             ///最大魔法物品获得率
    
    m_nEquipedWeaponID      = -1;               ///装备了武器ID
    m_nEquipedSecondWeaponID= -1;               ///装备了副手武器ID
    m_nEquipedArmorID       = -1;               ///装备了护甲ID
    m_nEquipedOrnamentsID   = -1;               ///装备了饰品ID
    
    m_nBagMaxSpace          = 15;               ///背包最大容量
    m_nBagExtendTimes       = 1;                ///背包扩容次数
    m_nBagExtendMaxTimes    = 5;                ///背包最大扩容次数
    
    m_BufferFlag            = PB_NONE;          ///默认状态
    
    m_curPlayerSkill        = PS_NONE;          ///无技能
    
    std::vector<PickableItemProperty*>::iterator iter;
    for (iter = m_Bag.begin(); iter != m_Bag.end(); iter++) {
        CC_SAFE_DELETE(*iter);
    }
    m_Bag.clear();
}
bool PlayerProperty::refreshAfterCreatePlayer()
{
    if(m_bNeedRefreshAfterCreatePlayer)
    {
        m_nMaxHP = m_nMaxHP + 8*(m_nLevel-1);
        m_nMaxMP = m_nMaxMP + 8*(m_nLevel-1);
        if(m_nEquipedWeaponID.GetLongValue() != -1)
        {
            if(!equipWeapon(m_nEquipedWeaponID, false))
                return false;
        }
        if(m_nEquipedSecondWeaponID.GetLongValue() != -1)
        {
            if(!equipSecondWeapon(m_nEquipedSecondWeaponID, false))
                return false;
        }
        if(m_nEquipedArmorID.GetLongValue() != -1)
        {
            if(!equipArmor(m_nEquipedArmorID, false))
                return false;
        }
        if(m_nEquipedOrnamentsID.GetLongValue() != -1)
        {
            if(!equipOrnaments(m_nEquipedOrnamentsID, false))
                return false;
        }
        m_nCurrentHP = m_nMaxHP;
        m_nCurrentMP = m_nMaxMP;
        
        m_bNeedRefreshAfterCreatePlayer = false;
        m_bDirty = true;
    }
    return true;
}
bool PlayerProperty::load(const cocos2d::ValueMap& data)
{
    reset();
    if(data.find("PlayerProperty") == data.end())
    {
        return initNewPlayer();
    }
    else
    {
        ValueMap playerProperty = data.at("PlayerProperty").asValueMap();
        m_nValueCopper = playerProperty.at("ValueCopper").asInt();
        m_nLevel = playerProperty.at("Level").asInt();
        m_nExp = playerProperty.at("Exp").asInt();
        
        m_nBagMaxSpace = playerProperty.at("BagMaxSpace").asInt();
        m_nBagExtendTimes = playerProperty.at("BagExtendTimes").asInt();
        
        m_snItemInstanceIDCounter = playerProperty.at("ItemInstanceIDCounter").asInt();
        
        ValueVector playerBag = playerProperty.at("PlayerBag").asValueVector();
        for (Value value : playerBag) {
            PickableItemProperty* property = nullptr;
            PickableItemProperty::PickableItemPropertyType propertyType = (PickableItemProperty::PickableItemPropertyType)value.asValueMap().at("PropertyType").asInt();
            PickableItem::PickableItemType itemType = (PickableItem::PickableItemType)value.asValueMap().at("ItemType").asInt();
            int instanceId = value.asValueMap().at("InstanceID").asInt();
            int level = value.asValueMap().at("Level").asInt();
            bool identified = value.asValueMap().at("Identified").asInt();
            if(propertyType == PickableItemProperty::PIPT_KEY)
                property = new (std::nothrow) KeyProperty(instanceId, itemType);
            else if(propertyType == PickableItemProperty::PIPT_WEAPON)
                property = new (std::nothrow) WeaponProperty(instanceId, itemType, level, identified);
            else if(propertyType == PickableItemProperty::PIPT_SECOND_WEAPON)
                property = new (std::nothrow) SecondWeaponProperty(instanceId, itemType, level, identified);
            else if(propertyType == PickableItemProperty::PIPT_ARMOR)
                property = new (std::nothrow) ArmorProperty(instanceId, itemType, level, identified);
            else if(propertyType == PickableItemProperty::PIPT_MAGIC_ORNAMENT)
                property = new (std::nothrow) MagicOrnamentProperty(instanceId, itemType, level, identified);
            else if(propertyType == PickableItemProperty::PIPT_SCROLL)
                property = new (std::nothrow) ScrollProperty(instanceId, itemType);
            else if(propertyType == PickableItemProperty::PIPT_POTIONS)
                property = new (std::nothrow) PotionsProperty(instanceId, itemType);
            if(!property || !property->load(value.asValueMap()))
                return false;
            m_Bag.push_back(property);
        }
        m_nEquipedWeaponID = playerProperty.at("EquipedWeaponID").asInt();
        m_nEquipedSecondWeaponID = playerProperty.at("EquipedSecondWeaponID").asInt();
        m_nEquipedArmorID = playerProperty.at("EquipedArmorID").asInt();
        m_nEquipedOrnamentsID = playerProperty.at("EquipedOrnamentsID").asInt();
        
        m_bNeedRefreshAfterCreatePlayer = true;
        return true;
    }
}
bool PlayerProperty::save(cocos2d::ValueMap& data)
{
    ValueMap playerProperty;
    playerProperty["ValueCopper"] = (int)m_nValueCopper.GetLongValue();
    playerProperty["Level"] = (int)m_nLevel.GetLongValue();
    playerProperty["Exp"] = (int)m_nExp.GetLongValue();
    
    playerProperty["EquipedWeaponID"] = (int)m_nEquipedWeaponID.GetLongValue();
    playerProperty["EquipedSecondWeaponID"] = (int)m_nEquipedSecondWeaponID.GetLongValue();
    playerProperty["EquipedArmorID"] = (int)m_nEquipedArmorID.GetLongValue();
    playerProperty["EquipedOrnamentsID"] = (int)m_nEquipedOrnamentsID.GetLongValue();
    
    playerProperty["BagMaxSpace"] = (int)m_nBagMaxSpace.GetLongValue();
    playerProperty["BagExtendTimes"] = (int)m_nBagExtendTimes.GetLongValue();
    
    playerProperty["ItemInstanceIDCounter"] = (int)m_snItemInstanceIDCounter;

    ValueVector playerBag;
    for (PickableItemProperty* property : m_Bag) {
        ValueMap pickableItemProperty;
        if(!property || !property->save(pickableItemProperty))
            return false;
        playerBag.push_back(Value(pickableItemProperty));
    }
    playerProperty["PlayerBag"] = playerBag;
    data["PlayerProperty"] = playerProperty;
    
    GameCenterController::getInstance()->reportLevel((int)m_nLevel.GetLongValue());
    GameCenterController::getInstance()->reportMoney((int)m_nValueCopper.GetLongValue());
    return true;
}
void PlayerProperty::levelUp()
{
    m_nLevel = m_nLevel + 1;
    m_nMaxHP = m_nMaxHP + 8;
    m_nMaxMP = m_nMaxMP + 8;
    m_nCurrentHP = m_nMaxHP;
    m_nCurrentMP = m_nMaxMP;
    m_bDirty = true;
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_LEVEL_UP);
    
    std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("PLAYER_LEVEL_UP");
    SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    StatisticsManager::getInstance()->addRoleAttr();
    VoxelExplorer::getInstance()->addParticle3DEffectToPlayer(P3D_PLAYER_LEVELUP);
    
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM ==CC_PLATFORM_ANDROID )
    SdkBoxManager::getInstance()->logEvent("Player", "LevelUp", "level", (int)m_nLevel.GetLongValue());
#endif
    GameCenterController::getInstance()->reportLevel((int)m_nLevel.GetLongValue());
}
PickableItemProperty* PlayerProperty::getItemFromBag(CChaosNumber id) const
{
    std::vector<PickableItemProperty*>::const_iterator iter;
    for (iter = m_Bag.begin(); iter != m_Bag.end(); iter++) {
        if((*iter) != nullptr && (*iter)->getInstanceID() == id.GetLongValue())
            return (*iter);
    }
    return nullptr;
}