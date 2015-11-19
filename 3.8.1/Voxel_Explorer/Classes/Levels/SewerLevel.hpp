//
//  SewerLevel.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/23.
//
//

#ifndef SewerLevel_hpp
#define SewerLevel_hpp

#include "StandardLevel.h"
class SewerLevel : public StandardLevel
{
public:
    SewerLevel();
    
    virtual bool createMonsters();
    virtual bool createSummoningMonsters(const cocos2d::Vec2& mapPos);
protected:
    int calculateLevelMonsterCount();
    int calculateLevelUseableItemCount(const cocos2d::Size& areaSize);
};

#endif /* SewerLevel_hpp */
