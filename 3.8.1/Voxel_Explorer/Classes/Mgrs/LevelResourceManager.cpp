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
    m_ItemsResMap = FileUtils::getInstance()->getValueMapFromFile("ItemsRes.plist");
    if(m_ItemsResMap.empty())
        return false;
    m_DungeonSoundsResMap = FileUtils::getInstance()->getValueMapFromFile("DungeonSoundsRes.plist");
    if(m_DungeonSoundsResMap.empty())
        return false;
    m_MonsterSoundsResMap = FileUtils::getInstance()->getValueMapFromFile("MonstersSoundsRes.plist");
    if(m_MonsterSoundsResMap.empty())
        return false;
    m_CommonSoundsResMap = FileUtils::getInstance()->getValueMapFromFile("CommonSoundsRes.plist");
    if(m_CommonSoundsResMap.empty())
        return false;
    m_MusicsResMap = FileUtils::getInstance()->getValueMapFromFile("MusicsRes.plist");
    if(m_MusicsResMap.empty())
        return false;
    m_Particles3DResMap = FileUtils::getInstance()->getValueMapFromFile("Particles3DRes.plist");
    if(m_Particles3DResMap.empty())
        return false;
    return true;
}
bool LevelResourceManager::initLevelRes()
{
    m_TerrainTilesLevelRes.clear();
    m_DoorsLevelRes.clear();
    m_DungeonSoundsLevelRes.clear();
    m_MusicsLevelRes.clear();
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
    
    m_DungeonSoundsLevelRes = m_DungeonSoundsResMap.at(dungeonName).asValueMap();
    if(m_DungeonSoundsLevelRes.empty())
        return false;
    
    m_MusicsLevelRes = m_MusicsResMap.at(dungeonName).asValueMap();
    if(m_MusicsLevelRes.empty())
        return false;
    return true;
}

std::string LevelResourceManager::getTerrainTileRes(const std::string& tileTypeName)
{
    return m_TerrainTilesLevelRes.at(tileTypeName).asString();
}
std::string LevelResourceManager::getDoorRes(const std::string& doorTypeName)
{
    return m_DoorsLevelRes.at(doorTypeName).asString();
}
std::string LevelResourceManager::getMonsterModelRes(const std::string& monsterTypeName)
{
    return m_MonstersResMap.at(monsterTypeName).asString()+".c3b";
}
std::string LevelResourceManager::getMonsterIconRes(const std::string& monsterTypeName)
{
    return m_MonstersResMap.at(monsterTypeName).asString() +".png";
}
std::string LevelResourceManager::getItemIconRes(const std::string& itemTypeName)
{
     return m_ItemsResMap.at(itemTypeName).asString() + ".png";
}
std::string LevelResourceManager::getItemModelRes(const std::string& itemTypeName)
{
    return m_ItemsResMap.at(itemTypeName).asString() + ".c3b";
}
std::string LevelResourceManager::getDungeonSoundEffectRes(const std::string& soundTypeName)
{
    return m_DungeonSoundsLevelRes.at(soundTypeName).asString();
}
std::string LevelResourceManager::getMonsterSoundEffectRes(const std::string& monsterTypeName, const std::string& soundTypeName)
{
    return m_MonsterSoundsResMap.at(monsterTypeName).asValueMap().at(soundTypeName).asString();
}
std::string LevelResourceManager::getCommonSoundEffectRes(const std::string& soundTypeName)
{
    return m_CommonSoundsResMap.at(soundTypeName).asString();
}
std::string LevelResourceManager::getBackgroundMusicRes(const std::string& bgMusicTypeName)
{
    return m_MusicsLevelRes.at(bgMusicTypeName).asString();
}
std::string LevelResourceManager::getParticles3DRes(const std::string& particles3DTypeName)
{
    return m_Particles3DResMap.at(particles3DTypeName).asString();
}
