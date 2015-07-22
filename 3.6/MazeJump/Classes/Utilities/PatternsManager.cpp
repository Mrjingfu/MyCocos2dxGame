//
//  PatternsManager.cpp
//  MazeJump
//
//  Created by wang haibo on 15/7/22.
//
//

#include "PatternsManager.h"
USING_NS_CC;

PatternsManager* g_pPatternsManagerInstance = nullptr;
PatternsManager::PatternsManager()
{
}
PatternsManager::~PatternsManager()
{
}
PatternsManager* PatternsManager::getInstance()
{
    if( g_pPatternsManagerInstance == nullptr )
        g_pPatternsManagerInstance = new PatternsManager();
    
    return g_pPatternsManagerInstance;
}
bool PatternsManager::init(const std::string& file)
{
    m_Patterns = FileUtils::getInstance()->getValueVectorFromFile(file);
    return !m_Patterns.empty();
}

ValueVector PatternsManager::getPatternTerrainCells(int patternIndex)
{
    if(patternIndex >= m_Patterns.size())
        return m_Patterns.at(0).asValueMap().at("TerrainCells").asValueVector();
    return m_Patterns.at(patternIndex).asValueMap().at("TerrainCells").asValueVector();
}