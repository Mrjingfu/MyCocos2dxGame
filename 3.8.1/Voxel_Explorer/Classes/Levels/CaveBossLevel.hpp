//
//  CaveBossLevel.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/12/3.
//
//

#ifndef CaveBossLevel_hpp
#define CaveBossLevel_hpp

#include "StandardLevel.h"
class CaveBossLevel : public StandardLevel
{
public:
    CaveBossLevel();
    
    virtual bool build();
    virtual void generateAreaStyle();
    virtual bool createMonsters();
    virtual bool createSummoningMonsters(const cocos2d::Vec2& mapPos);
    
    virtual bool createEliteMonster(int tileIndex);
    virtual void createSiegeMonsters(const cocos2d::Vec2& pos);
    
private:
    int m_nHallRadius;
    int m_nChamberWidth;
    int m_nChamberHeight;
    
    int m_nLeft;
    int m_nCenter;
    
    int m_nIndexEntrance;
    int m_nIndexExit;
    int m_nArenaDoor;
};

#endif /* CaveBossLevel_hpp */
