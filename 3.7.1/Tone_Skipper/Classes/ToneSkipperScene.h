//
//  ToneSkipperScene.h
//  Tone_Skipper
//
//  Created by wang haibo on 15/8/24.
//
//

#ifndef __Tone_Skipper__ToneSkipperScene__
#define __Tone_Skipper__ToneSkipperScene__

#include "cocos2d.h"

class ToneSkipperScene : public cocos2d::Layer
{
    ToneSkipperScene();
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(ToneSkipperScene);
    
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
};

#endif /* defined(__Tone_Skipper__ToneSkipperScene__) */
