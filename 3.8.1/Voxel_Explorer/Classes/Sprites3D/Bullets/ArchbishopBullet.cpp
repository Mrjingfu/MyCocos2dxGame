//
//  ArchbishopBullet.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 16/1/3.
//
//

#include "ArchbishopBullet.hpp"
#include "LevelResourceManager.h"
#include "VoxelExplorer.h"
USING_NS_CC;
ArchbishopBullet* ArchbishopBullet::create(BaseBoss* pOwner)
{
    auto bullet = new (std::nothrow) ArchbishopBullet();
    if (bullet && bullet->init() && bullet->createParticleEffect())
    {
        bullet->m_pOwner = pOwner;
        bullet->m_Type = BaseBullet::BT_ARCHBISHOP;
        bullet->setCameraMask((unsigned int)CameraFlag::USER1);
        
        bullet->autorelease();
        return bullet;
    }
    CC_SAFE_DELETE(bullet);
    return nullptr;
}
ArchbishopBullet::ArchbishopBullet()
{
}
ArchbishopBullet::~ArchbishopBullet()
{
}
bool ArchbishopBullet::createParticleEffect()
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
void ArchbishopBullet::onEnterDisappear()
{
    if(m_pEffect)
        m_pEffect->stopParticleSystem();
    if(m_pExplosionEffect)
        m_pExplosionEffect->startParticleSystem();
    BaseBoss* boss = dynamic_cast<BaseBoss*>(m_pOwner);
    if(boss)
    {
        Vec2 playerPos = VoxelExplorer::getInstance()->getPlayer()->getPosInMap();
        VoxelExplorer::getInstance()->handlePlayerHurtByBoss(playerPos, boss);
    }
    DelayTime* delayTime = DelayTime::create(1.5f);
    CallFunc* callback = CallFunc::create(CC_CALLBACK_0(BaseBullet::destroySelf,this));
    Sequence* sequence = Sequence::create(delayTime, callback, nullptr);
    this->runAction(sequence);
}