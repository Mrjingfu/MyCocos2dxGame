//
//  Player.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/9.
//
//

#ifndef Player_hpp
#define Player_hpp

#include "Actor.hpp"
#include "EventConst.h"
#include "MonsterProperty.hpp"
#include "PlayerProperty.hpp"
#include "BossProperty.hpp"
class FakeShadow;
class Player : public Actor
{
public:
    typedef enum {
        PS_IDLE = 0,
        PS_PREPARE_TO_JUMP,
        PS_JUMPLOCAL,
        PS_JUMPMOVE,
        PS_ATTACK,
        PS_DROP,
        PS_DEATH,
        PS_UNKNOWN
    } PlayerState;
protected:
    Player();
    virtual ~Player();
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
public:
    static Player* create(const std::string& modelPath);
    
    std::string getIconRes();
    virtual std::string getDesc();
    
    cocos2d::Vec2 getLastPosInMap() const { return m_LastPosInMap; }
    
    PlayerState getState() const { return m_curState; }
    void setState(PlayerState state);
    
    void refreshPlayerBuffer();
    void addPlayerBuffer(PlayerBuffer buff);
    void removePlayerBuffer(PlayerBuffer buff);
    
    bool isStealth() const { return m_bStealth; }
    void setStealth(bool stealth);
    
    bool isParalytic();
    
    virtual void rotateToLeft();
    virtual void rotateToRight();
    virtual void rotateToForward();
    virtual void rotateToBack();
    
    void attackByMonster(MonsterProperty* monsterProperty, bool miss);
    void attackByBoss(BossProperty* bossProperty, bool miss);
    void hurtByGrippingTrap();
    void fallAndDie();
private:
    void onEnterIdle();
    void onEnterPrepareToJump();
    void onEnterJumpLocal();
    void onEnterJumpMove();
    void onEnterAttack();
    void onEnterDrop();
    void onEnterDeath();
    
    void onExitIdle();
    void onExitPrepareToJump();
    void onExitJumpLocal();
    void onExitJumpMove();
    void onExitAttack();
    void onExitDrop();
    void onExitDeath();
    
    void onLand();
    void onFallDie();
    void updatePlayerBuffer(float delta);
    
    bool createPlayerLight();
    
    bool createFakeShadow();
private:
    PlayerState                 m_curState;
    cocos2d::PointLight*        m_pPlayerLight;
    FakeShadow*                 m_pFakeShadow;
    
    bool                        m_bStealth;     ///是否隐身
    
    static CChaosNumber                m_fSpeedupTime; ///加速时间
    static CChaosNumber                m_fStealthTime; ///隐身时间
    static CChaosNumber                m_fStrongerTime; ///强化时间
    
    static CChaosNumber                m_fFrozenTime;  ///冰冻时间
    static CChaosNumber                m_fParalyticTime;   ///麻痹时间
    static CChaosNumber                m_fFireTime;    ///着火时间
    
    float                       m_fSecondTimer;

    
    HurtData*                   m_pHurtData;
    
    cocos2d::Vec2               m_LastPosInMap;
};

#endif /* Player_hpp */
