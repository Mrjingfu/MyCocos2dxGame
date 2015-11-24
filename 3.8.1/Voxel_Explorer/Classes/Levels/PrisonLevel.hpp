//
//  PrisonLevel.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/11/24.
//
//

#ifndef PrisonLevel_hpp
#define PrisonLevel_hpp

#include "StandardLevel.h"
class PrisonLevel : public StandardLevel
{
public:
    PrisonLevel();
    
    virtual bool createMonsters();
    virtual bool createSummoningMonsters(const cocos2d::Vec2& mapPos);
};

#endif /* PrisonLevel_hpp */
