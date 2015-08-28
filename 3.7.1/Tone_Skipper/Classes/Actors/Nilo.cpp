//
//  Nilo.cpp
//  Tone_Skipper
//
//  Created by wang haibo on 15/8/27.
//
//

#include "Nilo.h"
USING_NS_CC;

Nilo::Nilo()
{
    m_PlayerType = PT_NILO;
}
Nilo::~Nilo()
{
}
bool Nilo::loadModel()
{
    bool ret = true;
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_red.plist");
    m_pSprite = HueSprite::createWithSpriteFrameName("red_idle_01.png");
    if(!m_pSprite)
    {
        CCLOG("Bob : Load model failed!");
        ret = false;
    }
    addChild(m_pSprite);
    return ret;
}
bool Nilo::loadAnimations()
{
    bool ret = true;
    ///idle
    m_pIdleAnimation = AnimationCache::getInstance()->getAnimation("nilo_idle");
    if(!m_pIdleAnimation)
    {
        Vector<SpriteFrame*> arrayOfAnimation;
        SpriteFrame* frame = nullptr;
        for (int i = 0; i<10; i++) {
            frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("red_idle_01.png");
            if(!frame)
                ret = false;
            arrayOfAnimation.pushBack(frame);
        }
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("red_idle_01.png");
        if(!frame)
            ret = false;
        arrayOfAnimation.pushBack(frame);
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("red_idle_02.png");
        if(!frame)
            ret = false;
        arrayOfAnimation.pushBack(frame);
        
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("red_idle_01.png");
        if(!frame)
            ret = false;
        arrayOfAnimation.pushBack(frame);
        
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("red_idle_02.png");
        if(!frame)
            ret = false;
        arrayOfAnimation.pushBack(frame);
        
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("red_idle_01.png");
        if(!frame)
            ret = false;
        arrayOfAnimation.pushBack(frame);
        m_pIdleAnimation = Animation::createWithSpriteFrames(arrayOfAnimation);
        if(!m_pIdleAnimation)
            ret = false;
        
        m_pIdleAnimation->setDelayPerUnit(3.0f / 15.0f);
        AnimationCache::getInstance()->addAnimation(m_pIdleAnimation, "nilo_idle");
    }
    ///run
    m_pRunAnimation = AnimationCache::getInstance()->getAnimation("nilo_run");
    if(!m_pRunAnimation)
    {
        Vector<SpriteFrame*> arrayOfAnimation;
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("red_run_01.png");
        if(!frame)
            ret = false;
        arrayOfAnimation.pushBack(frame);
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("red_run_02.png");
        if(!frame)
            ret = false;
        arrayOfAnimation.pushBack(frame);
        m_pRunAnimation = Animation::createWithSpriteFrames(arrayOfAnimation);
        if(!m_pRunAnimation)
            ret = false;
        
        m_pRunAnimation->setDelayPerUnit(0.3f / 2.0f);
        AnimationCache::getInstance()->addAnimation(m_pRunAnimation, "nilo_run");
    }
    ///jump
    m_pJumpAnimation = AnimationCache::getInstance()->getAnimation("nilo_jump");
    if(!m_pJumpAnimation)
    {
        Vector<SpriteFrame*> arrayOfAnimation;
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("red_jump.png");
        if(!frame)
            ret = false;
        arrayOfAnimation.pushBack(frame);
        
        m_pJumpAnimation = Animation::createWithSpriteFrames(arrayOfAnimation);
        if(!m_pJumpAnimation)
            ret = false;
        
        m_pJumpAnimation->setDelayPerUnit(0.2f / 1.0f);
        m_pJumpAnimation->setRestoreOriginalFrame(true);
        AnimationCache::getInstance()->addAnimation(m_pJumpAnimation, "nilo_jump");
    }
    ///superjump
    m_pSuperJumpAnimation = AnimationCache::getInstance()->getAnimation("nilo_superjump");
    if(!m_pSuperJumpAnimation)
    {
        Vector<SpriteFrame*> arrayOfAnimation;
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("red_superjump.png");
        if(!frame)
            ret = false;
        arrayOfAnimation.pushBack(frame);
        
        m_pSuperJumpAnimation = Animation::createWithSpriteFrames(arrayOfAnimation);
        if(!m_pSuperJumpAnimation)
            ret = false;
        
        m_pSuperJumpAnimation->setDelayPerUnit(0.2f / 1.0f);
        m_pSuperJumpAnimation->setRestoreOriginalFrame(true);
        AnimationCache::getInstance()->addAnimation(m_pSuperJumpAnimation, "nilo_superjump");
    }
    if(!ret)
        CCLOG("Bob : Load animations failed!");
    return ret;
}

void Nilo::onLeftBtnPressed()
{
    setPlayerDirection(PD_LEFT);
    setPlayerState(PS_RUN);
}
void Nilo::onLeftBtnReleased()
{
    setPlayerDirection(PD_LEFT);
    setPlayerState(PS_IDLE);
}
void Nilo::onUpBtnPressed()
{
}
void Nilo::onUpBtnReleased()
{
}

void Nilo::onRightBtnPressed()
{
    setPlayerDirection(PD_RIGHT);
    setPlayerState(PS_RUN);
}
void Nilo::onRightBtnReleased()
{
    setPlayerDirection(PD_RIGHT);
    setPlayerState(PS_IDLE);
}

void Nilo::onDownBtnPressed()
{
}
void Nilo::onDownBtnReleased()
{
}

void Nilo::onABtnPressed()
{
}
void Nilo::onABtnReleased()
{
}

void Nilo::onBBtnPressed()
{
    if(getPlayerState() == PS_JUMP)
        setPlayerState(PS_SUPERJUMP);
    else
        setPlayerState(PS_JUMP);
}
void Nilo::onBBtnReleased()
{
}