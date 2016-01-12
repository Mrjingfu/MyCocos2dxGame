//
//  PlayerFireBallBullet.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 16/1/11.
//
//

#include "PlayerFireBallBullet.hpp"
#include "LevelResourceManager.h"
#include "VoxelExplorer.h"
USING_NS_CC;
PlayerFireBallBullet* PlayerFireBallBullet::create(Player* pOwner, Actor* pTarget)
{
    auto bullet = new (std::nothrow) PlayerFireBallBullet();
    if (bullet && bullet->init() && bullet->createParticleEffect())
    {
        bullet->m_pOwner = pOwner;
        bullet->m_pTarget = pTarget;
        bullet->m_Type = BaseBullet::BT_PLAYER_FIREBALL;
        bullet->setCameraMask((unsigned int)CameraFlag::USER1);
        
        Actor::ActorDir actorDir = pOwner->getActorDir();
        switch (actorDir) {
            case Actor::AD_FORWARD:
                bullet->m_DefaultDir = Vec3(0,0,-1);
                break;
            case Actor::AD_LEFT:
                bullet->m_DefaultDir = Vec3(-1,0,0);
                break;
            case Actor::AD_RIGHT:
                bullet->m_DefaultDir = Vec3(1,0,0);
                break;
            case Actor::AD_BACK:
                bullet->m_DefaultDir = Vec3(0,0,1);
                break;
            default:
                break;
        }
        
        bullet->autorelease();
        return bullet;
    }
    CC_SAFE_DELETE(bullet);
    return nullptr;
}
PlayerFireBallBullet::PlayerFireBallBullet()
{
    m_pTarget = nullptr;
    m_fLifeTime = 1.0f;
}
PlayerFireBallBullet::~PlayerFireBallBullet()
{
}
bool PlayerFireBallBullet::createParticleEffect()
{
    std::string resBullet = LevelResourceManager::getInstance()->getParticles3DRes(P3D_EFFECT_NAMES[P3D_BOSS_BULLET02]);
    m_pEffect = PUParticleSystem3D::create(resBullet);
    if(!m_pEffect)
        return false;
    m_pEffect->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(m_pEffect);
    
    std::string resBulletExplosion = LevelResourceManager::getInstance()->getParticles3DRes(P3D_EFFECT_NAMES[P3D_BOSS_BULLET02_EXPLOSION]);
    m_pExplosionEffect = PUParticleSystem3D::create(resBulletExplosion);
    if(!m_pExplosionEffect)
        return false;
    m_pExplosionEffect->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(m_pExplosionEffect);
    
    return true;
}
void PlayerFireBallBullet::update(float delta)
{
    if(m_State == BS_NORMAL)
    {
        if (m_pTarget) {
            Vec3 targetPos = m_pTarget->getPosition3D() + Vec3(0, TerrainTile::CONTENT_SCALE*0.3f, 0);
            Vec3 currentPos = getPosition3D();
            Vec3 dir = targetPos - getPosition3D();
            if(dir.length() <= 1)
            {
                setBulletState(BS_DISAPPEAR);
            }
            else
            {
                dir.normalize();
                currentPos = currentPos + dir*delta*80;
                setPosition3D(currentPos);
            }
        }
        else
        {
            Vec3 currentPos = getPosition3D();
            currentPos = currentPos + m_DefaultDir*delta*80;
            setPosition3D(currentPos);
            m_fLifeTime = m_fLifeTime - delta;
            if(m_fLifeTime<=0)
            {
                setBulletState(BS_DISAPPEAR);
                m_fLifeTime = 0;
            }
        }
    }
}
void PlayerFireBallBullet::onEnterDisappear()
{
    if(m_pEffect)
        m_pEffect->stopParticleSystem();
    Player* player = dynamic_cast<Player*>(m_pOwner);
    if(m_pTarget && player)
    {
        if(m_pExplosionEffect)
            m_pExplosionEffect->startParticleSystem();
        Vec2 playerPos = player->getPosInMap();
        BaseBoss* targetBoss = dynamic_cast<BaseBoss*>(m_pTarget);
        if(targetBoss)
            targetBoss->attackedByPlayer(false);
        else
        {
            BaseMonster* targetMonster = dynamic_cast<BaseMonster*>(m_pTarget);
            if(targetMonster)
                targetMonster->attackedByPlayer(false);
        }
    }
    DelayTime* delayTime = DelayTime::create(1.5f);
    CallFunc* callback = CallFunc::create(CC_CALLBACK_0(BaseBullet::destroySelf,this));
    Sequence* sequence = Sequence::create(delayTime, callback, nullptr);
    this->runAction(sequence);
}