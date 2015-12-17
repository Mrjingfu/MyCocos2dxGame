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
    release();
}

bool AchieveProperty::init()
{
    return true;
}

void AchieveProperty::setAchieveTarget(std::string typeStr,std::string targetDesc,CChaosNumber targetNum)
{
    int type = checkArrName(STATIST_TYPE_NAME,typeStr);
    CCASSERT(type!=-1, "type error");
    eStatistType sStype = (eStatistType)type;
    AchieveTarget* achieveTarget = new AchieveTarget;
    achieveTarget->m_sAchieveTargetDesc = targetDesc;
    achieveTarget->m_nTargetNum  = targetNum;
    m_mAcheveTargets.insert(std::map<eStatistType,AchieveTarget*>::value_type(sStype,achieveTarget));
}

void AchieveProperty::setAchieveDetailType(std::string achieveDeType)
{
    m_sAchieveDesc = UtilityHelper::getLocalStringForPlist(achieveDeType, "achieve_chinese.plist", "achieve_english.plist");
    int type = checkArrName(ACHIEVEMENT_DATAIL_TYPE_NAME,achieveDeType);
    CCASSERT(type!=-1, "type error");
    m_detailType = (eAchievementDetailType)(type);
  
}
void AchieveProperty::release()
{
    for (auto iter = m_mAcheveTargets.begin(); iter!=m_mAcheveTargets.end(); iter++)
    {
        
        AchieveTarget* target = iter->second;
        CC_SAFE_DELETE(target);
    }
    m_mAcheveTargets.clear();
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



