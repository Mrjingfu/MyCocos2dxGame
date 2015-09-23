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
    void sliderPercentChanged(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
    CREATE_FUNC(MainUi);
private:
    cocos2d::Label* tipsLabel;
};

#endif /* defined(__Tone_Skipper__MainUi__) */
