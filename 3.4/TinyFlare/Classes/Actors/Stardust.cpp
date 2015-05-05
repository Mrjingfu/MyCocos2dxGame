//
//  Stardust.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/4/20.
//
//

#include "Stardust.h"
#include "GameController.h"
#include "ChaosNumber.h"
USING_NS_CC;
Stardust::Stardust()
{
    m_fAccel = 10;
    m_fMaxSpeed = 5;
}
Stardust::~Stardust()
{
}
void Stardust::loadModel(const std::string& modelName)
{
    if(m_pModel)
    {
        removeChild(m_pModel);
        m_pModel = nullptr;
    }
    m_pModel = ParticleSystemQuad::create("magicfire.plist");
    if(m_pModel == nullptr)
        CCLOGERROR("Load model magicfire.plist failed!");
    addChild(m_pModel);
}

void Stardust::update(float delta)
{
    Vec2 targetPos = GameController::getInstance()->getStardustTargetPos();
    
    if(getPosition().distance(targetPos) < 50)
        setActorState(AS_DEAD);
    
    setDirection(targetPos - getPosition());
    m_Velocity += m_Direction*m_fAccel*delta;
    if(m_Velocity.length() >= m_fMaxSpeed)
    {
        m_Velocity.normalize();
        m_Velocity = m_Velocity*m_fMaxSpeed;
    }
    Vec2 pos = getPosition();
    Vec2 newPos = pos + m_Velocity;
    setPosition(newPos);
}
void Stardust::onEnterDead()
{
    if (m_StardustType == ST_LARGE) {
        ChaosNumber num(5);
        GameController::getInstance()->addStardust(num);
    }
    else if(m_StardustType == ST_SMALL)
    {
        ChaosNumber num(1);
        GameController::getInstance()->addStardust(num);
    }
}