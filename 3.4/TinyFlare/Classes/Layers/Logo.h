//
//  Logo.h
//  TinyFlare
//
//  Created by wang haibo on 15/4/14.
//
//

#ifndef __TinyFlare__Logo__
#define __TinyFlare__Logo__

#include "cocos2d.h"

class Logo : public cocos2d::Layer
{
    Logo();
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Logo);
    
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
private:
    cocos2d::Sprite*        m_pLogo;
};

#endif /* defined(__TinyFlare__Logo__) */
