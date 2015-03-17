//
//  Bullet.cpp
//  Geometry-Wars
//
//  Created by wang haibo on 15/3/5.
//
//

#include "Bullet.h"
USING_NS_CC;
Bullet::Bullet()
{
}
Bullet::~Bullet()
{
}
void Bullet::update(float delta)
{
    float rotationZ = CC_RADIANS_TO_DEGREES(Vec2::angle(m_Orientation, Vec2::UNIT_Y));
    if (m_Orientation.x < 0)
        rotationZ = -rotationZ;
    setRotation(rotationZ);
    m_Velocity = m_Direction*m_fMaxSpeed;
    Vec2 pos = getPosition();
    Vec2 newPos = pos + m_Velocity;
    setPosition(newPos);
}
void Bullet::loadTexture(const std::string& textureName)
{
    m_pModel = Sprite::create(textureName);
    if(!m_pModel)
        CCLOG("Load bullet texture failed!");
    addChild(m_pModel);
    caculateRadius();
}
void Bullet::setColorMask(const cocos2d::Color3B& mask)
{
    if(m_pModel)
        m_pModel->setColor(mask);
}
void Bullet::setBlendFunc(const BlendFunc& blendFunc)
{
    Sprite* sprite = static_cast<Sprite*>(m_pModel);
    if(sprite)
        sprite->setBlendFunc(blendFunc);
}