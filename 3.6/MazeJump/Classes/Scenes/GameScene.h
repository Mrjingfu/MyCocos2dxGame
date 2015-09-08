//
//  GameScene.h
//  MazeJump
//
//  Created by wang haibo on 15/6/23.
//
//

#ifndef __MazeJump__GameScene__
#define __MazeJump__GameScene__

#include "cocos2d.h"
#include "GameController.h"
class GameScene : public cocos2d::Layer
{
    friend class GroundLayer;
    friend class Player;
    GameScene(int difficultLevel,GameController::MAZE_MODE mademode);
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(int difficultLevel,GameController::MAZE_MODE mazeMode);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually

    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
private:
    void gameWin();
    void gameLose();
    void gameRecordEnd();
private:
    int m_nDifficultLevel;
    GameController::MAZE_MODE m_mazeMode;
    int  m_nBgID;
};

#endif /* defined(__MazeJump__GameScene__) */
