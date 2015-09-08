//
//  Actor.cpp
//  Tone_Skipper
//
//  Created by wang haibo on 15/8/26.
//
//

#include "Actor.h"
#include "MapMgrs.h"
USING_NS_CC;

Actor::Actor()
{
    m_pSprite = nullptr;
    m_Velocity = Vec2::ZERO;
    m_Accel = Vec2::ZERO;
    m_bOnLand = true;
    m_fMaxSpeed = 0;
}
Actor::~Actor()
{
}
void Actor::update(float delta)
{
    if(!m_pSprite)
        return;
    if(!m_bOnLand)
        m_Accel = Vec2(m_Accel.x, Gravity);
    m_Velocity += m_Accel*delta;
    if(m_Velocity.x >= m_fMaxSpeed)
        m_Velocity.x = m_fMaxSpeed;
    else if(m_Velocity.x <= -m_fMaxSpeed)
        m_Velocity.x = -m_fMaxSpeed;
    if(m_Velocity.length() > 0)
    {
        Vec2 nextPos = getPosition() + m_Velocity;
        cocos2d::Rect rect = m_pSprite->getBoundingBox();
        rect.origin = nextPos;
        Actor::RAYCAST_TYPE type = Actor::RT_COLLIDER;
        int flag = MapMgrs::CF_NONE;
        bool collision = MapMgrs::getInstance()->checkCollision(rect, flag, type);
        if(collision)
        {
            if((flag & MapMgrs::CF_LAND) != 0)
            {
                if(m_bOnLand == false)
                {
                    m_bOnLand = true;
                    this->onLand();
                }
                else
                {
                    if(m_Velocity.y < 0)
                        m_Velocity.y = 0;
                }
            }
            setPosition(getPosition() + m_Velocity);
                
            switch (type) {
                case Actor::RT_COLLIDER:
                    break;
                    
                default:
                    break;
            }
        }
        else
        {
            setPosition(nextPos);
            if(m_bOnLand && m_Velocity.y > 0)
                m_bOnLand = false;
        }
    }
}
void Actor::setFlipX(bool fliped)
{
    if(m_pSprite)
        m_pSprite->setFlippedX(fliped);
}