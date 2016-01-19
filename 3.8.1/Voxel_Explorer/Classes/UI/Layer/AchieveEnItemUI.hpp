//
//  AchieveItemPopupUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/12/17.
//
//

#ifndef AchieveEnItemUI_hpp
#define AchieveEnItemUI_hpp

#include "AchieveItemUI.hpp"

class AchieveEnItemUI :public AchieveItemUI {
    
public:
  
    CREATE_FUNC(AchieveEnItemUI);
     bool initUi() override;
     void setAchieveDatas(const std::string icon, std::string name, std::string targetDesc) override;
};

#endif /* AchieveEnItemUI_hpp */
