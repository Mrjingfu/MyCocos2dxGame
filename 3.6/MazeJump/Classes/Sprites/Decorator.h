//
//  Decorator.h
//  MazeJump
//
//  Created by wang haibo on 15/7/29.
//
//

#ifndef __MazeJump__Decorator__
#define __MazeJump__Decorator__

#include "EffectSprite3D.h"
class Decorator : public EffectSprite3D
{
public:
    typedef enum
    {
        DT_HEART = 0,
        DT_GOLD,
        DT_GOLD_BIG,
        DT_BIRD,
        DT_PLANE,
        DT_PORTAL,
        DT_UNKNOWN
    }
    DecoratorType;
    
    static Decorator* create(DecoratorType type);
    Decorator();
    virtual ~Decorator();
    virtual void update(float delta);
    
    float getRadius() const { return m_fRadius; }
    bool getNeedToCollision() const { return m_bNeedToCollision; }
    void setNeedToCollision(bool need) { m_bNeedToCollision = need; }
    
    bool getNeedToUpdate() const { return m_bNeedToUpdate; }
    void setNeedToUpdate(bool need) { m_bNeedToUpdate = need; }
    
    DecoratorType getType() const { return m_Type; }
    void setType(DecoratorType type) { m_Type = type; }
    
    void setFakeShadow(cocos2d::Layer* ownerLayer);
protected:
    DecoratorType           m_Type;
    float                   m_fRadius;
    bool                    m_bNeedToCollision;
    bool                    m_bNeedToUpdate;
    float                   m_fTime;
    cocos2d::Sprite3D*         m_pFakeShadow;
};

#endif /* defined(__MazeJump__Decorator__) */
