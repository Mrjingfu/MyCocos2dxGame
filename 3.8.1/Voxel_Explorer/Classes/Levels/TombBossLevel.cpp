//
//  TombBossLevel.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/12/3.
//
//

#include "TombBossLevel.hpp"
#include "Graph.h"
#include "VoxelExplorer.h"
#include "StandardMonster.hpp"
#include "SkeletonKing.hpp"
USING_NS_CC;

TombBossLevel::TombBossLevel()
{
    m_nBottom           = 15;
    m_nHallWidth		= 15;
    m_nHallHeight       = 15;
    m_nChamberWidth     = 9;
    m_nChamberHeight	= 7;
    
    m_nLeft	= (m_nWidth - m_nHallWidth) / 2 + 1;
    m_nCenter	= m_nLeft + m_nHallWidth / 2;
    
    m_nIndexEntrance = -1;
    m_nIndexExit = -1;
    m_nArenaDoor = -1;
}
bool TombBossLevel::build()
{
    generateTerrainTiles( m_nLeft, m_nBottom, m_nHallWidth, m_nHallHeight, TerrainTile::TT_STANDARD, Area::AT_BOSS_ROOM );
    generateTerrainTiles( m_nCenter, m_nBottom, 1, m_nHallHeight, TerrainTile::TT_TUNNEL, Area::AT_BOSS_ROOM );
    generateTerrainTiles( m_nCenter-1, m_nBottom, 1, m_nHallHeight, TerrainTile::TT_TUNNEL, Area::AT_BOSS_ROOM );
    generateTerrainTiles( m_nCenter+1, m_nBottom, 1, m_nHallHeight, TerrainTile::TT_TUNNEL, Area::AT_BOSS_ROOM );
    
    generateTerrainTiles( m_nLeft + m_nChamberWidth/4 + 1, m_nBottom + m_nHallHeight + 1, m_nChamberWidth, m_nChamberHeight, TerrainTile::TT_STANDARD, Area::AT_BOSS_EXIT );
    
    generateTerrainTiles( m_nLeft + m_nChamberWidth/4 + 1, m_nBottom - m_nChamberHeight - 1, m_nChamberWidth, m_nChamberHeight, TerrainTile::TT_STANDARD, Area::AT_STANDARD );
    
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
    
    int y = m_nBottom + 1;
    while (y < m_nBottom + m_nHallHeight) {
        int wallIndexLeft = y * m_nWidth + m_nCenter - 4;
        int wallIndexRight = y * m_nWidth + m_nCenter + 4;
        int wallIndexLeftX = wallIndexLeft%m_nWidth;
        int wallIndexLeftY = wallIndexLeft/m_nWidth;
        int wallIndexRightX = wallIndexRight%m_nWidth;
        int wallIndexRightY = wallIndexRight/m_nWidth;
        setTerrainTile(wallIndexLeftX, wallIndexLeftY, TerrainTile::TT_WALL, Area::AT_BOSS_ROOM);
        setTerrainTile(wallIndexRightX, wallIndexRightY, TerrainTile::TT_WALL, Area::AT_BOSS_ROOM);
        y += 4;
    }
    
    for (int i=0; i < m_nLenght; i++) {
        if (m_Map[i].m_Type == TerrainTile::TT_STANDARD && m_Map[i].m_AreaType == Area::AT_BOSS_ROOM && cocos2d::random(0, 16) == 0) {
            int trapX = i%m_nWidth;
            int trapY = i/m_nWidth;
            std::vector<TerrainTile::TileType> randTypes = { TerrainTile::TT_HIDE_TOXIC_TRAP,TerrainTile::TT_HIDE_FIRE_TRAP, TerrainTile::TT_HIDE_PARALYTIC_TRAP, TerrainTile::TT_HIDE_GRIPPING_TRAP, TerrainTile::TT_HIDE_SUMMONING_TRAP, TerrainTile::TT_HIDE_WEAK_TRAP };
            int randTrap = cocos2d::random(0, int(randTypes.size() - 1));
            setTerrainTile(trapX, trapY, randTypes[randTrap], Area::AT_BOSS_ROOM);
        }
    }
    
    m_nIndexEntrance = (m_nBottom - 1 - m_nChamberHeight/2 - 1) * m_nWidth + m_nCenter;
    m_nIndexExit = (m_nBottom + m_nHallHeight) * m_nWidth + m_nCenter;
    m_nArenaDoor = (m_nBottom - 1) * m_nWidth + m_nCenter;
    
    int entranceX = m_nIndexEntrance%m_nWidth;
    int entranceY = m_nIndexEntrance/m_nWidth;
    int arenaDoorX = m_nArenaDoor%m_nWidth;
    int arenaDoorY = m_nArenaDoor/m_nWidth;
    int exitX = m_nIndexExit%m_nWidth;
    int exitY = m_nIndexExit/m_nWidth;
    
    setTerrainTile(entranceX, entranceY, TerrainTile::TT_ENTRANCE, Area::AT_BOSS_ROOM);
    setTerrainTile(arenaDoorX, arenaDoorY, TerrainTile::TT_DOOR, Area::AT_BOSS_ROOM, Actor::AD_FORWARD);
    setTerrainTile(exitX, exitY, TerrainTile::TT_LOCKED_BOSS_DOOR, Area::AT_BOSS_EXIT, Actor::AD_FORWARD);
    
    updateTerrainTileFogOfWar(0, 0, m_nWidth, m_nHeight, true);
    
    m_BossPosition = Vec2(exitX, exitY-2);
    generate();
    return true;
}
bool TombBossLevel::createMonsters()
{
    if(!createBoss(m_BossPosition))
    {
        CCLOG("Create boss failed!");
        return false;
    }
    return true;
}
bool TombBossLevel::createSummoningMonsters(const cocos2d::Vec2& mapPos)
{
    std::vector<int> neighbours4 = getNeighbours4();
    for (int i = 0; i < neighbours4.size(); i++) {
        int index = mapPos.x + mapPos.y * m_nWidth + neighbours4[i];
        if(isTerrainTilePassable(index))
        {
            BaseMonster::MonsterType type = (BaseMonster::MonsterType)cocos2d::random((int)BaseMonster::MT_SKELETON, (int)BaseMonster::MT_GHOUL);
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
bool TombBossLevel::createEliteMonster(int tileIndex)
{
    BaseMonster::MonsterType type = (BaseMonster::MonsterType)cocos2d::random((int)BaseMonster::MT_SKELETON, (int)BaseMonster::MT_GHOUL);
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
void TombBossLevel::createSiegeMonsters(const cocos2d::Vec2& pos)
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
                    BaseMonster::MonsterType type = (BaseMonster::MonsterType)cocos2d::random((int)BaseMonster::MT_SKELETON, (int)BaseMonster::MT_GHOUL);
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
bool TombBossLevel::createBoss(const cocos2d::Vec2& pos)
{
    SkeletonKing* skeletonKing = SkeletonKing::create(BaseBoss::BT_SKELETONKING);
    if(!skeletonKing)
        return false;
    int tileIndex = pos.x + pos.y * m_nWidth;
    skeletonKing->setPosition3D(Vec3(m_Map[tileIndex].m_nX*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -m_Map[tileIndex].m_nY*TerrainTile::CONTENT_SCALE));
    skeletonKing->setVisited(m_Map[tileIndex].m_bVisited);
    skeletonKing->addTerrainTileFlag(TileInfo::USEABLE);
    VoxelExplorer::getInstance()->getBossLayer()->addChild(skeletonKing);
    skeletonKing->setState(BaseBoss::BS_IDLE);
    
    return true;
}