//
//  StatisticsManager.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/12.
//
//

#include "StatisticsManager.hpp"

StatisticsManager::StatisticsManager()
{
    m_nGoodCollectedNum     = 0;
    m_nfoodEaten            = 0;
    m_nStepNum              = 0;
    m_nPotionsUse           = 0;
    m_nMonsterKillTotalNum  = 0;
    
    for (int i = BaseMonster::MT_UNKNOWN; i<BaseMonster::MT_MAX; i++) {
        
        m_mMonsterKills[i]=0;
    }
}
StatisticsManager::~StatisticsManager()
{
    
}
StatisticsManager* StatisticsManager::getInstance()
{
    static StatisticsManager instance;
    return &instance;
}
void StatisticsManager::setFoodEaten(CChaosNumber food)
{
//    m_nfoodEaten+= food;
}
void StatisticsManager::setGoodCollectdNum(CChaosNumber num)
{
    m_nGoodCollectedNum +=num;
}
void StatisticsManager::addMonsterKillNum(BaseMonster::MonsterType type)
{
    ++m_mMonsterKills[type] ;
    ++m_nMonsterKillTotalNum;
}

void StatisticsManager::addPotionUse()
{
    ++m_nPotionsUse;
}
void StatisticsManager::load()
{
    
}
void StatisticsManager::save()
{
    
}
