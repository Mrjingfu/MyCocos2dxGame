//
//  PatrolEnemy.cpp
//  Tone_Skipper
//
//  Created by 创李 on 15/10/8.
//
//

#include "AttackPatrolEnemy.h"
#include "EnemyState.h"
USING_NS_CC;
AttackPatrolEnemy::AttackPatrolEnemy()
{
    m_EnemyType = ET_ATTACK_PATROL;
}
AttackPatrolEnemy::~AttackPatrolEnemy()
{
    
}


bool AttackPatrolEnemy::loadModel()
{
    bool ret = true;
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shooter.plist");
    m_pSprite = HueSprite::createWithSpriteFrameName("shooter_idle1.png");
    if(!m_pSprite)
    {
        CCLOG("Nilo : Load model failed!");
        ret = false;
    }
    m_pSprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
    addChild(m_pSprite);
#if COCOS2D_DEBUG
    showDebug(true);
#endif
    return ret;
    return true;
}
bool AttackPatrolEnemy::loadAnimations()
{
    bool ret = true;
    ///superjump
    m_pIdleAnimation = cocos2d::AnimationCache::getInstance()->getAnimation("shooter_patrol_idle");
    if(!m_pIdleAnimation)
    {
        Vector<SpriteFrame*> arrayOfAnimation;
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("shooter_idle1.png");
        if(!frame)
            ret = false;
        arrayOfAnimation.pushBack(frame);
        
        m_pIdleAnimation = Animation::createWithSpriteFrames(arrayOfAnimation);
        if(!m_pIdleAnimation)
            ret = false;
        
        m_pIdleAnimation->setDelayPerUnit(0.2f / 1.0f);
        AnimationCache::getInstance()->addAnimation(m_pIdleAnimation, "shooter_patrol_idle");
    }
    
    
 
    m_pPatrolAnimation = cocos2d::AnimationCache::getInstance()->getAnimation("shooter_patrol_walk");
    if(!m_pPatrolAnimation)
    {
        cocos2d::Vector<cocos2d::SpriteFrame*> arrayOfAnimation;
        
        for (int i =1; i<7; i++) {
            cocos2d::SpriteFrame* frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(cocos2d::StringUtils::format("shooter_walk%d.png",i));
            if(!frame)
                ret = false;
            arrayOfAnimation.pushBack(frame);
        }
        
        m_pPatrolAnimation = cocos2d::Animation::createWithSpriteFrames(arrayOfAnimation);
        if(!m_pPatrolAnimation)
            ret = false;
        m_pPatrolAnimation->setDelayPerUnit(0.3f / 2.0f);
        cocos2d::AnimationCache::getInstance()->addAnimation(m_pPatrolAnimation, "shooter_patrol_walk");
    }
    
    m_pAttackAnimation = cocos2d::AnimationCache::getInstance()->getAnimation("shooter_patrol_attack");
    if(!m_pAttackAnimation)
    {
        cocos2d::Vector<cocos2d::SpriteFrame*> arrayOfAnimation;
        
        for (int i =1; i<4; i++) {
            cocos2d::SpriteFrame* frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(cocos2d::StringUtils::format("shooter_shoot%d.png",i));
            if(!frame)
                ret = false;
            arrayOfAnimation.pushBack(frame);
        }
        
        m_pAttackAnimation = cocos2d::Animation::createWithSpriteFrames(arrayOfAnimation);
        if(!m_pAttackAnimation)
            ret = false;
        m_pAttackAnimation->setDelayPerUnit(0.3f / 5.0f);
        cocos2d::AnimationCache::getInstance()->addAnimation(m_pAttackAnimation, "shooter_patrol_attack");
    }
    
    return true;
}
