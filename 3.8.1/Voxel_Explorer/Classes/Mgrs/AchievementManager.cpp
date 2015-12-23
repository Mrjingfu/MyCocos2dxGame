//
//  AchievementManager.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/12.
//
//

#include "AchievementManager.h"
#include "StatisticsManager.hpp"
#include "EventConst.h"
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
void AchievementManager::load()
{
    cocos2d::Vector<AchieveProperty*> m_vCompleteAchieves;
    //加载存档时 更新全局成就, 过滤掉已完成的成就
    for (auto iter = m_vAllAchieves.begin() ; iter!=m_vAllAchieves.end(); iter++)
    {
       
        if (nullptr !=(*iter))
        {
            AchieveProperty *prop = (*iter);
            for (int i =0; i< m_vCompleteAchieves.size(); i++)
            {
                if (prop->getAchieveDetailType() == m_vCompleteAchieves.at(i)->getAchieveDetailType())
                {
                    prop->onAcieveCommple();
                }
            }
        }
        
        
    }
}
void AchievementManager::save()
{
    
}
bool AchievementManager::loadAchieveData()
{
    cocos2d::ValueMap achieves = cocos2d::FileUtils::getInstance()->getValueMapFromFile("AchieveDatas.plist");
    for (auto iter =achieves.begin(); iter!=achieves.end(); iter++)
    {
        AchieveProperty* achieveProperty = AchieveProperty::create();
       
        achieveProperty->setAchieveDetailType(iter->first);
        cocos2d::ValueMap achieveItem = iter->second.asValueMap();
        
      
        auto  iterItem = achieveItem.find("achieve_icon");
        if (iterItem != achieveItem.end())
        {
            achieveProperty->setAchieveIcon(iterItem->second.asString());
        }
        
        iterItem = achieveItem.find("achieve_unlock_task");
        if (iterItem != achieveItem.end()) {
            for (auto iterUnlockTask = iterItem->second.asValueVector().begin();iterUnlockTask!= iterItem->second.asValueVector().end(); iterUnlockTask++) {
                std::string targetType = (*iterUnlockTask).asString();
                achieveProperty->setAchiveUnlockTarget(targetType);
            }
        }
        
       
        iterItem = achieveItem.find("achieve_task");
        if (iterItem != achieveItem.end())
        {
            for (auto iterTask = iterItem->second.asValueMap().begin(); iterTask!=iterItem->second.asValueMap().end(); iterTask++)
            {
                std::string targetType = iterTask->first;
                CChaosNumber  targetNum = iterTask->second.asInt();
                achieveProperty->setAchieveTarget(targetType,targetNum);
            }
        }
        
        m_vAllAchieves.pushBack(achieveProperty);
    }
    return true;
}

void AchievementManager::handleAchievement(eAchievementDetailType achiId)
{

    AchieveProperty* achieveProp = getAchievement(achiId);
    if (!achieveProp)
    {
        CCLOG("achieveProp is null");
        return;
    }
    switch (achiId) {
        case ADT_KILL_FIRST:
           
            updateAchieve(achieveProp);
            break;
        default:
            break;
    }
}
void AchievementManager::updateAchieve(AchieveProperty *achieve)
{
    int targetCompleteCount = 0;
    for (auto iter = achieve->getAcheveTargets().begin(); iter!=achieve->getAcheveTargets().end(); iter++)
    {
        eStatistType type = iter->first;
        CChaosNumber sourceNum =  StatisticsManager::getInstance()->getDataStatistType(type);
        CChaosNumber targetNum = iter->second;
//        CCLOG("sourceNum:%ld",sourceNum.GetLongValue());
//        CCLOG("targetNum:%ld",targetNum.GetLongValue());
        if (sourceNum >= targetNum) {
            ++targetCompleteCount;
        }
    }
    if (targetCompleteCount == achieve->getAcheveTargets().size())
    {
        achieve->onAcieveCommple();
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_ACHIEVE_COMPLETE,achieve);
    }
}
void AchievementManager::checkAllAchievement()
{
    for (int i= 0 ; i<m_vAllAchieves.size(); i++)
    {
        AchieveProperty *achieve = m_vAllAchieves.at(i);
        if (achieve && !achieve->isCommple()) {
            updateAchieve(achieve);
        }
    }
}
AchieveProperty* AchievementManager::getAchievement(eAchievementDetailType type)
{
    for (int i= 0 ; i<m_vAllAchieves.size(); i++)
    {
        AchieveProperty *achieve = m_vAllAchieves.at(i);
        if (achieve && achieve->getAchieveDetailType() == type) {
            return achieve;
        }
    }
    return nullptr;
}