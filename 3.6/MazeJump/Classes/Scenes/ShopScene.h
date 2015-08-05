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
    ShopScene(const std::string& tip);
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(const std::string& tip);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    
private:
    cocos2d::Camera*    m_pMainCamera;
    std::string m_tip;
};

#endif /* defined(__MazeJump__ShopScene__) */
