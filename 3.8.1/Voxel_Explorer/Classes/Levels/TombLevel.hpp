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
    
    virtual bool createMonsters() override;
    virtual bool createSummoningMonsters(const cocos2d::Vec2& mapPos) override;
    
    virtual bool createEliteMonster(int tileIndex) override;
    virtual void createSiegeMonsters(const cocos2d::Vec2& pos) override;
    
    virtual void generateSpawnPoint() override;
};

#endif /* TombLevel_hpp */
