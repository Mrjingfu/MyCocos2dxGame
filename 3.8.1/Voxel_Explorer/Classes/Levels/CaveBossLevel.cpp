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
#include "BossDoor.hpp"
#include "StandardPortal.hpp"
#include "StandardDoor.hpp"
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
                if(checkIndex >= m_Map.size())
                    continue;
                int checkX = checkIndex%m_nWidth;
                int checkY = checkIndex/m_nWidth;
                if(m_Map[checkIndex].m_Type == TerrainTile::TT_CHASM)
                    setTerrainTile(checkX, checkY, TerrainTile::TT_WALL, Area::AT_BOSS_ROOM);
            }
        }
    }
    m_nIndexEntrance = (bottomMost - m_nChamberHeight/2 - 2) * m_nWidth + m_nCenter;
    
    m_AreaExitRect = cocos2d::Rect(center.x - m_nChamberWidth/2 - 1, topMost, m_nChamberWidth + 2, m_nChamberHeight + 2);
    
    m_AreaExitCenter = Vec2((int)(m_AreaExitRect.getMidX()), (int)(m_AreaExitRect.getMidY()));
    
    if(m_AreaExitRect.size.width >= m_AreaExitRect.size.height)
    {
        setTerrainTile(m_AreaExitCenter.x - 1, m_AreaExitCenter.y, TerrainTile::TT_STANDARD_PORTAL, Area::AT_BOSS_EXIT);
        setTerrainTile(m_AreaExitCenter.x + 1, m_AreaExitCenter.y, TerrainTile::TT_STANDARD_PORTAL, Area::AT_BOSS_EXIT);
    }
    else
    {
        setTerrainTile(m_AreaExitCenter.x, m_AreaExitCenter.y - 1, TerrainTile::TT_STANDARD_PORTAL, Area::AT_BOSS_EXIT);
        setTerrainTile(m_AreaExitCenter.x, m_AreaExitCenter.y + 1, TerrainTile::TT_STANDARD_PORTAL, Area::AT_BOSS_EXIT);
    }

    
    int entranceX = m_nIndexEntrance%m_nWidth;
    int entranceY = m_nIndexEntrance/m_nWidth;
    setTerrainTile(entranceX, entranceY, TerrainTile::TT_ENTRANCE, Area::AT_STANDARD);
    
    updateTerrainTileFogOfWar(0, 0, m_nWidth, m_nHeight, true);
    
    m_BossPosition = Vec2(indexCenter%m_nWidth, indexCenter/m_nWidth);
    generate();
    return true;
}
bool CaveBossLevel::createTerrain()
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
                default:
                    break;
            }
            
        }
    }
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
            monster->setState(BaseMonster::MS_TRACKING);
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
                        monster->setState(BaseMonster::MS_TRACKING);
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
    giant->addTerrainTileFlag(TileInfo::ATTACKABLE);
    VoxelExplorer::getInstance()->getBossLayer()->addChild(giant);
    giant->setState(BaseBoss::BS_SLEEPING);

    return true;
}
bool CaveBossLevel::createTrapsByGiant(const cocos2d::Vec2& mapPos, int skillStage)
{
    if(!VoxelExplorer::getInstance()->getPlayer() || VoxelExplorer::getInstance()->getPlayer()->getState() == Player::PS_DEATH)
        return false;
    Vec2 playerPos = VoxelExplorer::getInstance()->getPlayer()->getPosInMap();
    if(skillStage == 1)
    {
        std::vector<int> neighbours13 = getNeighbours13();
        for (int i = 0; i < neighbours13.size(); i++) {
            if(neighbours13[i] == 0)
                continue;
            int index = playerPos.x + playerPos.y * m_nWidth + neighbours13[i];
            if(index >= m_Map.size())
                continue;
            if(m_Map[index].m_AreaType == Area::AT_BOSS_ROOM && m_Map[index].m_Type == TerrainTile::TT_STANDARD && cocos2d::random(0, 3) == 0)
            {
                std::vector<TerrainTile::TileType> trapTypes = { TerrainTile::TT_TOXIC_TRAP, TerrainTile::TT_FIRE_TRAP, TerrainTile::TT_PARALYTIC_TRAP, TerrainTile::TT_GRIPPING_TRAP, TerrainTile::TT_WEAK_TRAP };
                int randIndex = cocos2d::random(0, (int)(trapTypes.size() - 1));
                setTerrainTile(index%m_nWidth, index/m_nWidth, trapTypes[randIndex], Area::AT_BOSS_ROOM);
                VoxelExplorer::getInstance()->updateTerrainTile(index%m_nWidth, index/m_nWidth,trapTypes[randIndex]);
            }
        }
        return true;
    }
    else if(skillStage == 2)
    {
        std::vector<TerrainTile::TileType> trapTypes = { TerrainTile::TT_TOXIC_TRAP, TerrainTile::TT_FIRE_TRAP, TerrainTile::TT_PARALYTIC_TRAP, TerrainTile::TT_GRIPPING_TRAP, TerrainTile::TT_WEAK_TRAP };
        int randIndex = cocos2d::random(0, (int)(trapTypes.size() - 1));
        
        std::vector<int> neighbours9 = getNeighbours9();
        for (int i = 0; i < neighbours9.size(); i++) {
            if(neighbours9[i] == 0)
                continue;
            int index = mapPos.x + mapPos.y * m_nWidth + neighbours9[i];
            if(index >= m_Map.size())
                continue;
            if(m_Map[index].m_AreaType == Area::AT_BOSS_ROOM)
            {
                setTerrainTile(index%m_nWidth, index/m_nWidth, trapTypes[randIndex], Area::AT_BOSS_ROOM);
                VoxelExplorer::getInstance()->updateTerrainTile(index%m_nWidth, index/m_nWidth,trapTypes[randIndex]);
            }
        }
        return true;
    }
    else if(skillStage == 3)
    {
        return true;
    }
    return false;
}

