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
#include "ShatterSprite.h"
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
    
    void beginShatter();
    void endShatter();
private:
    ShatterSprite*        m_pLogo;
};

#endif /* defined(__TinyFlare__Logo__) */
