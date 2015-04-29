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
#include "EncrytionUtility.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

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
    m_pMultiNode  = nullptr;
    m_pProtectedNode = nullptr;
    m_fAccelTime     = 0.0f;
    m_fProtectedTime = 0.0f;
    m_fMultiTime     = 0.0f;
    m_fSlowTime      = 0.0f;
    m_fFireDelta     = 0.5f;
    m_nBoomBulletNum = 8;
    ////lwwhb add for debug
    addBuffer(BT_PROTECTED);
    ///
    m_pPlayerListener = nullptr;
}
Player::~Player()
{
}
void Player::onEnter()
{
    Node::onEnter();
    scheduleUpdate();
}
void Player::onExit()
{
    unscheduleUpdate();
    Node::onExit();
}
void Player::updateBuffer(float delta)
{
    if(m_nBufferType & BufferType::BT_ACCEL)
    {
        if(m_fAccelTime > 0.0f)
            m_fAccelTime -= delta/_scheduler->getTimeScale();
        else
            removeBuffer(BufferType::BT_ACCEL);
    }
    if(m_nBufferType & BufferType::BT_MULTI)
    {
        if(m_fMultiTime > 0.0f)
            m_fMultiTime -= delta/_scheduler->getTimeScale();
        else
            removeBuffer(BufferType::BT_MULTI);
    }
    if(m_nBufferType & BufferType::BT_PROTECTED)
    {
        ////lwwhb add for debug
//        if(m_fProtectedTime > 0.0f)
//            m_fProtectedTime -= delta/_scheduler->getTimeScale();
//        else
//            removeBuffer(BufferType::BT_PROTECTED);
        ///
        if(m_pProtectedNode)
        {
            float startSkewX = m_pProtectedNode->getRotationSkewX();
            float startSkewY = m_pProtectedNode->getRotationSkewY();
            m_pProtectedNode->setRotationSkewX(startSkewX + delta*90.0f);
            m_pProtectedNode->setRotationSkewY(startSkewY + delta*90.0f);
        }
    }
    if(m_nBufferType & BufferType::BT_TIME)
    {
        if(m_fSlowTime > 0.0f)
            m_fSlowTime -= delta/_scheduler->getTimeScale();
        else
            removeBuffer(BufferType::BT_TIME);
    }
}
void Player::update(float delta)
{
    updateBuffer(delta);
    if(m_curState == ActorState::AS_DEAD)
        return;
    float maskRotationZ = CC_RADIANS_TO_DEGREES(Vec2::angle(m_Orientation, Vec2::UNIT_Y));
    if (m_Orientation.x < 0)
        maskRotationZ = -maskRotationZ;
    m_pMaskModel->setRotation(maskRotationZ);
    if(m_pMultiNode)
        m_pMultiNode->setRotation(maskRotationZ);
    
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
void Player::addBuffer(BufferType type)
{
    SimpleAudioEngine::getInstance()->playEffect("Pickup_GemBells14.wav");
    m_nBufferType |= type;
    if(type == BT_ACCEL)
    {
        beginAccel();
    }
    if(type == BT_MULTI)
    {
        removeMulti();
        beginMulti();
    }
    if(type == BT_PROTECTED)
    {
        removeProtected();
        beginProtected();
    }
    if(type == BT_BOOM)
    {
        removeBuffer(BT_BOOM);
        ParticleSystemHelper::spawnExplosion(ET_EXPLOSION_CLEAR, getPosition());
        Vec2 orient = Vec2::UNIT_Y;
        m_nBoomBulletNum = 8*EncrytionUtility::getIntegerForKey("BoomLevel", 1);
        for (int i = 0; i<(int)(m_nBoomBulletNum.GetLongValue()); ++i) {
            orient.rotate(Vec2::ZERO, M_PI*2.0f/(int)(m_nBoomBulletNum.GetLongValue()));
            ActorsManager::spawnBullet(GameActor::AT_PLAYER_BULLET, getPosition(), orient, 10.0f,"bullet1.png", Color3B(0,224,252), 1.0f, 3.0f);
        }
    }
    if(type == BT_TIME)
    {
        beginTime();
    }
}
void Player::removeBuffer(BufferType type)
{
    if(type == BT_ACCEL)
    {
        endAccel();
    }
    if(type == BT_MULTI)
    {
        endMulti();
    }
    if(type == BT_PROTECTED)
    {
        endProtected();
    }
    if(type == BT_TIME)
    {
        endTime();
    }
    m_nBufferType = m_nBufferType&~type;
}
void Player::beginShadow()
{
    m_pShadowNode = Node::create();
    if(m_pShadowNode && m_pModel && m_pMaskModel)
    {
        auto shadowModel = Sprite::createWithTexture(((Sprite*)m_pModel)->getTexture());
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

void Player::beginAccel()
{
    m_fFireDelta = 0.5f*(powf(0.8f, EncrytionUtility::getIntegerForKey("AccelLevel", 1)));
    m_fAccelTime = 15.0f*(powf(1.1f, EncrytionUtility::getIntegerForKey("EffectTimeLevel", 1)));
    if(m_pPlayerListener)
        m_pPlayerListener->onBeginAccel(m_fAccelTime);
}
void Player::endAccel()
{
    m_fFireDelta = 0.5f;
    m_fAccelTime = 0.0f;
    if(m_pPlayerListener)
        m_pPlayerListener->onEndAccel();
}

void Player::beginMulti()
{
    m_fMultiTime = 15.0f*(powf(1.1f, EncrytionUtility::getIntegerForKey("EffectTimeLevel", 1)));
    m_pMultiNode = Sprite::create("playermask2.png");
    if(m_pMultiNode == nullptr)
        CCLOGERROR("Load multi model playermask2.png failed!");
    m_pMultiNode->setCascadeOpacityEnabled(true);
    m_pMultiNode->setOpacity(0);
    addChild(m_pMultiNode);
    
    ScaleTo* scaleTo = ScaleTo::create(0.5f, 0.55f);
    FadeIn* fadeIn = FadeIn::create(0.5f);
    Spawn* spawn = Spawn::createWithTwoActions(scaleTo, fadeIn);
    m_pMultiNode->runAction(spawn);
    m_pMultiNode->setCameraMask((unsigned short)CameraFlag::USER1);
    
    if(m_pPlayerListener)
        m_pPlayerListener->onBeginMulti(m_fMultiTime);
}
void Player::endMulti()
{
    m_fMultiTime = 0.0f;
    if(m_pMultiNode)
    {
        m_pMultiNode->stopAllActions();
        ScaleTo* scaleTo = ScaleTo::create(0.5f, 1.0f);
        FadeOut* fadeOut = FadeOut::create(0.5f);
        Spawn* spawn = Spawn::createWithTwoActions(scaleTo, fadeOut);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Player::removeMulti,this));
        Sequence* sequence = Sequence::createWithTwoActions(spawn, callFunc);
        m_pMultiNode->runAction(sequence);
        
        if(m_pPlayerListener)
            m_pPlayerListener->onEndMulti();
    }
}
void Player::removeMulti()
{
    if(m_pMultiNode)
    {
        m_pMultiNode->removeFromParentAndCleanup(true);
        m_pMultiNode = nullptr;
    }
}
void Player::beginProtected()
{
    m_fProtectedTime = 10.0f*(powf(1.1f, EncrytionUtility::getIntegerForKey("EffectTimeLevel", 1)));
    m_pProtectedNode = Sprite::create("protected.png");
    if(m_pProtectedNode == nullptr)
        CCLOGERROR("Load multi model protected.png failed!");
    m_pProtectedNode->setCascadeOpacityEnabled(true);
    m_pProtectedNode->setOpacity(0);
    addChild(m_pProtectedNode);
    
    ScaleTo* scaleTo = ScaleTo::create(0.5f, 0.5f);
    FadeIn* fadeIn = FadeIn::create(0.5f);
    Spawn* spawn = Spawn::createWithTwoActions(scaleTo, fadeIn);
    m_pProtectedNode->runAction(spawn);
    m_pProtectedNode->setCameraMask((unsigned short)CameraFlag::USER1);
    
    if(m_pPlayerListener)
        m_pPlayerListener->onBeginProtected(m_fProtectedTime);
}
void Player::endProtected()
{
    m_fProtectedTime = 0.0f;
    if(m_pProtectedNode)
    {
        m_pProtectedNode->stopAllActions();
        ScaleTo* scaleTo = ScaleTo::create(0.5f, 1.0f);
        FadeOut* fadeOut = FadeOut::create(0.5f);
        Spawn* spawn = Spawn::createWithTwoActions(scaleTo, fadeOut);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Player::removeProtected,this));
        Sequence* sequence = Sequence::createWithTwoActions(spawn, callFunc);
        m_pProtectedNode->runAction(sequence);
        
        if(m_pPlayerListener)
            m_pPlayerListener->onEndProtected();
    }
}
void Player::removeProtected()
{
    if(m_pProtectedNode)
    {
        m_pProtectedNode->removeFromParentAndCleanup(true);
        m_pProtectedNode = nullptr;
    }
}

