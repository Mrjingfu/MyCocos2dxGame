//
//  TestScene.h
//  Tone_Skipper
//
//  Created by wang haibo on 15/8/26.
//
//

#ifndef __Tone_Skipper__TestScene__
#define __Tone_Skipper__TestScene__

#include "cocos2d.h"

class TestScene : public cocos2d::Layer
{
    TestScene();
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(TestScene);
    
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
};

#endif /* defined(__Tone_Skipper__TestScene__) */
