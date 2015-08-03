//
//  MainScene.h
//  MazeJump
//
//  Created by wang haibo on 15/7/22.
//
//

#ifndef __MazeJump__MainScene__
#define __MazeJump__MainScene__

#include "cocos2d.h"
class MainScene : public cocos2d::Layer
{
    friend class TerrainLayer;
    MainScene();
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
    
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
private:
    void gameWin();
    void gameLose();
    
    int  m_nBgID;
};

#endif /* defined(__MazeJump__MainScene__) */
