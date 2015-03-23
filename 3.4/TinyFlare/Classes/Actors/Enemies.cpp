//
//  Enemies.cpp
//  Geometry-Wars
//
//  Created by wang haibo on 15/3/9.
//
//

#include "Enemies.h"
#include "GameController.h"
#include "ParticleSystemHelper.h"
USING_NS_CC;
Enemy::Enemy()
{
    m_type = AT_ENEMY;
    m_EnemyType = ET_UNKNOWN;
}
Enemy::~Enemy()
{
}
cocos2d::Color3B Enemy::getColor()
{
    if (m_pModel)
        return m_pModel->getColor();
    return Color3B::WHITE;
}
void Enemy::setColor(const cocos2d::Color3B& color)
{
    if(m_pModel)
        m_pModel->setColor(color);
}
void Enemy::beginTrack()
{
    m_fAccel = cocos2d::random(4.0f, 5.0f);
    m_fMaxSpeed = cocos2d::random(2.0f, 3.0f);
    setActorState(ActorState::AS_TRACK);
}
Circle::Circle()
{
    m_EnemyType = ET_CIRCLE;
    m_fAccel = 40.0f;
    m_fMaxSpeed = 10.0f;
}
Circle::~Circle()
{
}
void Circle::onEnterDead()
{
    ParticleSystemHelper::spawnExplosion(ExplosionType::ET_EXPLOSION_WHITE, getPosition());
}
void Circle::update(float delta)
{
    if(m_curState == ActorState::AS_TRACK)
    {
        if(GameController::getInstance()->getPlayer())
        {
            Vec2 playerPos = GameController::getInstance()->getPlayerPos();
            Vec2 dir = playerPos - getPosition();
            setDirection(dir);
        }
        else
            setDirection(Vec2::ZERO);
    }
    
    float mainRotationZ = CC_RADIANS_TO_DEGREES(Vec2::angle(m_Direction, Vec2::UNIT_Y));
    if (m_Direction.x < 0)
        mainRotationZ = -mainRotationZ;
    m_pModel->setRotation(mainRotationZ);
    
    if(!m_bBounce)
    {
        if (m_Direction == Vec2::ZERO) {
            m_Velocity *= 0.99f;
            if(m_Velocity.length() <0.001f)
                m_Velocity = Vec2::ZERO;
        }
        else
        {
            m_Velocity += m_Direction*m_fAccel*delta;
            if(m_Velocity.length() >= m_fMaxSpeed)
            {
                m_Velocity.normalize();
                m_Velocity = m_Velocity*m_fMaxSpeed;
            }
        }
    }
    Vec2 pos = getPosition();
    Vec2 newPos = pos + m_Velocity;
    setPosition(newPos);
}

/////ColorCircle
ColorCircle::ColorCircle()
{
    m_EnemyType = ET_CIRCLE_COLORED;
    m_fAccel = cocos2d::random(4.0f, 5.0f);
    m_fMaxSpeed = cocos2d::random(2.0f, 3.0f);
}
ColorCircle::~ColorCircle()
{
}
void ColorCircle::onEnterDead()
{
    ParticleSystemHelper::spawnExplosion(ExplosionType::ET_EXPLOSION_WHITE, getPosition());
    GameController::getInstance()->getEnemiesGenerator()->generateEnemiesByExplosion(Enemy::ET_CIRCLE, getPosition(), 2);
}
