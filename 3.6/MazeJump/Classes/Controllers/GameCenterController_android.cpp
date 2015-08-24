//
//  GameCenterController.cpp
//  MazeJump
//
//  Created by wang haibo on 15/8/17.
//
//

#include "GameCenterController.h"
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
//#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
//    m_AchievementDict = FileUtils::getInstance()->getValueMapFromFile("achievement.plist");
//#endif
}

GameCenterController::~GameCenterController()
{
}


void GameCenterController::openLeaderBoard()
{
//#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
//    [[NCSGameCenter sharedGameCenter] showLeaderboard];
//#endif
}
void GameCenterController::reportScore(int score)
{
//#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
//    [[NCSGameCenter sharedGameCenter] reportScore:score];
//#endif
}
void GameCenterController::reportCachedScores()
{
//#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
//    [[NCSGameCenter sharedGameCenter] reportCachedScores];
//#endif
}
void GameCenterController::retrieveTopXScores(int num)
{
//#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
//    [[NCSGameCenter sharedGameCenter] retrieveTopXScores:num];
//#endif
}

// 打开成就页。
void GameCenterController::openAchievementBoard()
{
//#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
//    [[NCSGameCenter sharedGameCenter] showAchievementboard];
//#endif
}

//判断成就是否已经解锁
bool GameCenterController::isAchievementUnlocked(const std::string& strId)
{
    bool ret = true;
//#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
//    const char* pIdentifier = m_AchievementDict[strId].asString().c_str();
//    GKAchievement* achievement = getAchievementByID(pIdentifier);
//    if ( achievement )
//    {
//        ret = achievement.completed;
//    }
//#endif
    return ret;
}

//解锁成就
void GameCenterController::unlockAchievement(const std::string& strId)
{
//#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
//    const char* pIdentifier = m_AchievementDict[strId].asString().c_str();
//    
//    GKAchievement* achievement = getAchievementByID(pIdentifier);
//    if ( achievement != NULL && achievement.completed != YES )
//    {
//        [[NCSGameCenter sharedGameCenter] unlockAchievement:achievement
//                                                    percent:100.0];
//    }
//#endif
}