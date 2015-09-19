//
//  Player.cpp
//  Tone_Skipper
//
//  Created by wang haibo on 15/8/26.
//
//

#include "Player.h"
#include "MapMgrs.h"
USING_NS_CC;

Player::Player()
{
    m_fMaxXSpeed = 0.8f;
    m_fMaxYSpeed = 2.7f;
    
    m_pIdleAnimation        = nullptr;
    m_pRunAnimation         = nullptr;
    m_pJumpAnimation        = nullptr;
    m_pSuperJumpAnimation   = nullptr;
    m_pShakeHeadAnimation   = nullptr;
    m_pTurnBackAnimation    = nullptr;
    m_pBackIdleAnimation    = nullptr;
    m_pBackFireRunAnimation     = nullptr;
    m_pBackJumpAnimation        = nullptr;
    m_pBackSuperJumpAnimation   = nullptr;
    m_pBackForwardRunAnimation  = nullptr;
    m_pSquatAnimation           = nullptr;
    
    m_PlayerType = PT_UNKNOWN;
    m_PlayerState = PS_UNKNOWN;
    m_PlayerDirection = PD_RIGHT;
    m_PlayerLastDirection = PD_RIGHT;
    
    m_bAcceptInput = true;
    m_bEquipedGun = false;
    
    m_bLeftBtnPressed   = false;
    m_bRightBtnPressed  = false;
    m_bUpBtnPressed     = false;
    m_bDownBtnPressed   = false;
}
Player::~Player()
{
}
void Player::update(float delta)
{
    if(!isVisible())
        return;
    if(!m_pSprite)
        return;
    if(!m_bOnLadder)
    {
        if(!m_bOnLand)
            m_Velocity += Vec2(0, Gravity)*delta;
        if(m_Velocity.y <= -m_fMaxYSpeed)
            m_Velocity.y = -m_fMaxYSpeed;
    }
    else
        checkOnLadder();
    
    updatePosition(delta);
    
    checkTriggers();
    
#if COCOS2D_DEBUG
    showDebug(true);
#endif
}
void Player::updatePosition(float delta)
{
    cocos2d::Rect rect = getBoundingBox();
    Vec2 nextPosY = getPosition() + Vec2(0,m_Velocity.y);
    rect.origin += nextPosY;
    
    Actor::RAYCAST_TYPE type = Actor::RT_UNKNOWN;
    bool raycast = MapMgrs::getInstance()->checkRayCast(rect, m_Velocity, type, m_bOnLand);
    if(raycast)
    {
        if(m_bOnLand == false)
        {
            m_bOnLand = true;
            if(m_Velocity.y < 1)
                m_bOnLadder = false;
            this->onLand();
            if(!m_bOnLadder)
            {
                if(m_Velocity.y > m_fMaxYSpeed)
                    m_Velocity.y = m_fMaxYSpeed*delta;
            }
            else
                setPlayerState(PS_BACKFORWARDRUN);
        }
        else
        {
            if(!m_bOnLadder)
            {
                if(m_Velocity.y < 0)
                    m_Velocity.y = 0;
            }
        }
    }
    else
    {
        if(m_bOnLand)
            m_bOnLand = false;
    }
  
    setPosition(getPosition() + Vec2(0,m_Velocity.y));
    if(m_bOnLadder)
        return;
    rect = getBoundingBox();
    Vec2 nextPosX = getPosition() + Vec2(m_Velocity.x, 0);
    rect.origin += nextPosX;
    
    int collisionFlag = MapMgrs::CF_NONE;
    bool collision = MapMgrs::getInstance()->checkCollision(rect, m_Velocity, collisionFlag);
    if(collision)
    {
        if((collisionFlag & MapMgrs::CF_RIGHT) != 0 )
        {
            if(m_Velocity.x > 0)
                m_Velocity.x = 0;
            else if(m_Velocity.x < 0)
            {
                setPosition(getPosition() + Vec2(m_Velocity.x, 0));
                m_Velocity.x = 0;
            }
        }
        else if((collisionFlag & MapMgrs::CF_LEFT) != 0 )
        {
            if(m_Velocity.x < 0)
                m_Velocity.x = 0;
            else if(m_Velocity.x > 0)
            {
                setPosition(getPosition() + Vec2(m_Velocity.x, 0));
                m_Velocity.x = 0;
            }
        }
        if((collisionFlag & MapMgrs::CF_BOUND) != 0)
            m_Velocity.x = 0;
    }
    else
    {
        if((collisionFlag & MapMgrs::CF_BOUND) == 0)
        {
            if(m_bRightBtnPressed && getPlayerState() != PS_SQUAT )
                m_Velocity.x = m_fMaxXSpeed;
            else if(m_bLeftBtnPressed && getPlayerState() != PS_SQUAT)
                m_Velocity.x = -m_fMaxXSpeed;
        }
    }
    setPosition(getPosition() + Vec2(m_Velocity.x, 0));
}
void Player::checkTriggers()
{
    cocos2d::Rect rect = getBoundingBox();
    rect.origin += getPosition();
    Actor::TRIGGER_TYPE type = Actor::TT_UNKNOWN;
    bool collision = MapMgrs::getInstance()->checkTrigger(rect, type);
    if(collision)
    {
        switch (type) {
            case Actor::TT_ROOM:
                 MapMgrs::getInstance()->hideCoverLayer();
                break;
            default:
                break;
        }
    }
    else
        MapMgrs::getInstance()->showCoverLayer();
}
void Player::checkOnLadder()
{
    cocos2d::Rect rect = getBoundingBox();
    rect.origin += getPosition();
    Actor::USABLE_ITEM_TYPE type = Actor::UIT_UNKNOWN;
    bool available = MapMgrs::getInstance()->checkUsableItems(rect, type);
    if(!available)
    {
        if(m_PlayerDirection == PD_BACK)
        {
            setPlayerState(PS_TURNFRONT);
            m_bOnLadder = false;
        }
    }
}
void Player::setPlayerState(PlayerState state)
{
    if (m_PlayerState == state)
        return;
    
    ///处理上一个状态退出逻辑
    switch (m_PlayerState) {
        case PS_IDLE:
            onExitIdleState();
            break;
        case PS_RUN:
            onExitRunState();
            break;
        case PS_JUMP:
            onExitJumpState();
            break;
        case PS_SUPERJUMP:
            onExitSuperJumpState();
            break;
        case PS_SHAKEHEAD:
            onExitShakeHead();
            break;
        case PS_TURNBACK:
            onExitTurnBackState();
            break;
        case PS_TURNFRONT:
            onExitTurnFrontState();
            break;
        case PS_BACKFORWARDRUN:
            onExitBackforwardRunState();
            break;
        case PS_SQUAT:
            onExitSquatState();
            break;
        case PS_DEATH:
            onExitDeathState();
            break;
        default:
            break;
    }
    
    m_PlayerState = state;
    ///处理下一个状态进入逻辑
    switch (m_PlayerState) {
        case PS_IDLE:
            onEnterIdleState();
            break;
        case PS_RUN:
            onEnterRunState();
            break;
        case PS_JUMP:
            onEnterJumpState();
            break;
        case PS_SUPERJUMP:
            onEnterSuperJumpState();
            break;
        case PS_SHAKEHEAD:
            onEnterShakeHead();
            break;
        case PS_TURNBACK:
            onEnterTurnBackState();
            break;
        case PS_TURNFRONT:
            onEnterTurnFrontState();
            break;
        case PS_BACKFORWARDRUN:
            onEnterBackforwardRunState();
            break;
        case PS_SQUAT:
            onEnterSquatState();
            break;
        case PS_DEATH:
            onEnterDeathState();
            break;
        default:
            break;
    }
}
void Player::setPlayerDirection(PLayerDirection direction)
{
    if(m_PlayerDirection == direction)
        return;
    m_PlayerLastDirection = m_PlayerDirection;
    m_PlayerDirection = direction;
    if(m_PlayerDirection == PD_LEFT)
    {
        setFlipX(true);
        if(getPlayerState() == PS_RUN)
            m_Velocity.x = -m_fMaxXSpeed;
    }
    else if(m_PlayerDirection == PD_RIGHT)
    {
        setFlipX(false);
        if(getPlayerState() == PS_RUN)
            m_Velocity.x = m_fMaxXSpeed;
    }
}
void Player::onEnterIdleState()
{
    if(!m_pSprite)
        return;
    m_Velocity.x = 0;
    Animate* action = nullptr;
    switch (m_PlayerDirection) {
        case PD_LEFT:
        case PD_RIGHT:
            action = Animate::create(m_pIdleAnimation);
            m_pSprite->runAction(RepeatForever::create(Sequence::create(action, DelayTime::create(3.0f), NULL)));
            break;
        case PD_BACK:
            action = Animate::create(m_pBackIdleAnimation);
            m_pSprite->runAction(RepeatForever::create(action));
            break;
        default:
            break;
    }
}
void Player::onExitIdleState()
{
    m_pSprite->stopAllActions();
}

