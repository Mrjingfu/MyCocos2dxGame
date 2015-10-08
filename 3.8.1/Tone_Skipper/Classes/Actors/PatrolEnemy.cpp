//
//  PatrolEnemy.cpp
//  Tone_Skipper
//
//  Created by 创李 on 15/10/8.
//
//

#include "PatrolEnemy.h"
USING_NS_CC;
PatrolEnemy::PatrolEnemy()
{
    m_EnemyType = ET_NORMAL_SKULL;
}
PatrolEnemy::~PatrolEnemy()
{
    
}


bool PatrolEnemy::loadModel()
{
    bool ret = true;
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("basic_zombie.plist");
    m_pSprite = HueSprite::createWithSpriteFrameName("basic_zombie_idle1.png");
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
bool PatrolEnemy::loadAnimations()
{
    bool ret = true;
    ///superjump
    m_pIdleAnimation = cocos2d::AnimationCache::getInstance()->getAnimation("skull_idle");
    if(!m_pIdleAnimation)
    {
        Vector<SpriteFrame*> arrayOfAnimation;
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("basic_zombie_idle1.png");
        if(!frame)
            ret = false;
        arrayOfAnimation.pushBack(frame);
        
        m_pIdleAnimation = Animation::createWithSpriteFrames(arrayOfAnimation);
        if(!m_pIdleAnimation)
            ret = false;
        
        m_pIdleAnimation->setDelayPerUnit(0.2f / 1.0f);
        AnimationCache::getInstance()->addAnimation(m_pIdleAnimation, "skull_idle");
    }
    
    
    ///run
    m_pWalkAnimation = cocos2d::AnimationCache::getInstance()->getAnimation("skull_walk");
    if(!m_pWalkAnimation)
    {
        cocos2d::Vector<cocos2d::SpriteFrame*> arrayOfAnimation;
        
        for (int i =1; i<7; i++) {
            cocos2d::SpriteFrame* frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(cocos2d::StringUtils::format("basic_zombie_walk%d.png",i));
            if(!frame)
                ret = false;
            arrayOfAnimation.pushBack(frame);
        }
        
        m_pWalkAnimation = cocos2d::Animation::createWithSpriteFrames(arrayOfAnimation);
        if(!m_pWalkAnimation)
            ret = false;
        m_pWalkAnimation->setDelayPerUnit(0.3f / 5.0f);
        cocos2d::AnimationCache::getInstance()->addAnimation(m_pWalkAnimation, "skull_walk");
    }
    return true;
}

void PatrolEnemy::onLand()
{
    switch (getEnemyDirection()) {
        case Enemy::ED_LEFT:
            setEnemyDirection(ED_RIGHT);
            break;
        case Enemy::ED_RIGHT:
           setEnemyDirection(ED_LEFT);
            break;
        case Enemy::ED_BACK:
            break;
        default:
            break;
    }

}
void PatrolEnemy::onCollision()
{
    switch (getEnemyDirection()) {
        case Enemy::ED_LEFT:
            setEnemyDirection(ED_RIGHT);
            break;
        case Enemy::ED_RIGHT:
            setEnemyDirection(ED_LEFT);
            break;
        case Enemy::ED_BACK:
            break;
        default:
            break;
    }
}