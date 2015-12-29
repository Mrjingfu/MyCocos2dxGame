//
//  ItemUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/23.
//
//

#ifndef BagMangerLayerUI_hpp
#define BagMangerLayerUI_hpp

#include "ui/CocosGUI.h"
#include "AchieveConst.h"

class AchieveMangerLayerUI:public cocos2d::ui::Layout {
    
    AchieveMangerLayerUI();
public:
    virtual ~AchieveMangerLayerUI();
    static AchieveMangerLayerUI* create(cocos2d::Size size);
    bool init(cocos2d::Size size);
    void addItemAchieve(eAchievementDetailType achieveId,cocos2d::Vec2 pt,std::string itemIcon,std::string name,std::string targetDesc,bool isUnlockeAchieve = false,bool isCommple = false);
  
    void removeItems();

    void setLayerContentSize(const cocos2d::Size &contentSize);
protected:
    cocos2d::ui::Layout* m_pItemImgLayer;
    cocos2d::ui::Layout* m_pAchieveNameLayer;
    cocos2d::ui::Layout* m_pAchieveTargetLayer;
    std::vector<eAchievementDetailType> m_Achieves;
};

#endif /* BagMangerLayerUI */