void Player::onEnterRunState()
{
    if(!m_pSprite)
        return;
    Animate* action = nullptr;
    switch (m_PlayerDirection) {
        case PD_LEFT:
            action = Animate::create(m_pRunAnimation);
            m_Velocity.x = -m_fMaxXSpeed;
            break;
        case PD_RIGHT:
            action = Animate::create(m_pRunAnimation);
            m_Velocity.x = m_fMaxXSpeed;
            break;
        case PD_BACK:
            action = Animate::create(m_pBackFireRunAnimation);
            break;
        default:
            break;
    }
    m_pSprite->runAction(RepeatForever::create(action));
}
void Player::onExitRunState()
{
    m_pSprite->stopAllActions();
}

void Player::onEnterJumpState()
{
    if(!m_pSprite)
        return;
    Animate* action = nullptr;
    switch (m_PlayerDirection) {
        case PD_LEFT:
        case PD_RIGHT:
            action = Animate::create(m_pJumpAnimation);
            break;
        case PD_BACK:
            action = Animate::create(m_pBackJumpAnimation);
            break;
        default:
            break;
    }
    m_Velocity.y = m_fMaxYSpeed;
    m_pSprite->runAction(action);
}
void Player::onExitJumpState()
{
    m_pSprite->stopAllActions();
}

