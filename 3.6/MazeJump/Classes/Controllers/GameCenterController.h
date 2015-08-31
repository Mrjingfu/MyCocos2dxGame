//
//  GameCenterController.h
//  MazeJump
//
//  Created by wang haibo on 15/8/17.
//
//

#ifndef __MazeJump__GameCenterController__
#define __MazeJump__GameCenterController__

#include "cocos2d.h"
class GameCenterController : public cocos2d::Ref
{
public:
    GameCenterController();
    virtual ~GameCenterController();
    
public:
    static GameCenterController* getInstance();
    
    void registerGameCenterController();
    void openLeaderBoard();
    void reportScore(int score);
    void reportCachedScores();
    void retrieveTopXScores(int num);
    
    void openAchievementBoard();
    // Unlock achievement APIs
    void unlockAchievement(const std::string& strId);
protected:
    bool isAchievementUnlocked(const std::string& strId);
    
private:
    cocos2d::ValueMap  m_AchievementDict;
};

#endif /* defined(__MazeJump__GameCenterController__) */
