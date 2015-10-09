//
//  WalkState.cpp
//  Tone_Skipper
//
//  Created by 创李 on 15/10/8.
//
//

#include "PatrolEnemyState.h"

USING_NS_CC;
PatrolEnemyState::PatrolEnemyState()
{
    m_pEnemyStateType = Enemy::EnemyStateType::ES_PATROL;
}
PatrolEnemyState::~PatrolEnemyState()
{
    
}
void PatrolEnemyState::onEnter(Enemy * enemy)
{
    if(!enemy->getEnemySprite())
        return;
    if (!enemy->getPatrolAnimation()) {
        return;
    }
    Animate* action = nullptr;
    float maxXSpeed = enemy->getMaxXSpeed();
    switch (enemy->getEnemyDirection()) {
        case Enemy::ED_LEFT:
            action = Animate::create(enemy->getPatrolAnimation());
            enemy->setVelocity(Vec2(-maxXSpeed, 0));
            break;
        case Enemy::ED_RIGHT:
            action = Animate::create(enemy->getPatrolAnimation());
            enemy->setVelocity(Vec2(maxXSpeed, 0));
            break;
        case Enemy::ED_BACK:
            break;
        default:
            break;
    }
    
    enemy->getEnemySprite()->runAction(RepeatForever::create(action));
}
void PatrolEnemyState::update(Enemy *enemy, float delta)
{
    
    switch (enemy->getEnemyType()) {
        case Enemy::EnemyType::ET_PATROL:
            updateNormalSkull(enemy,delta);
            break;
        
        default:
            break;
    }
   
}
void PatrolEnemyState::updateNormalSkull(Enemy *enemy, float delta)
{
    Vec2 velocity = enemy->getVelocity();
    Vec2 position = enemy->getPosition();
    enemy->setPosition(position + Vec2(velocity.x, 0));
}
void PatrolEnemyState::onExit(Enemy *enemy)
{
    if (enemy) {
        enemy->stopAllActions();
    }
}