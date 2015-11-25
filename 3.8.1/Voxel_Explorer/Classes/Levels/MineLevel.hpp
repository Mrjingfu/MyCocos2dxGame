//
//  MineLevel.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/11/24.
//
//

#ifndef MineLevel_hpp
#define MineLevel_hpp

#include "StandardLevel.h"
class MineLevel : public StandardLevel
{
public:
    MineLevel();
    
    virtual bool createMonsters();
    virtual bool createSummoningMonsters(const cocos2d::Vec2& mapPos);
};

#endif /* MineLevel_hpp */
