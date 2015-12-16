//
//  AchieveProperty.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/12.
//
//

#ifndef AchieveProperty_hpp
#define AchieveProperty_hpp

#include "AchieveConst.h"
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
    virtual bool init();
    AchieveProperty();
    virtual ~AchieveProperty();
    
    void setAchieveIcon(std::string icon){m_sAchieveIcon = icon;};
    std::string getAchieveIcon() const {return m_sAchieveIcon;};
    
    std::string getAchieveDesc() const{return m_sAchieveDesc;};
    
    void setAchieveTarget(std::string typeStr,CChaosNumber targetNum);
    const std::map<eStatistType,CChaosNumber>& getAcheveTargets() const {return m_mAcheveTargets;};
    
    void onAcieveCommple(){m_bCommple = true;};
    bool isCommple()const{ return m_bCommple;};
    void setAchieveDetailType(std::string achieveDeType);
    eAchievementDetailType getAchieveDetailType() const{return m_detailType;}
private:
    int checkArrName(const std::vector<std::string> arr,const std::string str);
private:
    std::string m_sAchieveIcon;    //成就图标
    std::string m_sAchieveDesc;    //成就描述
    std::map<eStatistType,CChaosNumber> m_mAcheveTargets;   //成就完成目标
    std::map<eStatistType, CChaosNumber> m_mProgress;  //完成目标
    eAchievementDetailType m_detailType;  //成就ID
    bool m_bCommple;
    
};

#endif /* AchieveProperty_hpp */
