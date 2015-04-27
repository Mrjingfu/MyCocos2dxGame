//
//  StageManager.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/4/24.
//
//

#include "StageManager.h"
#include "EnemiesGenerator.h"
#include "GameController.h"
#include "EncrytionUtility.h"
USING_NS_CC;

StageManager* g_pStageManagerInstance = nullptr;
StageManager* StageManager::getInstance()
{
    if( g_pStageManagerInstance == nullptr )
        g_pStageManagerInstance = new StageManager();
    return g_pStageManagerInstance;
}

StageManager::StageManager()
{
    m_nCurrentScore = 0;
    m_nTargetScore = 100;
    m_fCurrentPercent = 0;
    m_fLastPercent = 0;
    m_nCurrentIndex = 0;
}
StageManager::~StageManager()
{
}
bool StageManager::init()
{
    m_StageList = FileUtils::getInstance()->getValueVectorFromFile("stages.plist");
    if(m_StageList.empty())
        return false;
    return true;
}
void StageManager::reset()
{
    m_nCurrentScore = 0;
    m_nTargetScore = 100;
    m_fCurrentPercent = 0;
    m_fLastPercent = 0;
    m_nCurrentIndex = 0;
    GameController::getInstance()->getEnemiesGenerator()->stopGenerateEnemies();
}
void StageManager::nextStage(int stage)
{
    if(m_StageList.size() >= stage)
    {
        m_nCurrentIndex = stage - 1;
        ValueMap stageItem = m_StageList.at(m_nCurrentIndex).asValueMap();
        StageType stageType = (StageType)(stageItem["stageType"].asInt());
        if (stageType == ST_DEFAULT) {
            m_nTargetScore = stageItem["targetScore"].asInt();
        }
        ValueVector enemyList = stageItem["enemyList"].asValueVector();
        if(!enemyList.empty())
        {
            for (size_t i = 0; i < enemyList.size(); ++i) {
                ValueMap enemyItem = enemyList.at(i).asValueMap();
                Enemy::EnemyType type = (Enemy::EnemyType)(enemyItem["enemyType"].asInt());
                float delayTime = enemyItem["delayTime"].asFloat();
                float duration = enemyItem["duration"].asFloat();
                float lastTime = enemyItem["lastTime"].asFloat();
                int number = enemyItem["number"].asInt();
                EnemyUpdateType updateType = (EnemyUpdateType)(enemyItem["updateType"].asInt());
                if (updateType == EUT_TIME) {
                    GameController::getInstance()->getEnemiesGenerator()->generateEnemiesByTime(type, duration, delayTime, lastTime);
                }
                else if(updateType == EUT_NUM)
                {
                    GameController::getInstance()->getEnemiesGenerator()->generateEnemiesByNum(type, duration, number, delayTime);
                }
                else
                    continue;
            }
        }
    }
    else
    {
        m_nCurrentIndex = stage - 1;
        float param = stage/m_StageList.size();
        ValueMap stageItem = m_StageList.back().asValueMap();
        StageType stageType = (StageType)(stageItem["stageType"].asInt());
        if (stageType == ST_DEFAULT) {
            m_nTargetScore = stageItem["targetScore"].asInt();
        }
        ValueVector enemyList = stageItem["enemyList"].asValueVector();
        if(!enemyList.empty())
        {
            for (size_t i = 0; i < enemyList.size(); ++i) {
                ValueMap enemyItem = enemyList.at(i).asValueMap();
                Enemy::EnemyType type = (Enemy::EnemyType)(enemyItem["enemyType"].asInt());
                float delayTime = enemyItem["delayTime"].asFloat();
                float lastTime = enemyItem["lastTime"].asFloat();
                float duration = enemyItem["duration"].asFloat()*(1.0f/param);
                int number = enemyItem["number"].asInt()*param;
                EnemyUpdateType updateType = (EnemyUpdateType)(enemyItem["updateType"].asInt());
                if (updateType == EUT_TIME) {
                    GameController::getInstance()->getEnemiesGenerator()->generateEnemiesByTime(type, duration, delayTime, lastTime);
                }
                else if(updateType == EUT_NUM)
                {
                    GameController::getInstance()->getEnemiesGenerator()->generateEnemiesByNum(type, duration, number, delayTime);
                }
                else
                    continue;
            }
        }
    }
}

void StageManager::addScore(int score)
{
    m_fLastPercent = (float)m_nCurrentScore/(float)m_nTargetScore;
    m_nCurrentScore += score;
    m_fCurrentPercent = (float)m_nCurrentScore/(float)m_nTargetScore;
    if(m_fCurrentPercent >= 1.0f)
        m_fCurrentPercent = 1.0f;
    ValueMap stageItem;
    if(m_StageList.size() >= m_nCurrentIndex + 1)
        stageItem = m_StageList.at(m_nCurrentIndex).asValueMap();
    else
        stageItem = m_StageList.back().asValueMap();
    ValueVector enemyList = stageItem["enemyList"].asValueVector();
    if(!enemyList.empty())
    {
        for (size_t i = 0; i < enemyList.size(); ++i) {
            ValueMap enemyItem = enemyList.at(i).asValueMap();
            float percent = enemyItem["percent"].asFloat();
            if(m_fLastPercent < percent && m_fCurrentPercent>= percent)
            {
                Enemy::EnemyType type = (Enemy::EnemyType)(enemyItem["enemyType"].asInt());
                float delayTime = enemyItem["delayTime"].asFloat();
                float duration = enemyItem["duration"].asFloat();
                int number = enemyItem["number"].asInt();
                EnemyUpdateType updateType = (EnemyUpdateType)(enemyItem["updateType"].asInt());
                if(updateType == EUT_PERCENT_BY_TIME)
                {
                    GameController::getInstance()->getEnemiesGenerator()->generateEnemiesByTime(type, duration, delayTime);
                }
                else if(updateType == EUT_PERCENT_BY_NUM)
                {
                    GameController::getInstance()->getEnemiesGenerator()->generateEnemiesByNum(type, duration, number, delayTime);
                }
                else
                    continue;
            }
        }
    }
    if(m_fCurrentPercent >= 1.0f)
    {
        int stage = EncrytionUtility::getIntegerForKey("CurrentStage", 1);
        stage++;
        EncrytionUtility::setIntegerForKey("CurrentStage", stage);
        reset();
        GameController::getInstance()->nextStage();
    }
}
