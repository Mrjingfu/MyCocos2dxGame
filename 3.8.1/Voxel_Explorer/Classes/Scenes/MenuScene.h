//
//  MenuScene.h
//  Voxel_Explorer
//
//
//

#ifndef __Voxel_Explorer__MenuScene__
#define __Voxel_Explorer__MenuScene__

#include "cocos2d.h"
class LoadingLayer;
class MenuScene : public cocos2d::Layer
{
    MenuScene(bool isFirst);
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(bool isFirst = false);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;
    
    // implement the "static create()" method manually
    static MenuScene* create(bool isFirst = false);
    void update(float dt) override;
    virtual void onEnter() override;
    virtual void onExit() override;
private:
    void loadMenuLayer();
private:
    bool m_bIsFirst;
    float timedt;
    bool isLoading;
    LoadingLayer* loadingLayer;
};

#endif /* defined(__Voxel_Explorer__MenuScene__) */
