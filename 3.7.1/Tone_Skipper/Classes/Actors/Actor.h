//
//  Actor.h
//  Tone_Skipper
//
//  Created by wang haibo on 15/8/26.
//
//

#ifndef __Tone_Skipper__Actor__
#define __Tone_Skipper__Actor__

#include "cocos2d.h"
#include "HueSprite.h"
class Actor : public cocos2d::Node
{
protected:
    Actor();
    virtual ~Actor();
public:
    typedef enum{
        RT_UNKNOWN,
        RT_COLLIDER
    }
    RAYCAST_TYPE;
    static constexpr float Gravity = -10.0f;
    virtual void update(float delta);
    
    void setFlipX(bool fliped);
    void setMaxSpeed(float speed) { m_fMaxSpeed = speed;}
    
    void setAccelX(float x) { m_Accel.x = x;}
    void setAccelY(float y) { m_Accel.y = y;}
    
    virtual bool loadModel() = 0;
    virtual bool loadAnimations() = 0;
    virtual void onLand() = 0;
protected:
    HueSprite*  m_pSprite;
    
    float                       m_fMaxSpeed;
    cocos2d::Vec2               m_Velocity;
    cocos2d::Vec2               m_Accel;
    bool                        m_bOnLand;
};

#endif /* defined(__Tone_Skipper__Actor__) */
