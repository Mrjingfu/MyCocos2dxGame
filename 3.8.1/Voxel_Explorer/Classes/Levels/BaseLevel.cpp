//
//  BaseLevel.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/9/24.
//
//

#include "BaseLevel.h"
#include "VoxelExplorer.h"
#include "Pathfinder.hpp"
#include "AlisaMethod.h"
#include "UtilityHelper.h"
#include "RandomDungeon.hpp"
#include "BasePortal.hpp"
#include "LevelResourceManager.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

BaseLevel::BaseLevel()
{
    m_bShowMap = false;
    m_Type = LT_STANDARD;
    m_pMapDrawNode = nullptr;
    m_pDebugDrawNode = nullptr;
    m_nWidth = 32;
    m_nHeight = 48;
}
void BaseLevel::create()
{
    do
    {
        m_nLenght = m_nWidth*m_nHeight;
        m_Map.resize(m_nLenght);
    }
    while (!build());
    if(!createTerrain())
        CCLOGERROR("Create Terrain failed!");
    if(!decorateAreas())
        CCLOGERROR("Decorate Arears failed!");
    if(!createMonsters())
        CCLOGERROR("Create Monsters failed!");
    if(!createPickableItems())
        CCLOGERROR("Create Pickable Items failed!");
    
    if(!Pathfinder::getInstance()->init(m_nWidth, m_nHeight))
        CCLOGERROR("Pathfinder initialize failed!");
    
    preloadBGMusic();
}
BaseLevel::LEVEL_TYPE BaseLevel::getLevelType() const
{
    return m_Type;
}
void BaseLevel::setLevelType(BaseLevel::LEVEL_TYPE type)
{
    m_Type = type;
}
bool BaseLevel::isAdjacent(const cocos2d::Vec2& a, const cocos2d::Vec2& b)
{
    int indexA = a.x + a.y*m_nWidth;
    int indexB = a.x + a.y*m_nWidth;
    return isAdjacent(indexA, indexB);
}
int BaseLevel::getDistance(const cocos2d::Vec2& a, const cocos2d::Vec2& b)
{
    int indexA = a.x + a.y*m_nWidth;
    int indexB = a.x + a.y*m_nWidth;
    return getDistance(indexA, indexB);
}

bool BaseLevel::isAdjacent(int a, int b)
{
    int diff = std::abs( a - b );
    return diff == 1 || diff == getWidth() || diff == getWidth() + 1 || diff == getWidth() - 1;
}
int BaseLevel::getDistance(int a, int b)
{
    int ax = a % getWidth();
    int ay = a / getWidth();
    int bx = b % getWidth();
    int by = b / getWidth();
    return MAX( std::abs( ax - bx ), std::abs( ay - by ) );
}
std::string BaseLevel::getTerrainTileInfoDesc(int x, int y)
{
    int index = x + y * m_nWidth;
    if(!m_Map[index].m_bVisited)
        return UtilityHelper::getLocalString(TERRAIN_TILES_NAME[TerrainTile::TT_CHASM]);
    
    if (m_Map[index].m_Type == TerrainTile::TT_STANDARD) {
        return UtilityHelper::getLocalString(TERRAIN_TILES_NAME[m_Map[index].m_Type]);
    }
    else if(m_Map[index].m_Type == TerrainTile::TT_WALL) {
        return UtilityHelper::getLocalString(TERRAIN_TILES_NAME[m_Map[index].m_Type]);
    }
    else if(m_Map[index].m_Type == TerrainTile::TT_ENTRANCE)
    {
        if((RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nCurrentDepth == 1))
        {
            return UtilityHelper::getLocalString(PORTAL_NAMES[BasePortal::PT_STANDARD] + "_LOCK");
        }
    }
    return UtilityHelper::getLocalString(TERRAIN_TILES_NAME[m_Map[index].m_Type]);
}
void BaseLevel::generateTerrainTiles(int x, int y , int width, int height, TerrainTile::TileType tileType, Area::AREA_TYPE areaType, Actor::ActorDir dir)
{
    int pos = y * m_nWidth + x;
    for (int i = y; i < y + height; i++, pos += m_nWidth) {
        for (int j = pos, k = x; j<(pos + width); j++, k++) {
            m_Map[j].m_Type = tileType;
            m_Map[j].m_AreaType = areaType;
            m_Map[j].m_Flag = assignTerrainTileFlag(tileType);
            m_Map[j].m_nX = k;
            m_Map[j].m_nY = i;
            m_Map[j].m_Dir = dir;
        }
    }
}
void BaseLevel::setTerrainTile(int x, int y, TerrainTile::TileType tileType, Area::AREA_TYPE areaType, Actor::ActorDir dir)
{
    int index = x + y * m_nWidth;
    m_Map[index].m_Type = tileType;
    m_Map[index].m_AreaType = areaType;
    m_Map[index].m_Flag = assignTerrainTileFlag(tileType);
    m_Map[index].m_nX = x;
    m_Map[index].m_nY = y;
    m_Map[index].m_Dir = dir;
}
TerrainTile::TileType BaseLevel::getTerrainTileType(int x, int y)
{
    int index = x + y * m_nWidth;
    return m_Map[index].m_Type;
}
void BaseLevel::setTerrainTileType(int x, int y, TerrainTile::TileType tileType)
{
    int index = x + y * m_nWidth;
    m_Map[index].m_Type = tileType;
}

