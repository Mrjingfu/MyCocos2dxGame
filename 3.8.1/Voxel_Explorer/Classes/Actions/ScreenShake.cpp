//
//  ScreenShake.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/12/29.
//
//

#include "ScreenShake.hpp"
USING_NS_CC;
ScreenShake* ScreenShake::create(float d, float strength )
{
    // call other construction method with twice the same strength
    return create( d, strength, strength, strength);
}

ScreenShake* ScreenShake::create(float duration, float strength_x, float strength_y, float strength_z)
{
    ScreenShake *p_action = new ScreenShake();
    p_action->initWithDuration(duration, strength_x, strength_y, strength_z);
    p_action->autorelease();
    
    return p_action;
}

bool ScreenShake::initWithDuration(float duration, float strength_x, float strength_y, float strength_z)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _strength_x = strength_x;
        _strength_y = strength_y;
        _strength_z = strength_z;
        
        return true;
    }
    
    return false;
}

void ScreenShake::update(float time)
{
    float randx = cocos2d::random( -_strength_x, _strength_x );
    float randy = cocos2d::random( -_strength_y, _strength_y );
    float randz = cocos2d::random( -_strength_z, _strength_z );
    // move the target to a shaked position
    _target->setPosition3D(Vec3(_initial_x + randx,
                              _initial_y + randy, _initial_z + randz));
}

ScreenShake* ScreenShake::clone(void) const
{
    auto a = new ScreenShake();
    a->initWithDuration(_duration, _strength_x, _strength_y, _strength_z);
    a->autorelease();
    return a;
}

ScreenShake* ScreenShake::reverse() const
{
    return ScreenShake::create(_duration, -_strength_x, -_strength_y, -_strength_z);
}

void ScreenShake::startWithTarget(cocos2d::Node *target)
{
    ActionInterval::startWithTarget(target);
    
    // save the initial position
    _initial_x = target->getPosition3D().x;
    _initial_y = target->getPosition3D().y;
    _initial_z = target->getPosition3D().z;
}

void ScreenShake::stop(void)
{
    // Action is done, reset clip position
    _target->setPosition3D(Vec3( _initial_x, _initial_y, _initial_z ) );
    
    ActionInterval::stop();
}