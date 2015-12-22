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
    CREATE_FUNC(SettingPopupUI);
    virtual ~SettingPopupUI();
    bool initUi() override;
    bool addEvents() override;
private:
    void onClickSound(Ref* ref);
    void onClickMuisc(Ref* ref);
    void onClickHelp(Ref* ref);
private:
    cocos2d::ui::ImageView* m_pSoundImg;
    cocos2d::ui::ImageView* m_pMuiscImg;
    bool m_bIsSoundOn;
    bool m_bIsMuiscOn;
};

#endif /* SettingPopupUI_hpp */
