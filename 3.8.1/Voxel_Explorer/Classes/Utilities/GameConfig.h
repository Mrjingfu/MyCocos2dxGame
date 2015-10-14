//
//  GameConfig.h
//  Tone_Skipper
//
//  Created by 创李 on 15/9/18.
//
//

#ifndef __TinyFlare_GameConfig_h__
#define __TinyFlare_GameConfig_h__
#include "cocos2d.h"

#define SCREEN_HEIGHT        (cocos2d::Director::getInstance()->getVisibleSize().height)
#define SCREEN_WIDTH         (cocos2d::Director::getInstance()->getVisibleSize().width)
#define SCREEN_SCALE         (SCREEN_HEIGHT/320.0f)
#define WND_CENTER_X (SCREEN_WIDTH/2)
#define WND_CENTER_Y (SCREEN_HEIGHT/2)
#define WINDOW_CENTER cocos2d::Vec2(WND_CENTER_X,WND_CENTER_Y)

#define DEFAULT_FONT "ZpixEX2_EX.ttf"

#define sRecordMD5          "sM"
#define sHavePlayedGame		"HavePlayedGame"
#define sArchiveName        "GameArchive"
#define MAX_DIAMOD 100

#define SINGLE_FUNC(__TYPE__) \
static __TYPE__* getInstance() \
{ \
static __TYPE__ pRet;  \
return &pRet; \
}


//存储数据的版本号
enum eUserRecordVersion
{
    eUserRecordVersion0 = 0,
    eUserRecordVersionCount
};
enum eChaoType
{
    eCTDiamond = 0,
    eCTBomb,
    eCTBullet,
    eCTKeyCopper,
    eCTKeyGold,
    eCTKeySilver,
    eCTMax
    
};
enum eStartupType{
    eStartupNormal,
    eStartupFirstInstall
};

enum eZOrder
{
    eZOrderGameLayer = 5,     //游戏层
    eZOrderUILayer = 10,     //UI层
    eZOrderAboveUILayer = 15, //UI之上，popup之下的层
    eZOrderPopupUILayer = 20, //PopupUI层
    eZOrderPopupLayer = 25   //PopupUI之上层
};


//EVENT
static const std::string EVENT_MAIN_TIPS = "";

#endif//__Tone_Skipper_GameConfig_h__