bool BaseLevel::isTerrainTilePassable(int index)
{
    return m_Map[index].isPassable();
}
bool BaseLevel::isTerrainTileSearched(int x, int y)
{
    int index = x + y * m_nWidth;
    return m_Map[index].m_bSearched;
}
void BaseLevel::setTerrainTileSearched(int x, int y)
{
    int index = x + y * m_nWidth;
    m_Map[index].m_bSearched = true;
}
int BaseLevel::getTerrainTileFlag(int x, int y)
{
    int index = x + y * m_nWidth;
    return m_Map[index].m_Flag;
}
Area::AREA_TYPE BaseLevel::getTerrainTileAreaType(int x, int y)
{
    int index = x + y * m_nWidth;
    return m_Map[index].m_AreaType;
}
void BaseLevel::setTerrainTileFlag(int x, int y, int flag )
{
    int index = x + y * m_nWidth;
    m_Map[index].m_Flag = flag;
}
void BaseLevel::wrapTerrainTiles(int x, int y , int width, int height, TerrainTile::TileType type, TerrainTile::TileType withType)
{
    int pos = y * m_nWidth + x;
    for (int i = y; i < y + height; i++, pos += m_nWidth) {
        for (int j = pos; j<(pos + width); j++) {
            if(m_Map[j].m_Type == type)
            {
                for (int n : getNeighbours8()) {
                    int cell = j + n;
                    if(m_Map[cell].m_Type == TerrainTile::TT_CHASM)
                    {
                        m_Map[cell].m_nX = cell % m_nWidth;
                        m_Map[cell].m_nY = cell / m_nWidth;
                        m_Map[cell].m_Type = withType;
                        m_Map[cell].m_Flag = assignTerrainTileFlag(withType);
                    }
                }
            }
        }
    }
}
void BaseLevel::updateTerrainTileFogOfWar(int x, int y , int width, int height, bool visited)
{
    int pos = y * m_nWidth + x;
    for (int i = y; i < y + height; i++, pos += m_nWidth) {
        for (int j = pos, k = x; j<(pos + width); j++, k++) {
            m_Map[j].m_bVisited = visited;
        }
    }
}
void BaseLevel::updateTrapTileByPos(const cocos2d::Vec2& pos)
{
    int index = pos.x + pos.y * m_nWidth;
    if(m_Map[index].m_Type == TerrainTile::TT_HIDE_TOXIC_TRAP
       || m_Map[index].m_Type == TerrainTile::TT_HIDE_FIRE_TRAP
       || m_Map[index].m_Type == TerrainTile::TT_HIDE_PARALYTIC_TRAP
       || m_Map[index].m_Type == TerrainTile::TT_HIDE_GRIPPING_TRAP
       || m_Map[index].m_Type == TerrainTile::TT_HIDE_SUMMONING_TRAP
       || m_Map[index].m_Type == TerrainTile::TT_HIDE_WEAK_TRAP)
    {
        m_Map[index].m_Type = (TerrainTile::TileType)(m_Map[index].m_Type - 1);
        VoxelExplorer::getInstance()->handleTriggerTrap(pos, m_Map[index].m_Type);
    }
    else if(m_Map[index].m_Type == TerrainTile::TT_TOXIC_TRAP
            || m_Map[index].m_Type == TerrainTile::TT_FIRE_TRAP
            || m_Map[index].m_Type == TerrainTile::TT_PARALYTIC_TRAP
            || m_Map[index].m_Type == TerrainTile::TT_GRIPPING_TRAP
            || m_Map[index].m_Type == TerrainTile::TT_SUMMONING_TRAP
            || m_Map[index].m_Type == TerrainTile::TT_WEAK_TRAP)
    {
        VoxelExplorer::getInstance()->handleTriggerTrap(pos, m_Map[index].m_Type);
    }
}
bool BaseLevel::checkMovable(Actor* actor, TileInfo& info)
{
    if(!actor)
        return false;
    Vec2 pos = actor->getPosInMap();
    if(actor->getActorDir() == Actor::AD_LEFT)
        pos += Vec2(-1, 0);
    else if(actor->getActorDir() == Actor::AD_RIGHT)
        pos += Vec2(1, 0);
    else if(actor->getActorDir() == Actor::AD_FORWARD)
        pos += Vec2(0, 1);
    else if(actor->getActorDir() == Actor::AD_BACK)
        pos += Vec2(0, -1);
    int index = pos.x + pos.y*m_nWidth;
    info = m_Map[index];
    if((info.m_Flag & TileInfo::INITIALISED) != 0)
    {
        ///发送跳崖事件
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_GO_CHASM);
        return false;
    }
    if((info.m_Flag & TileInfo::STOPPABLE) != 0)
    {
        if(info.m_Type == TerrainTile::TT_ENTRANCE)
        {
            if(RandomDungeon::getInstance()->getCurrentDungeonNode()->isBossDepth())
            {
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_GO_UPSTAIRS_FORBIDDEN);
            }
            else if(RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nCurrentDepth > 1)
            {
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_GO_UPSTAIRS);
            }
            else
            {
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_GO_UPSTAIRS_FORBIDDEN);
            }
            return false;
        }
        else if(info.m_Type == TerrainTile::TT_EXIT)
        {
            if(RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nCurrentDepth < RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nTotalNum)
            {
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_GO_DOWNSTAIRS);
            }
            else if(RandomDungeon::getInstance()->getCurrentDungeonNode()->isLastDepth())
            {
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_GO_BOSSROOM);
            }
            return false;
        }
        else if(info.m_Type == TerrainTile::TT_STANDARD_PORTAL)
        {
            Vec2 pos = Vec2(info.m_nX, info.m_nY);
            VoxelExplorer::getInstance()->handlePlayerUseStandardPortal(pos);
            return false;
        }
        else if(info.m_Type == TerrainTile::TT_SMALL_PORTAL)
        {
            VoxelExplorer::getInstance()->handlePlayerUseSmallPortal();
            return false;
        }
        //碰墙
        return false;
    }
    if((info.m_Flag & TileInfo::ATTACKABLE) != 0)
    {
        return false;
    }
    if((info.m_Flag & TileInfo::USEABLE) != 0)
    {
        if( info.m_Type == TerrainTile::TT_DOOR || info.m_Type == TerrainTile::TT_LOCKED_DOOR || info.m_Type == TerrainTile::TT_LOCKED_BOSS_DOOR || info.m_Type == TerrainTile::TT_LOCKED_MAGIC_DOOR || info.m_Type == TerrainTile::TT_SECRET_DOOR )
            VoxelExplorer::getInstance()->handleDoor(pos);
        else
            VoxelExplorer::getInstance()->handleUseUseableItem(pos);
        return false;
    }
    if((info.m_Flag & TileInfo::PASSABLE) != 0)
    {
        return true;
    }
    return false;
}
int BaseLevel::assignTerrainTileFlag(TerrainTile::TileType type)
{
    int flag = TileInfo::INITIALISED;
    switch (type) {
        case TerrainTile::TT_STANDARD:
        case TerrainTile::TT_TUNNEL:
            flag = TileInfo::PASSABLE;
            break;
        case TerrainTile::TT_WALL:
        case TerrainTile::TT_ENTRANCE:
        case TerrainTile::TT_EXIT:
        case TerrainTile::TT_STANDARD_PORTAL:
        case TerrainTile::TT_SMALL_PORTAL:
            flag = TileInfo::STOPPABLE;
            break;
        case TerrainTile::TT_DOOR:
        case TerrainTile::TT_LOCKED_DOOR:
        case TerrainTile::TT_LOCKED_BOSS_DOOR:
        case TerrainTile::TT_LOCKED_MAGIC_DOOR:
        case TerrainTile::TT_SECRET_DOOR:
            flag = TileInfo::PASSABLE | TileInfo::USEABLE;
            break;
        case TerrainTile::TT_OPENED_DOOR:
            flag = TileInfo::PASSABLE;
            break;
        case TerrainTile::TT_TOXIC_TRAP:
        case TerrainTile::TT_HIDE_TOXIC_TRAP:
        case TerrainTile::TT_FIRE_TRAP:
        case TerrainTile::TT_HIDE_FIRE_TRAP:
        case TerrainTile::TT_PARALYTIC_TRAP:
        case TerrainTile::TT_HIDE_PARALYTIC_TRAP:
        case TerrainTile::TT_GRIPPING_TRAP:
        case TerrainTile::TT_HIDE_GRIPPING_TRAP:
        case TerrainTile::TT_SUMMONING_TRAP:
        case TerrainTile::TT_HIDE_SUMMONING_TRAP:
        case TerrainTile::TT_WEAK_TRAP:
        case TerrainTile::TT_HIDE_WEAK_TRAP:
            flag = TileInfo::PASSABLE;
            break;
        default:
            break;
    }
    return flag;
}

