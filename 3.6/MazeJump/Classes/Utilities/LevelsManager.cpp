//
//  LevelsManager.cpp
//  MazeJump
//
//  Created by wang haibo on 15/7/20.
//
//

#include "LevelsManager.h"
USING_NS_CC;

LevelsManager* g_pLevelsManagerInstance = nullptr;
LevelsManager::LevelsManager()
{
    m_nMaxReachLevel = UserDefault::getInstance()->getIntegerForKey("MaxReachLevel", 0);
    m_nCurrentLevel = m_nMaxReachLevel;
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
    if(m_nCurrentLevel > m_nMaxReachLevel)
        setMaxReachLevel(m_nCurrentLevel);
}
void LevelsManager::setMaxReachLevel(int maxReachLevel)
{
    if(maxReachLevel >= m_Levels.size())
        return;
    m_nMaxReachLevel = maxReachLevel;
    UserDefault::getInstance()->setIntegerForKey("MaxReachLevel", m_nMaxReachLevel);
}
