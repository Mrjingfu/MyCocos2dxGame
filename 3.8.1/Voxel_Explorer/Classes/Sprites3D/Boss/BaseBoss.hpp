//
//  BaseBoss.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/23.
//
//

#ifndef BaseBoss_hpp
#define BaseBoss_hpp

#include "Actor.hpp"
#include "TerrainTile.hpp"
class BaseBoss : public Actor
{
public:
    typedef enum{
        BS_UNKNOWN,
        BS_IDLE,
        BS_DEATH,
        BS_MAX
    } BossState;
    BossState getState() const { return m_State; }
    
    void setState(BossState state);
    
    void attackedByPlayer();
protected:
    BaseBoss();
    virtual ~BaseBoss();
    
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
    
    virtual void onEnterIdle();
    virtual void onExitIdle();
    
    virtual void onEnterDeath();
    virtual void onExitDeath();
protected:
    BossState        m_State;
    BossState        m_LastState;
};

#endif /* BaseBoss_hpp */