void CaveBossLevel::clearBossRoom()
{
    for (int i=0; i < m_nLenght; i++) {
        if (m_Map[i].m_AreaType == Area::AT_BOSS_ROOM && m_Map[i].m_Type >= TerrainTile::TT_TOXIC_TRAP) {
            setTerrainTile(i%m_nWidth, i/m_nWidth, TerrainTile::TT_STANDARD, Area::AT_BOSS_ROOM);
            VoxelExplorer::getInstance()->updateTerrainTile(i%m_nWidth, i/m_nWidth,TerrainTile::TT_STANDARD);
        }
    }
    VoxelExplorer::getInstance()->clearBoosRoom();
    playBGStandardMusic();
}

bool CaveBossLevel::createPickableItems()
{
    std::vector<int> edgeIndexList = getTilesOnEdge(1);
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
std::vector<int> CaveBossLevel::getTilesOnEdge(int m)
{
    int leftOuter = m_AreaExitRect.getMinX() + 1;
    int rightOuter = m_AreaExitRect.getMaxX() - 2;
    int bottomOuter = m_AreaExitRect.getMinY() + 1;
    int topOuter = m_AreaExitRect.getMaxY() - 2;
    
    int leftInner = m_AreaExitRect.getMinX() + m + 1;
    int rightInner = m_AreaExitRect.getMaxX() - m - 2;
    int bottomInner = m_AreaExitRect.getMinY() + m + 1;
    int topInner = m_AreaExitRect.getMaxY() - m - 2;
    cocos2d::Rect rectOuter = cocos2d::Rect(MIN(leftOuter, rightOuter), MIN(bottomOuter, topOuter), std::abs(rightOuter - leftOuter), std::abs(topOuter - bottomOuter));
    
    cocos2d::Rect rectInner = cocos2d::Rect(MIN(leftInner, rightInner), MIN(bottomInner, topInner), std::abs(rightInner - leftInner), std::abs(topInner - bottomInner));
    
    std::vector<int> ret;
    for (int j = MIN(bottomOuter, topOuter); j <= MAX(bottomOuter, topOuter); ++j)
        for (int i = MIN(leftOuter, rightOuter); i <= MAX(leftOuter, rightOuter); ++i)
        {
            if(rectInner.containsPoint(Vec2(i, j)))
                continue;
            int index = i + j*m_nWidth;
            ret.push_back(index);
        }
    return ret;
}
void CaveBossLevel::handleUseStandardPortal(const cocos2d::Vec2& pos)
{
    if(m_AreaExitRect.size.width >= m_AreaExitRect.size.height)
    {
        if(pos.x < m_AreaExitCenter.x)
        {
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_SELECT_LEFT_DUNGEON_NODE);
        }
        else if(pos.x > m_AreaExitCenter.x)
        {
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_SELECT_RIGHT_DUNGEON_NODE);
        }
    }
    else
    {
        if(pos.y < m_AreaExitCenter.y)
        {
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_SELECT_LEFT_DUNGEON_NODE);
        }
        else if(pos.y > m_AreaExitCenter.y)
        {
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_SELECT_RIGHT_DUNGEON_NODE);
        }
    }
}