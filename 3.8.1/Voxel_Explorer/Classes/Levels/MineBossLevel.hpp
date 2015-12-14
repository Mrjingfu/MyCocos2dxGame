//
//  MineBossLevel.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/12/3.
//
//

#ifndef MineBossLevel_hpp
#define MineBossLevel_hpp

#include "StandardLevel.h"
class MineBossLevel : public StandardLevel
{
public:
    MineBossLevel();
    
    virtual bool build();;
    virtual bool createMonsters();
    virtual bool createSummoningMonsters(const cocos2d::Vec2& mapPos);
    
    virtual bool createEliteMonster(int tileIndex);
    virtual void createSiegeMonsters(const cocos2d::Vec2& pos);
    
    virtual bool createBoss(const cocos2d::Vec2& pos);
    
    virtual int randomMonsterRespawnCell();
    
    virtual bool createSummoningMonstersByKoboldLeader(const cocos2d::Vec2& mapPos, int skillStage);
    virtual void clearBossRoom();
    
    virtual bool createPickableItems();
private:
    std::vector<int> getTilesOnEdge(int m = 1);
private:
    int m_nRoomLeft;
    int m_nRoomRight;
    int m_nRoomTop;
    int m_nRoomBottom;
    
    int m_nIndexEntrance;
    int m_nIndexExit;
    
    cocos2d::Vec2       m_BossPosition;
    
    cocos2d::Rect       m_AreaExitRect;
    cocos2d::Vec2       m_AreaExitCenter;
};

#endif /* MineBossLevel_hpp */
