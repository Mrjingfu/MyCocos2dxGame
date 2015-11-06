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
    
    PlayerState getState() const { return m_curState; }
    void setState(PlayerState state);
    
    bool isStealth() const { return m_bStealth; }
    void setStealth(bool stealth);
    
    virtual void rotateToLeft();
    virtual void rotateToRight();
    virtual void rotateToForward();
    virtual void rotateToBack();
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
    
    bool createPlayerLight();
private:
    PlayerState                 m_curState;
    cocos2d::PointLight*        m_pPlayerLight;
    
    bool                        m_bStealth;     ///是否隐身
};

#endif /* Player_hpp */
