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
class GameScene : public cocos2d::Layer
{
    GameScene();
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
private:
    cocos2d::Camera*    m_pMainCamera;
};

#endif /* defined(__MazeJump__GameScene__) */
