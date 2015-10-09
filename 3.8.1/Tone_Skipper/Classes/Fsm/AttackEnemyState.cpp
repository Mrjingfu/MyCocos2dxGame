//
//  AttackState.cpp
//  Tone_Skipper
//
//  Created by 创李 on 15/10/9.
//
//

#include "AttackEnemyState.h"
#include "MapMgrs.h"
USING_NS_CC;
AttackEnemyState::AttackEnemyState()
{
    m_pEnemyStateType = Enemy::EnemyStateType::ES_ATTACK;
    m_pDelayTime = 0.0f;
}
AttackEnemyState::~AttackEnemyState()
{
    
}
void AttackEnemyState::onEnter(Enemy *enemy)
{
    if(!enemy->getEnemySprite())
        return;

    Animate* action = nullptr;
    switch (enemy->getEnemyDirection()) {
        case Enemy::ED_LEFT:
        case Enemy::ED_RIGHT:
            action = Animate::create(enemy->getAttackAnimation());
            break;
        case Enemy::ED_BACK:
            break;
        default:
            break;
    }
    
    enemy->getEnemySprite()->runAction(RepeatForever::create(action));

}
void AttackEnemyState::update(Enemy *enemy, float delta)
{
    m_pDelayTime+=delta;
    Vec2 pt = enemy->getPosition();
    cocos2d::Rect box = enemy->getBoundingBox();
    pt+= Vec2(box.getMaxX(), box.size.height*0.3);
    if (m_pDelayTime>=1.0f) {
        MapMgrs::getInstance()->createBullet(Bullet::BT_SIMPLE, Bullet::ActorBulletType::ABT_ENEMY, pt, Vec2::UNIT_X);
        enemy->setEnemyState(Enemy::EnemyStateType::ES_IDLE);
    }
}
void AttackEnemyState::onExit(Enemy *enemy)
{
    m_pDelayTime = 0.0f;
    if (enemy)
        enemy->stopAllActions();
}