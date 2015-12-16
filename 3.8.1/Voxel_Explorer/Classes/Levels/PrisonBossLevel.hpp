//
//  PrisonBossLevel.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/12/3.
//
//

#ifndef PrisonBossLevel_hpp
#define PrisonBossLevel_hpp

#include "StandardLevel.h"
class PrisonBossLevel : public StandardLevel
{
public:
    PrisonBossLevel();
    
    virtual bool build();
    virtual void generateAreaStyle();
    virtual bool createMonsters();
    virtual bool createSummoningMonsters(const cocos2d::Vec2& mapPos);
    
    virtual bool createEliteMonster(int tileIndex);
    virtual void createSiegeMonsters(const cocos2d::Vec2& pos);
    
    virtual bool createBoss(const cocos2d::Vec2& pos);
    
    virtual bool createSummoningMonstersByWarden(const cocos2d::Vec2& mapPos, int skillStage);
    virtual void clearBossRoom();
    
    virtual bool createPickableItems();
    
    virtual void handleUseStandardPortal(const cocos2d::Vec2& pos);
private:
    Area*               m_pArenaRoom;
    int                 m_nArenaDoor;

    cocos2d::Vec2       m_BossPosition;
};

#endif /* PrisonBossLevel_hpp */
