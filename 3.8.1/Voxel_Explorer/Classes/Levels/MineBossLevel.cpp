//
//  MineBossLevel.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/12/3.
//
//

#include "MineBossLevel.hpp"
#include "Graph.h"
#include "VoxelExplorer.h"
#include "StandardMonster.hpp"
USING_NS_CC;

MineBossLevel::MineBossLevel()
{
    m_nRoomLeft     = m_nWidth / 2 - 2;
    m_nRoomRight    = m_nWidth / 2 + 2;
    m_nRoomTop      = m_nHeight / 2 + 2;
    m_nRoomBottom   = m_nHeight / 2 - 2;
    
    m_nIndexEntrance = -1;
    m_nIndexExit = -1;
}
bool MineBossLevel::build()
{
    int bottomMost = INT_MAX;
    
    for (int i=0; i < 8; i++) {
        int left, right, top, bottom;
        if (cocos2d::random(0, 1) == 0) {
            left = cocos2d::random( 1, m_nRoomLeft - 5 );
            right = m_nRoomRight + 5;
        } else {
            left = m_nRoomLeft - 5;
            right = cocos2d::random( m_nRoomRight + 5, m_nWidth - 2 );
        }
        if (cocos2d::random(0, 1) == 0) {
            bottom = cocos2d::random( 2, m_nRoomBottom - 3 );
            top = m_nRoomTop + 3;
        } else {
            bottom = m_nRoomLeft - 3;
            top = cocos2d::random( m_nRoomBottom + 3, m_nHeight - 1 );
        }
        
        generateTerrainTiles(left, bottom, right - left + 1, top - bottom + 1, TerrainTile::TT_STANDARD, Area::AT_BOSS_ROOM);
        
        if (bottom < bottomMost) {
            bottomMost = bottom;
            m_nIndexEntrance = cocos2d::random( left + 3, right - 3 ) + (bottomMost+3) * m_nWidth;
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
    
    generateTerrainTiles( m_nRoomLeft - 1, m_nRoomBottom - 1,
                         m_nRoomRight - m_nRoomLeft + 5, m_nRoomTop - m_nRoomBottom + 5, TerrainTile::TT_WALL, Area::AT_BOSS_EXIT );
    generateTerrainTiles(m_nRoomLeft, m_nRoomBottom,
                         m_nRoomRight - m_nRoomLeft + 3, m_nRoomTop - m_nRoomBottom + 3, TerrainTile::TT_STANDARD, Area::AT_BOSS_EXIT );
    
    m_nIndexExit = cocos2d::random( m_nRoomLeft, m_nRoomRight ) + (m_nRoomBottom-1) * m_nWidth;
    
    int entranceX = m_nIndexEntrance%m_nWidth;
    int entranceY = m_nIndexEntrance/m_nWidth;

    int exitX = m_nIndexExit%m_nWidth;
    int exitY = m_nIndexExit/m_nWidth;
    
    setTerrainTile(entranceX, entranceY, TerrainTile::TT_ENTRANCE, Area::AT_BOSS_ROOM);
    setTerrainTile(exitX, exitY, TerrainTile::TT_LOCKED_BOSS_DOOR, Area::AT_BOSS_EXIT);
    
    for (int i=0; i < m_nLenght; i++) {
        if (m_Map[i].m_Type == TerrainTile::TT_STANDARD && cocos2d::random(0, 5) == 0) {
            m_Map[i].m_Type = TerrainTile::TT_GRIPPING_TRAP;
        }
    }
    updateTerrainTileFogOfWar(0, 0, m_nWidth, m_nHeight, true);
    
    generate();
    return true;
}
void MineBossLevel::generateAreaStyle()
{
    m_Style = LevelStyle::LS_STANDARD;
}
bool MineBossLevel::createMonsters()
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
bool MineBossLevel::createSummoningMonsters(const cocos2d::Vec2& mapPos)
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
bool MineBossLevel::createEliteMonster(int tileIndex)
{
    BaseMonster::MonsterType type = (BaseMonster::MonsterType)cocos2d::random((int)BaseMonster::MT_DEATHMINER, (int)BaseMonster::MT_ANKHEG);
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
void MineBossLevel::createSiegeMonsters(const cocos2d::Vec2& pos)
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
                    BaseMonster::MonsterType type = (BaseMonster::MonsterType)cocos2d::random((int)BaseMonster::MT_DEATHMINER, (int)BaseMonster::MT_ANKHEG);
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