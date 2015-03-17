//
//  Player.cpp
//  Geometry-Wars
//
//  Created by wang haibo on 15/2/5.
//
//

#include "Player.h"
#include "ActorsManager.h"
USING_NS_CC;

Player::Player()
{
    m_type = AT_PLAYER;
    m_bScheduledFire = false;
    m_fMaxSpeed = 10.0f;
    m_fAccel = 20.0f;
    m_fDecel = -1.0f;
    m_pMaskModel = nullptr;
    m_WeaponType = WT_NORMAL;
}
Player::~Player()
{
}
void Player::update(float delta)
{
    float maskRotationZ = CC_RADIANS_TO_DEGREES(Vec2::angle(m_Orientation, Vec2::UNIT_Y));
    if (m_Orientation.x < 0)
        maskRotationZ = -maskRotationZ;
    m_pMaskModel->setRotation(maskRotationZ);
    
    if(m_Direction != Vec2::ZERO)
    {
        float mainRotationZ = CC_RADIANS_TO_DEGREES(Vec2::angle(m_Direction, Vec2::UNIT_Y));
        if (m_Direction.x < 0)
            mainRotationZ = -mainRotationZ;
        m_pModel->setRotation(mainRotationZ);
    }
    
    if(!m_bBounce)
    {
        if (m_Direction == Vec2::ZERO) {
            m_Velocity *= 0.99f;
            if(m_Velocity.length() <0.001f)
                m_Velocity = Vec2::ZERO;
        }
        else
        {
            m_Velocity += m_Direction*m_fAccel*delta;
            if(m_Velocity.length() >= m_fMaxSpeed)
            {
                m_Velocity.normalize();
                m_Velocity = m_Velocity*m_fMaxSpeed;
            }
        }
    }
    Vec2 pos = getPosition();
    Vec2 newPos = pos + m_Velocity;
    setPosition(newPos);
}
void Player::loadMaskModel(const std::string& texName)
{
    if(m_pMaskModel)
    {
        removeChild(m_pMaskModel);
        m_pMaskModel = nullptr;
    }
    m_pMaskModel = Sprite::create(texName);
    if(m_pMaskModel == nullptr)
        CCLOGERROR("Load mask model %s failed!" , texName.c_str());
    m_pMaskModel->setScale(0.5f);
    addChild(m_pMaskModel);
}
void Player::onJoystickUpdateDirection(TwoJoysticks* joystick, const cocos2d::Vec2& dir)
{
    setDirection(dir);
}
void Player::onJoystickUpdateOrientation(TwoJoysticks* joystick, const cocos2d::Vec2& dir)
{
    if(dir == Vec2::ZERO)
        return;
    setOrientation(dir);
}
void Player::onJoystickPressed(TwoJoysticks* joystick, float pressedTime)
{
    if(!m_bScheduledFire)
    {
        schedule(schedule_selector(Player::fire), 0.5f, -1, 0);
        m_bScheduledFire = true;
    }
}
void Player::onJoystickReleased(TwoJoysticks* joystick, float pressedTime)
{
    if(m_bScheduledFire)
    {
        unschedule(schedule_selector(Player::fire));
        m_bScheduledFire = false;
    }
}

Vec2 Player::getFirePos()
{
    Vec2 ret = getPosition();
    ret += m_Orientation*m_fRadius*0.8f;
    return ret;
}

void Player::fire(float delta)
{
    switch (m_WeaponType) {
        case WT_NORMAL:
            {
                ActorsManager::spawnBullet(GameActor::AT_PLAYER_BULLET, getFirePos(), getOrientation(), 2.0f,"bullet1.png");
                ActorsManager::spawnExplosion(Explosion::ExplosionType::ET_BLUE, getFirePos());
            }
            break;
            
        default:
            break;
    }
}
void Player::hurt()
{
}
void Player::die()
{
}

