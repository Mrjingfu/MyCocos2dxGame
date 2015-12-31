//
//  ScreenShake.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/12/29.
//
//

#ifndef CircleMoveAct_hpp
#define CircleMoveAct_hpp

#include "cocos2d.h"
class CircleMoveAct : public cocos2d::ActionInterval
{
public:
   static CircleMoveAct* create(float duration, const cocos2d::Vec2& center, float scale, float angle);
   bool initWithDuration(float duration, const cocos2d::Vec2& center, float scaleDiff, float angle);
    virtual CircleMoveAct* clone() const override;
    virtual void startWithTarget(cocos2d::Node *target) override;
    virtual void update(float time) override;
    virtual CircleMoveAct* reverse(void) const override;
    void stop(void) override;
protected:
    float m_duration;
    cocos2d::Vec2 m_center;
    float m_scaleDiff;
    float m_currScale;
    float m_angle;
    float m_anglePreFrame;
    int m_frameCnts;
    cocos2d::Vec2 m_initPos;
};

#endif /* CircleMoveAct_hpp */
