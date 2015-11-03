//
//  BaseBoss.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/23.
//
//

#include "BaseBoss.hpp"
USING_NS_CC;
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
