//
//  Laser.h
//  TinyFlare
//
//  Created by wang haibo on 15/3/30.
//
//

#ifndef __TinyFlare__Laser__
#define __TinyFlare__Laser__

#include "GameActor.h"
#include "LaserSprite.h"
class Laser : public GameActor
{
    friend class ActorsManager;
protected:
    Laser();
    virtual ~Laser();
public:
    bool initLaser();
    cocos2d::Vec2 getStart() const;
    void setStart(const cocos2d::Vec2& start);
    cocos2d::Vec2 getEnd() const;
    void setEnd(const cocos2d::Vec2& end);
    void setLaserColor(const cocos2d::Color4F& color);
    virtual void update(float delta) override;
private:
    LaserSprite*    m_pHalfLaserSprite1;
    LaserSprite*    m_pHalfLaserSprite2;
    LaserSprite*    m_pSlimHalfLaserSprite1;
    LaserSprite*    m_pSlimHalfLaserSprite2;
    cocos2d::Vec2   m_start;
    cocos2d::Vec2   m_end;
    float           m_fLifeTime;
    float           m_fAlpha;
};

#endif /* defined(__TinyFlare__Laser__) */
