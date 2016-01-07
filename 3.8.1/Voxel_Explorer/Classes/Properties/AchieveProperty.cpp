//
//  AchieveProperty.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/12.
//
//

#include "AchieveProperty.hpp"
#include "UtilityHelper.h"
#include "AchievementManager.h"
#include "StatisticsManager.hpp"
AchieveProperty::AchieveProperty()
{
    m_bCommple = false;
    m_bIsUnlockAchieve = false;
}
AchieveProperty::~AchieveProperty()
{
   
}

bool AchieveProperty::init()
{
    return true;
}

void AchieveProperty::setAchieveTarget(std::string typeStr,CChaosNumber targetNum)
{
    int type = checkArrName(STATIST_TYPE_NAME,typeStr);
    CCASSERT(type!=-1, "type error");
    eStatistType sStype = (eStatistType)type;

    m_mAcheveTargets.insert(std::map<eStatistType,CChaosNumber>::value_type(sStype,targetNum));
    m_mProgress.insert(std::map<eStatistType,CChaosNumber>::value_type(sStype,CChaosNumber(0)));
}

void AchieveProperty::setAchieveDetailType(std::string achieveDeType)
{
    int type = checkArrName(ACHIEVEMENT_DATAIL_TYPE_NAME,achieveDeType);
    CCASSERT(type!=-1, "type error");
    m_detailType = (eAchievementDetailType)(type);
    m_sAchieveName = UtilityHelper::getLocalStringForPlist(achieveDeType, "achieve_chinese.plist", "achieve_english.plist");
    m_sAchieveTargetDesc = UtilityHelper::getLocalStringForPlist(achieveDeType+"_TARGET", "achieve_chinese.plist", "achieve_english.plist");
}
void AchieveProperty::setAchiveUnlockTarget(std::string typeStr,CChaosNumber targetNum)
{
    int type = checkArrName(STATIST_TYPE_NAME,typeStr);;
    CCASSERT(type!=-1, "type error");
    eStatistType sStype = (eStatistType)type;
    m_mUnlockTargets.insert(std::map<eStatistType,CChaosNumber>::value_type(sStype,targetNum));
}
void AchieveProperty::setProgress(eStatistType type,CChaosNumber targetNum)
{
    auto iter = m_mProgress.find(type);
    if (iter!=m_mProgress.end())
    {
        m_mProgress[iter->first] = targetNum;
    }
}

CChaosNumber AchieveProperty::getPorgress(eStatistType type)
{
    auto iter = m_mProgress.find(type);
    if (iter!=m_mProgress.end())
    {
        return iter->second ;
    }
    return CChaosNumber(0);
}
int AchieveProperty::checkArrName(const std::vector<std::string> arr,const std::string str)
{
    for (int i =0 ; i< arr.size(); i++)
    {
        std::string name = arr[i];
        if (name == str) {
            return i;
        }
    }
    return -1;
}
std::string  AchieveProperty::getAchieveDesc() const
{
    return ACHIEVEMENT_DATAIL_TYPE_NAME[m_detailType];
}

bool AchieveProperty::operator<(const AchieveProperty* v) const
{
   
    return m_detailType < v->getAchieveDetailType();
}



