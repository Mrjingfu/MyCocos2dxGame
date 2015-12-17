//
//  AchieveProperty.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/12.
//
//

#include "AchieveProperty.hpp"
#include "UtilityHelper.h"
AchieveProperty::AchieveProperty()
{
    m_bCommple = false;
    m_bIsHideAchieve = false;
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
}

void AchieveProperty::setAchieveDetailType(std::string achieveDeType)
{
    int type = checkArrName(ACHIEVEMENT_DATAIL_TYPE_NAME,achieveDeType);
    CCASSERT(type!=-1, "type error");
    m_detailType = (eAchievementDetailType)(type);
    m_sAchieveName = UtilityHelper::getLocalStringForPlist(achieveDeType, "achieve_chinese.plist", "achieve_english.plist");
    m_sAchieveTargetDesc = UtilityHelper::getLocalStringForPlist(achieveDeType+"_TARGET", "achieve_chinese.plist", "achieve_english.plist");
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
bool AchieveProperty::operator<(const AchieveProperty* v) const
{
   
    return m_detailType < v->getAchieveDetailType();
}



