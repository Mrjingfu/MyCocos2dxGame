//
//  SettingUILayer.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/26.
//
//

#ifndef PausePopupUI_hpp
#define PausePopupUI_hpp

#include "PopupUILayer.h"

class PausePopupUI: public PopupUILayer{
    PausePopupUI();
    
public:
    CREATE_FUNC(PausePopupUI);
    virtual ~PausePopupUI();
    virtual bool initUi() override;
    virtual bool addEvents() override;
};

#endif /* PausePopupUI_hpp */
