//
//  AchieveMangerEnLayerUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 16/1/18.
//
//

#ifndef AchieveMangerEnLayerUI_hpp
#define AchieveMangerEnLayerUI_hpp

#include "AchieveMangerLayerUI.h"

class  AchieveMangerEnLayerUI:public AchieveMangerLayerUI{
    
public:
    static AchieveMangerEnLayerUI* create(cocos2d::Size size);
    void addItemAchieve(cocos2d::ui::ImageView* achieveItemUi,eAchievementDetailType achieveId,std::string itemIcon,std::string name,std::string targetDesc,bool isUnlockeAchieve = false,bool isCommple = false) override;
};

#endif /* AchieveMangerEnLayerUI_hpp */
