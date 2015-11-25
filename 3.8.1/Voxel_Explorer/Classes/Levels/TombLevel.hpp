//
//  TombLevel.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/11/24.
//
//

#ifndef TombLevel_hpp
#define TombLevel_hpp

#include "StandardLevel.h"
class TombLevel : public StandardLevel
{
public:
    TombLevel();
    
    virtual bool createMonsters();
    virtual bool createSummoningMonsters(const cocos2d::Vec2& mapPos);
};

#endif /* TombLevel_hpp */
