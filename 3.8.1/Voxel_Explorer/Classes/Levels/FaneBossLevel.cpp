//
//  FaneBossLevel.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/12/3.
//
//

#include "FaneBossLevel.hpp"
#include "Graph.h"
#include "VoxelExplorer.h"
#include "StandardMonster.hpp"
USING_NS_CC;

FaneBossLevel::FaneBossLevel()
{
    m_nRoomLeft     = m_nWidth / 2 - 1;
    m_nRoomRight    = m_nWidth / 2 + 1;
    m_nRoomTop      = m_nHeight / 2 + 1;
    m_nRoomBottom   = m_nHeight / 2 - 1;
    
    m_nIndexEntrance = -1;
    m_nIndexExit = -1;
}
bool FaneBossLevel::build()
{
    for (int i=0; i < 6; i++) {
        
        int bottom = cocos2d::random( 2, m_nRoomBottom - 1 );
        int top = cocos2d::random( m_nRoomTop + 1, 36 );
        
        generateTerrainTiles(4 + i * 4, bottom, 4, top - bottom + 1, TerrainTile::TT_STANDARD, Area::AT_BOSS_ROOM);
        
        if (i == 2) {
            m_nIndexExit = (i * 6 + 3) + (top + 1) * m_nWidth ;
        }
        
        for (int j=0; j < 4; j++) {
            if (cocos2d::random(0, 1) == 0) {
                int y = cocos2d::random( bottom + 1, top - 1 );
                int wallIndex = i*4+j + y*m_nWidth;
                int wallX = wallIndex%m_nWidth;
                int wallY = wallIndex/m_nWidth;
                std::vector<int> neighbour8 = getNeighbours8();
                bool canPlace = true;
                for (int k = 0; k < neighbour8.size(); k++) {
                    wallIndex = wallIndex + neighbour8[k];
                    if(!(m_Map[wallIndex].isPassable()))
                    {
                        canPlace = false;
                        break;
                    }
                }
                if(canPlace)
                    setTerrainTile(wallX, wallY, TerrainTile::TT_WALL, Area::AT_BOSS_ROOM);
            }
        }
    }
    for (int i = 0; i<m_nLenght; i++) {
        if(m_Map[i].m_Type == TerrainTile::TT_STANDARD)
        {
            std::vector<int> neighbour8 = getNeighbours8();
            for (int k = 0; k < neighbour8.size(); k++) {
                int checkIndex = i + neighbour8[k];
                int checkX = checkIndex%m_nWidth;
                int checkY = checkIndex/m_nWidth;
                if(m_Map[checkIndex].m_Type == TerrainTile::TT_CHASM)
                    setTerrainTile(checkX, checkY, TerrainTile::TT_WALL, Area::AT_BOSS_ROOM);
            }
        }
    }
    int exitX = m_nIndexExit%m_nWidth;
    int exitY = m_nIndexExit/m_nWidth;
    
    generateTerrainTiles( exitX - 3, exitY,
                         m_nRoomRight - m_nRoomLeft + 7, m_nRoomTop - m_nRoomBottom + 7, TerrainTile::TT_WALL, Area::AT_BOSS_EXIT );;
    generateTerrainTiles(  exitX - 2, exitY+1,
                 m_nRoomRight - m_nRoomLeft + 5, m_nRoomTop - m_nRoomBottom + 5, TerrainTile::TT_STANDARD, Area::AT_BOSS_EXIT );
    
    m_nIndexEntrance = cocos2d::random( m_nRoomLeft + 1, m_nRoomRight - 1 ) + cocos2d::random( m_nRoomBottom + 1, m_nRoomTop - 1 ) * m_nWidth;
    
    int entranceX = m_nIndexEntrance%m_nWidth;
    int entranceY = m_nIndexEntrance/m_nWidth;
    setTerrainTile(exitX, exitY, TerrainTile::TT_LOCKED_BOSS_DOOR, Area::AT_BOSS_EXIT);
    setTerrainTile(entranceX, entranceY, TerrainTile::TT_ENTRANCE, Area::AT_BOSS_ROOM);
    
    updateTerrainTileFogOfWar(0, 0, m_nWidth, m_nHeight, true);
    generate();
    return true;
}
void FaneBossLevel::generateAreaStyle()
{
    m_Style = LevelStyle::LS_STANDARD;
}
bool FaneBossLevel::createMonsters()
{
    int monsterNum = calculateLevelMonsterCount();
    for (int i=0; i < monsterNum; i++) {
        BaseMonster::MonsterType type = (BaseMonster::MonsterType)cocos2d::random((int)BaseMonster::MT_BELIEVER, (int)BaseMonster::MT_PRIEST);
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
bool FaneBossLevel::createSummoningMonsters(const cocos2d::Vec2& mapPos)
{
    std::vector<int> neighbours4 = getNeighbours4();
    for (int i = 0; i < neighbours4.size(); i++) {
        int index = mapPos.x + mapPos.y * m_nWidth + neighbours4[i];
        if(isTerrainTilePassable(index))
        {
            BaseMonster::MonsterType type = (BaseMonster::MonsterType)cocos2d::random((int)BaseMonster::MT_BELIEVER, (int)BaseMonster::MT_PRIEST);
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
bool FaneBossLevel::createEliteMonster(int tileIndex)
{
    BaseMonster::MonsterType type = (BaseMonster::MonsterType)cocos2d::random((int)BaseMonster::MT_BELIEVER, (int)BaseMonster::MT_PRIEST);
    StandardMonster* monster = StandardMonster::create(type, true);
    if(!monster)
        return false;
    monster->setPosition3D(Vec3(m_Map[tileIndex].m_nX*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -m_Map[tileIndex].m_nY*TerrainTile::CONTENT_SCALE));
    monster->setVisited(m_Map[tileIndex].m_bVisited);
    monster->addTerrainTileFlag(TileInfo::ATTACKABLE);
    VoxelExplorer::getInstance()->getMonstersLayer()->addChild(monster);
    monster->setState(BaseMonster::MS_SLEEPING);
    
    return true;
}
void FaneBossLevel::createSiegeMonsters(const cocos2d::Vec2& pos)
{
    for (PathGraphNode* node : m_Areas) {
        Area* area = static_cast<Area*>(node);
        if(area && area->checkInside(pos))
        {
            std::vector<int> coners = area->getTilesOnCorner(this);
            for (int i = 0; i<coners.size(); ++i) {
                int tileIndex = coners[i];
                if(m_Map[tileIndex].isPassable())
                {
                    BaseMonster::MonsterType type = (BaseMonster::MonsterType)cocos2d::random((int)BaseMonster::MT_BELIEVER, (int)BaseMonster::MT_PRIEST);
                    StandardMonster* monster = StandardMonster::create(type);
                    if(monster)
                    {
                        monster->setPosition3D(Vec3(m_Map[tileIndex].m_nX*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -m_Map[tileIndex].m_nY*TerrainTile::CONTENT_SCALE));
                        monster->setVisited(m_Map[tileIndex].m_bVisited);
                        monster->addTerrainTileFlag(TileInfo::ATTACKABLE);
                        VoxelExplorer::getInstance()->getMonstersLayer()->addChild(monster);
                        monster->setState(BaseMonster::MS_SLEEPING);
                    }
                }
            }
        }
    }
}