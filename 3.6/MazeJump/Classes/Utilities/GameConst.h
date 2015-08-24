#ifndef _Game_Const_h_
#define _Game_Const_h_

#include <string>


static const std::string USER_MAX_LEVEL = "MaxReachDifficultLevel";

static const std::string USER_LAST_LEVEL = "LastReachDifficultLevel";

static const std::string USER_HEART_NUM = "UserHeartNum";

static const std::string USER_GOLD_NUM = "UserGoldNum";

static const std::string USER_ROLE_DATA  = "UserRoleData";

static const std::string USER_DEFAULT_ROLE_ID = "UserDefaultRoleID";

static const std::string USER_SELECT_ROLE_ID = "USER_SELECT_ROLE_ID";

static const std::string USER_UUID = "USER_UUID";

///Font
static std::string FONT_FXZS = "comic_sans_ms.ttf";


//UI

static const int LAYER_WHITE = 3;

static const std::string LAYER_NAME_UI = "UILayer";
static const int LAYER_UI = 0;


static const std::string LAYER_NAME_MASK = "MaskLayer";
static const int LAYER_MASK = 1;


static const std::string LAYER_NAME_DIALOG = "UIDialogLayer";
static const int LAYER_DIALOG = 2;

///purchase
static const std::string PURCHASE_ID1 = "coin_package1";
static const std::string PURCHASE_ID2 = "coin_package2";
static const std::string PURCHASE_ID3 = "coin_package3";
static const std::string PURCHASE_ID4 = "coin_package4";
static const std::string PURCHASE_ID5 = "coin_package5";
static const std::string PURCHASE_ID6 = "remove_ads";


////Event
static const std::string EVENT_GAME_PAUSE = "GAME_PAUSE";
static const std::string EVENT_GOLD_CHANGE = "GOLD_CHANGE";
static const std::string EVENT_HEART_CHANGE = "HEART_CHANGE";
static const std::string EVENT_RUNNER_ADD_PRODUCT = "RUNNER_ADD_PRODUCT";
static const std::string EVENT_MAX_DISTANCE_CHANGE = "MAX_DISTANCE_CHANGE";
static const std::string EVENT_RAINBOW_COLUMN_VALUE_CHANGE = "RAINBOW_COLUMN_VALUE_CHANGE";
static const std::string EVENT_RAINBOW_ROW_VALUE_CHANGE = "RAINBOW_ROW_VALUE_CHANGE";
static const std::string EVENT_RUNNER_LOSE = "RUNNER_LOSE";
static const std::string EVENT_RUNNER_LOSE_CHANGE_VIEW = "RUNNER_LOSE_CHANGE_VIEW";
static const std::string EVENT_RUNNER_RECOVER_PAUSE = "RUNNER_RECOVER_PAUSE";
static const std::string EVENT_RUNNER_PAUSE_RESUME = "RUNNER_PAUSE_RESUME";
static const std::string EVENT_MAZEJUMP_WIN = "MAZEJUMP_WIN";
static const std::string EVENT_MAZEJUMP_LOSE = "MAZEJUMP_LOSE";
static const std::string EVENT_MAZEJUMP_RECORD_END = "MAZEJUMP_RECORD_END";
static const std::string EVENT_START_GOLD_CHANGE = "START_GOLD_CHANGE";
static const std::string EVENT_START_HEART_CHANGE = "START_HEART_CHANGE";
static const std::string EVENT_CHARACTER_MODEL_CHANGE = "CHARACTER_MODEL_CHANGE";
static const std::string EVENT_PURCHASE_GOLD_OK = "PURCHASE_GOLD_OK";
static const std::string EVENT_PURCHASE_REMOVEADS_OK = "PURCHASE_REMOVEADS_OK";
#endif //_Scene_Const_h_