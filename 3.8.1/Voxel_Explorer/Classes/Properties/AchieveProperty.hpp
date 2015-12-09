//
//  AchieveProperty.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/12.
//
//

#ifndef AchieveProperty_hpp
#define AchieveProperty_hpp

#include "GameConfig.h"
#include "ChaosNumber.h"
enum AchievementType
{
    eAchieveTypeOne = 1,
    eAchieveTypeTwo,
    eAchieveTypeThree,
    eAchieveTypeFour,
    eAchieveTypeFive,
    eAchieveCount
};
class AchieveProperty:public cocos2d::Ref {
    
    
public:

    CREATE_FUNC(AchieveProperty);
    virtual bool init(){return true;}
    AchieveProperty(){};
    virtual ~AchieveProperty(){};
    
    std::string m_sAchieveIcon;    //成就图标
    std::string m_sAchieveDesc;    //成就描述
    std::map<eStatistType,CChaosNumber> m_mTargets;   //成就完成目标
    std::map<eStatistType, CChaosNumber> m_mProgress;  //完成目标
    AchievementType m_achieveType;
    eAchievementDetailType m_detailType;  //成就ID
    
};

#endif /* AchieveProperty_hpp */
