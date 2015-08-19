//
//  Player.h
//  MazeJump
//
//  Created by wang haibo on 15/7/3.
//
//

#ifndef __MazeJump__Player__
#define __MazeJump__Player__

#include "EffectSprite3D.h"
class GroundLayer;
class GroundCell;
class Player : public EffectSprite3D
{
public:
    
    typedef enum {
        PS_IDLE = 0,
        PS_MOVE_LEFT,
        PS_MOVE_RIGHT,
        PS_MOVE_UP,
        PS_MOVE_DOWN,
        PS_JUMP_STAY,
        PS_CHECK_NEXT_CELL,
        PS_CHECK_SPEICAL_ART,
        PS_UNKNOWN
    } PlayerState;
protected:
    Player();
public:
    static Player* create(const std::string& modelPath, GroundLayer* ground);
    
    float getRadius() const { return m_fRadius; }
    
    PlayerState getPlayerState() const { return m_curState; }
    void setPlayerState(PlayerState state);
    
    int getIndexX() const { return m_nIndexX; }
    void setIndexX(int indexX) { m_nIndexX = indexX; }
    int getIndexY() const { return m_nIndexY; }
    void setIndexY(int indexY) { m_nIndexY = indexY; }
    
private:
    void onEnterIdle();
    void onEnterMoveLeft();
    void onEnterMoveRight();
    void onEnterMoveUp();
    void onEnterMoveDown();
    void onEnterJumpStay();
    void onEnterCheckNextCell();
    void onEnterCheckSpeicalArt();
    
    
    void onExitIdle();
    void onExitMoveLeft();
    void onExitMoveRight();
    void onExitMoveUp();
    void onExitMoveDown();
    void onExitJumpStay();
    void onExitCheckNextCell();
    void onExitCheckSpeicalArt();
    
    void recalculateCells();
    void jumpFinish();
    void carryStar(Node* node,GroundCell* cell);
    void speicaArtFinish(Node* node,GroundCell* cell);
    
    
protected:
    PlayerState     m_curState;
    float           m_fRadius;
    GroundLayer*    m_pGround;
    int             m_nIndexX;
    int             m_nIndexY;
    int             m_nNextIndexX;
    int             m_nNextIndexY;
};

#endif /* defined(__MazeJump__Player__) */
