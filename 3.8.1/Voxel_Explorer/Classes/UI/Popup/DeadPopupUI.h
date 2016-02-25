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
    //是否观看广告倒计时
    void CountDown(float dt);
    //复活按钮点击倒计时
    void reveiveCountDown(float dt);
    //更新重新开始按钮UI
    void updateRestartUi();
    //更新复活按钮UI
    void updateReviveUi();
    
    void onKeyBackClick()override;

private:
    cocos2d::ui::Button* m_pBtnDead;
    cocos2d::ui::ImageView* m_pAdaIcon;
    cocos2d::ui::TextBMFont*  m_pAdaDesc;
    cocos2d::ui::TextBMFont*  m_pContinueNum;
    cocos2d::ui::TextBMFont*  m_pDepthReviveText;
    int m_nCountDownNum;    
    int m_nReviveTouchNum;

};

#endif /* DeadPopupUI_hpp */
