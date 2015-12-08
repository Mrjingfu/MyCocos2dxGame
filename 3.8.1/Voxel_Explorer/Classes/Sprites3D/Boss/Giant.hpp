//
//  Giant.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/22.
//
//

#ifndef Giant_hpp
#define Giant_hpp

#include "BaseBoss.hpp"
class Giant : public BaseBoss
{
    Giant();
    virtual ~Giant();
public:
    static Giant* create(BaseBoss::BossType type);
};

#endif /* Giant_hpp */
