//
//  SlimeKing.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/22.
//
//

#ifndef SlimeKing_hpp
#define SlimeKing_hpp

#include "BaseBoss.hpp"
class SlimeKing : public BaseBoss
{
    SlimeKing();
    virtual ~SlimeKing();
public:
    static SlimeKing* create(BaseBoss::BossType type);
    
    virtual void onEnterSkill1Stage();
    virtual void onEnterSkill2Stage();
    virtual void onEnterSkill3Stage();
    virtual void onEnterDeath();
    
    virtual bool isPlayerInsideBossRoom();
};

#endif /* SlimeKing_hpp */
