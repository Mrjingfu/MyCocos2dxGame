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
Circle::Circle()
{
    m_EnemyType = ET_CIRCLE;
    m_fAccel = cocos2d::random(4.0f, 5.0f);
}
Circle::~Circle()
{
}
void Circle::die()
{
    ParticleSystemHelper::spawnExplosion(ExplosionType::ET_EXPLOSION_WHITE, getPosition());
}
void Circle::update(float delta)
{
    if(GameController::getInstance()->getPlayer())
    {
        Vec2 playerPos = GameController::getInstance()->getPlayer()->getPosition();
        Vec2 dir = playerPos - getPosition();
        setDirection(dir);
    }
    else
        setDirection(Vec2::ZERO);
    
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
