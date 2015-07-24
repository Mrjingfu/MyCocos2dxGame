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
void StepManager::setStep(int index,int direction)
{
    ValueVector localVector;
    localVector.push_back(Value(index));
    localVector.push_back(Value(direction));
    m_Steps.push_back(cocos2d::Value(localVector));
}
void StepManager::setLevelStep(int level,int levelStaus)
{
    
    //通过关卡获取当前所有步数记录
    m_levelSteps = FileUtils::getInstance()->getValueMapFromFile(FileUtils::getInstance()->getWritablePath().append("steps"));
    ValueVector levelIndexVector  = atVectorValue(level);
    
    //记录当前关卡胜负状态及步数
    ValueVector stepVector;
    stepVector.push_back(Value(levelStaus));
    stepVector.push_back(Value(m_Steps));
    
    //记录当前关卡的步数
    levelIndexVector.push_back(Value(stepVector));
    
    //记录当前关卡的所有步数
    auto iter = m_levelSteps.find(Value(level).asString());
    if (iter != m_levelSteps.end())
    {
        m_levelSteps.erase(iter);
    }
    
    m_levelSteps.insert(std::pair<std::string, Value>(Value(level).asString(),Value(levelIndexVector)));
    FileUtils::getInstance()->writeToFile(m_levelSteps, FileUtils::getInstance()->getWritablePath().append("steps"));
   
    m_Steps.clear();
    m_levelSteps.clear();
}
cocos2d::ValueVector StepManager::getLevelWinSteps(int level)
{
    m_levelSteps = FileUtils::getInstance()->getValueMapFromFile(FileUtils::getInstance()->getWritablePath().append("steps"));
    ValueVector levelIndexVector  = atVectorValue(level);
    if(levelIndexVector.size() > 0)
    {
        for (Value indexStep: levelIndexVector) {
            int levelStaus = indexStep.asValueVector()[0].asInt();
            ValueVector steps = indexStep.asValueVector()[1].asValueVector();
            if (levelStaus == LEVEL_WIN) {
                return steps;
            }
        }
    }
    return ValueVector();
}
cocos2d::ValueVector StepManager::getLevelSteps(int level)
{
   
    m_levelSteps = FileUtils::getInstance()->getValueMapFromFile(FileUtils::getInstance()->getWritablePath().append("steps"));
    ValueVector levelIndexVector  = atVectorValue(level);
    if(levelIndexVector.size() > 0)
    {
        return levelIndexVector;
    }
    return ValueVector();
}
cocos2d::ValueVector StepManager::atVectorValue(int index)
{
    Value  indexValue(index);
    auto iter = m_levelSteps.find(indexValue.asString());
    if (iter != m_levelSteps.end())
        return iter->second.asValueVector();
    return ValueVector();
}