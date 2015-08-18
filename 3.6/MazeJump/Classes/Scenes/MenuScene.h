//
//  MenuScene.h
//  MazeJump
//
//  Created by wang haibo on 15/6/23.
//
//

#ifndef __MazeJump__MenuScene__
#define __MazeJump__MenuScene__

#include "cocos2d.h"
#include "EffectSprite3D.h"
#include "Runner.h"
#include "RibbonTrail.h"
class MenuScene : public cocos2d::Layer
{
    MenuScene();
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);
    
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
    
    // 处理输入
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) override;
private:
    void switchToMainScene();
    void startGame();
    void runnerJump();
private:
    cocos2d::Camera*    m_pMainCamera;
    EffectSprite3D*     m_pSea;
    EffectSprite3D*     m_pSea1;
    EffectSprite3D*     m_pSea2;
    EffectSprite3D*     m_pSea3;
    EffectSprite3D*     m_pStandPlatform;
    Runner*             m_pRunner;
    RibbonTrail*        m_pRainbow;
    cocos2d::LayerColor*        m_pWhiteLayer;
    bool                m_bStartGame;
    float               m_fTime;
    cocos2d::Vec3       m_dirDist;
};

#endif /* defined(__MazeJump__MenuScene__) */
