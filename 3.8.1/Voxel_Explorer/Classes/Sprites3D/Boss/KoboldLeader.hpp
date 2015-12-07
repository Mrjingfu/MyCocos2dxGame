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
};

#endif /* KoboldLeader_hpp */
