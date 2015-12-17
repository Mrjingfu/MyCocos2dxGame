//
//  AchieveItemPopupUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/12/17.
//
//

#ifndef AchieveItemPopupUI_hpp
#define AchieveItemPopupUI_hpp

#include "PopupUILayer.h"

class AchieveItemPopupUI :public PopupUILayer {
    
    AchieveItemPopupUI();
public:
    virtual ~AchieveItemPopupUI();
    CREATE_FUNC(AchieveItemPopupUI);
     bool initUi() override;
     bool addEvents() override;
     void inAction() override;
     void outAction() override;
     void inActionCallFunc() override;
     bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
     void setAchieveDatas(const std::string icon,const std::string name,const std::string targetDesc);
private:
    cocos2d::ui::ImageView* m_pAchieveIcon;
    cocos2d::ui::Text*  m_pAchieveName;
    cocos2d::ui::Text*  m_pAchieveTargetDesc;
};

#endif /* AchieveItemPopupUI_hpp */