bool BaseLevel::getNextPathStep(const cocos2d::Vec2& from, const cocos2d::Vec2& to, cocos2d::Vec2& nextPos)
{
    int f = from.x + from.y * m_nWidth;
    int t = to.x + to.y * m_nWidth;
    int next = Pathfinder::getInstance()->getStep(f, t, m_Map);
    if(next == -1)
        return false;
    nextPos.x = next % m_nWidth;
    nextPos.y = next / m_nWidth;
    return true;
}
bool BaseLevel::getBackPathStep(const cocos2d::Vec2& current, const cocos2d::Vec2& from, cocos2d::Vec2& nextPos)
{
    int c = current.x + current.y * m_nWidth;
    int f = from.x + from.y * m_nWidth;
    int next = Pathfinder::getInstance()->getStepBack(c, f, m_Map);
    if(next == -1)
        return false;
    nextPos.x = next % m_nWidth;
    nextPos.y = next / m_nWidth;
    return true;
}
cocos2d::Vec2 BaseLevel::getRandomPassableTile()
{
    int cell = -1;
    do {
        cell = cocos2d::random(0, (int)(m_Map.size()-1));
    } while (!m_Map[cell].isPassable());
    return Vec2(cell % m_nWidth, cell / m_nWidth);
}
cocos2d::Vec2 BaseLevel::getRandomTranspotTile()
{
    int cell = -1;
    do {
        cell = cocos2d::random(0, (int)(m_Map.size()-1));
    } while (!m_Map[cell].isAvalidRandomTransport());
    return Vec2(cell % m_nWidth, cell / m_nWidth);
}
cocos2d::Vec2 BaseLevel::getRandomVisitedTranspotTile(const cocos2d::Vec2& playerPos)
{
    int playerIndex = playerPos.y*m_nWidth + playerPos.x;
    if(RandomDungeon::getInstance()->getCurrentDungeonNode()->isBossDepth())
    {
        if(m_Map[playerIndex].m_AreaType == Area::AT_BOSS_ROOM)
        {
            int cell = -1;
            do {
                cell = cocos2d::random(0, (int)(m_Map.size()-1));
            } while (m_Map[cell].m_AreaType != Area::AT_BOSS_ROOM || !(m_Map[cell].m_bVisited) || !(m_Map[cell].isPassable()) || playerIndex == cell);
            return Vec2(cell % m_nWidth, cell / m_nWidth);
        }
        else
        {
            int cell = -1;
            do {
                cell = cocos2d::random(0, (int)(m_Map.size()-1));
            } while (!m_Map[cell].isAvalidAndVistedRandomTransport() || playerIndex == cell);
            return Vec2(cell % m_nWidth, cell / m_nWidth);
        }
    }
    else
    {
        int cell = -1;
        do {
            cell = cocos2d::random(0, (int)(m_Map.size()-1));
        } while (!m_Map[cell].isAvalidAndVistedRandomTransport() || playerIndex == cell );
        return Vec2(cell % m_nWidth, cell / m_nWidth);
    }
}
bool BaseLevel::searchAndCheck(int x, int y, int searchDistance)
{
    std::vector<int> neighbours;
    if(searchDistance == 1)
        neighbours = getNeighbours5();
    else if(searchDistance == 2)
        neighbours = getNeighbours9();
    else if(searchDistance == 3)
        neighbours = getNeighbours13();
    else if(searchDistance == 4)
        neighbours = getNeighbours21();
    else
        neighbours = getNeighbours25();
    bool found = false;
    int pos = y * m_nWidth + x;
    for (int i = 0; i < neighbours.size(); ++i) {
        int j = pos + neighbours[i];
        VoxelExplorer::getInstance()->handleShowSearchEffect(Vec2(m_Map[j].m_nX, m_Map[j].m_nY));
        if(m_Map[j].m_bSearched)
            continue;
        else
            m_Map[j].m_bSearched = true;
        
        if(m_Map[j].m_Type == TerrainTile::TT_HIDE_TOXIC_TRAP
            || m_Map[j].m_Type == TerrainTile::TT_HIDE_FIRE_TRAP
            || m_Map[j].m_Type == TerrainTile::TT_HIDE_PARALYTIC_TRAP
            || m_Map[j].m_Type == TerrainTile::TT_HIDE_GRIPPING_TRAP
            || m_Map[j].m_Type == TerrainTile::TT_HIDE_SUMMONING_TRAP
            || m_Map[j].m_Type == TerrainTile::TT_HIDE_WEAK_TRAP)
        {
            m_Map[j].m_Type = (TerrainTile::TileType)(m_Map[j].m_Type - 1);
            VoxelExplorer::getInstance()->handleShowHiddenTrap(Vec2(m_Map[j].m_nX, m_Map[j].m_nY), m_Map[j].m_Type);
            found = true;
        }
        else if(m_Map[j].m_Type == TerrainTile::TT_SECRET_DOOR)
        {
            VoxelExplorer::getInstance()->handleShowSecretDoor(Vec2(m_Map[j].m_nX, m_Map[j].m_nY));
            found = true;
        }
    }
    return found;
}
void BaseLevel::preloadBGMusic()
{
    if(RandomDungeon::getInstance()->getCurrentDungeonNode())
    {
        if(RandomDungeon::getInstance()->getCurrentDungeonNode()->isBossDepth())
        {
            std::string bossMusicName = LevelResourceManager::getInstance()->getBackgroundMusicRes("BOSS_BG");
            SimpleAudioEngine::getInstance()->preloadBackgroundMusic(bossMusicName.c_str());
        }
        else
        {
            std::string standardMusicName = LevelResourceManager::getInstance()->getBackgroundMusicRes("STANDARD_BG");
            SimpleAudioEngine::getInstance()->preloadBackgroundMusic(standardMusicName.c_str());
        }
    }
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.4f);
}
bool BaseLevel::checkAllAreaBeExplored()
{
    int visSize = 0;
    int tileInfoSize = 0;
    for (int i=0; i<m_Map.size(); i++)
    {
        TileInfo info = m_Map[i];
        if (info.m_AreaType!=Area::AT_UNKNOWN && info.m_Type != TerrainTile::TT_CHASM )
        {
            if (info.m_bVisited) {
                 ++visSize;
            }
           ++tileInfoSize;
        }
    }
    
    
    if (visSize == tileInfoSize ) {
        return true;
    }
    return false;
}
void BaseLevel::playBGStandardMusic()
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    std::string musicName = LevelResourceManager::getInstance()->getBackgroundMusicRes("STANDARD_BG");
    SimpleAudioEngine::getInstance()->playBackgroundMusic(musicName.c_str(), true);
}
void BaseLevel::playBGBossMusic()
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    std::string musicName = LevelResourceManager::getInstance()->getBackgroundMusicRes("BOSS_BG");
    SimpleAudioEngine::getInstance()->playBackgroundMusic(musicName.c_str(), true);
}
