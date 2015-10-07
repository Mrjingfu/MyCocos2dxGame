//
//  MainUi.h
//  Tone_Skipper
//
//  Created by 创李 on 15/9/19.
//
//

#ifndef __Tone_Skipper__MainUi__
#define __Tone_Skipper__MainUi__

#include "WrapperUILayer.h"
#include "GameConfig.h"


class MainUi:public WrapperUILayer
{

    
public:
    MainUi();
    virtual ~MainUi();
    
    virtual void addEvents();
    virtual void onEnter();
    virtual void onExit();
    
    void onEventTips(cocos2d::EventCustom *sender);
    void update(float dt);
    void sliderPercentChanged(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
    void onBag(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    CREATE_FUNC(MainUi);
private:
    cocos2d::Label* m_pTipsLabel;
    cocos2d::ui::ImageView* m_pHeart[4];
    cocos2d::ui::LoadingBar* m_pEnergyBar;
    cocos2d::Label* m_pTimeLabel;
    cocos2d::Label* m_pScoreLabel;
    cocos2d::Label* m_pBombLabel;
    cocos2d::Label* m_pDiamondLabel;
    cocos2d::Label* m_pBulletLabel;
    cocos2d::Label* m_pKeyCopperLabel;
    cocos2d::Label* m_pKeyGoldLabel;
    cocos2d::Label* m_pKeySilverLabel;
    float m_pTime;
};

#endif /* defined(__Tone_Skipper__MainUi__) */
