//
//  GameCenterController.cpp
//  MazeJump
//
//  Created by wang haibo on 15/8/17.
//
//

#include "GameCenterController.h"
#include "NCSGameCenter.h"
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
    m_AchievementDict = FileUtils::getInstance()->getValueMapFromFile("achievement.plist");
}

GameCenterController::~GameCenterController()
{
}
void GameCenterController::registerGameCenterController()
{
    [[NCSGameCenter sharedGameCenter] authenticateLocalUser];
}

void GameCenterController::openLeaderBoard()
{
    [[NCSGameCenter sharedGameCenter] showLeaderboard];
}
void GameCenterController::reportScore(int score)
{
    [[NCSGameCenter sharedGameCenter] reportScore:score];
}
void GameCenterController::reportCachedScores()
{
    [[NCSGameCenter sharedGameCenter] reportCachedScores];
}
void GameCenterController::retrieveTopXScores(int num)
{
    [[NCSGameCenter sharedGameCenter] retrieveTopXScores:num];
}

//公共函数，通过成就id获取成就指针
GKAchievement* getAchievementByID(const char* id)
{
    GKAchievement* pRet = NULL;
    if ( id )
    {
        NSString* identifier = [[NSString alloc] initWithUTF8String:id];
        pRet = [[NCSGameCenter sharedGameCenter] getAchievementForID:identifier];
    }
    
    return pRet;
}

// 打开成就页。
void GameCenterController::openAchievementBoard()
{
    [[NCSGameCenter sharedGameCenter] showAchievementboard];
}

//判断成就是否已经解锁
bool GameCenterController::isAchievementUnlocked(const std::string& strId)
{
    bool ret = true;
    
    const char* pIdentifier = m_AchievementDict[strId].asString().c_str();
    
    GKAchievement* achievement = getAchievementByID(pIdentifier);
    if ( achievement )
    {
        ret = achievement.completed;
    }
    return ret;
}

//解锁成就
void GameCenterController::unlockAchievement(const std::string& strId)
{
    const char* pIdentifier = m_AchievementDict[strId].asString().c_str();
    
    GKAchievement* achievement = getAchievementByID(pIdentifier);
    if ( achievement != NULL && achievement.completed != YES )
    {
        [[NCSGameCenter sharedGameCenter] unlockAchievement:achievement
                                                    percent:100.0];
    }
}