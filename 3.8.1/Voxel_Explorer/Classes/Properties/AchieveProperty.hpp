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

class AchieveProperty:public cocos2d::Ref {
    
    
public:
    AchieveProperty(){};
    virtual ~AchieveProperty(){};
    
    
private:
    std::string m_sAchieveIcon;    //成就图标
    std::string m_sAchieveDesc;    //成就描述
    std::vector<int> m_vTargets;   //成就完成目标
    int m_nAchiveId;               //成就ID
    
};

#endif /* AchieveProperty_hpp */
