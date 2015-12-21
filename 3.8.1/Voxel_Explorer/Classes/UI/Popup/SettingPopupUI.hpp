//
//  SettingPopupUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/12/19.
//
//

#ifndef SettingPopupUI_hpp
#define SettingPopupUI_hpp

#include "PopupUILayer.h"

class SettingPopupUI :public PopupUILayer
{
    SettingPopupUI();
public:
    virtual ~SettingPopupUI();
    bool initUi() override;
    bool addEvents() override;
private:
    
};

#endif /* SettingPopupUI_hpp */
