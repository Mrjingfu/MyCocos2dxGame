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

void AchievementManager::handleAchievement(eAchievementDetailType achiId,int value)
{
    std::vector<CChaosNumber> targetList;
    targetList.clear();
    AchieveProperty* achieveProp = getAchievement(achiId);
    switch (achiId) {
        case eAchiDetailType_Firstkill:
           
            updateAchieve(achieveProp, targetList);
            break;
        default:
            break;
    }
}
void AchievementManager::updateAchieve(AchieveProperty *achieve,std::vector<CChaosNumber> targetList)
{
    
}
AchieveProperty* AchievementManager::getAchievement(eAchievementDetailType type)
{
    auto iter = m_pAllAchieves.find(type);
    CCASSERT(iter != m_pAllAchieves.end(),"No this Achieve !! Error !!");
    return iter->second;
}