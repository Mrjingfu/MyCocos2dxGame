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

struct AchieveTarget
{
    std::string m_sAchieveTargetDesc;
    CChaosNumber m_nTargetNum;
    AchieveTarget()
    {
        m_nTargetNum = 0;
    }
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
    
    void setAchieveTarget(std::string typeStr,std::string targetDesc,CChaosNumber targetNum);
    const std::map<eStatistType,AchieveTarget*>& getAcheveTargets() const {return m_mAcheveTargets;};
    void onHideAchieve(){m_bIsHideAchieve = true;}
    void onAcieveCommple(){m_bCommple = true;};
    bool isCommple()const{ return m_bCommple;};
    void setAchieveDetailType(std::string achieveDeType);
    void release();
    eAchievementDetailType getAchieveDetailType() const{return m_detailType;}
private:
    int checkArrName(const std::vector<std::string> arr,const std::string str);
private:
    std::string m_sAchieveIcon;    //成就图标
    std::string m_sAchieveDesc;    //成就描述
    std::map<eStatistType,AchieveTarget*> m_mAcheveTargets;   //成就完成目标
    std::map<eStatistType, CChaosNumber> m_mProgress;  //完成目标
    eAchievementDetailType m_detailType;  //成就ID
    bool m_bIsHideAchieve;
    bool m_bCommple;
    
};

#endif /* AchieveProperty_hpp */
