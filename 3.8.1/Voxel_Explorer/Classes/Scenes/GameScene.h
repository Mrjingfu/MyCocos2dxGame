//
//  GameScene.h
//  Voxel_Explorer
//
//  Created by wang haibo on 15/9/24.
//
//

#ifndef __Voxel_Explorer__GameScene__
#define __Voxel_Explorer__GameScene__

#include "cocos2d.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init() override;
    
    CREATE_FUNC(GameScene);
    
    virtual void onEnter() override;
    virtual void onExit() override;
protected:
    // 处理输入
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) override;
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event) override;
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) override;
private:
    void prepareToJump();
    void rotateToForward();
    void rotateToBack();
    void rotateToLeft();
    void rotateToRight();
    void excuteToJump();
private:
    cocos2d::Vec2   m_TouchBegin;
    cocos2d::Vec2   m_TouchEnd;
};

#endif /* defined(__Voxel_Explorer__GameScene__) */
