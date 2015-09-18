//
//  Enemy.cpp
//  Tone_Skipper
//
//
//

#include "Enemy.h"
#include "MapMgrs.h"
USING_NS_CC;

Enemy::Enemy()
{
    m_fMaxXSpeed = 0.5f;
    m_fMaxYSpeed = 2.5f;
    
    m_EnemyType = ET_UNKNOWN;
    m_EnemyState = ES_UNKNOWN;
    m_EnemyDirection = ED_RIGHT;
    m_EnemyLastDirection = ED_RIGHT;

}
Enemy::~Enemy()
{
}
void Enemy::update(float delta)
{
    if(!m_pSprite)
        return;
    if(!m_bOnLand)
        m_Velocity += Vec2(0, Gravity)*delta;
    if(m_Velocity.y <= -m_fMaxYSpeed)
        m_Velocity.y = -m_fMaxYSpeed;
    
    updatePosition(delta);
    
    checkTriggers();
    
#if COCOS2D_DEBUG
    showDebug(true);
#endif
}
void Enemy::setEnemyState(Enemy state)
{
    if (m_EnemyState == state )
        return;
    
    ///处理上一个状态退出逻辑
    switch (m_PlayerState) {
        case PS_IDLE:
            onExitIdleState();
            break;
        case PS_DEATH:
            onExitDeathState();
            break;
        default:
            break;
    }
    
    m_PlayerState = state;
    ///处理下一个状态进入逻辑
    switch (m_PlayerState) {
        case PS_IDLE:
            onEnterIdleState();
            break;
        case PS_DEATH:
            onEnterDeathState();
            break;
        default:
            break;
    }
}
void Enemy::setEnemyDirection(EnemyDirection direction)
{
    if(m_EnemyDirection == direction)
        return;
    m_EnemyLastDirection = m_EnemyDirection;
    m_EnemyDirection = direction;
    if(m_EnemyDirection == ED_LEFT)
    {
        setFlipX(true);
        if(getEnemyState() == ES_PATROL)
            m_Velocity.x = -m_fMaxXSpeed;
    }
    else if(m_EnemyDirection == ED_RIGHT)
    {
        setFlipX(false);
        if(getEnemyState() == ES_PATROL)
            m_Velocity.x = m_fMaxXSpeed;
    }
}
