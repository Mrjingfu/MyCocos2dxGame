//
//  AchievePopupUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/12/7.
//
//

#ifndef AchievePopupUI_hpp
#define AchievePopupUI_hpp

#include "PopupUILayer.h"

class AchieveMangerLayerUI;
class AchievePopupUI: public PopupUILayer{
    AchievePopupUI();
    
public:
    virtual ~AchievePopupUI();
    CREATE_FUNC(AchievePopupUI);
    virtual bool initUi() override;
    virtual bool addEvents() override;
private:
    AchieveMangerLayerUI*  m_pAchieveMangerLayer;
};

#endif /* AchievePopupUI_hpp */
