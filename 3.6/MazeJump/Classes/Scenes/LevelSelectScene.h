//
//  LevelSelectScene.h
//  MazeJump
//
//  Created by wang haibo on 15/6/23.
//
//

#ifndef __MazeJump__LevelSelectScene__
#define __MazeJump__LevelSelectScene__

#include "cocos2d.h"
class LevelSelectScene : public cocos2d::Layer
{
    LevelSelectScene();
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(LevelSelectScene);
private:
    cocos2d::Skybox*    m_pSkyBox;
};

#endif /* defined(__MazeJump__LevelSelectScene__) */
