//
//  SewerBossLevel.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/12/1.
//
//

#ifndef SewerBossLevel_hpp
#define SewerBossLevel_hpp

#include "StandardLevel.h"
class SewerBossLevel : public StandardLevel
{
public:
    SewerBossLevel();
    
    virtual bool build();
    virtual void generateAreaStyle();
    virtual bool createMonsters();
    virtual bool createSummoningMonsters(const cocos2d::Vec2& mapPos);
    
    virtual bool createEliteMonster(int tileIndex);
    virtual void createSiegeMonsters(const cocos2d::Vec2& pos);
};


#endif /* SewerBossLevel_hpp */
