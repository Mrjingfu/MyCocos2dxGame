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
    CCLOG("AttackEnemyState::onEnter");
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
    CCLOG("action time:%f",action->getAnimation()->getDuration());
    enemy->getEnemySprite()->runAction(RepeatForever::create(action));

}
void AttackEnemyState::update(Enemy *enemy, float delta)
{
    m_pDelayTime+=delta;
    Vec2 pt = enemy->getPosition();
    cocos2d::Rect box = enemy->getBoundingBox();

    Vec2 rightpt = Vec2(box.getMaxX(), box.size.height*0.3) + pt;
    Vec2 leftpt = Vec2(box.getMinX(), box.size.height*0.3)+ pt;
    
    if (m_pDelayTime>=enemy->getAttackAnimation()->getDuration()*0.5) {
        if (enemy->getEnemyDirection() == Enemy::ED_LEFT) {
            
            MapMgrs::getInstance()->createBullet(Bullet::BT_SIMPLE, Bullet::ActorBulletType::ABT_ENEMY, leftpt, Vec2(-1, 0),1.5f);
        }else if(enemy->getEnemyDirection() == Enemy::ED_RIGHT){
            
            MapMgrs::getInstance()->createBullet(Bullet::BT_SIMPLE, Bullet::ActorBulletType::ABT_ENEMY, rightpt, Vec2::UNIT_X,1.5f);
        }
        enemy->setEnemyState(Enemy::EnemyStateType::ES_IDLE);
    }
}
void AttackEnemyState::onExit(Enemy *enemy)
{
    CCLOG("AttackEnemyState::onExit");
    m_pDelayTime = 0.0f;
    if (enemy)
        enemy->getEnemySprite()->stopAllActions();
}