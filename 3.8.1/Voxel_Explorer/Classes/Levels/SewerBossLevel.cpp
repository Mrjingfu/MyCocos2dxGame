//
//  SewerBossLevel.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/12/1.
//
//

#include "SewerBossLevel.hpp"
#include "Graph.h"
#include "VoxelExplorer.h"
#include "StandardMonster.hpp"
#include "SlimeKing.hpp"
USING_NS_CC;

SewerBossLevel::SewerBossLevel()
{
    m_nMinAreaSize  = 9;
    m_nMaxAreaSize  = 11;
    m_nSplitAreaSize = 3;
}
bool SewerBossLevel::build()
{
    if(!initAreas())
        return false;
    int distance = 0;
    int retry = 0;
    int minDistance = (int)sqrt(m_Areas.size());
    
    do
    {
        int innerRetry = 0;
        do
        {
            if (innerRetry++ > 10) {
                return false;
            }
            int rand = cocos2d::random(0, (int)(m_Areas.size())-1);
            m_AreaEntrance = static_cast<Area*>(m_Areas[rand]);
        } while (m_AreaEntrance->getRect().size.width < 4 || m_AreaEntrance->getRect().size.height <4);
        
        innerRetry = 0;
        do
        {
            if (innerRetry++ > 10) {
                return false;
            }
            int rand = cocos2d::random(0, (int)(m_Areas.size())-1);
            m_AreaExit = static_cast<Area*>(m_Areas[rand]);
        } while (m_AreaExit == m_AreaEntrance || m_AreaExit->getRect().size.width < 8 || m_AreaExit->getRect().size.height < 8 || m_AreaExit->getRect().getMinY() <= m_AreaEntrance->getRect().getMaxY());
        
        PathGraph::buildDistanceMap(m_Areas, m_AreaExit);
        
        distance = m_AreaEntrance->getDistance();
        
        if (retry++ > 10) {
            return false;
        }
    }
    while (distance < minDistance);
    
    m_AreaEntrance->setAreaType(Area::AT_ENTRANCE);
    m_AreaExit->setAreaType(Area::AT_BOSS_ROOM);
    
    PathGraph::buildDistanceMap( m_Areas, m_AreaExit );
    
    std::vector<PathGraphNode*> path = PathGraph::buildPath( m_Areas, m_AreaEntrance, m_AreaExit );

    PathGraph::setWeight(path, m_AreaEntrance->getDistance());
    
    PathGraph::buildDistanceMap( m_Areas, m_AreaExit );
    path = PathGraph::buildPath( m_Areas, m_AreaEntrance, m_AreaExit );
    
    Area* area = m_AreaEntrance;
    for (PathGraphNode* node : path) {
        Area* next = static_cast<Area*>(node);
        if(next)
        {
            area->connectArea(next);
            area = next;
        }
    }
    
    area = m_AreaExit->getConnectedAreas().begin()->first;
    if(m_AreaExit->getRect().getMinY() == area->getRect().getMaxY())
        return false;
    
    for (PathGraphNode* node : path) {
        Area* areaNode = static_cast<Area*>(node);
        if(areaNode)
        {
            if(areaNode->getAreaType() == Area::AT_UNKNOWN && areaNode->getConnectedAreas().size() > 0)
                areaNode->setAreaType(Area::AT_TUNNEL);
        }
    }
    std::vector<Area*> candidates;
    for (PathGraphNode* node : m_AreaExit->getNeigbours()) {
        Area* areaNode = static_cast<Area*>(node);
        if(areaNode)
        {
            if (m_AreaExit->getConnectedAreas().find(areaNode) == m_AreaExit->getConnectedAreas().end() && (m_AreaExit->getRect().getMaxX() == areaNode->getRect().getMinX() || m_AreaExit->getRect().getMinX() == areaNode->getRect().getMaxX() || m_AreaExit->getRect().getMaxY() == areaNode->getRect().getMinY()) && (areaNode->getRect().size.width >= 6 && areaNode->getRect().size.height >= 6)) {
                candidates.push_back(areaNode);
            }
        }
    }
    if (candidates.size() > 0) {
        int rand = cocos2d::random(0, (int)(candidates.size())-1);
        Area* bossExitRoom = candidates[rand];
        if(bossExitRoom)
        {
            bossExitRoom->connectArea(m_AreaExit);
            bossExitRoom->setAreaType(Area::AT_BOSS_EXIT);
        }
    }
    else
        return false;
    
    m_BossPosition = m_AreaExit->getCenter();
    ///处理
    assignAreasType();
    generate();
    
    return true;
}
void SewerBossLevel::generateAreaStyle()
{
    m_Style = LevelStyle::LS_STANDARD;
}
bool SewerBossLevel::createMonsters()
{
    if(!createBoss(m_BossPosition))
    {
        CCLOG("Create boss failed!");
        return false;
    }
    int monsterNum = calculateLevelMonsterCount();
    for (int i=0; i < monsterNum; i++) {
        StandardMonster* monster = StandardMonster::create(BaseMonster::MT_SLIME);
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
bool SewerBossLevel::createSummoningMonsters(const cocos2d::Vec2& mapPos)
{
    std::vector<int> neighbours4 = getNeighbours4();
    for (int i = 0; i < neighbours4.size(); i++) {
        int index = mapPos.x + mapPos.y * m_nWidth + neighbours4[i];
        if(isTerrainTilePassable(index))
        {
            StandardMonster* monster = StandardMonster::create(BaseMonster::MT_SLIME);
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
bool SewerBossLevel::createEliteMonster(int tileIndex)
{
    StandardMonster* monster = StandardMonster::create(BaseMonster::MT_SLIME, true);
    if(!monster)
        return false;
    monster->setPosition3D(Vec3(m_Map[tileIndex].m_nX*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -m_Map[tileIndex].m_nY*TerrainTile::CONTENT_SCALE));
    monster->setVisited(m_Map[tileIndex].m_bVisited);
    monster->addTerrainTileFlag(TileInfo::ATTACKABLE);
    VoxelExplorer::getInstance()->getMonstersLayer()->addChild(monster);
    monster->setState(BaseMonster::MS_SLEEPING);
    
    return true;
}
void SewerBossLevel::createSiegeMonsters(const cocos2d::Vec2& pos)
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
                    BaseMonster::MonsterType type = (BaseMonster::MonsterType)cocos2d::random((int)BaseMonster::MT_RAT, (int)BaseMonster::MT_SLIME);
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
bool SewerBossLevel::createBoss(const cocos2d::Vec2& pos)
{
    SlimeKing* slimeKing = SlimeKing::create(BaseBoss::BT_SLIMEKING);
    if(!slimeKing)
        return false;
    int tileIndex = pos.x + pos.y * m_nWidth;
    slimeKing->setPosition3D(Vec3(m_Map[tileIndex].m_nX*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -m_Map[tileIndex].m_nY*TerrainTile::CONTENT_SCALE));
    slimeKing->setVisited(m_Map[tileIndex].m_bVisited);
    slimeKing->addTerrainTileFlag(TileInfo::USEABLE);
    VoxelExplorer::getInstance()->getBossLayer()->addChild(slimeKing);
    slimeKing->setState(BaseBoss::BS_IDLE);
    
    return true;
}