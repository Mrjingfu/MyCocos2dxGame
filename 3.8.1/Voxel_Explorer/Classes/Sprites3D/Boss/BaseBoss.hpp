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
extern const std::string BOSS_MODEL_NAMES[];
class BaseBoss : public Actor
{
public:
    typedef enum{
        BT_UNKNOWN = 0,

        BT_SLIMEKING,               ///史莱姆王
        BT_WARDEN,                  ///典狱长
        BT_ARCHBISHOP,              ///大主教
        BT_KOBOLDLEADER,            ///狗头人首领
        BT_GIANT,                   ///巨人格鲁尔德
        BT_SKELETONKING,            ///骷髅王
        
        BT_MAX
    } BossType;
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
