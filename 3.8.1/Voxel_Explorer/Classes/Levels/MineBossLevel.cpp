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
#include "LevelResourceManager.h"
#include "KoboldLeader.hpp"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

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
                if(checkIndex >= m_Map.size())
                    continue;
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
    
    m_AreaExitRect = cocos2d::Rect(m_nRoomLeft - 1, m_nRoomBottom - 1, m_nRoomRight - m_nRoomLeft + 5, m_nRoomTop - m_nRoomBottom + 5);
    
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

    int exitX = m_nIndexExit%m_nWidth;
    int exitY = m_nIndexExit/m_nWidth;
    
    setTerrainTile(entranceX, entranceY, TerrainTile::TT_ENTRANCE, Area::AT_BOSS_ROOM);
    setTerrainTile(exitX, exitY, TerrainTile::TT_LOCKED_BOSS_DOOR, Area::AT_BOSS_EXIT, Actor::AD_FORWARD);
    
    updateTerrainTileFogOfWar(0, 0, m_nWidth, m_nHeight, true);
    
    int tileIndex = -1;
    do {
        tileIndex = randomMonsterRespawnCell();
        m_BossPosition = Vec2(tileIndex%m_nWidth, tileIndex/m_nWidth);
        if(m_BossPosition.distance(Vec2(entranceX, entranceY)) < 7)
            tileIndex = -1;
    } while (tileIndex == -1);
    
    generate();
    return true;
}
int MineBossLevel::randomMonsterRespawnCell()
{
    int count = 0;
    int tileIndex = -1;
    
    while (true) {
        if (++count > 10) {
            return -1;
        }
        tileIndex = cocos2d::random(0, m_nLenght -1);
        if(m_Map[tileIndex].m_AreaType != Area::AT_BOSS_ROOM)
            continue;
        if((m_Map[tileIndex].m_Flag & TileInfo::USEABLE) != 0 || (m_Map[tileIndex].m_Flag & TileInfo::ATTACKABLE) != 0 || (m_Map[tileIndex].m_Flag & TileInfo::STOPPABLE) != 0)
            continue;
        if ((m_Map[tileIndex].m_Flag & TileInfo::PASSABLE) != 0 ) {
            return tileIndex;
        }
    }
}
bool MineBossLevel::createMonsters()
{
    if(!createBoss(m_BossPosition))
    {
        CCLOG("Create boss failed!");
        return false;
    }
    int monsterNum = 10;
    for (int i=0; i < monsterNum; i++) {
        StandardMonster* monster = StandardMonster::create(BaseMonster::MT_KOBOLD);
        if(!monster)
            return false;
        int tileIndex = -1;
        do {
            tileIndex = randomMonsterRespawnCell();
            Vec2 monsterPos = Vec2(tileIndex%m_nWidth, tileIndex/m_nWidth);
            if(monsterPos.distance(m_BossPosition) >= 7)
                tileIndex = -1;
        } while (tileIndex == -1);
        
        monster->setPosition3D(Vec3(m_Map[tileIndex].m_nX*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -m_Map[tileIndex].m_nY*TerrainTile::CONTENT_SCALE));
        monster->setVisited(m_Map[tileIndex].m_bVisited);
        monster->addTerrainTileFlag(TileInfo::ATTACKABLE);
        VoxelExplorer::getInstance()->getMonstersLayer()->addChild(monster);
        monster->setMonsterFOV(11);
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
bool MineBossLevel::createBoss(const cocos2d::Vec2& pos)
{
    KoboldLeader* koboldLeader = KoboldLeader::create(BaseBoss::BT_KOBOLDLEADER);
    if(!koboldLeader)
        return false;
    int tileIndex = pos.x + pos.y * m_nWidth;
    koboldLeader->setPosition3D(Vec3(m_Map[tileIndex].m_nX*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -m_Map[tileIndex].m_nY*TerrainTile::CONTENT_SCALE));
    koboldLeader->setVisited(m_Map[tileIndex].m_bVisited);
    koboldLeader->addTerrainTileFlag(TileInfo::ATTACKABLE);
    VoxelExplorer::getInstance()->getBossLayer()->addChild(koboldLeader);
    koboldLeader->setState(BaseBoss::BS_SLEEPING);
    return true;
}
bool MineBossLevel::createSummoningMonstersByKoboldLeader(const cocos2d::Vec2& mapPos, int skillStage)
{
    if(!VoxelExplorer::getInstance()->getPlayer() || VoxelExplorer::getInstance()->getPlayer()->getState() == Player::PS_DEATH)
        return false;
    
    if(skillStage == 1)
    {
        return true;
    }
    else if(skillStage == 2)
    {
        for (int i=0; i < m_nLenght; i++) {
            if (m_Map[i].m_AreaType == Area::AT_BOSS_ROOM && m_Map[i].m_Type == TerrainTile::TT_STANDARD && cocos2d::random(0, 4) == 0) {
                setTerrainTile(i%m_nWidth, i/m_nWidth, TerrainTile::TT_GRIPPING_TRAP, Area::AT_BOSS_ROOM);
                VoxelExplorer::getInstance()->updateTerrainTile(i%m_nWidth, i/m_nWidth,TerrainTile::TT_GRIPPING_TRAP);
            }
        }
        
        int monsterNum = 10;
        for (int i=0; i < monsterNum; i++) {
            StandardMonster* monster = StandardMonster::create(BaseMonster::MT_KOBOLD);
            if(!monster)
                return false;
            int tileIndex = -1;
            do {
                tileIndex = randomMonsterRespawnCell();
                Vec2 monsterPos = Vec2(tileIndex%m_nWidth, tileIndex/m_nWidth);
                if(monsterPos.distance(mapPos) >= 7)
                    tileIndex = -1;
            } while (tileIndex == -1);
            
            monster->setPosition3D(Vec3(m_Map[tileIndex].m_nX*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -m_Map[tileIndex].m_nY*TerrainTile::CONTENT_SCALE));
            monster->setVisited(m_Map[tileIndex].m_bVisited);
            monster->addTerrainTileFlag(TileInfo::ATTACKABLE);
            VoxelExplorer::getInstance()->getMonstersLayer()->addChild(monster);
            monster->setMonsterFOV(11);
            monster->setState(BaseMonster::MS_TRACKING);
        }
        return true;
    }
    else if(skillStage == 3)
    {
        if(VoxelExplorer::getInstance()->getMonstersLayer()->getChildrenCount() >= 16)
            return false;
        int monsterNum = 3;
        for (int i=0; i < monsterNum; i++) {
            StandardMonster* monster = StandardMonster::create(BaseMonster::MT_KOBOLD, true);
            if(!monster)
                return false;
            int tileIndex = -1;
            do {
                tileIndex = randomMonsterRespawnCell();
                Vec2 monsterPos = Vec2(tileIndex%m_nWidth, tileIndex/m_nWidth);
                if(monsterPos.distance(mapPos) >= 3)
                    tileIndex = -1;
            } while (tileIndex == -1);
            
            monster->setPosition3D(Vec3(m_Map[tileIndex].m_nX*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -m_Map[tileIndex].m_nY*TerrainTile::CONTENT_SCALE));
            monster->setVisited(m_Map[tileIndex].m_bVisited);
            monster->addTerrainTileFlag(TileInfo::ATTACKABLE);
            VoxelExplorer::getInstance()->getMonstersLayer()->addChild(monster);
            monster->setMonsterFOV(11);
            monster->setState(BaseMonster::MS_TRACKING);
        }
        return true;
    }
    return false;
}
void MineBossLevel::clearBossRoom()
{
    for (int i=0; i < m_nLenght; i++) {
        if (m_Map[i].m_AreaType == Area::AT_BOSS_ROOM && m_Map[i].m_Type == TerrainTile::TT_GRIPPING_TRAP) {
            setTerrainTile(i%m_nWidth, i/m_nWidth, TerrainTile::TT_STANDARD, Area::AT_BOSS_ROOM);
            VoxelExplorer::getInstance()->updateTerrainTile(i%m_nWidth, i/m_nWidth,TerrainTile::TT_STANDARD);
        }
    }
    VoxelExplorer::getInstance()->clearBoosRoom();
    playBGBossMusic();
}

bool MineBossLevel::createPickableItems()
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
        
        int playerlevel = PlayerProperty::getInstance()->getLevel().GetLongValue();
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
std::vector<int> MineBossLevel::getTilesOnEdge(int m)
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
void MineBossLevel::handleUseStandardPortal(const cocos2d::Vec2& pos)
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
void MineBossLevel::playBGStandardMusic()
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    std::string musicName = LevelResourceManager::getInstance()->getBackgroundMusicRes("BOSS_BG");
    SimpleAudioEngine::getInstance()->playBackgroundMusic(musicName.c_str(), true);
}
void MineBossLevel::playBGBossMusic()
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    std::string musicName = LevelResourceManager::getInstance()->getBackgroundMusicRes("STANDARD_BG");
    SimpleAudioEngine::getInstance()->playBackgroundMusic(musicName.c_str(), true);
}