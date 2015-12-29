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
private:
    void onClickMainMenu(Ref* ref);
    void onClickAchieve(Ref* ref);
    void onClickHelp(Ref* ref);
    void onClickSound(Ref* ref);
    void onClickMuisc(Ref* ref);
private:
    cocos2d::ui::ImageView* m_pSoundImg;
    cocos2d::ui::ImageView* m_pMuiscImg;
    bool m_bIsSoundOn;
    bool m_bIsMuiscOn;
    
};

#endif /* PausePopupUI_hpp */
