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
#include "GameController.h"
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
    m_pShadowNode = nullptr;
}
Player::~Player()
{
}
void Player::update(float delta)
{
    if(m_curState == ActorState::AS_DEAD)
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
}

void Player::respawn()
{
    ParticleSystemHelper::spawnExplosion(ExplosionType::ET_EXPLOSION_ACTOR_RESPAWN, Vec2::ZERO);
    EaseSineIn* easeIn = EaseSineIn::create(FadeIn::create(1.0f));
    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Player::beginShadow,this));
    
    Sequence* sequence = Sequence::create(easeIn, callFunc, NULL);
    runAction(sequence);
}
void Player::beginShadow()
{
    m_pShadowNode = Node::create();
    if(m_pShadowNode && m_pModel && m_pMaskModel)
    {
        auto shadowModel = Sprite::createWithTexture(m_pModel->getTexture());
        if(shadowModel)
        {
            shadowModel->setBlendFunc(BlendFunc::ADDITIVE);
            m_pShadowNode->addChild(shadowModel);
        }
        auto shadowMaskModel = Sprite::createWithTexture(m_pMaskModel->getTexture());
        if(shadowMaskModel)
        {
            shadowMaskModel->setBlendFunc(BlendFunc::ADDITIVE);
            m_pShadowNode->addChild(shadowMaskModel);
        }
        m_pShadowNode->setCascadeOpacityEnabled(true);
        m_pShadowNode->setOpacity(255);
        m_pShadowNode->setScale(0.5f);
        m_pShadowNode->setCameraMask((unsigned short)CameraFlag::USER1);
        
        addChild(m_pShadowNode);
        
        EaseSineIn* easeIn1 = EaseSineIn::create(FadeOut::create(0.5f));
        EaseSineIn* easeIn2 = EaseSineIn::create(ScaleTo::create(0.5f, 1.3f));
        Spawn* spawn = Spawn::createWithTwoActions(easeIn1, easeIn2);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Player::endShadow,this));
        Sequence* sequence = Sequence::create(spawn, callFunc, NULL);
        
        m_pShadowNode->runAction(sequence);
        
        m_pLeftTail = ParticleSystemHelper::spawnActorWidget(ActorWidgetType::AWT_PLAYER_TAIL, getLeftTailLocalPos(), this);
        m_pRightTail = ParticleSystemHelper::spawnActorWidget(ActorWidgetType::AWT_PLAYER_TAIL, getRightTailLocalPos(), this);
    }
}
void Player::endShadow()
{
    if(m_pShadowNode)
    {
        m_pShadowNode->removeFromParentAndCleanup(true);
        m_pShadowNode = nullptr;
    }
    setActorState(ActorState::AS_UNDERCONTROL);
}
void Player::onJoystickUpdateDirection(TwoJoysticks* joystick, const cocos2d::Vec2& dir)
{
    if(m_curState != ActorState::AS_UNDERCONTROL)
        return;
    setDirection(dir);
}
void Player::onJoystickUpdateOrientation(TwoJoysticks* joystick, const cocos2d::Vec2& dir)
{
    if(m_curState != ActorState::AS_UNDERCONTROL)
        return;
    if(dir == Vec2::ZERO)
        return;
    setOrientation(dir);
}
void Player::onJoystickPressed(TwoJoysticks* joystick, float pressedTime)
{
    if(!m_bScheduledFire)
    {
        schedule(CC_SCHEDULE_SELECTOR(Player::fire), 0.5f, -1, 0);
        m_bScheduledFire = true;
    }
}
void Player::onJoystickReleased(TwoJoysticks* joystick, float pressedTime)
{
    if(m_bScheduledFire)
    {
        unschedule(CC_SCHEDULE_SELECTOR(Player::fire));
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
    if(m_curState != ActorState::AS_UNDERCONTROL)
        return;
    switch (m_WeaponType) {
        case WT_NORMAL:
            {
                ActorsManager::spawnBullet(GameActor::AT_PLAYER_BULLET, getFireWorldPos(), getOrientation(),m_fMaxSpeed*2.0f,"bullet1.png", Color3B(254,148,236), 0.5f, 3.0f);
                ParticleSystemHelper::spawnActorWidget(ActorWidgetType::AWT_FIRE_FLARE, getFireLocalPos(), this);
            }
            break;
            
        default:
            break;
    }
}

void Player::onEnterDead()
{
    ParticleSystemHelper::spawnExplosion(ExplosionType::ET_EXPLOSION_BLUE, getPosition());
    if (m_pModel)
        m_pModel->setVisible(false);
    if(m_pMaskModel)
        m_pMaskModel->setVisible(false);
    if(m_pLeftTail)
        m_pLeftTail->removeFromParentAndCleanup(true);
    if(m_pRightTail)
        m_pRightTail->removeFromParentAndCleanup(true);
    
    GameController::getInstance()->setGameState(GameState::GS_PAUSE);
}
void Player::onExitDead()
{
    if (m_pModel)
        m_pModel->setVisible(true);
    if(m_pMaskModel)
        m_pMaskModel->setVisible(true);
}