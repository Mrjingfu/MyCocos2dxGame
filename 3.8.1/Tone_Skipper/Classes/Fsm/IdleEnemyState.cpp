//
//  IdleEnemyState.cpp
//  Tone_Skipper
//
//  Created by 创李 on 15/10/9.
//
//

#include "IdleEnemyState.h"
USING_NS_CC;
IdleEnemyState::IdleEnemyState()
{
    m_pEnemyStateType = Enemy::EnemyStateType::ES_IDLE;
    m_pDelayTime = 0.0f;
}
IdleEnemyState::~IdleEnemyState()
{
    
}
void IdleEnemyState::onEnter(Enemy *enemy)
{
    CCLOG("IdleEnemyState::onEnter");
    if(!enemy->getEnemySprite())
        return;

    enemy->setVelocity(Vec2::ZERO);
    Animate* action = nullptr;
    switch (enemy->getEnemyDirection()) {
        case Enemy::ED_LEFT:
        case Enemy::ED_RIGHT:
            action = Animate::create(enemy->getIdleAnimation());
            break;
        case Enemy::ED_BACK:
            break;
        default:
            break;
    }
    
    enemy->getEnemySprite()->runAction(RepeatForever::create(action));

}
void IdleEnemyState::update(Enemy *enemy, float delta)
{
    switch (enemy->getEnemyType()) {
        case Enemy::ET_ATTACK_PATROL:
            updateAttackPatrol(enemy, delta);
            break;
        case Enemy::ET_ATTACK:
            updateAttack(enemy, delta);
        default:
            break;
    }
    
}
void IdleEnemyState::updateAttack(Enemy *enemy, float delta)
{
    m_pDelayTime+=delta;
    if (m_pDelayTime>1.0f) {
        CCLOG("m_pDelayTime:%f",m_pDelayTime);
        enemy->setEnemyState(Enemy::EnemyStateType::ES_ATTACK);
        m_pDelayTime = 0.0f;
    }
}
void IdleEnemyState::updateAttackPatrol(Enemy *enemy,float delta)
{
    m_pDelayTime+=delta;
    if (m_pDelayTime>1.0f) {
        CCLOG("m_pDelayTime:%f",m_pDelayTime);
        enemy->setEnemyState(Enemy::EnemyStateType::ES_PATROL);
        m_pDelayTime = 0.0f;
    }
}
void IdleEnemyState::onExit(Enemy *enemy)
{
    CCLOG("IdleEnemyState::onExit");
    if (enemy)
        enemy->getEnemySprite()->stopAllActions();
    m_pDelayTime = 0.0f;
}