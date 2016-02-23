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
#include "BossDoor.hpp"
#include "StandardPortal.hpp"
#include "StandardDoor.hpp"
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
        distance = (int)PathGraph::buildPath(m_Areas, m_AreaEntrance, m_AreaExit).size();
        
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
    
    m_BossPosition = m_pArenaRoom->getCenter();
    ///处理
    assignAreasType();
    generate();
    
    return true;
}
bool PrisonBossLevel::createTerrain()
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
                        StandardPortal* portal = StandardPortal::create(false);
                        if(!portal)
                            return false;
                        portal->setPosition3D(Vec3(j*TerrainTile::CONTENT_SCALE, 0, -i*TerrainTile::CONTENT_SCALE));
                        VoxelExplorer::getInstance()->getTerrainPortalsLayer()->addChild(portal);
                        portal->setVisited(info.m_bVisited);
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
                case TerrainTile::TT_LOCKED_BOSS_DOOR:
                    {
                        BossDoor* door = BossDoor::create(false);
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
                case TerrainTile::TT_LOCKED_MAGIC_DOOR:
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
            monster->setState(BaseMonster::MS_TRACKING);
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
                        monster->setState(BaseMonster::MS_TRACKING);
                    }
                }
            }
        }
    }
}
bool PrisonBossLevel::createBoss(const cocos2d::Vec2& pos)
{
    Warden* warden = Warden::create(BaseBoss::BT_WARDEN);
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
bool PrisonBossLevel::createSummoningMonstersByWarden(const cocos2d::Vec2& mapPos, int skillStage)
{
    if(!VoxelExplorer::getInstance()->getPlayer() || VoxelExplorer::getInstance()->getPlayer()->getState() == Player::PS_DEATH)
        return false;
    if(!m_pArenaRoom)
        return false;
    if(skillStage == 1)
    {
        int count = 0;
        std::vector<int> cornerPosList = m_pArenaRoom->getTilesOnCorner(this);
        for (int i = 0; i<cornerPosList.size(); i++) {
            int tileIndex = cornerPosList[i];
            if(isTerrainTilePassable(tileIndex))
            {
                StandardMonster* monster = StandardMonster::create(BaseMonster::MT_PRISONGUARD);
                if(!monster)
                    return false;
                monster->setPosition3D(Vec3(m_Map[tileIndex].m_nX*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -m_Map[tileIndex].m_nY*TerrainTile::CONTENT_SCALE));
                monster->setVisited(m_Map[tileIndex].m_bVisited);
                monster->addTerrainTileFlag(TileInfo::ATTACKABLE);
                VoxelExplorer::getInstance()->getMonstersLayer()->addChild(monster);
                monster->setState(BaseMonster::MS_TRACKING);
                monster->setMonsterFOV(7);
                count++;
                if(count == 4)
                    break;
            }
        }
        if(count < 4)
        {
            int newCount = 4 - count;
            for (int i = 0; i<newCount; i++) {
                int tileIndex = m_pArenaRoom->getRandomTile(this);
                if(isTerrainTilePassable(tileIndex))
                {
                    StandardMonster* monster = StandardMonster::create(BaseMonster::MT_PRISONGUARD);
                    if(!monster)
                        return false;
                    monster->setPosition3D(Vec3(m_Map[tileIndex].m_nX*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -m_Map[tileIndex].m_nY*TerrainTile::CONTENT_SCALE));
                    monster->setVisited(m_Map[tileIndex].m_bVisited);
                    monster->addTerrainTileFlag(TileInfo::ATTACKABLE);
                    VoxelExplorer::getInstance()->getMonstersLayer()->addChild(monster);
                    monster->setState(BaseMonster::MS_TRACKING);
                    monster->setMonsterFOV(7);
                }
                else
                {
                    i--;
                    continue;
                }
            }
        }
        if(m_pArenaRoom)
        {
            std::vector<int> edgeIndexList = m_pArenaRoom->getTilesOnEdge(this, 1);
            for (int i = 0; i < edgeIndexList.size(); i++) {
                int x = edgeIndexList[i]%m_nWidth;
                int y = edgeIndexList[i]/m_nWidth;
                setTerrainTileType(x, y, TerrainTile::TT_GRIPPING_TRAP);
                VoxelExplorer::getInstance()->updateTerrainTile(x, y, TerrainTile::TT_GRIPPING_TRAP);
            }
        }
        return true;
    }
    else if(skillStage == 2)
    {
        return true;
    }
    else if(skillStage == 3)
    {
        int count = 0;
        std::vector<int> cornerPosList = m_pArenaRoom->getTilesOnCorner(this);
        for (int i = 0; i<cornerPosList.size(); i++) {
            int tileIndex = cornerPosList[i];
            if(isTerrainTilePassable(tileIndex))
            {
                StandardMonster* monster = StandardMonster::create(BaseMonster::MT_TORTURE);
                if(!monster)
                    return false;
                monster->setPosition3D(Vec3(m_Map[tileIndex].m_nX*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -m_Map[tileIndex].m_nY*TerrainTile::CONTENT_SCALE));
                monster->setVisited(m_Map[tileIndex].m_bVisited);
                monster->addTerrainTileFlag(TileInfo::ATTACKABLE);
                VoxelExplorer::getInstance()->getMonstersLayer()->addChild(monster);
                monster->setState(BaseMonster::MS_TRACKING);
                monster->setMonsterFOV(7);
                count++;
                if(count == 4)
                    break;
            }
        }
        if(count < 4)
        {
            int newCount = 4 - count;
            for (int i = 0; i<newCount; i++) {
                int tileIndex = m_pArenaRoom->getRandomTile(this);
                if(isTerrainTilePassable(tileIndex))
                {
                    StandardMonster* monster = StandardMonster::create(BaseMonster::MT_TORTURE, true);
                    if(!monster)
                        return false;
                    monster->setPosition3D(Vec3(m_Map[tileIndex].m_nX*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -m_Map[tileIndex].m_nY*TerrainTile::CONTENT_SCALE));
                    monster->setVisited(m_Map[tileIndex].m_bVisited);
                    monster->addTerrainTileFlag(TileInfo::ATTACKABLE);
                    VoxelExplorer::getInstance()->getMonstersLayer()->addChild(monster);
                    monster->setState(BaseMonster::MS_TRACKING);
                    monster->setMonsterFOV(7);
                }
                else
                {
                    i--;
                    continue;
                }
            }
        }
        return true;
    }
    return false;
}
void PrisonBossLevel::clearBossRoom()
{
    if(m_pArenaRoom)
    {
        std::vector<int> edgeIndexList = m_pArenaRoom->getTilesOnEdge(this, 1);
        for (int i = 0; i < edgeIndexList.size(); i++) {
            int x = edgeIndexList[i]%m_nWidth;
            int y = edgeIndexList[i]/m_nWidth;
            setTerrainTileType(x, y, TerrainTile::TT_STANDARD);
            VoxelExplorer::getInstance()->updateTerrainTile(x, y, TerrainTile::TT_STANDARD);
        }
    }

    VoxelExplorer::getInstance()->clearBoosRoom();
    playBGStandardMusic();
}

bool PrisonBossLevel::createPickableItems()
{
    if(!m_AreaExit)
        return false;
    std::vector<int> edgeIndexList = m_AreaExit->getTilesOnEdge(this, 1);
    for (int i = 0; i < edgeIndexList.size(); i++) {
        int tileIndex = edgeIndexList[i];
        
        std::vector<int> neighbours8 = this->getNeighbours8();
        bool neighbourHasDoor = false;
        for (int j = 0; j<neighbours8.size(); ++j) {
            if(m_Map[neighbours8[j] + tileIndex].m_Type == TerrainTile::TT_LOCKED_BOSS_DOOR)
                neighbourHasDoor = true;
        }
        if(neighbourHasDoor)
            continue;
        
        int playerlevel = (int)PlayerProperty::getInstance()->getLevel().GetLongValue();
        int itemLevel = cocos2d::random(playerlevel - 3, playerlevel + 3);
        if(itemLevel < 1)
            itemLevel = 1;
        
        PickableItem::PickableItemType type = PickableItem::generatePickItemByMonsterLevel(itemLevel);
        if(type == PickableItem::PIT_UNKNOWN)
            continue;
        
        PickableItem* item = PickableItem::create(type, itemLevel);
        if(!item)
            return false;
        else
        {
            item->setPosition3D(Vec3(m_Map[tileIndex].m_nX*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -m_Map[tileIndex].m_nY*TerrainTile::CONTENT_SCALE));
            item->setVisited(m_Map[tileIndex].m_bVisited);
            VoxelExplorer::getInstance()->getPickableItemsLayer()->addChild(item);
            item->setState(PickableItem::PIS_IDLE);
        }
        
    }
    return true;
}
void PrisonBossLevel::handleUseStandardPortal(const cocos2d::Vec2& pos)
{
    if(m_AreaExit)
    {
        cocos2d::Rect rect = m_AreaExit->getRect();
        Vec2 center = m_AreaExit->getCenter();
        if(rect.size.width >= rect.size.height)
        {
            if(pos.x < center.x)
            {
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_SELECT_LEFT_DUNGEON_NODE);
            }
            else if(pos.x > center.x)
            {
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_SELECT_RIGHT_DUNGEON_NODE);
            }
        }
        else
        {
            if(pos.y < center.y)
            {
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_SELECT_LEFT_DUNGEON_NODE);
            }
            else if(pos.y > center.y)
            {
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_SELECT_RIGHT_DUNGEON_NODE);
            }
        }
    }
}