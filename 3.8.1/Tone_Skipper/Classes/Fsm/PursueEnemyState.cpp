//
//  PursueEnemyState.cpp
//  Tone_Skipper
//
//  Created by 创李 on 15/10/12.
//
//

#include "PursueEnemyState.h"
#include "MapMgrs.h"
USING_NS_CC;
PursueEnemyState::PursueEnemyState()
{
    m_pEnemyStateType = Enemy::EnemyStateType::ES_PURSUE;
}
PursueEnemyState::~PursueEnemyState()
{
    
}

void PursueEnemyState::onEnter(Enemy *enemy)
{
    if(!enemy->getEnemySprite())
        return;
    if (!enemy->getPatrolAnimation()) {
        return;
    }
    enemy->setMaxXSpeed(0.5f);
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

void PursueEnemyState::update(Enemy *enemy, float delta)
{
    Vec2 velocity = enemy->getVelocity();
    Vec2 enemyPt = enemy->getPosition();
    Vec2 ninoPt = MapMgrs::getInstance()->getNilo()->getPosition();
    if (fabsf(enemyPt.x - ninoPt.x) >35 )
    {
        Vec2 dir = ninoPt-enemyPt;
        dir.normalize();
        CCLOG("dir:%f",dir.x);
        if (dir.x > 0) {
            if (enemy->getEnemyDirection() ==Enemy::EnemyDirection::ED_LEFT ) {
                enemy->setEnemyDirection(Enemy::EnemyDirection::ED_RIGHT);
                enemy->setVelocity(Vec2(enemy->getMaxXSpeed(), velocity.y));
            }
        }else{
            if (enemy->getEnemyDirection() ==Enemy::EnemyDirection::ED_RIGHT ) {
                enemy->setEnemyDirection(Enemy::EnemyDirection::ED_LEFT);
                enemy->setVelocity(Vec2(-enemy->getMaxXSpeed(), velocity.y));
            }
            
        }
    }
        enemy->setPosition(enemyPt + velocity);
    
    }

void PursueEnemyState::onExit(Enemy *enemy)
{
    if (enemy) {
        enemy->getEnemySprite()->stopAllActions();
    }
}
