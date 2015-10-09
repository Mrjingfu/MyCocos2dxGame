//
//  Player.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/9.
//
//

#ifndef Player_hpp
#define Player_hpp

#include "cocos2d.h"
class Player : public cocos2d::Sprite3D
{
public:
    typedef enum {
        PS_IDLE = 0,
        PS_PREPARE_TO_JUMP,
        PS_JUMPLOCAL,
        PS_JUMPMOVE,
        PS_DROP,
        PS_DEATH,
        PS_UNKNOWN
    } PlayerState;
    typedef enum {
        PD_FORWARD = 0,
        PD_LEFT,
        PD_RIGHT,
        PD_BACK,
        RD_UNKNOWN
    } PlayerDir;
protected:
    Player();
    virtual ~Player();
public:
    static Player* create(const std::string& modelPath);
    
    PlayerState getState() const { return m_curState; }
    void setState(PlayerState state);
    
    void rotateToLeft();
    void rotateToRight();
    void rotateToForward();
    void rotateToBack();
private:
    void onEnterIdle();
    void onEnterPrepareToJump();
    void onEnterJumpLocal();
    void onEnterJumpMove();
    void onEnterDrop();
    void onEnterDeath();
    
    void onExitIdle();
    void onExitPrepareToJump();
    void onExitJumpLocal();
    void onExitJumpMove();
    void onExitDrop();
    void onExitDeath();
    
    void onLand();
private:
    PlayerState     m_curState;
    PlayerDir       m_dir;
};

#endif /* Player_hpp */
