//
//  LevelsManager.cpp
//  MazeJump
//
//  Created by wang haibo on 15/7/20.
//
//

#include "LevelsManager.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;

LevelsManager* g_pLevelsManagerInstance = nullptr;
LevelsManager::LevelsManager()
{
    m_nCurrentLevel = 0;
}
LevelsManager::~LevelsManager()
{
}
LevelsManager* LevelsManager::getInstance()
{
    if( g_pLevelsManagerInstance == nullptr )
        g_pLevelsManagerInstance = new LevelsManager();
    
    return g_pLevelsManagerInstance;
}
bool LevelsManager::init(const std::string& file)
{
    m_Levels = FileUtils::getInstance()->getValueVectorFromFile(file);
    return !m_Levels.empty();
}

std::string LevelsManager::getCurrentLevelName()
{
    if(m_nCurrentLevel >= m_Levels.size())
    {
        ValueMap map = m_Levels.at(0).asValueMap();
        return map.at("LevelName").asString();
    }
    ValueMap map = m_Levels.at(m_nCurrentLevel).asValueMap();
    return map.at("LevelName").asString();
}

std::string LevelsManager::getCurrentLevelSkyTextureName()
{
    if(m_nCurrentLevel >= m_Levels.size())
    {
        ValueMap map = m_Levels.at(0).asValueMap();
        return map.at("SkyTex").asString();
    }
    ValueMap map = m_Levels.at(m_nCurrentLevel).asValueMap();
    return map.at("SkyTex").asString();
}
std::string LevelsManager::getCurrentLevelPlatformModelName()
{
    if(m_nCurrentLevel >= m_Levels.size())
    {
        ValueMap map = m_Levels.at(0).asValueMap();
        return map.at("PlatformModel").asString();
    }
    ValueMap map = m_Levels.at(m_nCurrentLevel).asValueMap();
    return map.at("PlatformModel").asString();
}
void LevelsManager::setCurrentLevel(int currentLevel)
{
    if(currentLevel >= m_Levels.size())
        return;
    m_nCurrentLevel = currentLevel;
}
std::string LevelsManager::getLevelName(int level)
{

//    if(level > m_nMaxReachLevel)
//        level = m_nCurrentLevel;
    
    if(level >= m_Levels.size())
    {
        ValueMap map = m_Levels.at(0).asValueMap();
        return map.at("LevelName").asString();
    }
    ValueMap map = m_Levels.at(level).asValueMap();
    return map.at("LevelName").asString();
}

std::string LevelsManager::getLevelSkyTextureName(int level)
{
//    if(level > m_nMaxReachLevel)
//        level = m_nCurrentLevel;
    
    if(level >= m_Levels.size())
    {
        ValueMap map = m_Levels.at(0).asValueMap();
        return map.at("SkyTex").asString();
    }
    ValueMap map = m_Levels.at(level).asValueMap();
    return map.at("SkyTex").asString();
}
std::string LevelsManager::getLevelPlatformModelName(int level)
{
//    if(level > m_nMaxReachLevel)
//        level = m_nCurrentLevel;
    
    if(level >= m_Levels.size())
    {
        ValueMap map = m_Levels.at(0).asValueMap();
        return map.at("PlatformModel").asString();
    }
    ValueMap map = m_Levels.at(level).asValueMap();
    return map.at("PlatformModel").asString();
}
