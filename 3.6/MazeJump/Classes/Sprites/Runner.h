//
//  Runner.h
//  MazeJump
//
//  Created by wang haibo on 15/7/22.
//
//

#ifndef __MazeJump__Runner__
#define __MazeJump__Runner__

#include "EffectSprite3D.h"
#include "TerrainCell.h"
#include "RibbonTrail.h"
class Runner : public EffectSprite3D
{
public:
    typedef enum {
        RS_IDLE = 0,
        RS_MOVE_LEFT,
        RS_MOVE_RIGHT,
        RS_MOVE_FORWARD,
        RS_MOVE_SUPERJUMP,
        RS_MOVE_JUMPLOCAL,
        RS_MOVE_DROP,
        RS_DEATH,
        RS_UNKNOWN
    } RunnerState;
    typedef enum {
        RD_FORWARD = 0,
        RD_LEFT,
        RD_RIGHT,
        RD_UNKNOWN
    } RunnerDir;
protected:
    Runner();
    virtual ~Runner();
public:
    static Runner* create();
    
    virtual void update(float delta);
    
    float getRadius() const { return m_fRadius; }
    
    RunnerState getState() const { return m_curState; }
    void setState(RunnerState state);
    
    void onCollision(TerrainCell* cell);
    
    const cocos2d::AABB& getModifyAABB();
    
    void fadeIn();
    void fadeOut();
    
    void setRibbonTrail(const std::string& file);
    void setFakeShadow(cocos2d::Layer* ownerLayer);
    
    bool isSpeedUp() const { return m_bSpeedUp; }
    void setSpeedUp(bool speedUp) { m_bSpeedUp = speedUp; }
private:
    void onEnterIdle();
    void onEnterMoveLeft();
    void onEnterMoveRight();
    void onEnterMoveForward();
    void onEnterMoveSuperJump();
    void onEnterMoveJumpLocal();
    void onEnterMoveDrop();
    void onEnterDeath();
    
    void onExitIdle();
    void onExitMoveLeft();
    void onExitMoveRight();
    void onExitMoveForward();
    void onExitMoveSuperJump();
    void onExitMoveJumpLocal();
    void onExitMoveDrop();
    void onExitDeath();
    
    void checkSafe();
protected:
    RunnerState     m_curState;
    RunnerDir       m_dir;
    float           m_fRadius;
    mutable cocos2d::AABB    m_modifyAABB;
    RibbonTrail*            m_pRibbonTrail;
    cocos2d::Sprite3D*         m_pFakeShadow;
    
    bool    m_bSpeedUp;
};

#endif /* defined(__MazeJump__Runner__) */
