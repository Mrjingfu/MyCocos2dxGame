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
        
        monster->setPosition3D(Vec3(m_Map[tileIndex].m_nX*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -m_Map[tileIndex].m_nX*TerrainTile::CONTENT_SCALE));
        
        VoxelExplorer::getInstance()->getMonstersLayer()->addChild(monster);
        //        Actor.occupyCell( mob );
    }
    return true;
}
bool SewerLevel::createItems()
{
    //    int nItems = 3;
    //    while (cocos2d::rand_0_1() < 0.4f) {
    //        nItems++;
    //    }
    //
    //    for (int i=0; i < nItems; i++) {
    //        Heap.Type type = null;
    //        switch (Random.Int( 20 )) {
    //            case 0:
    //                type = Heap.Type.SKELETON;
    //                break;
    //            case 1:
    //            case 2:
    //            case 3:
    //            case 4:
    //                type = Heap.Type.CHEST;
    //                break;
    //            case 5:
    //                type = Dungeon.depth > 1 ? Heap.Type.MIMIC : Heap.Type.CHEST;
    //                break;
    //            default:
    //                type = Heap.Type.HEAP;
    //        }
    //        drop( Generator.random(), randomDropCell() ).type = type;
    //    }
    //
    //    for (Item item : itemsToSpawn) {
    //        int cell = randomDropCell();
    //        if (item instanceof ScrollOfUpgrade) {
    //            while (map[cell] == Terrain.FIRE_TRAP || map[cell] == Terrain.SECRET_FIRE_TRAP) {
    //                cell = randomDropCell();
    //            }
    //        }
    //        drop( item, cell ).type = Heap.Type.HEAP;
    //    }
    //    
    //    Item item = Bones.get();
    //    if (item != null) {
    //        drop( item, randomDropCell() ).type = Heap.Type.SKELETON;
    //    }
    return true;
}