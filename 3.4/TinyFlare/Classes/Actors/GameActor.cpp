//
//  GameActor.cpp
//  Geometry-Wars
//
//  Created by wang haibo on 15/2/5.
//
//

#include "GameActor.h"
#include "ParticleSystemHelper.h"
USING_NS_CC;

GameActor::GameActor()
{
    m_type = AT_UNKNOWN;
    m_pModel = nullptr;
    m_Orientation = Vec2::UNIT_Y;
    m_Direction = Vec2::ZERO;
    m_Velocity = Vec2::ZERO;
    m_fAccel = 20.0f;
    m_fRadius = 0.0f;
    m_fMaxSpeed = 1.0f;
    m_bBounce = false;
    m_curState   = ActorState::AS_UNKNOWN;
    m_nBufferType = BufferType::BT_NORMAL;
}
GameActor::~GameActor()
{
}
void GameActor::onEnter()
{
    Node::onEnter();
    scheduleUpdate();
}
void GameActor::onExit()
{
    unscheduleUpdate();
    Node::onExit();
}
void GameActor::loadModel(const std::string& texName)
{
    if(m_pModel)
    {
        removeChild(m_pModel);
        m_pModel = nullptr;
    }
    m_pModel = Sprite::create(texName);
    if(m_pModel == nullptr)
        CCLOGERROR("Load model %s failed!" , texName.c_str());
    m_pModel->setScale(0.5f);
    addChild(m_pModel);
    caculateRadius();
}
void GameActor::loadModel(const std::string& texName, const cocos2d::Rect& rect)
{
    if(m_pModel)
    {
        removeChild(m_pModel);
        m_pModel = nullptr;
    }
    m_pModel = Sprite::create(texName, rect);
    if(m_pModel == nullptr)
        CCLOGERROR("Load model %s failed!" , texName.c_str());
    m_pModel->setScale(0.5f);
    addChild(m_pModel);
    caculateRadius();
}
void GameActor::setBounce(bool bounce)
{
    m_bBounce = bounce;
    if(m_bBounce)
    {
        ParticleSystemHelper::spawnExplosion(ExplosionType::ET_EXPLOSION_ACTOR_COLLISION, getPosition());
    }
}
void GameActor::caculateRadius()
{
    if (m_pModel) {
        Rect rect = m_pModel->getBoundingBox();
        Vec2 min = Vec2(rect.getMaxX(), rect.getMaxY());
        Vec2 max = Vec2(rect.getMinX(), rect.getMinY());
        m_fRadius = max.distance(min) * 0.5f;
        float scaleX = getScaleX();
        float scaleY = getScaleY();
        if(scaleX == scaleY)
            m_fRadius *= getScale();
        else
            m_fRadius *= MAX(scaleX, scaleY);
    }
}
void GameActor::updateOrientation()
{
    float rotationZ = CC_RADIANS_TO_DEGREES(cocos2d::Vec2::angle(m_Orientation, cocos2d::Vec2::UNIT_Y));
    if (m_Orientation.x < 0)
        rotationZ = -rotationZ;
    setRotation(rotationZ);
}
void GameActor::setActorState(ActorState state)
{
    if (m_curState == state)
        return;
    if((m_nBufferType & BufferType::BT_PROTECTED) && (state == ActorState::AS_DEAD))
        return;
        
    ///处理上一个状态退出逻辑
    switch (m_curState) {
        case ActorState::AS_UNDERCONTROL:
            onExitUnderControl();
            break;
        case ActorState::AS_TRACK:
            onExitTrack();
            break;
        case ActorState::AS_IDLE:
            onExitIdle();
            break;
        case ActorState::AS_DEAD:
            onExitDead();
            break;
        case ActorState::AS_CHARGE:
            onExitCharge();
            break;
        case ActorState::AS_FLEE:
            onExitCharge();
            break;
        case ActorState::AS_BLINK:
            onExitBlink();
            break;
        default:
            break;
    }
    
    m_curState = state;
    ///处理下一个状态进入逻辑
    switch (m_curState) {
        case ActorState::AS_UNDERCONTROL:
            onEnterUnderControl();
            break;
        case ActorState::AS_TRACK:
            onEnterTrack();
            break;
        case ActorState::AS_IDLE:
            onEnterIdle();
            break;
        case ActorState::AS_DEAD:
            onEnterDead();
            break;
        case ActorState::AS_CHARGE:
            onEnterCharge();
            break;
        case ActorState::AS_FLEE:
            onEnterFlee();
            break;
        case ActorState::AS_BLINK:
            onEnterBlink();
            break;
        default:
            break;
    }

}
void GameActor::resumeScheduler(void)
{
    _scheduler->resumeTarget(this);
}
void GameActor::pauseScheduler(void)
{
    _scheduler->pauseTarget(this);
}