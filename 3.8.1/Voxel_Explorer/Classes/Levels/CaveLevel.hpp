//
//  CaveLevel.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/11/24.
//
//

#ifndef CaveLevel_hpp
#define CaveLevel_hpp

#include "StandardLevel.h"
class CaveLevel : public StandardLevel
{
public:
    CaveLevel();
    
    virtual bool createMonsters();
    virtual bool createSummoningMonsters(const cocos2d::Vec2& mapPos);
};

#endif /* CaveLevel_hpp */
