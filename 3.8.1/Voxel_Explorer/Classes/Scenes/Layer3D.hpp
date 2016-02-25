//
//  Layer3D.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/29.
//
//

#ifndef Layer3D_hpp
#define Layer3D_hpp

#include "cocos2d.h"

class Layer3D : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init() override;
    
    CREATE_FUNC(Layer3D);
    
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
    float           m_fRotateThreshold;
};

#endif /* Layer3D_hpp */
