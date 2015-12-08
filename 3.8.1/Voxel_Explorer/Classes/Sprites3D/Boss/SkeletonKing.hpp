//
//  SkeletonKing.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/22.
//
//

#ifndef SkeletonKing_hpp
#define SkeletonKing_hpp

#include "BaseBoss.hpp"
class SkeletonKing : public BaseBoss
{
    SkeletonKing();
    virtual ~SkeletonKing();
public:
    static SkeletonKing* create(BaseBoss::BossType type);
};

#endif /* SkeletonKing_hpp */
