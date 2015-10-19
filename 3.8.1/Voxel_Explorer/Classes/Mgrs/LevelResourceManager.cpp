//
//  PatternsManager.cpp
//  MazeJump
//
//
//

#include "LevelResourceManager.h"
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
bool LevelResourceManager::init(const std::string& file)
{
    m_LevelRes = FileUtils::getInstance()->getValueMapFromFile(file);
    return !m_LevelRes.empty();
}
bool LevelResourceManager::initLevelRes(const std::string &type)
{
    bool ret = true;
   
    m_tileds = m_LevelRes.at(type).asValueMap();
    
    ret = !m_tileds.empty();
    
    m_models = m_LevelRes.at("model").asValueMap();
    
    ret = !m_LevelRes.empty();
    
    return ret;
    
}
void LevelResourceManager::clearLevelRes(const std::string& type)
{
    if (!m_tileds.empty()) {
        m_tileds.clear();
    }
    
    if (!m_models.empty()) {
        m_models.clear();
    }
}
std::string LevelResourceManager::getModelRes(std::string &type)
{
    if (!m_models.empty()) {
        return m_models.at(type).asString();
    }
    return Value().asString();
}
std::string LevelResourceManager::getTerrainTileRes(std::string &type)
{
    if (!m_tileds.empty()) {
        return m_tileds.at(type).asString();
    }
    return Value().asString();
}


