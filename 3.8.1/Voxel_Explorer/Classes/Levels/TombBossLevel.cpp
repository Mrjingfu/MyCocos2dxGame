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
#include "BossDoor.hpp"
#include "StandardPortal.hpp"
#include "StandardDoor.hpp"
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
                if(checkIndex >= m_Map.size())
                    continue;
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
        m_GeneratePoints.push_back(Vec2(wallIndexLeftX, wallIndexLeftY));
        m_GeneratePoints.push_back(Vec2(wallIndexRightX, wallIndexRightY));
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
    
    m_AreaExitRect = cocos2d::Rect(m_nLeft + m_nChamberWidth/4, m_nBottom + m_nHallHeight, m_nChamberWidth + 2, m_nChamberHeight + 2);
    
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
    int arenaDoorX = m_nArenaDoor%m_nWidth;
    int arenaDoorY = m_nArenaDoor/m_nWidth;
    int exitX = m_nIndexExit%m_nWidth;
    int exitY = m_nIndexExit/m_nWidth;
    
    setTerrainTile(entranceX, entranceY, TerrainTile::TT_ENTRANCE, Area::AT_STANDARD);
    setTerrainTile(arenaDoorX, arenaDoorY, TerrainTile::TT_LOCKED_MAGIC_DOOR, Area::AT_BOSS_ROOM, Actor::AD_FORWARD);
    setTerrainTile(exitX, exitY, TerrainTile::TT_LOCKED_BOSS_DOOR, Area::AT_BOSS_EXIT, Actor::AD_FORWARD);
    
    updateTerrainTileFogOfWar(0, 0, m_nWidth, m_nHeight, true);
    
    m_BossPosition = Vec2(exitX, exitY-2);
    generate();
    return true;
}
bool TombBossLevel::createTerrain()
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
            StandardMonster* monster = StandardMonster::create(BaseMonster::MT_SKELETON);
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
    skeletonKing->addTerrainTileFlag(TileInfo::ATTACKABLE);
    VoxelExplorer::getInstance()->getBossLayer()->addChild(skeletonKing);
    skeletonKing->setState(BaseBoss::BS_SLEEPING);
    
    return true;
}

bool TombBossLevel::createSummoningMonstersBySkeletonKing(const cocos2d::Vec2& mapPos, int skillStage)
{
    if(!VoxelExplorer::getInstance()->getPlayer() || VoxelExplorer::getInstance()->getPlayer()->getState() == Player::PS_DEATH)
        return false;
    if(VoxelExplorer::getInstance()->getMonstersLayer()->getChildrenCount() >= 8)
        return false;
    if(skillStage == 1)
    {
        for (int i = 0; i < m_GeneratePoints.size(); i++) {
            Vec2 pos = m_GeneratePoints[i];
            int index = pos.y*m_nWidth + pos.x;
            std::vector<int> neighbours4 = getNeighbours4();
            for (int j = 0; j < neighbours4.size(); j++) {
                int neighbourIndex = index + neighbours4[j];
                if(m_Map[neighbourIndex].isPassable())
                {
                    StandardMonster* monster = StandardMonster::create(BaseMonster::MT_SKELETON);
                    if(!monster)
                        return false;
                    monster->setPosition3D(Vec3(m_Map[neighbourIndex].m_nX*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -m_Map[neighbourIndex].m_nY*TerrainTile::CONTENT_SCALE));
                    monster->setVisited(m_Map[neighbourIndex].m_bVisited);
                    monster->addTerrainTileFlag(TileInfo::ATTACKABLE);
                    VoxelExplorer::getInstance()->getMonstersLayer()->addChild(monster);
                    monster->setState(BaseMonster::MS_TRACKING);
                    break;
                }
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
        return true;
    }
    return false;
}

void TombBossLevel::clearBossRoom()
{
    VoxelExplorer::getInstance()->clearBoosRoom();
    playBGStandardMusic();
}

bool TombBossLevel::createPickableItems()
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

std::vector<int> TombBossLevel::getTilesOnEdge(int m)
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
Vec2 TombBossLevel::getRandomPassableTileInBossRoom()
{
    int cell = -1;
    Vec2 tilePos;
    do {
        tilePos = getRandomPassableTile();
        cell = tilePos.y*m_nWidth + tilePos.x;
    } while (m_Map[cell].m_AreaType != Area::AT_BOSS_ROOM);
    
    return tilePos;
}
void TombBossLevel::handleUseStandardPortal(const cocos2d::Vec2& pos)
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