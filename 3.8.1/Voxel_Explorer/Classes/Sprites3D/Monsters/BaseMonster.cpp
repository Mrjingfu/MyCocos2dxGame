//
//  BaseMonster.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/22.
//
//

#include "BaseMonster.hpp"
#include "BaseLevel.h"
#include "AlisaMethod.h"
#include "PlayerProperty.hpp"
#include "VoxelExplorer.h"
USING_NS_CC;
const std::string MONSTER_MODEL_NAMES[] = {
    "MMN_UNKNOWN",
    
    //SEWER_BEGIN
    "MMN_RAT",             ///老鼠
    "MMN_BAT",             ///蝙蝠
    "MMN_SNAKE",           ///蛇
    "MMN_SPIDER",          ///蜘蛛
    "MMN_SLIME",           ///史莱姆
    //SEWER_END
    
    //PRISON_BEGIN
    "MMN_ALLIP",           ///怨魂
    "MMN_PRISONER",        ///囚犯
    "MMN_PRISONGUARD",     ///监狱守卫
    "MMN_TORTURE",         ///拷问者
    "MMN_MOB",             ///暴徒
    //PRISON_END
    
    //FANE_BEGIN
    "MMN_BELIEVER",        ///信徒
    "MMN_GATEKEEPER",      ///看门人
    "MMN_APOLOGIST",       ///辩护者
    "MMN_ADJUDICATOR",     ///审判者
    "MMN_PRIEST",          ///牧师
    //FANE_END
    
    //MINES_BEGIN
    "MMN_DEATHMINER",      ///死亡矿工
    "MMN_KOBOLD",          ///狗头人
    "MMN_OOZE",            ///软泥怪
    "MMN_SHADOW",          ///阴影怪
    "MMN_ANKHEG",          ///掘地虫
    //MINES_END
    
    //CAVE_BEGIN
    "MMN_WOLF",            ///狼
    "MMN_BEAR",            ///熊
    "MMN_GOBLIN",          ///地精
    "MMN_DINOSAUR",        ///恐龙
    "MMN_GNOLL",           ///豺狼人
    //CAVE_END
    
    //TOMB_BEGIN
    "MMN_SKELETON",        ///骷髅
    "MMN_ZOMBIE",          ///僵尸
    "MMN_GARGOYLE",        ///石像鬼
    "MMN_GHOST",           ///幽灵
    "MMN_GHOUL",           ///食尸鬼
    //TOMB_END
    
    "MMN_MAX"
};
BaseMonster::BaseMonster()
{
    m_Type = MT_UNKNOWN;
    m_State = MS_UNKNOWN;
    m_LastState = MS_UNKNOWN;
    m_bJumpMove = true;
    
    m_pHurtData = new (std::nothrow) HurtData();
    
    m_nFOV = 5;
    m_nAttackRange = 1;
    
    m_pMonsterProperty = new (std::nothrow) MonsterProperty();
    if(m_pMonsterProperty)
        m_pMonsterProperty->adjustByDC();
}
BaseMonster::~BaseMonster()
{
    CC_SAFE_DELETE(m_pHurtData);
    CC_SAFE_DELETE(m_pMonsterProperty);
}
void BaseMonster::attackedByPlayer()
{
    if(m_pMonsterProperty && m_pHurtData)
    {
        m_pHurtData->reset();
        float percentDodgeRate = m_pMonsterProperty->getDodgeRate().GetFloatValue();
        float percentHit = 1.0 - percentDodgeRate;
        AlisaMethod* amDodgeRate = AlisaMethod::create(percentDodgeRate,percentHit,-1.0, NULL);
        if(amDodgeRate)
        {
            if(amDodgeRate->getRandomIndex() == 0)
            {
                m_pHurtData->m_bDodge = true;
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_MONSTER_HURT, m_pHurtData);
                return;
            }
        }
        int attack = PlayerProperty::getInstance()->getRandomAttack().GetLongValue();
        float percentCriticalStrikeRate = PlayerProperty::getInstance()->getCriticalStrikeRate().GetFloatValue();
        float percentNormal = 1.0 - percentCriticalStrikeRate;
        AlisaMethod* amCriticalStrikeRate = AlisaMethod::create(percentCriticalStrikeRate,percentNormal,-1.0, NULL);
        if(amCriticalStrikeRate)
        {
            if(amCriticalStrikeRate->getRandomIndex() == 0)
            {
                attack = attack*2.0f;
                m_pHurtData->m_bCriticalStrike = true;
            }
        }
        
        int defense = m_pMonsterProperty->getDefense().GetLongValue();
        
        attack = MAX(attack + defense, 0);
        
        float percentBlockRate = m_pMonsterProperty->getBlockRate().GetFloatValue();
        float percentNull = 1.0 - percentBlockRate;
        AlisaMethod* amBlockRate = AlisaMethod::create(percentBlockRate,percentNull,-1.0, NULL);
        if(amBlockRate)
        {
            if(amBlockRate->getRandomIndex() == 0)
            {
                attack = attack*0.5f;
                m_pHurtData->m_bBlocked = true;
            }
        }
        
        int currentHp = m_pMonsterProperty->getCurrentHP().GetLongValue();
        currentHp = MAX(currentHp - attack , 0);
        CCLOG("Monster: CurrentHp = %d, playerAttack = %d", currentHp, attack);
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_MONSTER_HURT, m_pHurtData);
        if(currentHp == 0)
        {
            setState(MS_DEATH);
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_MONSTER_DEATH, this);
        }
        else
            m_pMonsterProperty->setCurrentHP(currentHp);
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_MONSTER_PROPERTY_DIRTY, this);
    }
}
void BaseMonster::setState(MonsterState state)
{
    if(m_State == state)
        return;
    switch (m_State) {
        case MS_SLEEPING:
            onExitSleeping();
            break;
        case MS_WANDERING:
            onExitWandering();
            break;
        case MS_TRACKING:
            onExitTracking();
            break;
        case MS_FLEEING:
            onExitFleeing();
            break;
        case MS_PASSIVE:
            onExitPassive();
            break;
        case MS_CONFUSING:
            onExitConfusing();
            break;
        case MS_ATTACK:
            onExitAttack();
            break;
        case MS_DEATH:
            onExitDeath();
            break;
        default:
            break;
    }
    
    m_LastState = m_State;
    m_State = state;
    
    switch (m_State) {
        case MS_SLEEPING:
            onEnterSleeping();
            break;
        case MS_WANDERING:
            onEnterWandering();
            break;
        case MS_TRACKING:
            onEnterTracking();
            break;
        case MS_FLEEING:
            onEnterFleeing();
            break;
        case MS_PASSIVE:
            onEnterPassive();
            break;
        case MS_CONFUSING:
            onEnterConfusing();
            break;
        case MS_ATTACK:
            onEnterAttack();
            break;
        case MS_DEATH:
            onEnterDeath();
            break;
        default:
            break;
    }

}
void BaseMonster::onEnter()
{
    Actor::onEnter();
    scheduleUpdate();
    int flag = TileInfo::PASSABLE | TileInfo::ATTACKABLE;
    updateTerrainTileFlag(flag);
}
void BaseMonster::onExit()
{
    unscheduleUpdate();
    Actor::onExit();
}
void BaseMonster::update(float delta)
{
    switch (m_State) {
        case MS_SLEEPING:
            {
                if(VoxelExplorer::getInstance()->checkMonsterAlert(this))
                    setState(MS_TRACKING);
            }
            break;
        case MS_TRACKING:
            {
                if(VoxelExplorer::getInstance()->checkMonsterAlert(this))
                    setState(MS_CONFUSING);
                else
                {
                    if(VoxelExplorer::getInstance()->checkMonsterCanAttack(this))
                    {
                    }
                    else
                    {
                    }
                }
            }
            break;
        default:
            break;
    }
}

void BaseMonster::onEnterSleeping()
{
}
void BaseMonster::onExitSleeping()
{
}

void BaseMonster::onEnterWandering()
{
}
void BaseMonster::onExitWandering()
{
}

void BaseMonster::onEnterTracking()
{
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_MONSTER_ALERT, this);
}
void BaseMonster::onExitTracking()
{
}

void BaseMonster::onEnterFleeing()
{
}
void BaseMonster::onExitFleeing()
{
}

void BaseMonster::onEnterPassive()
{
}
void BaseMonster::onExitPassive()
{
}
void BaseMonster::onEnterConfusing()
{
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_MONSTER_CONFUSING, this);
}
void BaseMonster::onExitConfusing()
{
}
void BaseMonster::onEnterAttack()
{
}
void BaseMonster::onExitAttack()
{
}

void BaseMonster::onEnterDeath()
{
    VoxelExplorer::getInstance()->addExplosion(getPosition3D());
}
void BaseMonster::onExitDeath()
{
}