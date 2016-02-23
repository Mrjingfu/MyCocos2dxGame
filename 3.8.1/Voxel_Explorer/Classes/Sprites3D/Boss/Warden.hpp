//
//  Warden.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/22.
//
//

#ifndef Warden_hpp
#define Warden_hpp

#include "BaseBoss.hpp"
class Warden : public BaseBoss
{
    Warden();
    virtual ~Warden();
public:
    static Warden* create(BaseBoss::BossType type);
    
    virtual void onEnterSkill1Stage();
    virtual void onEnterSkill2Stage();
    virtual void onEnterSkill3Stage();
    virtual void onEnterDeath();
    
    virtual bool isPlayerInsideBossRoom();
};

#endif /* Warden_hpp */
