//
//  Actor.h
//  Tone_Skipper
//
//  Created by wang haibo on 15/8/26.
//
//

#ifndef __Tone_Skipper__Actor__
#define __Tone_Skipper__Actor__

#include "cocos2d.h"
#include "HueSprite.h"
class Actor : public cocos2d::Node
{
protected:
    Actor();
    virtual ~Actor();
public:
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta){};
    
    virtual bool loadModel() = 0;
    virtual bool loadAnimations() = 0;
protected:
    HueSprite*  m_pSprite;
};

#endif /* defined(__Tone_Skipper__Actor__) */
