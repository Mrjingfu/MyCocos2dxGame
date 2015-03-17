//
//  Enemies.cpp
//  Geometry-Wars
//
//  Created by wang haibo on 15/3/9.
//
//

#include "Enemies.h"
USING_NS_CC;
Enemy::Enemy()
{
    m_type = AT_ENEMY;
}
Enemy::~Enemy()
{
}
Enemy::EnemyType Enemy::getEnemyType() const
{
    return m_EnemyType;
}
void Enemy::setEnemyType(Enemy::EnemyType type)
{
    m_EnemyType = type;
}

Brown::Brown()
{}
Brown::~Brown()
{
}
void Brown::executeAI(float delta)
{
}