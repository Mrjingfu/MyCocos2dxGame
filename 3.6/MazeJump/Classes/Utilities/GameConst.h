#ifndef _Game_Const_h_
#define _Game_Const_h_

#include <string>


static const std::string USER_MAX_LEVEL = "MaxReachDifficultLevel";

static const std::string USER_LAST_LEVEL = "LastReachDifficultLevel";

static const std::string USER_HEART_NUM = "UserHeartNum";

static const std::string USER_GOLD_NUM = "UserGoldNum";

///Font
static std::string FONT_FXZS = "FZXS12.TTF";


//UI
static const std::string LAYER_NAME_UI = "UILayer";
static const int LAYER_UI = 0;


static const std::string LAYER_NAME_MASK = "MaskLayer";
static const int LAYER_MASK = 1;


static const std::string LAYER_NAME_DIALOG = "UIDialogLayer";
static const int LAYER_DIALOG = 2;
//SHOP
static const std::string SHOP_HEART_NOT_ENOUGH= "HEART_NOT_ENOUGH";
static const std::string SHOP_GOLD_NOT_ENOUGH= "GOLDT_NOT_ENOUGH";
static const std::string SHOP_BUY= "SHOP_BUY";




////Event
static const std::string EVENT_GOLD_CHANGE = "GOLD_CHANGE";
static const std::string EVENT_HEART_CHANGE = "HEART_CHANGE";
static const std::string EVENT_MAX_DISTANCE_CHANGE = "MAX_DISTANCE_CHANGE";
static const std::string EVENT_RAINBOW_VALUE_CHANGE = "RAINBOW_VALUE_CHANGE";
static const std::string EVENT_RUNNER_LOSE = "RUNNER_LOSE";
static const std::string EVENT_MAZEJUMP_WIN = "MAZEJUMP_WIN";
static const std::string EVENT_MAZEJUMP_LOSE = "MAZEJUMP_LOSE";
static const std::string EVENT_HIDE_NOT_AIN = "EVENT_HIDE_NOT_AIN";
#endif //_Scene_Const_h_