void Player::beginTime()
{
    ParticleSystemHelper::spawnExplosion(ET_EXPLOSION_FLARE, getPosition());
    m_fSlowTime = 8.0f*(powf(1.1f, EncrytionUtility::getIntegerForKey("EffectTimeLevel", 1)));
    ActorsManager::getInstance()->setEnemyActorPause(true);
    _scheduler->setTimeScale(0.3f);
    
    if(m_bScheduledFire)
    {
        unschedule(CC_SCHEDULE_SELECTOR(Player::fire));
        schedule(CC_SCHEDULE_SELECTOR(Player::fire), m_fFireDelta*_scheduler->getTimeScale(), -1, 0);
        m_bScheduledFire = true;
    }
    SimpleAudioEngine::getInstance()->playEffect("Pickup_Speed02.wav");
    if(m_pPlayerListener)
        m_pPlayerListener->onBeginTime(m_fSlowTime);
}
void Player::endTime()
{
    m_fSlowTime = 0.0f;
    ActorsManager::getInstance()->setEnemyActorPause(false);
    _scheduler->setTimeScale(1.0f);
    if(m_bScheduledFire)
    {
        unschedule(CC_SCHEDULE_SELECTOR(Player::fire));
        schedule(CC_SCHEDULE_SELECTOR(Player::fire), m_fFireDelta*_scheduler->getTimeScale(), -1, 0);
        m_bScheduledFire = true;
    }
    SimpleAudioEngine::getInstance()->playEffect("Pickup_Speed03.wav");
    if(m_pPlayerListener)
        m_pPlayerListener->onEndTime();
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
        schedule(CC_SCHEDULE_SELECTOR(Player::fire), m_fFireDelta*_scheduler->getTimeScale(), -1, 0);
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

Vec2 Player::getFireWorldPos(const Vec2& orient)
{
    Vec2 ret = getPosition();
    ret += orient*m_fRadius*0.8f;
    return ret;
}
Vec2 Player::getFireLocalPos(const Vec2& orient)
{
    return orient*m_fRadius*0.8f;
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
                if(m_pMultiNode)
                {
                    Vec2 orient = getOrientation();
                    ActorsManager::spawnBullet(GameActor::AT_PLAYER_BULLET, getFireWorldPos(orient), orient,m_fMaxSpeed*2.0f,"bullet1.png", Color3B(174,250,27), 0.5f, 2.0f);
                    ParticleSystemHelper::spawnActorWidget(ActorWidgetType::AWT_FIRE_FLARE_MULTI, getFireLocalPos(orient), this);
                    orient.rotate(Vec2::ZERO, M_PI*0.125f);
                    ActorsManager::spawnBullet(GameActor::AT_PLAYER_BULLET, getFireWorldPos(orient), orient,m_fMaxSpeed*2.0f,"bullet1.png", Color3B(174,250,27), 0.5f, 2.0f);
                    ParticleSystemHelper::spawnActorWidget(ActorWidgetType::AWT_FIRE_FLARE_MULTI, getFireLocalPos(orient), this);
                    orient.rotate(Vec2::ZERO, -M_PI*0.25f);
                    ActorsManager::spawnBullet(GameActor::AT_PLAYER_BULLET, getFireWorldPos(orient), orient,m_fMaxSpeed*2.0f,"bullet1.png", Color3B(174,250,27), 0.5f, 2.0f);
                    ParticleSystemHelper::spawnActorWidget(ActorWidgetType::AWT_FIRE_FLARE_MULTI, getFireLocalPos(orient), this);
                    SimpleAudioEngine::getInstance()->playEffect("LaserRifle_Shot06.wav");
                }
                else
                {
                    ActorsManager::spawnBullet(GameActor::AT_PLAYER_BULLET, getFireWorldPos(m_Orientation), m_Orientation,m_fMaxSpeed*2.0f,"bullet1.png", Color3B(254,148,236), 0.5f, 2.0f);
                    ParticleSystemHelper::spawnActorWidget(ActorWidgetType::AWT_FIRE_FLARE, getFireLocalPos(m_Orientation), this);
                    SimpleAudioEngine::getInstance()->playEffect("LaserRifle_Shot04.wav");
                }
            }
            break;
            
        default:
            break;
    }
}

void Player::onEnterDead()
{
    ParticleSystemHelper::spawnExplosion(ExplosionType::ET_EXPLOSION_PLAYER, getPosition());
    setOpacity(0);
    if(m_pLeftTail)
    {
        m_pLeftTail->removeFromParentAndCleanup(true);
        m_pLeftTail = nullptr;
    }
    if(m_pRightTail)
    {
        m_pRightTail->removeFromParentAndCleanup(true);
        m_pRightTail = nullptr;
    }
    removeMulti();
    removeProtected();
    removeBuffer(BT_TIME);
    SimpleAudioEngine::getInstance()->playEffect("explodeEffect2.wav");
    GameController::getInstance()->setGameState(GameState::GS_PAUSE);
}
void Player::onExitDead()
{
}