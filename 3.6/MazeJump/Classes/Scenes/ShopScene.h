//
//  ShopScene.h
//  MazeJump
//
//  
//
//

#ifndef __MazeJump__ShopScene__
#define __MazeJump__ShopScene__

#include "cocos2d.h"
class ShopScene : public cocos2d::Layer
{
    ShopScene();
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(ShopScene);
    
private:
    cocos2d::Camera*    m_pMainCamera;
};

#endif /* defined(__MazeJump__ShopScene__) */
