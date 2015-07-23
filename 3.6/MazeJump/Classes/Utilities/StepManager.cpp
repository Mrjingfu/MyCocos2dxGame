//
//  StepManager.cpp
//  MazeJump
//
//  Created by wang haibo on 15/7/20.
//
//

#include "StepManager.h"
USING_NS_CC;

StepManager* g_pStepManagerInstance = nullptr;

StepManager::StepManager()
{
 
}

StepManager* StepManager::getInstance()
{
    if( g_pStepManagerInstance == nullptr )
        g_pStepManagerInstance = new StepManager();
    
    return g_pStepManagerInstance;
}
void StepManager::setStep(int index)
{
    m_Steps.push_back(cocos2d::Value(index));
}
void StepManager::setLevelStep(int level)
{
    m_levelSteps.insert(std::pair<int, Value>(level,Value(m_Steps)));
    
}
cocos2d::ValueVector StepManager::getLevelSteps(int level)
{
    auto iter = m_levelSteps.find(level);
    if (iter != m_levelSteps.end())
        return iter->second.asValueVector();
    return ValueVector();
}