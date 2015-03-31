//
//  Laser.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/3/30.
//
//

#include "Laser.h"
USING_NS_CC;
Laser::Laser()
{
    m_type = AT_LASER;
    m_pHalfLaserSprite1     = nullptr;
    m_pHalfLaserSprite2     = nullptr;
    m_pSlimHalfLaserSprite1 = nullptr;
    m_pSlimHalfLaserSprite2 = nullptr;
    m_fLifeTime             = 9.0f;
    m_fAlpha                = 1.0f;
}
Laser::~Laser()
{
}
void Laser::update(float delta)
{
    if(m_curState == ActorState::AS_IDLE)
    {
        m_fLifeTime -= delta;
        if(m_fLifeTime <= 0)
        {
            m_fLifeTime = 0;
            //setActorState(ActorState::AS_DEAD);
        }
    }
}
bool Laser::initLaser()
{
    //halfLaser1
    m_pHalfLaserSprite1 = LaserSprite::create();
    if(m_pHalfLaserSprite1)
    {
        m_pHalfLaserSprite1->setPorN(1.0f);
        m_pHalfLaserSprite1->setBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        m_pHalfLaserSprite1->setScaleY(0.6);
        m_pHalfLaserSprite1->setGlowColorFactor(1.6f);
        m_pHalfLaserSprite1->setLightColorFactor(0.5f);
        m_pHalfLaserSprite1->setNoiseScale(2.2f);
        addChild(m_pHalfLaserSprite1);
    }
    else
        return false;
    
    //halfLaser2
    m_pHalfLaserSprite2 = LaserSprite::create();
    if(m_pHalfLaserSprite2)
    {
        m_pHalfLaserSprite2->setPorN(-1.0f);
        m_pHalfLaserSprite2->setBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        m_pHalfLaserSprite2->setScaleY(0.6f);
        m_pHalfLaserSprite2->setGlowColorFactor(1.6f);
        m_pHalfLaserSprite2->setLightColorFactor(0.5f);
        m_pHalfLaserSprite2->setNoiseScale(2.2f);
        addChild(m_pHalfLaserSprite2);
    }
    else
        return false;
    //slimHalfLaser1
    m_pSlimHalfLaserSprite1 = LaserSprite::create();
    if(m_pSlimHalfLaserSprite1)
    {
        m_pSlimHalfLaserSprite1->setPorN(1.0f);
        m_pSlimHalfLaserSprite1->setBlendFunc(GL_ONE, GL_ONE);
        m_pSlimHalfLaserSprite1->setScaleY(0.3f);;
        m_pSlimHalfLaserSprite1->setGlowColorFactor(2.5f);
        m_pSlimHalfLaserSprite1->setLightColorFactor(0.5f);
        m_pSlimHalfLaserSprite1->setNoiseScale(1.5f);
        addChild(m_pSlimHalfLaserSprite1);
    }
    else
        return false;
    //slimHalfLaser2
    m_pSlimHalfLaserSprite2 = LaserSprite::create();
    if(m_pSlimHalfLaserSprite2)
    {
        m_pSlimHalfLaserSprite2->setPorN(-1.0f);
        m_pSlimHalfLaserSprite2->setBlendFunc(GL_ONE, GL_ONE);
        m_pSlimHalfLaserSprite2->setScaleY(0.3f);;
        m_pSlimHalfLaserSprite2->setGlowColorFactor(2.5f);
        m_pSlimHalfLaserSprite2->setLightColorFactor(0.5f);
        m_pSlimHalfLaserSprite2->setNoiseScale(1.5f);
        addChild(m_pSlimHalfLaserSprite2);
    }
    else
        return false;
    return true;
}
Vec2 Laser::getStart() const
{
    return m_start;
}
void Laser::setStart(const cocos2d::Vec2& start)
{
    m_start = start;
    m_pHalfLaserSprite1->setStart(m_start);
    m_pHalfLaserSprite2->setStart(m_start);
    m_pSlimHalfLaserSprite1->setStart(m_start);
    m_pSlimHalfLaserSprite2->setStart(m_start);
}
Vec2 Laser::getEnd() const
{
    return m_end;
}
void Laser::setEnd(const cocos2d::Vec2& end)
{
    m_end = end;
    m_pHalfLaserSprite1->setEnd(m_end);
    m_pHalfLaserSprite2->setEnd(m_end);
    m_pSlimHalfLaserSprite1->setEnd(m_end);
    m_pSlimHalfLaserSprite2->setEnd(m_end);
}
void Laser::setLaserColor(const cocos2d::Color4F& color)
{
    m_pHalfLaserSprite1->setLaserColor(color);
    m_pHalfLaserSprite2->setLaserColor(color);
    m_pSlimHalfLaserSprite1->setLaserColor(color);
    m_pSlimHalfLaserSprite2->setLaserColor(color);
}