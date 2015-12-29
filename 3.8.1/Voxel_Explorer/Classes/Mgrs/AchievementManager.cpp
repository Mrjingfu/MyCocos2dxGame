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
            for (auto iterUnlockTask = iterItem->second.asValueMap().begin();iterUnlockTask!= iterItem->second.asValueMap().end(); iterUnlockTask++) {
                std::string unlockType = iterUnlockTask->first;
                CChaosNumber  unlockNum = iterUnlockTask->second.asInt();
                achieveProperty->setAchiveUnlockTarget(unlockType,unlockNum);
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
        
        checkAchieveUnlock(achieveProperty);
        m_vAllAchieves.pushBack(achieveProperty);
    }
    sortAchieves();
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
    if (!achieveProp->isCommple())
        updateAchieve(achieveProp);

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
        }else{
//            achieve->setProgress(type, sourceNum);
            checkAchieveUnlock(achieve);
            sortAchieves();
        }
    }
    if (targetCompleteCount == achieve->getAcheveTargets().size())
    {
        achieve->onAcieveCommple();
        sortAchieves();
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
void AchievementManager::checkKillMonsterAchievement()
{
    handleAchievement(ADT_MONSTER_1);
    handleAchievement(ADT_MONSTER_2);
    handleAchievement(ADT_MONSTER_3);
    handleAchievement(ADT_MONSTER_4);
    handleAchievement(ADT_MONSTER_5);
    handleAchievement(ADT_MONSTER_6);
    
    handleAchievement(ADT_SPECIFIED_MONSTER_1);
    handleAchievement(ADT_SPECIFIED_MONSTER_2);
    handleAchievement(ADT_SPECIFIED_MONSTER_3);
    handleAchievement(ADT_SPECIFIED_MONSTER_4);
    handleAchievement(ADT_SPECIFIED_MONSTER_5);
    handleAchievement(ADT_SPECIFIED_MONSTER_6);
    
}
void AchievementManager::checkKillBossAchievement()
{
    handleAchievement(ADT_BOSS_KILL_1);
    handleAchievement(ADT_BOSS_KILL_2);
    handleAchievement(ADT_BOSS_KILL_3);
    handleAchievement(ADT_BOSS_KILL_4);
    handleAchievement(ADT_BOSS_KILL_5);
    handleAchievement(ADT_BOSS_KILL_6);
}
void AchievementManager::checkRoleDeadAchievement()
{
    handleAchievement(ADT_ROLE_FALL_DEAD);
    handleAchievement(ADT_ROLE_POISON_DEAD);
    handleAchievement(ADT_ROLE_CLIP_DEAD);
    handleAchievement(ADT_ROLE_FILE_DEAD);
    
    handleAchievement(ADT_ROLE_DEAD_1);
    handleAchievement(ADT_ROLE_DEAD_2);
    handleAchievement(ADT_ROLE_DEAD_3);
    handleAchievement(ADT_ROLE_DEAD_4);
}
void AchievementManager::checkHaveGoldAchievement()
{
    handleAchievement(ADT_HAVE_GOLD_1);
    handleAchievement(ADT_HAVE_GOLD_2);
    handleAchievement(ADT_HAVE_GOLD_3);
    handleAchievement(ADT_HAVE_GOLD_4);
}
void AchievementManager::checkFoundHideAchievement()
{
    handleAchievement(ADT_FOUND_HIDDEN_DOOR);
    handleAchievement(ADT_FOUND_HIDDEN_TRAP_FIRST);
    handleAchievement(ADT_FOUND_HIDDEN_TRAP);
    handleAchievement(ADT_FOUND_HIDDEN_MSG_FIRST);
    handleAchievement(ADT_FOUND_HIDDEN_MSG);
}
void AchievementManager::checkBoxAchievement()
{
    handleAchievement(ADT_BREAK_JAR_1);
    handleAchievement(ADT_BREAK_JAR_2);
    handleAchievement(ADT_COPPER_BOX_FIRST);
    handleAchievement(ADT_SILVER_BOX_FIRST);
    handleAchievement(ADT_GOLD_BOX_FIRST);
    handleAchievement(ADT_OPEN_BOX);
}
void AchievementManager::checkAchieveUnlock(AchieveProperty *prop)
{
    if (prop->isCommple()) {
        prop->onUnlockAchieve();
        return;
    }
    int unlockCount = 0;
    std::map<eStatistType,CChaosNumber> unlockAcheve = prop->getAcheveUnlockTargets();
    for (auto iter = unlockAcheve.begin(); iter!=unlockAcheve.end(); iter++)
    {
        eStatistType unlockType = iter->first;
        CChaosNumber unlockNum = iter->second;
        CChaosNumber currentNum = StatisticsManager::getInstance()->getDataStatistType(unlockType);
        if (currentNum > unlockNum) {
            ++unlockCount;
        }
    }
    if (unlockCount == unlockAcheve.size()) {
       prop->onUnlockAchieve();
    }
}
void AchievementManager::sortAchieves()
{
    cocos2d::Vector<AchieveProperty*> unlockAchieve;
    cocos2d::Vector<AchieveProperty*> compleAchieve;
    cocos2d::Vector<AchieveProperty*> unCompleAchieve;
    cocos2d::Vector<AchieveProperty*> achieves;
    for (auto iter = m_vAllAchieves.begin(); iter!=m_vAllAchieves.end(); ++iter)
    {
        if (*iter)
        {
            AchieveProperty* prop= *iter;
            if (prop) {
                if (prop->isCommple())
                    compleAchieve.pushBack(prop);
                else
                {
                    if (prop->isUnlockAchieve())
                        unCompleAchieve.pushBack(prop);
                    else
                        unlockAchieve.pushBack(prop);
                }
                
            }
        }
    }
    
    std::sort(compleAchieve.begin(), compleAchieve.end(), std::less<AchieveProperty*>());
    std::sort(unlockAchieve.begin(), unlockAchieve.end(), std::less<AchieveProperty*>());
    std::sort(unCompleAchieve.begin(), unCompleAchieve.end(), std::less<AchieveProperty*>());
    
    for (auto iter = compleAchieve.begin(); iter!=compleAchieve.end(); ++iter)
    {
        if (*iter) {
            achieves.pushBack(*iter);
        }
    }
    
    for (auto iter = unCompleAchieve.begin(); iter!=unCompleAchieve.end(); ++iter)
    {
        if (*iter) {
            achieves.pushBack(*iter);
        }
    }
    
    for (auto iter = unlockAchieve.begin(); iter!=unlockAchieve.end(); ++iter)
    {
        if (*iter) {
            achieves.pushBack(*iter);
        }
    }
    
    compleAchieve.clear();
    unlockAchieve.clear();
    unCompleAchieve.clear();
    
    m_vAllAchieves.clear();
    
    for (auto iter = achieves.begin(); iter!=achieves.end(); ++iter) {
        if (*iter) {
            m_vAllAchieves.pushBack(*iter);
        }
    }
    achieves.clear();
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