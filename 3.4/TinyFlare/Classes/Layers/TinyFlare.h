//
//  TinyFlare.h
//  TinyFlare
//
//  Created by wang haibo on 15/3/12.
//
//

#ifndef __TinyFlare__TinyFlare__
#define __TinyFlare__TinyFlare__

#include "cocos2d.h"

class TinyFlare : public cocos2d::Layer
{
    TinyFlare();
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(TinyFlare);
    
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
    
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *unused_event);
};

#endif /* defined(__TinyFlare__TinyFlare__) */
