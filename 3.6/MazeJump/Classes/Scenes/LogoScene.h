//
//  LogoScene.h
//  MazeJump
//
//  Created by wang haibo on 15/6/23.
//
//

#ifndef __MazeJump__LogoScene__
#define __MazeJump__LogoScene__

#include "cocos2d.h"
class LogoScene : public cocos2d::Layer
{
    LogoScene();
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(LogoScene);
private:
    void precache();
    void endcache();
private:
    cocos2d::Sprite*    m_pLogoSprite;
};

#endif /* defined(__MazeJump__LogoScene__) */
