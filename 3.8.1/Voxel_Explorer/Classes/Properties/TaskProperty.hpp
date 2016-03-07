//
//  TaskProperty.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 16/3/5.
//
//

#ifndef TaskProperty_hpp
#define TaskProperty_hpp
#include "AchieveConst.h"
#include "ChaosNumber.h"
#include "PickableItemProperty.hpp"
class TaskProperty:public cocos2d::Ref {
    TaskProperty();
public:
    ~TaskProperty();
    static TaskProperty* create();
    const std::map<eStatistType,CChaosNumber>&  getTaskTargets() const {return m_mTaskTargets; }
    const std::map<PickableItemProperty::PickableItemPropertyType,CChaosNumber>&  getRewards() const {return m_mRewards; }
private:
    void randomDatas();
private:
    std::string m_sTaskDesc;
    std::map<eStatistType,CChaosNumber> m_mTaskTargets;
    std::map<PickableItemProperty::PickableItemPropertyType,CChaosNumber> m_mRewards;
    
};

#endif /* TaskProperty_hpp */
