//
//  Bullet.cpp
//  Tone_Skipper
//
//  Created by 创李 on 15/10/9.
//
//

#include "Bullet.h"

Bullet::Bullet()
{
    m_Direction = cocos2d::Vec2::ZERO;
}
Bullet::~Bullet()
{
    
}
void Bullet::update(float delta)
{
    m_Velocity = m_Direction*m_fMaxXSpeed;
    cocos2d::Vec2 pos = getPosition();
    cocos2d::Vec2 newPos = pos + m_Velocity;
    setPosition(newPos);
//#if COCOS2D_DEBUG
//    showDebug(true);
//#endif
}

bool Bullet::loadModel()
{
    bool ret = true;
    m_pSprite = HueSprite::create("bullet.png");
    if(!m_pSprite)
    {
        CCLOG("QuestionMark : Load frame model failed!");
        ret = false;
    }
    addChild(m_pSprite);
    return ret;
}
bool Bullet::loadAnimations()
{
    return true;
}
void Bullet::onLand()
{
    
}
 cocos2d::Rect  Bullet::getBoundingBox() const
{
    return m_pSprite->getBoundingBox();
}