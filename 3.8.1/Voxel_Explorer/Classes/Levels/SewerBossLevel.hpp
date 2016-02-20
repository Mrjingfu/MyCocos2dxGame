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
    virtual bool createTerrain();
    virtual void generateAreaStyle();
    virtual bool createMonsters();
    virtual bool createSummoningMonsters(const cocos2d::Vec2& mapPos);
    
    virtual bool createEliteMonster(int tileIndex);
    virtual void createSiegeMonsters(const cocos2d::Vec2& pos);
    
    virtual bool createBoss(const cocos2d::Vec2& pos);
    
    virtual bool createSummoningMonstersBySlimeKing(const cocos2d::Vec2& mapPos, int skillStage);
    virtual void clearBossRoom();

    virtual bool createPickableItems();
    
    virtual void handleUseStandardPortal(const cocos2d::Vec2& pos);
private:
    cocos2d::Vec2       m_BossPosition;
    Area*               m_pBossExitRoom;
};


#endif /* SewerBossLevel_hpp */
