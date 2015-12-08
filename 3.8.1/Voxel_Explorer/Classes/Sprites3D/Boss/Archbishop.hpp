//
//  Archbishop.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/22.
//
//

#ifndef Archbishop_hpp
#define Archbishop_hpp

#include "BaseBoss.hpp"
class Archbishop : public BaseBoss
{
    Archbishop();
    virtual ~Archbishop();
public:
    static Archbishop* create(BaseBoss::BossType type);
};

#endif /* Archbishop_hpp */
