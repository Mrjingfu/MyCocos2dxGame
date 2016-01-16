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
    void reportScore(const std::string& rank_id, const cocos2d::Value& value);
    void reportCachedScores();
    void retrieveTopXScores(const std::string& rank_id, int num);
    
    void reportLevel(int level);
    void reportMoney(float goldcoins);
    void retrieveTopXLevel(int num);
    void retrieveTopXMoney(int num);
    
    void openAchievementBoard();
    void reportAchievement(const std::string& strId, float percent);
};

#endif /* defined(__MazeJump__GameCenterController__) */
