//
//  AchievementManager.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/12.
//
//

#ifndef AchievementManager_hpp
#define AchievementManager_hpp
#include "AchieveProperty.hpp"
#include "ChaosNumber.h"



class AchievementManager {
    
    AchievementManager();
public:
    virtual ~AchievementManager();
    static AchievementManager* getInstance();
    void loadAchieveData();
    void handleAchievement(eAchievementDetailType achiId);
    AchieveProperty* getAchievement(eAchievementDetailType type);
    const std::map<eAchievementDetailType, AchieveProperty*> & getAllAchieves() const{ return m_pAllAchieves;}
protected:
    void updateAchieve(AchieveProperty * achieve);
   
private:
    std::map<eAchievementDetailType, AchieveProperty*> m_pAllAchieves;
 
 };

#endif /* AchievementManager_hpp */
