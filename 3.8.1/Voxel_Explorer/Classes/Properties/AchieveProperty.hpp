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



class AchieveProperty:public cocos2d::Ref {
    
public:
    CREATE_FUNC(AchieveProperty);
    virtual bool init();
    AchieveProperty();
    virtual ~AchieveProperty();
    
    void setAchieveIcon(const std::string icon){m_sAchieveIcon = icon;};
    std::string getAchieveIcon() const {return m_sAchieveIcon;};
    
    std::string getAchieveName() const{return m_sAchieveName;};
    
    std::string getTargetDesc() const{return  m_sAchieveTargetDesc;};
    
    void setAchieveTarget(std::string typeStr,CChaosNumber targetNum);
    
    const std::map<eStatistType,CChaosNumber>& getAcheveTargets() const {return m_mAcheveTargets;};
    
    void setHideAchieve(bool isHide){m_bIsHideAchieve = isHide;}
    void onAcieveCommple(){m_bCommple = true;};
    bool isCommple()const{ return m_bCommple;};
    bool isHideAchieve() const {return m_bIsHideAchieve;}
    void setAchieveDetailType(std::string achieveDeType);

    eAchievementDetailType getAchieveDetailType() const{return m_detailType;}
    
    bool operator<(const AchieveProperty* v) const;
    
private:
    int checkArrName(const std::vector<std::string> arr,const std::string str);
private:
    std::string m_sAchieveIcon;    //成就图标
    std::string m_sAchieveName;    //成就描述
    std::string m_sAchieveTargetDesc;
    std::map<eStatistType,CChaosNumber> m_mAcheveTargets;   //成就完成目标
    std::map<eStatistType, CChaosNumber> m_mProgress;  //完成目标
    eAchievementDetailType m_detailType;  //成就ID
    bool m_bIsHideAchieve;
    bool m_bCommple;
    
};

#endif /* AchieveProperty_hpp */
