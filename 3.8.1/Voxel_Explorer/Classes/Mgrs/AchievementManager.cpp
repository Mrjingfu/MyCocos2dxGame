//
//  AchievementManager.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/12.
//
//

#include "AchievementManager.h"
#include "StatisticsManager.hpp"
AchievementManager::AchievementManager()
{
    
}
AchievementManager::~AchievementManager()
{
    
}
AchievementManager* AchievementManager::getInstance()
{
    static AchievementManager instance;
    return &instance;
}
void AchievementManager::loadAchieveData()
{
    
}

void AchievementManager::handleAchievement(eAchievementDetailType achiId)
{

    AchieveProperty* achieveProp = getAchievement(achiId);
    switch (achiId) {
        case eAchiDetailType_Firstkill:
           
            updateAchieve(achieveProp);
            break;
        default:
            break;
    }
}
void AchievementManager::updateAchieve(AchieveProperty *achieve)
{
    bool isComplete = false;
    
    for (auto iter = achieve->m_mTargets.begin(); iter!=achieve->m_mTargets.end(); iter++) {
        
        CChaosNumber sourceNum =  StatisticsManager::getInstance()->getDataStatistType(iter->first);
        CChaosNumber targetNum = iter->second;
        if (sourceNum >= targetNum) {
            achieve->m_mProgress[iter->first] = targetNum;
            isComplete = true;
        }else{
            achieve->m_mProgress[iter->first] = sourceNum.GetLongValue();
            isComplete = false;
        }
    }
    
    if (isComplete) {
        CCLOG("成就完成");
    }else{
        CCLOG("成就未完成");
    }
}
AchieveProperty* AchievementManager::getAchievement(eAchievementDetailType type)
{
    auto iter = m_pAllAchieves.find(type);
    CCASSERT(iter != m_pAllAchieves.end(),"No this Achieve !! Error !!");
    return iter->second;
}