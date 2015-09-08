//
//  GameController.h
//  MazeJump
//
//  Created by wang haibo on 15/7/4.
//
//

#ifndef __MazeJump__GameController__
#define __MazeJump__GameController__

#include "cocos2d.h"
#include "GroundLayer.h"
#include "GameInfoUI.h"
class GameController : public cocos2d::Ref
{
    GameController();
    ~GameController();
public:
    typedef enum {
        NORAML,
        MAZE,
    } MAZE_MODE;

    static GameController* getInstance();
    bool init(cocos2d::Layer* pMainLayer,int difficultLevel,MAZE_MODE mazeMode);
    void update(float delta);
    void destroy();
    int randomLevel();
    void switchToRainbowRun();
    void switchToMenu();
    int getCurrentLevel(){return m_currentLevel;}
    int getDifficultLevel(){return m_difficultLevel;}
    MAZE_MODE getMazeMode(){return m_mazeMode;}
    bool createMap(bool _playing,int level);
    int  getCurrentGoldReward();
    int  getCurrentHeartReward();
private:
    void switchToMainScene();
    void switchToMenuScene();
private:
    cocos2d::Layer*     m_pMainLayer;
    cocos2d::Skybox*    m_pSkyBox;
    GroundLayer*        m_pGroundLayer;
    cocos2d::Camera*    m_pMainCamera;
    MAZE_MODE           m_mazeMode;
    cocos2d::LayerColor*        m_pWhiteLayer;
    int m_currentLevel;
    int m_difficultLevel;
};

#endif /* defined(__MazeJump__GameController__) */
