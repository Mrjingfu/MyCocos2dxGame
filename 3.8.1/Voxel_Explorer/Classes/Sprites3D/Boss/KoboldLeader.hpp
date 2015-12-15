//
//  KoboldLeader.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/12/5.
//
//

#ifndef KoboldLeader_hpp
#define KoboldLeader_hpp

#include "BaseBoss.hpp"
class KoboldLeader : public BaseBoss
{
    KoboldLeader();
    virtual ~KoboldLeader();
public:
    static KoboldLeader* create(BaseBoss::BossType type);
    
    virtual void update(float delta);
    virtual void onEnterTracking();
    virtual void onEnterSkill1();
    virtual void onEnterSkill2();
    virtual void onEnterSkill3();
    virtual void onEnterDeath();
    
    virtual bool isPlayerInsideBossRoom();
private:
    float           m_fSkill3Timer;
    bool            m_bInSkill3Stage;
};

#endif /* KoboldLeader_hpp */
