//
//  PatternsManager.cpp
//  MazeJump
//
//
//

#include "LevelResourceManager.h"
#include "RandomDungeon.hpp"
USING_NS_CC;

LevelResourceManager* g_pLevelResourceManagerInstance = nullptr;
LevelResourceManager::LevelResourceManager()
{
}
LevelResourceManager::~LevelResourceManager()
{
}
LevelResourceManager* LevelResourceManager::getInstance()
{
    if( g_pLevelResourceManagerInstance == nullptr )
        g_pLevelResourceManagerInstance = new LevelResourceManager();
    
    return g_pLevelResourceManagerInstance;
}
bool LevelResourceManager::init()
{
    m_TerrainTilesResMap = FileUtils::getInstance()->getValueMapFromFile("TerrainTilesRes.plist");
    if(m_TerrainTilesResMap.empty())
        return false;
    m_DoorsResMap = FileUtils::getInstance()->getValueMapFromFile("DoorsRes.plist");
    if(m_DoorsResMap.empty())
        return false;
    m_MonstersResMap = FileUtils::getInstance()->getValueMapFromFile("MonstersRes.plist");
    if(m_MonstersResMap.empty())
        return false;
//    m_ItemsResMap = FileUtils::getInstance()->getValueMapFromFile("ItemsRes.plist");
//    if(m_ItemsResMap.empty())
//        return false;
    return true;
}
bool LevelResourceManager::initLevelRes()
{
    if(!RandomDungeon::getInstance()->getCurrentDungeonNode())
        return false;
    std::string dungeonName = DUNGEON_NAMES[RandomDungeon::getInstance()->getCurrentDungeonNode()->m_Type];
    if(dungeonName.empty())
        return false;
    m_TerrainTilesLevelRes = m_TerrainTilesResMap.at(dungeonName).asValueMap();
    if(m_TerrainTilesLevelRes.empty())
        return false;
    
    m_DoorsLevelRes = m_DoorsResMap.at(dungeonName).asValueMap();
    if(m_DoorsLevelRes.empty())
        return false;
    return true;
    
}
void LevelResourceManager::clearLevelRes()
{
    m_TerrainTilesLevelRes.clear();
    m_DoorsLevelRes.clear();
}
std::string LevelResourceManager::getTerrainTileRes(const std::string& tileTypeName)
{
    return m_TerrainTilesLevelRes.at(tileTypeName).asString();
}
std::string LevelResourceManager::getDoorRes(const std::string& doorTypeName)
{
    return m_DoorsLevelRes.at(doorTypeName).asString();
}
std::string LevelResourceManager::getMonsterRes(const std::string& monsterTypeName)
{
    return m_MonstersResMap.at(monsterTypeName).asString();
}
std::string LevelResourceManager::getItemRes(const std::string& itemTypeName)
{
    return m_ItemsResMap.at(itemTypeName).asString();
}


