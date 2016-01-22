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
    void onClickRevive(cocos2d::Ref* ref);
    void onClickRestart(cocos2d::Ref* ref);
    void onClickAda(cocos2d::Ref* ref);
    void CountDown(float dt);
private:
    cocos2d::ui::Button* m_pBtnDead;
    cocos2d::ui::ImageView* m_pAdaIcon;
    cocos2d::ui::TextBMFont*  m_pAdaDesc;
    cocos2d::ui::TextBMFont*  m_pContinueNum;
    int m_nCountDownNum;
    
};

#endif /* DeadPopupUI_hpp */
