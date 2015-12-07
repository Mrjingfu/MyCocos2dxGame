//
//  FaneBossLevel.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/12/3.
//
//

#ifndef FaneBossLevel_hpp
#define FaneBossLevel_hpp

#include "StandardLevel.h"
class FaneBossLevel : public StandardLevel
{
public:
    FaneBossLevel();
    
    virtual bool build();
    virtual bool createMonsters();
    virtual bool createSummoningMonsters(const cocos2d::Vec2& mapPos);
    
    virtual bool createEliteMonster(int tileIndex);
    virtual void createSiegeMonsters(const cocos2d::Vec2& pos);
    
    virtual bool createBoss(const cocos2d::Vec2& pos);
    
    virtual int randomMonsterRespawnCell();
private:
    int m_nRoomLeft;
    int m_nRoomRight;
    int m_nRoomTop;
    int m_nRoomBottom;
    
    int m_nIndexEntrance;
    int m_nIndexExit;
    
    cocos2d::Vec2       m_BossPosition;
};

#endif /* FaneBossLevel_hpp */
