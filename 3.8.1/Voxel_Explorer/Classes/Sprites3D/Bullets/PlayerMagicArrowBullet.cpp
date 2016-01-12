//
//  PlayerMagicArrowBullet.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 16/1/12.
//
//

#include "PlayerMagicArrowBullet.hpp"
#include "LevelResourceManager.h"
#include "VoxelExplorer.h"
USING_NS_CC;
PlayerMagicArrowBullet* PlayerMagicArrowBullet::create(Player* pOwner, const cocos2d::Vec3& dir)
{
    auto bullet = new (std::nothrow) PlayerMagicArrowBullet();
    if (bullet && bullet->init() && bullet->createParticleEffect())
    {
        bullet->m_pOwner = pOwner;
        bullet->m_Type = BaseBullet::BT_PLAYER_MAGICARROW;
        bullet->setCameraMask((unsigned int)CameraFlag::USER1);
        bullet->m_DefaultDir = dir;
        bullet->autorelease();
        return bullet;
    }
    CC_SAFE_DELETE(bullet);
    return nullptr;
}
PlayerMagicArrowBullet::PlayerMagicArrowBullet()
{
    m_pRibbonTrail = nullptr;
    m_fLifeTime = 0.6f;
    m_bCollision = false;
}
PlayerMagicArrowBullet::~PlayerMagicArrowBullet()
{
}
bool PlayerMagicArrowBullet::createParticleEffect()
{
    std::string resBullet = LevelResourceManager::getInstance()->getParticles3DRes(P3D_EFFECT_NAMES[P3D_PLAYER_MAGICARROW]);
    m_pEffect = PUParticleSystem3D::create(resBullet);
    if(!m_pEffect)
        return false;
    m_pEffect->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(m_pEffect);
    
    std::string resBulletExplosion = LevelResourceManager::getInstance()->getParticles3DRes(P3D_EFFECT_NAMES[P3D_BOSS_BULLET01_EXPLOSION]);
    m_pExplosionEffect = PUParticleSystem3D::create(resBulletExplosion);
    if(!m_pExplosionEffect)
        return false;
    m_pExplosionEffect->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(m_pExplosionEffect);
    
    m_pRibbonTrail = RibbonTrail::create("ribbontrail.png", 1, 8);
    if(!m_pRibbonTrail)
        return false;
    m_pRibbonTrail->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(m_pRibbonTrail);
    return true;
}
void PlayerMagicArrowBullet::update(float delta)
{
    if(m_State == BS_NORMAL)
    {
        Vec3 currentPos = getPosition3D();
        currentPos = currentPos + m_DefaultDir*delta*150;
        setPosition3D(currentPos);
        m_fLifeTime = m_fLifeTime - delta;
        if(m_fLifeTime<=0)
        {
            setBulletState(BS_DISAPPEAR);
            m_fLifeTime = 0;
        }
        else if(VoxelExplorer::getInstance()->checkBulletCollideMonster(getPosition3D()))
        {
            m_bCollision = true;
            setBulletState(BS_DISAPPEAR);
            m_fLifeTime = 0;
        }
        m_pRibbonTrail->setPosition3D(currentPos);
        m_pRibbonTrail->update(delta);
    }
}
void PlayerMagicArrowBullet::onEnterDisappear()
{
    if(m_pEffect)
        m_pEffect->stopParticleSystem();
    if(m_pExplosionEffect && m_bCollision)
        m_pExplosionEffect->startParticleSystem();
    
    if(m_pRibbonTrail)
        m_pRibbonTrail->setVisible(false);
    DelayTime* delayTime = DelayTime::create(0.5f);
    CallFunc* callback = CallFunc::create(CC_CALLBACK_0(BaseBullet::destroySelf,this));
    Sequence* sequence = Sequence::create(delayTime, callback, nullptr);
    this->runAction(sequence);
}