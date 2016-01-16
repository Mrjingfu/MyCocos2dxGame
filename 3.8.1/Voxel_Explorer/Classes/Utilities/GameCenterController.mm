//
//  GameCenterController.cpp
//  MazeJump
//
//  Created by wang haibo on 15/8/17.
//
//

#include "GameCenterController.h"
#include "AchieveConst.h"
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
#include "NCSGameCenter.h"
#endif
USING_NS_CC;

GameCenterController* g_pGameCenterControllerInstance = nullptr;
GameCenterController* GameCenterController::getInstance()
{
    if( g_pGameCenterControllerInstance == nullptr )
        g_pGameCenterControllerInstance = new GameCenterController();
    
    return g_pGameCenterControllerInstance;
}

GameCenterController::GameCenterController()
{
}

GameCenterController::~GameCenterController()
{
}

void GameCenterController::registerGameCenterController()
{
 #if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
    [[NCSGameCenter sharedGameCenter] authenticateLocalUser];
#endif
}


void GameCenterController::openLeaderBoard()
{
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
    [[NCSGameCenter sharedGameCenter] showLeaderboard];
#endif
}
void GameCenterController::reportScore(const std::string& rank_id, const cocos2d::Value& value)
{
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
    NSNumber *number = nil;
    if (value.getType() == Value::Type::FLOAT) {
        number = [NSNumber numberWithFloat:value.asFloat()];
    }
    else if (value.getType() == Value::Type::INTEGER) {
        number = [NSNumber numberWithInt:value.asInt()];
    }
    else
        number = [NSNumber numberWithInt:0];
    [[NCSGameCenter sharedGameCenter] reportScore:[NSString stringWithUTF8String: rank_id.c_str()] score:number];
#endif
}
void GameCenterController::reportCachedScores()
{
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
    [[NCSGameCenter sharedGameCenter] reportCachedScores];
#endif
}
void GameCenterController::retrieveTopXScores(const std::string& rank_id, int num)
{
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
    [[NCSGameCenter sharedGameCenter] retrieveTopXScores:[NSString stringWithUTF8String: rank_id.c_str()] number: num];
#endif
}

void GameCenterController::reportLevel(int level)
{
    reportScore("level_ranking",Value(level));
}
void GameCenterController::reportMoney(float goldcoins)
{
    reportScore("rich_ranking",Value(goldcoins));
}
void GameCenterController::retrieveTopXLevel(int num)
{
    retrieveTopXScores("level_ranking", num);
}
void GameCenterController::retrieveTopXMoney(int num)
{
    retrieveTopXScores("rich_ranking", num);
}

// 打开成就页。
void GameCenterController::openAchievementBoard()
{
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
    [[NCSGameCenter sharedGameCenter] showAchievementboard];
#endif
}

//解锁成就
void GameCenterController::reportAchievement(const std::string& strId, float percent)
{
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
    NSString* achievementID = [NSString stringWithUTF8String: strId.c_str()];
    [[NCSGameCenter sharedGameCenter] reportAchievement:achievementID percent:percent];
#endif
}