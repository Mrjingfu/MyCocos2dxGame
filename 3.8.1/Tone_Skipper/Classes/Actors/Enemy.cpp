//
//  Enemy.cpp
//  Tone_Skipper
//
//
//

#include "Enemy.h"
#include "MapMgrs.h"
#include "WalkState.h"
USING_NS_CC;

Enemy::Enemy()
{
    m_fMaxXSpeed = 0.5f;
    m_fMaxYSpeed = 2.5f;
    
    m_EnemyType = ET_UNKNOWN;
    m_EnemyDirection = ED_RIGHT;
    m_EnemyLastDirection = ED_RIGHT;
    m_pEnemyState = nullptr;

}
Enemy::~Enemy()
{
}
void Enemy::update(float delta)
{
    if(!isVisible())
        return;
    if(!m_pSprite)
        return;
    
    
    updatePosition(delta);
    
    if (m_pEnemyState)
        m_pEnemyState->update(this, delta);
#if COCOS2D_DEBUG
    showDebug(true);
#endif
}
void Enemy::updatePosition(float delta)
{
    cocos2d::Rect rect = getBoundingBox();
    Vec2 nextPosY= getPosition() + Vec2(0,m_Velocity.y);
    if (getEnemyDirection() == ED_LEFT)
        nextPosY =  getPosition() + Vec2(rect.origin.x,m_Velocity.y);
    else if(getEnemyDirection() == ED_RIGHT)
        nextPosY =  getPosition() + Vec2(-rect.origin.x,m_Velocity.y);
    
    rect.origin += nextPosY;
    Actor::RAYCAST_TYPE type = Actor::RT_UNKNOWN;
    bool raycast = MapMgrs::getInstance()->checkRayCast(rect, m_Velocity, type, m_bOnLand);
    if(raycast)
    {
        if(m_bOnLand == false)
        {
            m_bOnLand = true;
            if(m_Velocity.y < 1)
                m_bOnLadder = false;
            
            if(m_Velocity.y > m_fMaxYSpeed)
                 m_Velocity.y = m_fMaxYSpeed*delta;
            
            
        }
        else
        {
            if(m_Velocity.y < 0)
                m_Velocity.y = 0;
        }
    }
    else
    {
        if(m_bOnLand)
            m_bOnLand = false;
        this->onLand();
    }
    setPosition(getPosition() + Vec2(0,m_Velocity.y));
    
    rect = getBoundingBox();
    Vec2 nextPosX = getPosition() + Vec2(m_Velocity.x, 0);
    rect.origin += nextPosX;
    
    int collisionFlag = MapMgrs::CF_NONE;
    bool collision = MapMgrs::getInstance()->checkCollision(rect, m_Velocity, collisionFlag);
    if(collision)
    {
        if((collisionFlag & MapMgrs::CF_RIGHT) != 0 )
        {
            if(m_Velocity.x > 0)
            {
                this->onCollision();
            }
            else if(m_Velocity.x < 0)
            {
                setPosition(getPosition() + Vec2(m_Velocity.x, 0));
                this->onCollision();
            }
        }
        else if((collisionFlag & MapMgrs::CF_LEFT) != 0 )
        {
            if(m_Velocity.x < 0)
            {
                
                this->onCollision();
            }
            else if(m_Velocity.x > 0)
            {
                setPosition(getPosition() + Vec2(m_Velocity.x, 0));
                this->onCollision();
            }
        }
        if((collisionFlag & MapMgrs::CF_BOUND) != 0)
        {
           
            this->onCollision();
        }
    }
    
}
    
void Enemy::setEnemyState(EnemyStateType stateType)
{
    EnemyState* state = createState(stateType);
    
    if (m_pEnemyState) {
        if (m_pEnemyState->getEnemyStateType() == state->getEnemyStateType() )
            return;
        m_pEnemyState->onExit(this);
    }
    m_pEnemyState = state;
    
    m_pEnemyState->onEnter(this);
    
}
EnemyState* Enemy::createState(EnemyStateType stateType)
{
    EnemyState* enemyState = nullptr;
    switch (stateType) {
        case ES_PATROL:
            enemyState = WalkState::getInstance();
            break;
        default:
            break;
    }
    return enemyState;
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
        if(getEnemyState()->getEnemyStateType() == ES_PATROL)
            m_Velocity.x = -m_fMaxXSpeed;
    }
    else if(m_EnemyDirection == ED_RIGHT)
    {
        setFlipX(false);
        if(getEnemyState()->getEnemyStateType() == ES_PATROL)
            m_Velocity.x = m_fMaxXSpeed;
    }
}
cocos2d::Rect Enemy::getBoundingBox() const
{
    cocos2d::Rect spriteRect;
    
    return m_pSprite->getBoundingBox();
}
