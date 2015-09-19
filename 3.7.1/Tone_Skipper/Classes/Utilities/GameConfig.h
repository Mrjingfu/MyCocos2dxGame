//
//  GameConfig.h
//  Tone_Skipper
//
//  Created by 创李 on 15/9/18.
//
//

#ifndef Tone_Skipper_GameConfig_h
#define Tone_Skipper_GameConfig_h
#include "cocos2d.h"

#define SCREEN_HEIGHT        (cocos2d::Director::getInstance()->getVisibleSize().height)
#define SCREEN_WIDTH         (cocos2d::Director::getInstance()->getVisibleSize().width)
#define SCREEN_SCALE         (SCREEN_HEIGHT/320.0f)
#define WND_CENTER_X (SCREEN_WIDTH/2)
#define WND_CENTER_Y (SCREEN_HEIGHT/2)
#define WINDOW_CENTER cocos2d::Vec2(WND_CENTER_X,WND_CENTER_Y)



enum eZOrder
{
    eZOrderGameLayer = 5,     //游戏层
    eZOrderUILayer = 10,     //UI层
    eZOrderAboveUILayer = 15, //UI之上，popup之下的层
    eZOrderPopupUILayer = 20, //PopupUI层
    eZOrderPopupLayer = 25   //PopupUI之上层
};



#endif
