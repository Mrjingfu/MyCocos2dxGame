//
//  WalkState.cpp
//  Tone_Skipper
//
//  Created by 创李 on 15/10/8.
//
//

#include "WalkState.h"

USING_NS_CC;
WalkState::WalkState()
{
    m_pEnemyStateType = Enemy::EnemyStateType::ES_PATROL;
}
WalkState::~WalkState()
{
    
}
void WalkState::onEnter(Enemy * enemy)
{
    if(!enemy->getEnemySprite())
        return;
    Animate* action = nullptr;
    float maxXSpeed = enemy->getMaxXSpeed();
    switch (enemy->getEnemyDirection()) {
        case Enemy::ED_LEFT:
            action = Animate::create(enemy->getWalkAnimation());
            enemy->setVelocity(Vec2(-maxXSpeed, 0));
            break;
        case Enemy::ED_RIGHT:
            action = Animate::create(enemy->getWalkAnimation());
            enemy->setVelocity(Vec2(maxXSpeed, 0));
            break;
        case Enemy::ED_BACK:
            break;
        default:
            break;
    }
    
    enemy->getEnemySprite()->runAction(RepeatForever::create(action));
}
void WalkState::update(Enemy *enemy, float delta)
{
    Vec2 velocity = enemy->getVelocity();
    Vec2 position = enemy->getPosition();
    //CCLOG("position(%f,%f) velocity(%f,%f)",position.x,position.y,velocity.x,velocity.y);
    enemy->setPosition(position + Vec2(velocity.x, 0));
}
void WalkState::onExit(Enemy *enemy)
{
    if (enemy) {
        enemy->stopAllActions();
    }
}