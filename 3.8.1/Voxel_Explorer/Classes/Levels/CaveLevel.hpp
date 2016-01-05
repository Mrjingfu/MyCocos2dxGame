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
    
    virtual bool createMonsters() override;
    virtual bool createSummoningMonsters(const cocos2d::Vec2& mapPos) override;
    
    virtual bool createEliteMonster(int tileIndex) override;
    virtual void createSiegeMonsters(const cocos2d::Vec2& pos) override;
    
    virtual void generateSpawnPoint() override;
    virtual void generateReturnPoint() override;
};

#endif /* CaveLevel_hpp */
