//
//  Dog.cpp
//  Tone_Skipper
//
//
//

#include "Pudge.h"
USING_NS_CC;

Pudge::Pudge()
{
    m_PlayerType = PT_PUDGE;
}
Pudge::~Pudge()
{
}
bool Pudge::loadModel()
{
    bool ret = true;
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_dog.plist");
    m_pSprite = HueSprite::createWithSpriteFrameName("dog_idle_01.png");
    if(!m_pSprite)
    {
        CCLOG("dog : Load model failed!");
        ret = false;
    }
    CCLOG("width:%f,height:%f",getBoundingBox().size.width,getBoundingBox().size.height);
    m_pSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    addChild(m_pSprite);
#if COCOS2D_DEBUG
    showDebug(true);
#endif
    return ret;
}

bool Pudge::loadAnimations()
{
    bool ret = true;
    ///idle
    m_pIdleAnimation = AnimationCache::getInstance()->getAnimation("pudge_idle");
    if(!m_pIdleAnimation)
    {
        Vector<SpriteFrame*> arrayOfAnimation;
        SpriteFrame* frame = nullptr;
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dog_idle_01.png");
        if(!frame)
            ret = false;
        arrayOfAnimation.pushBack(frame);
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dog_idle_02.png");
        if(!frame)
            ret = false;
        arrayOfAnimation.pushBack(frame);
        
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dog_idle_01.png");
        if(!frame)
            ret = false;
        arrayOfAnimation.pushBack(frame);
        
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dog_idle_02.png");
        if(!frame)
            ret = false;
        arrayOfAnimation.pushBack(frame);

        m_pIdleAnimation = Animation::createWithSpriteFrames(arrayOfAnimation);
        if(!m_pIdleAnimation)
            ret = false;
        
        m_pIdleAnimation->setDelayPerUnit(3.0f / 15.0f);
        AnimationCache::getInstance()->addAnimation(m_pIdleAnimation, "pudge_idle");
    }
    ///run
    m_pRunAnimation = AnimationCache::getInstance()->getAnimation("pudge_run");
    if(!m_pRunAnimation)
    {
        Vector<SpriteFrame*> arrayOfAnimation;
        
        for (int i =1; i<8; i++) {
            SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("dog_run_0%d.png",i));
            if(!frame)
                ret = false;
            arrayOfAnimation.pushBack(frame);
        }
        
        m_pRunAnimation = Animation::createWithSpriteFrames(arrayOfAnimation);
        if(!m_pRunAnimation)
            ret = false;
        m_pRunAnimation->setDelayPerUnit(0.3f / 7.0f);
        AnimationCache::getInstance()->addAnimation(m_pRunAnimation, "pudge_run");
    }
    ///jump
    m_pJumpAnimation = AnimationCache::getInstance()->getAnimation("pugde_jump");
    if(!m_pJumpAnimation)
    {
        Vector<SpriteFrame*> arrayOfAnimation;
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dog_jump.png");
        if(!frame)
            ret = false;
        arrayOfAnimation.pushBack(frame);
        
        m_pJumpAnimation = Animation::createWithSpriteFrames(arrayOfAnimation);
        if(!m_pJumpAnimation)
            ret = false;
        
        m_pJumpAnimation->setDelayPerUnit(0.2f / 3.0f);
        AnimationCache::getInstance()->addAnimation(m_pJumpAnimation, "pugde_jump");
    }
    ///superjump
    m_pSuperJumpAnimation = AnimationCache::getInstance()->getAnimation("pugde_superjump");
    if(!m_pSuperJumpAnimation)
    {
        Vector<SpriteFrame*> arrayOfAnimation;
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dog_superjump.png");
        if(!frame)
            ret = false;
        arrayOfAnimation.pushBack(frame);
        
        m_pSuperJumpAnimation = Animation::createWithSpriteFrames(arrayOfAnimation);
        if(!m_pSuperJumpAnimation)
            ret = false;
        
        m_pSuperJumpAnimation->setDelayPerUnit(0.2f / 1.0f);
        AnimationCache::getInstance()->addAnimation(m_pSuperJumpAnimation, "pugde_superjump");
    }
    
    Animation* m_pFireAnimation = AnimationCache::getInstance()->getAnimation("pugde_fire");
    if(!m_pBackFireRunAnimation)
    {
        Vector<SpriteFrame*> arrayOfAnimation;
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dog_call_01.png");
        if(!frame)
            ret = false;
        arrayOfAnimation.pushBack(frame);
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dog_call_02.png");
        if(!frame)
            ret = false;
        arrayOfAnimation.pushBack(frame);
        m_pBackFireRunAnimation = Animation::createWithSpriteFrames(arrayOfAnimation);
        if(!m_pBackFireRunAnimation)
            ret = false;
        
        m_pBackFireRunAnimation->setDelayPerUnit(0.3f / 2.0f);
        AnimationCache::getInstance()->addAnimation(m_pBackFireRunAnimation, "pugde_fire");
    }
    if(!ret)
        CCLOG("Pudge : Load animations failed!");
    return ret;
}
void Pudge::onLand()
{
    if(getPlayerDirection() != PD_BACK)
    {
        if(m_bLeftBtnPressed || m_bRightBtnPressed)
            setPlayerState(PS_RUN);
        else
        {
            if(!m_bDownBtnPressed)
                setPlayerState(PS_IDLE);
        }
    }
}
void Pudge::onLeftBtnPressed()
{
    if(!m_bAcceptInput)
        return;
    m_bLeftBtnPressed = true;
    if(getPlayerDirection() != PD_BACK)
        setPlayerDirection(PD_LEFT);
    setPlayerState(PS_RUN);
}
void Pudge::onLeftBtnReleased()
{
    if(!m_bAcceptInput)
        return;
    m_bLeftBtnPressed = false;
    if(m_bOnLand)
    {
        if(!m_bRightBtnPressed)
            setPlayerState(PS_IDLE);
        else
            setPlayerDirection(PD_RIGHT);
    }
    else
    {
        if(m_bRightBtnPressed)
            setPlayerDirection(PD_RIGHT);
    }
}
void Pudge::onUpBtnPressed()
{

}
void Pudge::onUpBtnReleased()
{

    
}

void Pudge::onRightBtnPressed()
{
    if(!m_bAcceptInput)
        return;
    m_bRightBtnPressed = true;
    if(getPlayerDirection() != PD_BACK)
        setPlayerDirection(PD_RIGHT);
    setPlayerState(PS_RUN);
}
void Pudge::onRightBtnReleased()
{
    if(!m_bAcceptInput)
        return;
    m_bRightBtnPressed = false;
    if(m_bOnLand)
    {
        if(!m_bLeftBtnPressed)
            setPlayerState(PS_IDLE);
        else
            setPlayerDirection(PD_LEFT);
    }
    else
    {
        if(m_bLeftBtnPressed)
            setPlayerDirection(PD_LEFT);
    }
}

void Pudge::onABtnPressed()
{
    if(!m_bAcceptInput)
        return;
}
void Pudge::onABtnReleased()
{
    if(!m_bAcceptInput)
        return;
}

void Pudge::onBBtnPressed()
{
    if(!m_bAcceptInput)
        return;
    if(getPlayerState() == PS_SUPERJUMP)
        return;
    if(getPlayerState() == PS_JUMP)
        setPlayerState(PS_SUPERJUMP);
    else if(m_bOnLand)
        setPlayerState(PS_JUMP);
}
void Pudge::onBBtnReleased()
{
    if(!m_bAcceptInput)
        return;
}