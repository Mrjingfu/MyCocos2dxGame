//
//  WalkState.cpp
//  Tone_Skipper
//
//  Created by 创李 on 15/10/8.
//
//

#include "PatrolEnemyState.h"
#include "MapMgrs.h"
USING_NS_CC;
PatrolEnemyState::PatrolEnemyState()
{
    m_pEnemyStateType = Enemy::EnemyStateType::ES_PATROL;
    m_pDelayTime = 0.0f;
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
    m_Initpt = enemy->getPosition();
    enemy->getEnemySprite()->runAction(RepeatForever::create(action));
}
void PatrolEnemyState::update(Enemy *enemy, float delta)
{
    
    switch (enemy->getEnemyType()) {
        case Enemy::EnemyType::ET_PATROL:
            updatePatrol(enemy,delta);
            break;
        case Enemy::EnemyType::ET_ATTACK_PATROL:
            updateAttackPatrol(enemy,delta);
            break;
        case Enemy::EnemyType::ET_PURSUE:
            updatePursue(enemy, delta);
        default:
            break;
    }
   
}
void PatrolEnemyState::updatePatrol(Enemy *enemy, float delta)
{
    Vec2 velocity = enemy->getVelocity();
    Vec2 position = enemy->getPosition();
    enemy->setPosition(position + Vec2(velocity.x, 0));
}
void PatrolEnemyState::updateAttackPatrol(Enemy *enemy, float delta)
{
    Vec2 velocity = enemy->getVelocity();
    Vec2 position = enemy->getPosition();
    enemy->setPosition(position + Vec2(velocity.x, 0));
    if (m_Initpt.distanceSquared(enemy->getPosition()) > 60*60) {
        enemy->setEnemyState(Enemy::EnemyStateType::ES_ATTACK);
    }
}
void PatrolEnemyState::updatePursue(Enemy *enemy, float delta)
{
    Vec2 velocity = enemy->getVelocity();
    Vec2 enemyPt = enemy->getPosition();
    Vec2 ninoPt = MapMgrs::getInstance()->getNilo()->getPosition();
    enemy->setPosition(enemyPt + Vec2(velocity.x, 0));
    
    if (fabsf(enemyPt.x - ninoPt.x)<60) {
        
        Vec2 dir = ninoPt-enemyPt;
        dir.normalize();
        CCLOG("dir:%f",dir.x);
        if (dir.x > 0) {
            if (enemy->getEnemyDirection() ==Enemy::EnemyDirection::ED_LEFT ) {
                enemy->setEnemyDirection(Enemy::EnemyDirection::ED_RIGHT);
            }
        }else{
            if (enemy->getEnemyDirection() ==Enemy::EnemyDirection::ED_RIGHT ) {
                enemy->setEnemyDirection(Enemy::EnemyDirection::ED_LEFT);
            }
            
        }
        enemy->setEnemyState(Enemy::EnemyStateType::ES_PURSUE);
    }
    
    
}
void PatrolEnemyState::onExit(Enemy *enemy)
{
    if (enemy) {
        enemy->stopAllActions();
    }
}