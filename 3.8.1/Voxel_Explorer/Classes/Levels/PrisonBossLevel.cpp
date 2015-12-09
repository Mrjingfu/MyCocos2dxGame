//
//  PrisonBossLevel.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/12/3.
//
//

#include "PrisonBossLevel.hpp"
#include "Graph.h"
#include "VoxelExplorer.h"
#include "StandardMonster.hpp"
#include "Warden.hpp"
USING_NS_CC;

PrisonBossLevel::PrisonBossLevel()
{
    m_nMinAreaSize  = 7;
    m_nMaxAreaSize  = 9;
    m_nSplitAreaSize = 3;
    m_nMinStandardAreaCount = 2;
    
    m_pArenaRoom = nullptr;
    m_nArenaDoor = -1;
}
bool PrisonBossLevel::build()
{
    if(!initAreas())
        return false;
    int distance = 0;
    int retry = 0;
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
        } while (m_AreaExit == m_AreaEntrance || m_AreaExit->getRect().size.width < 7 || m_AreaExit->getRect().size.height < 7 || m_AreaExit->getRect().getMinY() <= m_AreaEntrance->getRect().getMaxY());
        
        PathGraph::buildDistanceMap(m_Areas, m_AreaExit);
        distance = PathGraph::buildPath(m_Areas, m_AreaEntrance, m_AreaExit).size();
        
        if (retry++ > 10) {
            return false;
        }
    }
    while (distance < 4);
    
    m_AreaEntrance->setAreaType(Area::AT_ENTRANCE);
    m_AreaExit->setAreaType(Area::AT_BOSS_EXIT);
    
    std::vector<PathGraphNode*> path = PathGraph::buildPath( m_Areas, m_AreaEntrance, m_AreaExit );
    PathGraph::setWeight(path, m_AreaEntrance->getDistance());
    
    PathGraph::buildDistanceMap( m_Areas, m_AreaExit );
    path = PathGraph::buildPath( m_Areas, m_AreaEntrance, m_AreaExit );
    
    m_pArenaRoom = static_cast<Area*>(path[path.size()-2]);
    if(m_pArenaRoom)
    {
        if(m_pArenaRoom->getRect().size.width < 7 || m_pArenaRoom->getRect().size.height < 7)
            return false;
        m_pArenaRoom->setAreaType(Area::AT_BOSS_ROOM);
    }
    
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
    if(m_AreaExit->getRect().getMinY() == area->getRect().getMinY())
        return false;
    
    for (PathGraphNode* node : path) {
        Area* areaNode = static_cast<Area*>(node);
        if(areaNode)
        {
            if(areaNode->getAreaType() == Area::AT_UNKNOWN && areaNode->getConnectedAreas().size() > 0)
                areaNode->setAreaType(Area::AT_PASSAGE);
        }
    }
    
    m_BossPosition = m_AreaExit->getCenter();
    ///处理
    assignAreasType();
    generate();
    
    return true;
}
void PrisonBossLevel::generateAreaStyle()
{
    m_Style = LevelStyle::LS_STANDARD;
}
bool PrisonBossLevel::createMonsters()
{
    if(!createBoss(m_BossPosition))
    {
        CCLOG("Create boss failed!");
        return false;
    }
    int monsterNum = calculateLevelMonsterCount();
    for (int i=0; i < monsterNum; i++) {
        std::vector<BaseMonster::MonsterType> monsterTypes = { BaseMonster::MT_PRISONGUARD, BaseMonster::MT_TORTURE };
        int rand = cocos2d::random(0, int(monsterTypes.size() - 1));
        StandardMonster* monster = StandardMonster::create(monsterTypes[rand]);
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
bool PrisonBossLevel::createSummoningMonsters(const cocos2d::Vec2& mapPos)
{
    std::vector<int> neighbours4 = getNeighbours4();
    for (int i = 0; i < neighbours4.size(); i++) {
        int index = mapPos.x + mapPos.y * m_nWidth + neighbours4[i];
        if(isTerrainTilePassable(index))
        {
            std::vector<BaseMonster::MonsterType> monsterTypes = { BaseMonster::MT_PRISONGUARD, BaseMonster::MT_TORTURE };
            int rand = cocos2d::random(0, int(monsterTypes.size() - 1));
            StandardMonster* monster = StandardMonster::create(monsterTypes[rand]);
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
bool PrisonBossLevel::createEliteMonster(int tileIndex)
{
    std::vector<BaseMonster::MonsterType> monsterTypes = { BaseMonster::MT_PRISONGUARD, BaseMonster::MT_TORTURE };
    int rand = cocos2d::random(0, int(monsterTypes.size() - 1));
    StandardMonster* monster = StandardMonster::create(monsterTypes[rand], true);
    if(!monster)
        return false;
    monster->setPosition3D(Vec3(m_Map[tileIndex].m_nX*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -m_Map[tileIndex].m_nY*TerrainTile::CONTENT_SCALE));
    monster->setVisited(m_Map[tileIndex].m_bVisited);
    monster->addTerrainTileFlag(TileInfo::ATTACKABLE);
    VoxelExplorer::getInstance()->getMonstersLayer()->addChild(monster);
    monster->setState(BaseMonster::MS_SLEEPING);
    
    return true;
}
void PrisonBossLevel::createSiegeMonsters(const cocos2d::Vec2& pos)
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
                    std::vector<BaseMonster::MonsterType> monsterTypes = { BaseMonster::MT_PRISONGUARD, BaseMonster::MT_TORTURE };
                    int rand = cocos2d::random(0, int(monsterTypes.size() - 1));
                    StandardMonster* monster = StandardMonster::create(monsterTypes[rand]);
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
bool PrisonBossLevel::createBoss(const cocos2d::Vec2& pos)
{
    Warden* warden = Warden::create(BaseBoss::BT_SKELETONKING);
    if(!warden)
        return false;
    int tileIndex = pos.x + pos.y * m_nWidth;
    warden->setPosition3D(Vec3(m_Map[tileIndex].m_nX*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -m_Map[tileIndex].m_nY*TerrainTile::CONTENT_SCALE));
    warden->setVisited(m_Map[tileIndex].m_bVisited);
    warden->addTerrainTileFlag(TileInfo::ATTACKABLE);
    VoxelExplorer::getInstance()->getBossLayer()->addChild(warden);
    warden->setState(BaseBoss::BS_SLEEPING);

    return true;
}