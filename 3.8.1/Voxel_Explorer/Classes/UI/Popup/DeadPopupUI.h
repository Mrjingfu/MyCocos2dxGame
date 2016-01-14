//
//  DeadPopupUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/26.
//
//

#ifndef DeadPopupUI_hpp
#define DeadPopupUI_hpp

#include "PopupUILayer.h"

class DeadPopupUI:public PopupUILayer {
    DeadPopupUI();
    
public:
    CREATE_FUNC(DeadPopupUI);
    virtual ~DeadPopupUI();
    virtual bool initUi() override;
    bool addEvents() override;
private:
    void onClickMainMenu(cocos2d::Ref* ref);
    void onClickRestart(cocos2d::Ref* ref);
private:
    cocos2d::ui::Button* m_pBtnMenu;
    cocos2d::ui::Button* m_pBtnRestart;
};

#endif /* DeadPopupUI_hpp */
