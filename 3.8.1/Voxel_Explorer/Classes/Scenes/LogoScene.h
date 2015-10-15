//
//  LogoScene.h
//  Voxel_Explorer
//
//  Created by wang haibo on 15/9/17.
//
//

#ifndef __Voxel_Explorer__LogoScene__
#define __Voxel_Explorer__LogoScene__

#include "cocos2d.h"
#include "HueSprite.h"
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
    
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
private:
    void precache();
    void endcache();
    void createColorLogo();
private:
    cocos2d::Node*  m_NodeRoot1;
    cocos2d::Sprite*      m_pT0;
    cocos2d::Sprite*      m_pI0;
    cocos2d::Sprite*      m_pN0;
    cocos2d::Sprite*      m_pY0;
    cocos2d::Sprite*      m_pF0;
    cocos2d::Sprite*      m_pL0;
    cocos2d::Sprite*      m_pA0;
    cocos2d::Sprite*      m_pR0;
    cocos2d::Sprite*      m_pE0;
    
    cocos2d::Node*  m_NodeRoot2;
    HueSprite*      m_pT1;
    HueSprite*      m_pI1;
    HueSprite*      m_pN1;
    HueSprite*      m_pY1;
    HueSprite*      m_pF1;
    HueSprite*      m_pL1;
    HueSprite*      m_pA1;
    HueSprite*      m_pR1;
    HueSprite*      m_pE1;
};

#endif /* defined(__Voxel_Explorer__LogoScene__) */