void Player::onEnterSuperJumpState()
{
    if(!m_pSprite)
        return;
    Animate* action = nullptr;
    switch (m_PlayerDirection) {
        case PD_LEFT:
        case PD_RIGHT:
            action = Animate::create(m_pSuperJumpAnimation);
            break;
        case PD_BACK:
            action = Animate::create(m_pBackSuperJumpAnimation);
            break;
        default:
            break;
    }
    m_Velocity.y = m_fMaxYSpeed;
    m_pSprite->runAction(action);
}
void Player::onExitSuperJumpState()
{
    m_pSprite->stopAllActions();
}

void Player::onEnterShakeHead()
{
    if(!m_pSprite)
        return;
    m_Velocity.x = 0;
    Animate* action = Animate::create(m_pShakeHeadAnimation);
    CallFunc* callback = CallFunc::create(CC_CALLBACK_0(Player::setPlayerState, this, PS_IDLE));
    Sequence* sequence = Sequence::create(action, callback, NULL);
    m_pSprite->runAction(sequence);
}
void Player::onExitShakeHead()
{
    m_pSprite->stopAllActions();
}

void Player::onEnterTurnBackState()
{
    if(!m_pSprite)
        return;
    Animate* action = Animate::create(m_pTurnBackAnimation);
    CallFunc* callback1 = CallFunc::create(CC_CALLBACK_0(Player::setPlayerDirection, this, PD_BACK));
    CallFunc* callback2 = nullptr;
    if(m_bUpBtnPressed || m_bDownBtnPressed)
        callback2 = CallFunc::create(CC_CALLBACK_0(Player::setPlayerState, this, PS_BACKFORWARDRUN));
    else
        callback2 = CallFunc::create(CC_CALLBACK_0(Player::setPlayerState, this, PS_IDLE));
    Sequence* sequence = Sequence::create(action, callback1, callback2, NULL);
    m_pSprite->runAction(sequence);
}
void Player::onExitTurnBackState()
{
     m_pSprite->stopAllActions();
}

void Player::onEnterTurnFrontState()
{
    if(!m_pSprite)
        return;
    Animate* action = Animate::create(m_pTurnBackAnimation);
    CallFunc* callback1 = nullptr;
    if(m_PlayerLastDirection == PD_RIGHT)
        callback1 =CallFunc::create(CC_CALLBACK_0(Player::setPlayerDirection, this, PD_RIGHT));
    else if(m_PlayerLastDirection == PD_LEFT)
        callback1 =CallFunc::create(CC_CALLBACK_0(Player::setPlayerDirection, this, PD_LEFT));
    CallFunc* callback2 = CallFunc::create(CC_CALLBACK_0(Player::setPlayerState, this, PS_IDLE));
    Sequence* sequence = Sequence::create(action->reverse(), callback1, callback2, NULL);
    m_pSprite->runAction(sequence);

}
void Player::onExitTurnFrontState()
{
    m_pSprite->stopAllActions();
}
void Player::onEnterBackforwardRunState()
{
    if(!m_pSprite)
        return;
    if(m_bOnLadder)
    {
        if(m_bUpBtnPressed)
        {
            m_Velocity.y = m_fMaxYSpeed*0.2f;
            Animate* action = Animate::create(m_pBackForwardRunAnimation);
            m_pSprite->runAction(RepeatForever::create(action));
        }
        else if(m_bDownBtnPressed)
        {
            m_Velocity.y = -m_fMaxYSpeed*0.2f;
            Animate* action = Animate::create(m_pBackForwardRunAnimation);
            m_pSprite->runAction(RepeatForever::create(action));
        }
        else
        {
            m_Velocity.y = 0;
            setPlayerState(PS_IDLE);
        }
    }
}
void Player::onExitBackforwardRunState()
{
    if(m_bOnLadder)
        m_Velocity.y = 0;
    m_pSprite->stopAllActions();
}
void Player::onEnterSquatState()
{
    if(!m_pSprite)
        return;
    m_Velocity.x = 0;
    Animate* action = Animate::create(m_pSquatAnimation);
    m_pSprite->runAction(RepeatForever::create(action));
}
void Player::onExitSquatState()
{
    m_pSprite->stopAllActions();
}
void Player::onEnterDeathState()
{
    disableAcceptInput();
}
void Player::onExitDeathState()
{
    enableAcceptInput();
}
cocos2d::Rect Player::getBoundingBox() const
{
    cocos2d::Rect spriteRect;
    if (m_pSprite) {
        switch (m_PlayerType) {
            case PT_NILO:
                spriteRect = m_pSprite->getBoundingNiloBox();
                break;
            case PT_PUDGE:
                spriteRect = m_pSprite->getBoundingPudgeBox();
                break;
            default:
                spriteRect = m_pSprite->getBoundingBox();
                break;
        }
    }
    return spriteRect;
}