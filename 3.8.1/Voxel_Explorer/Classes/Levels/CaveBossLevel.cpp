//
//  CaveBossLevel.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/12/3.
//
//

#include "CaveBossLevel.hpp"
#include "Graph.h"
#include "VoxelExplorer.h"
#include "StandardMonster.hpp"
#include "Giant.hpp"
USING_NS_CC;

CaveBossLevel::CaveBossLevel()
{
    m_nHallRadius		= 9;
    m_nChamberWidth     = 9;
    m_nChamberHeight	= 7;
    
    m_nLeft	= (m_nWidth - m_nHallRadius) / 2 + 1;
    m_nCenter	= m_nLeft + m_nHallRadius / 2;
    
    m_nIndexEntrance = -1;
    m_nIndexExit = -1;
    m_nArenaDoor = -1;
}
bool CaveBossLevel::build()
{
    int topMost = 0;
    int bottomMost = INT_MAX;
    int leftMost = INT_MAX;
    int rightMost = 0;
    int indexCenter = (m_nHeight/2 + 1)*m_nWidth + m_nCenter;
    Vec2 center = Vec2(indexCenter%m_nWidth, indexCenter/m_nWidth);
    for (int i=0; i < m_nLenght; i++) {
        int checkPointX = i%m_nWidth;
        int checkPointY = i/m_nWidth;
        Vec2 checkPoint = Vec2(checkPointX, checkPointY);
        if(checkPoint.distance(center) <= m_nHallRadius)
        {
            setTerrainTile(checkPoint.x, checkPoint.y, TerrainTile::TT_STANDARD, Area::AT_BOSS_ROOM);
            if(checkPoint.y > topMost)
                topMost = checkPoint.y;
            else if(checkPoint.y < bottomMost)
                bottomMost = checkPoint.y;
            if(checkPoint.x < leftMost)
                leftMost = checkPoint.x;
            else if(checkPoint.x > rightMost)
                rightMost = checkPoint.x;
        }
    }
    setTerrainTile(leftMost, center.y, TerrainTile::TT_CHASM, Area::AT_UNKNOWN);
    setTerrainTile(rightMost, center.y, TerrainTile::TT_CHASM, Area::AT_UNKNOWN);
    setTerrainTile(center.x, topMost, TerrainTile::TT_LOCKED_BOSS_DOOR, Area::AT_BOSS_EXIT, Actor::AD_FORWARD);
    setTerrainTile(center.x, bottomMost - 1, TerrainTile::TT_LOCKED_MAGIC_DOOR, Area::AT_BOSS_ROOM, Actor::AD_FORWARD);
    
    generateTerrainTiles( center.x - m_nChamberWidth/2, topMost + 1, m_nChamberWidth, m_nChamberHeight, TerrainTile::TT_STANDARD, Area::AT_BOSS_EXIT );
    
    generateTerrainTiles( center.x - m_nChamberWidth/2, bottomMost - m_nChamberHeight - 1, m_nChamberWidth, m_nChamberHeight, TerrainTile::TT_STANDARD, Area::AT_STANDARD );
    
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
    m_nIndexEntrance = (bottomMost - m_nChamberHeight/2 - 2) * m_nWidth + m_nCenter;
    int entranceX = m_nIndexEntrance%m_nWidth;
    int entranceY = m_nIndexEntrance/m_nWidth;
    setTerrainTile(entranceX, entranceY, TerrainTile::TT_ENTRANCE, Area::AT_BOSS_ROOM);
    
    updateTerrainTileFogOfWar(0, 0, m_nWidth, m_nHeight, true);
    
    m_BossPosition = Vec2(indexCenter%m_nWidth, indexCenter/m_nWidth);
    generate();
    return true;
}
bool CaveBossLevel::createMonsters()
{
    if(!createBoss(m_BossPosition))
    {
        CCLOG("Create boss failed!");
        return false;
    }
    return true;
}
bool CaveBossLevel::createSummoningMonsters(const cocos2d::Vec2& mapPos)
{
    std::vector<int> neighbours4 = getNeighbours4();
    for (int i = 0; i < neighbours4.size(); i++) {
        int index = mapPos.x + mapPos.y * m_nWidth + neighbours4[i];
        if(isTerrainTilePassable(index))
        {
            BaseMonster::MonsterType type = (BaseMonster::MonsterType)cocos2d::random((int)BaseMonster::MT_WOLF, (int)BaseMonster::MT_GNOLL);
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
bool CaveBossLevel::createEliteMonster(int tileIndex)
{
    BaseMonster::MonsterType type = (BaseMonster::MonsterType)cocos2d::random((int)BaseMonster::MT_WOLF, (int)BaseMonster::MT_GNOLL);
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
void CaveBossLevel::createSiegeMonsters(const cocos2d::Vec2& pos)
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
                    BaseMonster::MonsterType type = (BaseMonster::MonsterType)cocos2d::random((int)BaseMonster::MT_WOLF, (int)BaseMonster::MT_GNOLL);
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
bool CaveBossLevel::createBoss(const cocos2d::Vec2& pos)
{
    Giant* giant = Giant::create(BaseBoss::BT_GIANT);
    if(!giant)
        return false;
    int tileIndex = pos.x + pos.y * m_nWidth;
    giant->setPosition3D(Vec3(m_Map[tileIndex].m_nX*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -m_Map[tileIndex].m_nY*TerrainTile::CONTENT_SCALE));
    giant->setVisited(m_Map[tileIndex].m_bVisited);
    giant->addTerrainTileFlag(TileInfo::USEABLE);
    VoxelExplorer::getInstance()->getBossLayer()->addChild(giant);
    giant->setState(BaseBoss::BS_SLEEPING);

    return true;
}