//
//  Player.h
//  Tone_Skipper
//
//  Created by wang haibo on 15/8/26.
//
//

#ifndef __Tone_Skipper__Player__
#define __Tone_Skipper__Player__

#include "Actor.h"
#include "JoyStick.h"
class Player : public Actor, public JoystickListener
{
public:
    typedef enum {
        PT_NILO = 0,
        PT_PUDGE,
        PT_LEA,
        PT_UNKNOWN
    } PlayerType;
    
    typedef enum {
        PS_IDLE = 0,
        PS_RUN,
        PS_JUMP,
        PS_SUPERJUMP,
        PS_TURNBACK,
        PS_TURNFRONT,
        PS_DEATH,
        PS_UNKNOWN
    } PlayerState;
    
    typedef enum {
        PD_LEFT = 0,
        PD_RIGHT,
        PD_BACK,
        PD_UNKNOWN
    } PLayerDirection;
protected:
    Player();
    virtual ~Player();
    
    virtual void onEnterIdleState();
    virtual void onExitIdleState();
    
    virtual void onEnterRunState();
    virtual void onExitRunState();
    
    virtual void onEnterJumpState();
    virtual void onExitJumpState();
    
    virtual void onEnterSuperJumpState();
    virtual void onExitSuperJumpState();
    
    virtual void onEnterTurnBackState();
    virtual void onExitTurnBackState();
    
    virtual void onEnterTurnFrontState();
    virtual void onExitTurnFrontState();
    
    virtual void onEnterDeathState();
    virtual void onExitDeathState();
public:
    PlayerType getPlayerType() const { return m_PlayerType; }
    PlayerState getPlayerState() const { return m_PlayerState; }
    void setPlayerState(PlayerState state);
    PLayerDirection getPlayerDirection() const { return m_PlayerDirection; }
    void setPlayerDirection(PLayerDirection direction);
protected:
    cocos2d::Animation*       m_pIdleAnimation;
    cocos2d::Animation*       m_pRunAnimation;
    cocos2d::Animation*       m_pJumpAnimation;
    cocos2d::Animation*       m_pSuperJumpAnimation;
    cocos2d::Animation*       m_pShakeHeadAnimation;
    cocos2d::Animation*       m_pTurnBackAnimation;
    cocos2d::Animation*       m_pTurnFrontAnimation;
    
    PlayerType                  m_PlayerType;
    PlayerState                 m_PlayerState;
    PLayerDirection             m_PlayerDirection;
};

#endif /* defined(__Tone_Skipper__Player__) */
