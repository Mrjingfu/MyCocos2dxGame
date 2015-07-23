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
        RS_UNKNOWN
    } RunnerState;
protected:
    Runner();
public:
    static Runner* create();
    
    float getRadius() const { return m_fRadius; }
    
    RunnerState getState() const { return m_curState; }
    void setState(RunnerState state);
    
    void onCollision(TerrainCell* cell);
private:
    void onEnterIdle();
    void onEnterMoveLeft();
    void onEnterMoveRight();
    void onEnterMoveForward();
    void onEnterMoveSuperJump();
    void onEnterMoveJumpLocal();
    void onEnterMoveDrop();
    
    void onExitIdle();
    void onExitMoveLeft();
    void onExitMoveRight();
    void onExitMoveForward();
    void onExitMoveSuperJump();
    void onExitMoveJumpLocal();
    void onExitMoveDrop();
    
    void checkSafe();
protected:
    RunnerState     m_curState;
    float           m_fRadius;
};

#endif /* defined(__MazeJump__Runner__) */
