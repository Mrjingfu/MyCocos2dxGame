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
    void onClickSetting(Ref* ref);
    void onClickExitGame(Ref* ref);
private:
    cocos2d::ui::Button*     m_pBtnMainMenu;
    cocos2d::ui::Button*     m_pBtnSetting;
    cocos2d::ui::Button*     m_pBtnExitGame;
};

#endif /* PausePopupUI_hpp */
