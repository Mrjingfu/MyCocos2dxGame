//
//  KoboldLeader.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/12/5.
//
//

#include "KoboldLeader.hpp"
#include "LevelResourceManager.h"
#include "OutlineEffect3D.h"
USING_NS_CC;

KoboldLeader* KoboldLeader::create(BaseBoss::BossType type)
{
    std::string model = LevelResourceManager::getInstance()->getMonsterModelRes(BOSS_MODEL_NAMES[type]);
    auto boss = new (std::nothrow) KoboldLeader();
    if (boss && boss->initWithFile(model) && boss->createFakeShadow())
    {
        boss->m_Type = type;
        boss->setCameraMask((unsigned int)CameraFlag::USER1);
        boss->setLightMask((unsigned int)LightFlag::LIGHT0 |(unsigned int)LightFlag::LIGHT1|(unsigned int)LightFlag::LIGHT2);
        boss->autorelease();
        return boss;
    }
    CC_SAFE_DELETE(boss);
    return nullptr;
}
KoboldLeader::KoboldLeader()
{
    m_Type = BT_KOBOLDLEADER;
}
KoboldLeader::~KoboldLeader()
{
}