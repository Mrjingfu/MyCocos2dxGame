//
//  Player.cpp
//  Geometry-Wars
//
//  Created by wang haibo on 15/2/5.
//
//

#include "Player.h"
#include "ActorsManager.h"
#include "ParticleSystemHelper.h"
USING_NS_CC;

Player::Player()
{
    m_type = AT_PLAYER;
    m_bScheduledFire = false;
    m_fMaxSpeed = 8.0f;
    m_fAccel = 20.0f;
    m_pMaskModel = nullptr;
    m_WeaponType = WT_NORMAL;
    m_pLeftTail = nullptr;
    m_pRightTail = nullptr;
    m_bIsLive = true;
}
Player::~Player()
{
}
void Player::update(float delta)
{
    if(!m_bIsLive)
        return;
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
        
        if(m_pLeftTail)
            m_pLeftTail->setPosition(getLeftTailLocalPos().rotateByAngle(Vec2::ZERO, -M_PI*(mainRotationZ/180.0f)));
        if(m_pRightTail)
            m_pRightTail->setPosition(getRightTailLocalPos().rotateByAngle(Vec2::ZERO, -M_PI*(mainRotationZ/180.0f)));
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
    
    m_pLeftTail = ParticleSystemHelper::spawnPlayerWidget(PlayerWidgetType::PWT_TAIL, getLeftTailLocalPos());
    m_pRightTail = ParticleSystemHelper::spawnPlayerWidget(PlayerWidgetType::PWT_TAIL, getRightTailLocalPos());
}
void Player::onJoystickUpdateDirection(TwoJoysticks* joystick, const cocos2d::Vec2& dir)
{
    if(!m_bIsLive)
        return;
    setDirection(dir);
}
void Player::onJoystickUpdateOrientation(TwoJoysticks* joystick, const cocos2d::Vec2& dir)
{
    if(!m_bIsLive)
        return;
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

Vec2 Player::getFireWorldPos()
{
    Vec2 ret = getPosition();
    ret += m_Orientation*m_fRadius*0.8f;
    return ret;
}
Vec2 Player::getFireLocalPos()
{
    return m_Orientation*m_fRadius*0.8f;
}
Vec2 Player::getLeftTailLocalPos()
{
    return Vec2(-1.0f,-1.0f)*m_fRadius*0.5f;
}
Vec2 Player::getRightTailLocalPos()
{
    return Vec2(1.0f,-1.0f)*m_fRadius*0.5f;
}
void Player::fire(float delta)
{
    if(!m_bIsLive)
        return;
    switch (m_WeaponType) {
        case WT_NORMAL:
            {
                ActorsManager::spawnBullet(GameActor::AT_PLAYER_BULLET, getFireWorldPos(), getOrientation(),m_fMaxSpeed*2.0f,"bullet1.png");
                ParticleSystemHelper::spawnPlayerWidget(PlayerWidgetType::PWT_FIRE_FLARE, getFireLocalPos());
            }
            break;
            
        default:
            break;
    }
}
void Player::die()
{
    ParticleSystemHelper::spawnExplosion(ExplosionType::ET_EXPLOSION_BLUE, getPosition());
    m_bIsLive = false;
}
void Player::respawn()
{
    m_bIsLive = true;
}
bool Player::islive() const
{
    return m_bIsLive;
}
