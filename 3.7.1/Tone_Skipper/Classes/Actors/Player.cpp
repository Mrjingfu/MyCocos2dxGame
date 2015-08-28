//
//  Player.cpp
//  Tone_Skipper
//
//  Created by wang haibo on 15/8/26.
//
//

#include "Player.h"
USING_NS_CC;

Player::Player()
{
    m_pIdleAnimation        = nullptr;
    m_pRunAnimation         = nullptr;
    m_pJumpAnimation        = nullptr;
    m_pSuperJumpAnimation   = nullptr;
    
    m_PlayerType = PT_UNKNOWN;
    m_PlayerState = PS_UNKNOWN;
    m_PlayerDirection = PD_LEFT;
}
Player::~Player()
{
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
        case PS_TURNBACK:
            onExitTurnBackState();
            break;
        case PS_TURNFRONT:
            onExitTurnFrontState();
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
        case PS_TURNBACK:
            onEnterTurnBackState();
            break;
        case PS_TURNFRONT:
            onEnterTurnFrontState();
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
    m_PlayerDirection = direction;
    if(m_PlayerDirection == PD_LEFT)
        m_pSprite->setFlippedX(true);
    else if(m_PlayerDirection == PD_RIGHT)
        m_pSprite->setFlippedX(false);
}
void Player::onEnterIdleState()
{
    if(!m_pSprite)
        return;
    Animate* action = nullptr;
    switch (m_PlayerDirection) {
        case PD_LEFT:
        case PD_RIGHT:
            action = Animate::create(m_pIdleAnimation);
            break;
        default:
            break;
    }
    m_pSprite->runAction(RepeatForever::create(Sequence::create(action, DelayTime::create(3.0f), NULL)));
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
        case PD_RIGHT:
            action = Animate::create(m_pRunAnimation);
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
        default:
            break;
    }
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
        default:
            break;
    }
    m_pSprite->runAction(action);
}
void Player::onExitSuperJumpState()
{
    m_pSprite->stopAllActions();
}

void Player::onEnterTurnBackState()
{
}
void Player::onExitTurnBackState()
{
}

void Player::onEnterTurnFrontState()
{
}
void Player::onExitTurnFrontState()
{
}

void Player::onEnterDeathState()
{
}
void Player::onExitDeathState()
{
}