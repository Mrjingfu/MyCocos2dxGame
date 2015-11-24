//
//  FaneLevel.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/11/24.
//
//

#ifndef FaneLevel_hpp
#define FaneLevel_hpp

#include "StandardLevel.h"
class FaneLevel : public StandardLevel
{
public:
    FaneLevel();
    
    virtual bool createMonsters();
    virtual bool createSummoningMonsters(const cocos2d::Vec2& mapPos);
};

#endif /* FaneLevel_hpp */
