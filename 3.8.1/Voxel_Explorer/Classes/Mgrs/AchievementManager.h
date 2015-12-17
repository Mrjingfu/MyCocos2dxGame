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
    bool loadAchieveData();
    void handleAchievement(eAchievementDetailType achiId);
    void checkAllAchievement();
    void load();
    void save();
   
    const cocos2d::Vector<AchieveProperty*> & getAllAchieves() const{ return m_vAllAchieves;}
protected:
    AchieveProperty* getAchievement(eAchievementDetailType type);
    void updateAchieve(AchieveProperty * achieve);
   
private:
    cocos2d::Vector<AchieveProperty*> m_vAllAchieves;
 
 };

#endif /* AchievementManager_hpp */
