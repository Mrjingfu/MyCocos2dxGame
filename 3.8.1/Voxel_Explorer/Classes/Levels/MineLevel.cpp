//
//  MineLevel.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/11/24.
//
//

#include "MineLevel.hpp"
#include "VoxelExplorer.h"
#include "StandardMonster.hpp"
#include "StandardPortal.hpp"
#include "SmallPortal.hpp"
#include "RandomDungeon.hpp"
#include "TerrainTile.hpp"
#include "StandardDoor.hpp"
#include "Ladder.hpp"
USING_NS_CC;
MineLevel::MineLevel()
{
}
bool MineLevel::createTerrain()
{
    if(!VoxelExplorer::getInstance()->getTerrainTilesLayer())
        return false;
    for (int i = 0; i<m_nHeight; i++) {
        for (int j = 0; j<m_nWidth; j++) {
            int index = i*m_nWidth+j;
            TileInfo info = m_Map[index];
            if(info.m_Type == TerrainTile::TT_CHASM)
                continue;
            TerrainTile* tile = TerrainTile::create(info.m_Type);
            if(!tile)
                return false;
            tile->setPosition3D(Vec3(j*TerrainTile::CONTENT_SCALE, -TerrainTile::CONTENT_SCALE, -i*TerrainTile::CONTENT_SCALE));
            tile->setVisited(info.m_bVisited);
            VoxelExplorer::getInstance()->getTerrainTilesLayer()->addChild(tile);
            
            switch (info.m_Type) {
                case TerrainTile::TT_WALL:
                    {
                        tile->setPosition3D(Vec3(j*TerrainTile::CONTENT_SCALE, -TerrainTile::CONTENT_SCALE*0.5f, -i*TerrainTile::CONTENT_SCALE));
                    }
                    break;
                case TerrainTile::TT_ENTRANCE:
                    {
                        if((RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nCurrentDepth == 1))
                        {
                            StandardPortal* portal = StandardPortal::create(false);
                            if(!portal)
                                return false;
                            portal->setPosition3D(Vec3(j*TerrainTile::CONTENT_SCALE, 0, -i*TerrainTile::CONTENT_SCALE));
                            VoxelExplorer::getInstance()->getTerrainPortalsLayer()->addChild(portal);
                            portal->setVisited(info.m_bVisited);
                        }
                        else
                        {
                            Ladder* ladder = Ladder::create();
                            if(!ladder)
                                return false;
                            ladder->setPosition3D(Vec3(j*TerrainTile::CONTENT_SCALE, -TerrainTile::CONTENT_SCALE*0.5f, -i*TerrainTile::CONTENT_SCALE));
                            VoxelExplorer::getInstance()->getTerrainPortalsLayer()->addChild(ladder);
                        ladder->setVisited(info.m_bVisited);

                        }
                    }
                    break;
                case TerrainTile::TT_STANDARD_PORTAL:
                    {
                        StandardPortal* portal = StandardPortal::create(true);
                        if(!portal)
                            return false;
                        portal->setPosition3D(Vec3(j*TerrainTile::CONTENT_SCALE, 0, -i*TerrainTile::CONTENT_SCALE));
                        VoxelExplorer::getInstance()->getTerrainPortalsLayer()->addChild(portal);
                        portal->setVisited(info.m_bVisited);
                    }
                    break;
                case TerrainTile::TT_SMALL_PORTAL:
                    {
                        SmallPortal* portal = SmallPortal::create(true);
                        if(!portal)
                            return false;
                        portal->setPosition3D(Vec3(j*TerrainTile::CONTENT_SCALE, 0, -i*TerrainTile::CONTENT_SCALE));
                        VoxelExplorer::getInstance()->getTerrainPortalsLayer()->addChild(portal);
                        portal->setVisited(info.m_bVisited);
                    }
                    break;
                case TerrainTile::TT_DOOR:
                    {
                        StandardDoor* door = StandardDoor::create(false);
                        if(!door)
                            return false;
                        door->setPosition3D(Vec3(j*TerrainTile::CONTENT_SCALE, -TerrainTile::CONTENT_SCALE*0.5f, -i*TerrainTile::CONTENT_SCALE));
                        VoxelExplorer::getInstance()->getTerrainDoorsLayer()->addChild(door);
                        if(!door->createFakeDoor())
                            return false;
                        door->setVisited(info.m_bVisited);
                        door->setActorDir(info.m_Dir);
                        door->setDoorState(BaseDoor::DS_CLOSED);
                    }
                    break;
                case TerrainTile::TT_OPENED_DOOR:
                    {
                        StandardDoor* door = StandardDoor::create(false);
                        if(!door)
                            return false;
                        door->setPosition3D(Vec3(j*TerrainTile::CONTENT_SCALE, -TerrainTile::CONTENT_SCALE*0.5f, -i*TerrainTile::CONTENT_SCALE));
                        VoxelExplorer::getInstance()->getTerrainDoorsLayer()->addChild(door);
                        if(!door->createFakeDoor())
                            return false;
                        door->setVisited(info.m_bVisited);
                        door->setActorDir(info.m_Dir);
                        door->setDoorState(BaseDoor::DS_OPENED);
                    }
                    break;
                case TerrainTile::TT_LOCKED_DOOR:
                    {
                        StandardDoor* door = StandardDoor::create(false);
                        if(!door)
                            return false;
                        door->setPosition3D(Vec3(j*TerrainTile::CONTENT_SCALE, -TerrainTile::CONTENT_SCALE*0.5f, -i*TerrainTile::CONTENT_SCALE));
                        VoxelExplorer::getInstance()->getTerrainDoorsLayer()->addChild(door);
                        if(!door->createFakeDoor())
                            return false;
                        door->setVisited(info.m_bVisited);
                        door->setActorDir(info.m_Dir);
                        door->setDoorState(BaseDoor::DS_LOCKED);
                    }
                    break;
                case TerrainTile::TT_SECRET_DOOR:
                    {
                        StandardDoor* door = StandardDoor::create(true);
                        if(!door)
                            return false;
                        door->setPosition3D(Vec3(j*TerrainTile::CONTENT_SCALE, -TerrainTile::CONTENT_SCALE*0.5f, -i*TerrainTile::CONTENT_SCALE));
                        VoxelExplorer::getInstance()->getTerrainDoorsLayer()->addChild(door);
                        if(!door->createFakeDoor())
                            return false;
                        door->setVisited(info.m_bVisited);
                        door->setActorDir(info.m_Dir);
                        door->setDoorState(BaseDoor::DS_HIDE);
                    }
                    break;
                default:
                    break;
            }
            
        }
    }
    return true;
}
bool MineLevel::createMonsters()
{
    int monsterNum = calculateLevelMonsterCount();
    for (int i=0; i < monsterNum; i++) {
        BaseMonster::MonsterType type = (BaseMonster::MonsterType)cocos2d::random((int)BaseMonster::MT_DEATHMINER, (int)BaseMonster::MT_ANKHEG);
        StandardMonster* monster = StandardMonster::create(type);
        if(!monster)
            return false;
        int tileIndex = -1;
        do {
            tileIndex = randomMonsterRespawnCell();
        } while (tileIndex == -1);
        
        monster->setPosition3D(Vec3(m_Map[tileIndex].m_nX*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -m_Map[tileIndex].m_nY*TerrainTile::CONTENT_SCALE));
        monster->setVisited(m_Map[tileIndex].m_bVisited);
        monster->addTerrainTileFlag(TileInfo::ATTACKABLE);
        VoxelExplorer::getInstance()->getMonstersLayer()->addChild(monster);
        monster->setState(BaseMonster::MS_SLEEPING);
    }
    return true;
}
bool MineLevel::createSummoningMonsters(const cocos2d::Vec2& mapPos)
{
    std::vector<int> neighbours4 = getNeighbours4();
    for (int i = 0; i < neighbours4.size(); i++) {
        int index = mapPos.x + mapPos.y * m_nWidth + neighbours4[i];
        if(isTerrainTilePassable(index))
        {
            BaseMonster::MonsterType type = (BaseMonster::MonsterType)cocos2d::random((int)BaseMonster::MT_DEATHMINER, (int)BaseMonster::MT_ANKHEG);
            StandardMonster* monster = StandardMonster::create(type);
            if(!monster)
                return false;
            monster->setPosition3D(Vec3(m_Map[index].m_nX*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -m_Map[index].m_nY*TerrainTile::CONTENT_SCALE));
            monster->setVisited(m_Map[index].m_bVisited);
            monster->addTerrainTileFlag(TileInfo::ATTACKABLE);
            VoxelExplorer::getInstance()->getMonstersLayer()->addChild(monster);
            monster->setState(BaseMonster::MS_SLEEPING);
        }
    }
    return true;
}
void MineLevel::generateSpawnPoint()
{
    for (int i = 0; i<m_Map.size()-1; i++) {
        if(m_Map[i].m_Type == TerrainTile::TT_ENTRANCE)
            m_spawnPoint = Vec2((m_Map[i].m_nX)*TerrainTile::CONTENT_SCALE,(m_Map[i].m_nY-1)*TerrainTile::CONTENT_SCALE);
    }
}