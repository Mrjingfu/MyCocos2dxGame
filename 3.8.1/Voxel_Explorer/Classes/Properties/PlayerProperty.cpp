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
USING_NS_CC;

PlayerProperty* g_pPlayerPropertyInstance = nullptr;
PlayerProperty* PlayerProperty::getInstance()
{
    if( g_pPlayerPropertyInstance == nullptr )
        g_pPlayerPropertyInstance = new PlayerProperty();
    
    return g_pPlayerPropertyInstance;
}
PlayerProperty::PlayerProperty()
{
    m_nGold                 = 0;                ///金币
    m_nSilver               = 0;                ///银币
    m_nCopper               = 0;                ///铜币
    m_nLevel                = 1;                ///等级
    m_nExp                  = 0;                ///经验
    m_nLightDistance        = 5;                ///光照范围
    m_nSearchDistance       = 1;                ///侦查范围
    m_nMaxHP                = 30;               ///最大生命值
    m_nMaxMP                = 30;               ///最大魔法值
    m_nCurrentHP            = 30;               ///当前生命值
    m_nCurrentMP            = 30;               ///当前魔法值
    m_nAddedMinAttack       = 0;                ///额外最小攻击增加值
    m_nAddedMaxAttack       = 0;                ///额外最大攻击增加值
    m_nAttackDiceNum        = 1;                ///攻击骰子数
    m_nAttackDiceFaceNum    = 4;                ///攻击骰子面数
    m_nArmorClass           = 4;                ///防御等级
    m_nBaseArmorClass       = 4;                ///基础防御等级
    m_fBlockRate            = 0.01f;            ///格挡率
    m_fCriticalStrikeRate   = 0.01f;            ///暴击率
    m_fDodgeRate            = 0.02f;            ///闪避率
    
    m_nEquipedWeaponID      = -1;               ///装备了武器ID
    m_nEquipedArmorID       = -1;               ///装备了护甲ID
    m_nEquipedOrnamentsID   = -1;               ///装备了饰品ID
    
    m_bDirty = false;
}
PlayerProperty::~PlayerProperty()
{
}
void PlayerProperty::update(float delta)
{
    if(m_bDirty)
    {
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_PROPERTY_DIRTY);
        m_bDirty = false;
    }
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
    return -m_nArmorClass.GetLongValue() + m_nBaseArmorClass.GetLongValue();
}
void PlayerProperty::addMoney(CChaosNumber gold, CChaosNumber silver, CChaosNumber copper)
{
    if(silver<0 || silver>99 || copper<0 || copper>99 )
    {
        CCLOGERROR("Money add error!");
        return;
    }
    m_nGold = m_nGold + gold.GetLongValue();
    m_nSilver = m_nSilver + silver.GetLongValue();
    m_nCopper = m_nCopper + copper.GetLongValue();
    m_bDirty = true;
}
void PlayerProperty::costMoney(CChaosNumber gold, CChaosNumber silver, CChaosNumber copper)
{
    CChaosNumber cost = GameFormula::exchangeMoney(gold,silver,copper);
    CChaosNumber own = GameFormula::exchangeMoney(m_nGold,m_nSilver,m_nCopper);
    if(own < cost)
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_MONEY_NOT_ENOUGH);
    else
    {
        CChaosNumber left = own.GetLongValue() - cost.GetLongValue();
        GameFormula::exchangeMoney(left, m_nGold, m_nSilver, m_nCopper);
    }
    m_bDirty = true;
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
    
    m_bDirty = true;
}
void PlayerProperty::setCurrentMP(CChaosNumber mp)
{
    if(mp >= m_nMaxMP)
        m_nMaxMP = mp;
    else if(mp <= 0)
    {
        m_nCurrentMP = 0;
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_NO_MANA);
    }
    else
        m_nCurrentMP = mp;
    
    m_bDirty = true;
}
void PlayerProperty::EquipWeapon(CChaosNumber id)
{
    m_nEquipedWeaponID = id;
    m_bDirty = true;
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_EQUIPED_WEAPON);
}
void PlayerProperty::EquipArmor(CChaosNumber id)
{
    m_nEquipedArmorID = id;
    m_bDirty = true;
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_EQUIPED_ARMOR);
}
void PlayerProperty::EquipOrnaments(CChaosNumber id)
{
    m_nEquipedOrnamentsID = id;
    m_bDirty = true;
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_EQUIPED_ORNAMENTS);
}
void PlayerProperty::load()
{
}
void PlayerProperty::save()
{
}
void PlayerProperty::levelUp()
{
    m_nLevel = m_nLevel + 1;
    m_nMaxHP = m_nMaxHP + 8;
    m_nMaxHP = m_nMaxMP + 8;
    m_nCurrentHP = m_nMaxHP;
    m_nCurrentMP = m_nMaxMP;
    m_bDirty = true;
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_LEVEL_UP);
}