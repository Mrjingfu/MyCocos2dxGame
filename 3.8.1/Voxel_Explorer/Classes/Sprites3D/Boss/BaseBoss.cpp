//
//  BaseBoss.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/23.
//
//

#include "BaseBoss.hpp"
USING_NS_CC;
const std::string BOSS_MODEL_NAMES[] = {
    "BMN_UNKNOWN",
    
    "BMN_SLIMEKING",               ///史莱姆王
    "BMN_WARDEN",                  ///典狱长
    "BMN_ARCHBISHOP",              ///大主教
    "BMN_KOBOLDLEADER",            ///狗头人首领
    "BMN_GIANT",                   ///巨人格鲁尔德
    "BMN_SKELETONKING",            ///骷髅王
    
    "BMN_MAX"
};

BaseBoss::BaseBoss()
{
    m_State = BS_UNKNOWN;
    m_LastState = BS_UNKNOWN;
}
BaseBoss::~BaseBoss()
{
}
void BaseBoss::attackedByPlayer()
{
}
void BaseBoss::setState(BossState state)
{
    if(m_State == state)
        return;
    switch (m_State) {
        case BS_IDLE:
            onExitIdle();
            break;
        case BS_DEATH:
            onExitDeath();
            break;
        default:
            break;
    }
    
    m_LastState = m_State;
    m_State = state;
    
    switch (m_State) {
        case BS_IDLE:
            onEnterIdle();
            break;
        case BS_DEATH:
            onEnterDeath();
            break;
        default:
            break;
    }
}
void BaseBoss::onEnter()
{
    Actor::onEnter();
    scheduleUpdate();
}
void BaseBoss::onExit()
{
    unscheduleUpdate();
    Actor::onExit();
}
void BaseBoss::update(float delta)
{
}

void BaseBoss::onEnterIdle()
{
}
void BaseBoss::onExitIdle()
{
}

void BaseBoss::onEnterDeath()
{
}
void BaseBoss::onExitDeath()
{
}
