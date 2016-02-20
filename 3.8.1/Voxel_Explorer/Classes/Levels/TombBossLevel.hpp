//
//  TombBossLevel.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/12/3.
//
//

#ifndef TombBossLevel_hpp
#define TombBossLevel_hpp

#include "StandardLevel.h"
class TombBossLevel : public StandardLevel
{
public:
    TombBossLevel();
    
    virtual bool build();
    virtual bool createTerrain();
    virtual bool createMonsters();
    virtual bool createSummoningMonsters(const cocos2d::Vec2& mapPos);
    
    virtual bool createEliteMonster(int tileIndex);
    virtual void createSiegeMonsters(const cocos2d::Vec2& pos);
    
    virtual bool createBoss(const cocos2d::Vec2& pos);
    
    virtual bool createSummoningMonstersBySkeletonKing(const cocos2d::Vec2& mapPos, int skillStage);
    
    virtual void clearBossRoom();
    
    virtual bool createPickableItems();
    
    cocos2d::Vec2 getRandomPassableTileInBossRoom();
    
    virtual void handleUseStandardPortal(const cocos2d::Vec2& pos);
private:
    std::vector<int> getTilesOnEdge(int m = 1);
private:
    int m_nBottom;
    int m_nHallWidth;
    int m_nHallHeight;
    int m_nChamberWidth;
    int m_nChamberHeight;
    
    int m_nLeft;
    int m_nCenter;
    
    int m_nIndexEntrance;
    int m_nIndexExit;
    int m_nArenaDoor;
    
    cocos2d::Vec2       m_BossPosition;
    
    cocos2d::Rect       m_AreaExitRect;
    cocos2d::Vec2       m_AreaExitCenter;
    
    std::vector<cocos2d::Vec2>  m_GeneratePoints;
};

#endif /* TombBossLevel_hpp */
