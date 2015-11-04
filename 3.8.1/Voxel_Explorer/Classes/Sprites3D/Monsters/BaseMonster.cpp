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
        case MS_IDLE:
            onExitIdle();
            break;
        case MS_TRACK:
            onExitTrack();
            break;
        case MS_ATTACK:
            onExitAttack();
            break;
        case MS_ESCAPE:
            onExitEscape();
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
        case MS_IDLE:
            onEnterIdle();
            break;
        case MS_TRACK:
            onEnterTrack();
            break;
        case MS_ATTACK:
            onEnterAttack();
            break;
        case MS_ESCAPE:
            onEnterEscape();
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
}
void BaseMonster::onExit()
{
    unscheduleUpdate();
    Actor::onExit();
}
void BaseMonster::update(float delta)
{
}
void BaseMonster::onEnterIdle()
{
    int flag = TileInfo::PASSABLE | TileInfo::ATTACKABLE;
    updateTerrainTileFlag(flag);
}
void BaseMonster::onExitIdle()
{
}

void BaseMonster::onEnterTrack()
{
}
void BaseMonster::onExitTrack()
{
}

void BaseMonster::onEnterEscape()
{
}
void BaseMonster::onExitEscape()
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