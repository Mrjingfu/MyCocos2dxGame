//
//  KoboldLeaderBullet.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 16/1/3.
//
//

#ifndef KoboldLeaderBullet_hpp
#define KoboldLeaderBullet_hpp

#include "BaseBullet.hpp"
class KoboldLeaderBullet : public BaseBullet
{
    KoboldLeaderBullet();
    virtual ~KoboldLeaderBullet();
    
    bool createParticleEffect();
public:
    static KoboldLeaderBullet* create(BaseBoss* pOwner);
    
    virtual void onEnterDisappear();
};

#endif /* KoboldLeaderBullet_hpp */
