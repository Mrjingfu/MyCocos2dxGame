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
protected:
    AchieveItemUI();
public:
    virtual ~AchieveItemUI();
    CREATE_FUNC(AchieveItemUI);
    virtual bool initUi() override;
    bool addEvents() override;
    virtual void setAchieveDatas(const std::string icon, std::string name, std::string targetDesc);
protected:
    cocos2d::ui::ImageView* m_pAchieveIcon;
    cocos2d::ui::TextBMFont*  m_pAchieveName;
    cocos2d::ui::TextBMFont*  m_pAchieveTargetDesc;
};

#endif /* AchieveItemLayer_hpp */
