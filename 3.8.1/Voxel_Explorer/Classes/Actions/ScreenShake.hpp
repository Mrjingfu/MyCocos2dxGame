//
//  ScreenShake.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/12/29.
//
//

#ifndef ScreenShake_hpp
#define ScreenShake_hpp

#include "cocos2d.h"
class ScreenShake : public cocos2d::ActionInterval
{
public:
    // Create the action with a time and a strength (same in x and y)
    // 产生震动效果的初始化函数参数,两个方向相同
    // @param d 震动持续的时间
    // @param strength 震动的幅度
    static ScreenShake* create(float d, float strength);
    // Create the action with a time and strengths (different in x and y)
    // 产生震动效果的初始化函数,两个方向值不一样
    static ScreenShake* create(float d, float strength_x, float strength_y, float strength_z);
    bool initWithDuration(float d, float strength_x, float strength_y, float strength_z);
    
    //以下都是重写父类抽象类的函数(必须重写)
    virtual ScreenShake* clone() const override;
    virtual ScreenShake* reverse(void) const override;
    virtual void startWithTarget(cocos2d::Node *target) override;
    virtual void update(float time) override;
    virtual void stop(void) override;
    
protected:
    // Initial position of the shaked node
    // 精灵的位置
    float _initial_x, _initial_y, _initial_z;
    // Strength of the action
    // 抖动的幅度
    float _strength_x, _strength_y, _strength_z;
};

#endif /* ScreenShake_hpp */
