//
//  AchieveItemPopupUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/12/17.
//
//

#ifndef AchieveItemUI_hpp
#define AchieveItemUI_hpp

#include "WrapperUILayer.h"

class AchieveItemUI :public WrapperUILayer {
    
    AchieveItemUI();
public:
    virtual ~AchieveItemUI();
    CREATE_FUNC(AchieveItemUI);
     bool initUi() override;
     bool addEvents() override;
     void setAchieveDatas(const std::string icon,const std::string name,const std::string targetDesc);
private:
    cocos2d::ui::ImageView* m_pAchieveIcon;
    cocos2d::ui::Text*  m_pAchieveName;
    cocos2d::ui::Text*  m_pAchieveTargetDesc;
};

#endif /* AchieveItemLayer_hpp */
