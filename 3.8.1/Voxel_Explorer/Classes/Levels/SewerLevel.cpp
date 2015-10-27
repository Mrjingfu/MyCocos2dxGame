//
//  SewerLevel.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/23.
//
//

#include "SewerLevel.hpp"
#include "GameFormula.hpp"
#include "RandomDungeon.hpp"
#include "StandardMonster.hpp"
#include "PickableItem.hpp"
#include "VoxelExplorer.h"
USING_NS_CC;

SewerLevel::SewerLevel()
{
}

bool SewerLevel::createMonsters()
{
    int monsterNum = GameFormula::getLevelMonsterCount(m_nStandardAreaCount);
    for (int i=0; i < monsterNum; i++) {
        BaseMonster::MonsterType type = (BaseMonster::MonsterType)cocos2d::random((int)BaseMonster::MT_RAT, (int)BaseMonster::MT_SLIME);
        StandardMonster* monster = StandardMonster::create(type);
        if(!monster)
            return false;
        int tileIndex = -1;
        do {
             tileIndex = randomRespawnCell();
        } while (tileIndex == -1);
        
        monster->setPosition3D(Vec3(m_Map[tileIndex].m_nX*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -m_Map[tileIndex].m_nY*TerrainTile::CONTENT_SCALE));
        VoxelExplorer::getInstance()->getMonstersLayer()->addChild(monster);
        monster->setState(BaseMonster::MS_IDLE);
        
        CCLOG("monster : x = %d , y = %d", (int)monster->getPosInMap().x, (int)monster->getPosInMap().y);
    }
    return true;
}
bool SewerLevel::createUseableItems()
{
    ///临时测试物品生成
    int nItems = 13;
    while (cocos2d::rand_0_1() < 0.4f) {
        nItems++;
    }
    PickableItem::PickableItemType type = (PickableItem::PickableItemType)cocos2d::random(PickableItem::PIT_KEY_COPPER, PickableItem::PIT_CLOTH_PRO_STEELARMOR);
    
    
    for (int i=0; i < nItems; i++)
    {
        PickableItem* item = PickableItem::create(type);
        if(!item)
            return false;
        int tileIndex = -1;
        do {
            tileIndex = randomRespawnCell();
        } while (tileIndex == -1);
        
        item->setPosition3D(Vec3(m_Map[tileIndex].m_nX*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -m_Map[tileIndex].m_nY*TerrainTile::CONTENT_SCALE));
        VoxelExplorer::getInstance()->getPickableItemsLayer()->addChild(item);
        item->setState(PickableItem::PIS_IDLE);
        
        CCLOG("item : x = %d , y = %d", (int)item->getPosInMap().x, (int)item->getPosInMap().y);
    }
    return true;
}