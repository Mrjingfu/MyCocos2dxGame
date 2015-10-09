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
        PS_SHAKEHEAD,
        PS_TURNBACK,
        PS_TURNFRONT,
        PS_BACKFORWARDRUN,
        PS_SQUAT,
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
    
    virtual void onEnterShakeHead();
    virtual void onExitShakeHead();
    
    virtual void onEnterTurnBackState();
    virtual void onExitTurnBackState();
    
    virtual void onEnterTurnFrontState();
    virtual void onExitTurnFrontState();
    
    virtual void onEnterBackforwardRunState();
    virtual void onExitBackforwardRunState();
    
    virtual void onEnterSquatState();
    virtual void onExitSquatState();
    
    virtual void onEnterDeathState();
    virtual void onExitDeathState();
    
    virtual void onEquipedGun() {};
    virtual void onUnloadGun() {};
    
    virtual cocos2d::Rect getBoundingBox() const override;
public:
    virtual void update(float delta) override;
    
    PlayerType getPlayerType() const { return m_PlayerType; }
    PlayerState getPlayerState() const { return m_PlayerState; }
    void setPlayerState(PlayerState state);
    PLayerDirection getPlayerDirection() const { return m_PlayerDirection; }
    void setPlayerDirection(PLayerDirection direction);
    PLayerDirection getPlayerLastDirection() const { return m_PlayerLastDirection;}
    
    bool isInShadow() const { return m_bInShadow; }
    void setInShadow(bool inShadow) { m_bInShadow = inShadow; }
    
    void disableAcceptInput() { m_bAcceptInput = false; }
    void enableAcceptInput() { m_bAcceptInput = true; }
    
    void equipGun() { m_bEquipedGun = true; }
    void unloadGun() { m_bEquipedGun = false; }
private:
    void updatePosition(float delta);
    void checkTriggers();
    void checkOnLadder();
    void checkInShadow();
   
    void fadeInShadow();
    void fadeOutShadow();
protected:
    cocos2d::Animation*       m_pIdleAnimation;
    cocos2d::Animation*       m_pRunAnimation;
    cocos2d::Animation*       m_pJumpAnimation;
    cocos2d::Animation*       m_pSuperJumpAnimation;
    cocos2d::Animation*       m_pShakeHeadAnimation;
    cocos2d::Animation*       m_pTurnBackAnimation;
    cocos2d::Animation*       m_pBackIdleAnimation;
    cocos2d::Animation*       m_pBackFireRunAnimation;
    cocos2d::Animation*       m_pBackJumpAnimation;
    cocos2d::Animation*       m_pBackSuperJumpAnimation;
    cocos2d::Animation*       m_pBackForwardRunAnimation;
    cocos2d::Animation*       m_pSquatAnimation;
    
    PlayerType                  m_PlayerType;
    PlayerState                 m_PlayerState;
    PLayerDirection             m_PlayerDirection;
    PLayerDirection             m_PlayerLastDirection;
    
    bool                        m_bAcceptInput;
    bool                        m_bEquipedGun;
    bool                        m_bInShadow;
    
    bool        m_bLeftBtnPressed;
    bool        m_bRightBtnPressed;
    bool        m_bUpBtnPressed;
    bool        m_bDownBtnPressed;
};

#endif /* defined(__Tone_Skipper__Player__) */
