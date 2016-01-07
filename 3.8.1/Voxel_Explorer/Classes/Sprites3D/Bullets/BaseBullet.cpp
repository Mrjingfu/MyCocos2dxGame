//
//  BaseBullet.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 16/1/3.
//
//

#include "BaseBullet.hpp"
#include "VoxelExplorer.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

BaseBullet::BaseBullet()
{
    m_Type = BT_UNKNOWN;
    m_pEffect = nullptr;
    m_pExplosionEffect = nullptr;
    m_State = BS_UNKNOWN;
    m_pOwner = nullptr;
}
BaseBullet::~BaseBullet()
{
}

void BaseBullet::onEnter()
{
    Node::onEnter();
    scheduleUpdate();
}
void BaseBullet::onExit()
{
    unscheduleUpdate();
    Node::onExit();
}
void BaseBullet::update(float delta)
{
    if(m_State == BS_NORMAL)
    {
        Vec3 targetPos = VoxelExplorer::getInstance()->getPlayer()->getPosition3D() + Vec3(0, TerrainTile::CONTENT_SCALE*0.3f, 0);
        Vec3 currentPos = getPosition3D();
        Vec3 dir = targetPos - getPosition3D();
        if(dir.length() <= 1)
        {
            setBulletState(BS_DISAPPEAR);
        }
        else
        {
            dir.normalize();
            currentPos = currentPos + dir*delta*40;
            setPosition3D(currentPos);
        }
    }
}

BaseBullet::BulletState BaseBullet::getBulletState() const
{
    return m_State;
}
void BaseBullet::setBulletState(BulletState state)
{
    if(m_State == state)
        return;
    
    ///处理上一个状态退出逻辑
    switch (m_State) {
        case BaseBullet::BS_NORMAL:
            onExitNormal();
            break;
        case BaseBullet::BS_DISAPPEAR:
            onExitDisappear();
            break;
        default:
            break;
    }
    m_State = state;
    ///处理下一个状态进入逻辑
    switch (m_State) {
        case BaseBullet::BS_NORMAL:
            onEnterNormal();
            break;
        case BaseBullet::BS_DISAPPEAR:
            onEnterDisappear();
            break;
        default:
            break;
    }
}
void BaseBullet::onEnterNormal()
{
    if(m_pEffect)
        m_pEffect->startParticleSystem();
}
void BaseBullet::onExitNormal()
{
}
void BaseBullet::onEnterDisappear()
{
    if(m_pEffect)
        m_pEffect->stopParticleSystem();
    if(m_pExplosionEffect)
        m_pExplosionEffect->startParticleSystem();
    if(m_pOwner)
    {
        Vec2 playerPos = VoxelExplorer::getInstance()->getPlayer()->getPosInMap();
        VoxelExplorer::getInstance()->handlePlayerHurtByBoss(playerPos, m_pOwner);
    }
    DelayTime* delayTime = DelayTime::create(1.5f);
    CallFunc* callback = CallFunc::create(CC_CALLBACK_0(BaseBullet::destroySelf,this));
    Sequence* sequence = Sequence::create(delayTime, callback, nullptr);
    this->runAction(sequence);
}
void BaseBullet::onExitDisappear()
{
}
void BaseBullet::destroySelf()
{
    this->removeFromParentAndCleanup(true);
}