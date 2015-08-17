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
    static GameController* getInstance();
    bool init(cocos2d::Layer* pMainLayer,int difficultLevel);
    void update(float delta);
    void destroy();
    int randomLevel();
    void switchToRainbowRun();
    int getCurrentLevel(){return m_currentLevel;}
    int getDifficultLevel(){return m_difficultLevel;}
    bool createMap(bool _playing,int level);
    int  getCurrentGoldReward();
    int  getCurrentHeartReward();
private:
    void switchToMainScene();
private:
    cocos2d::Layer*     m_pMainLayer;
    cocos2d::Skybox*    m_pSkyBox;
    GroundLayer*        m_pGroundLayer;
    cocos2d::Camera*    m_pMainCamera;

    cocos2d::LayerColor*        m_pWhiteLayer;
    int m_currentLevel;
    int m_difficultLevel;
};

#endif /* defined(__MazeJump__GameController__) */
