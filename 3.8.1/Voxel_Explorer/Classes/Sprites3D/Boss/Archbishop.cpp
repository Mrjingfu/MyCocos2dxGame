//
//  Archbishop.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/22.
//
//

#include "Archbishop.hpp"
#include "LevelResourceManager.h"
#include "OutlineEffect3D.h"
USING_NS_CC;

Archbishop* Archbishop::create(BaseBoss::BossType type)
{
    std::string model = LevelResourceManager::getInstance()->getMonsterModelRes(BOSS_MODEL_NAMES[type]);
    auto boss = new (std::nothrow) Archbishop();
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
Archbishop::Archbishop()
{
    m_Type = BT_ARCHBISHOP;
}
Archbishop::~Archbishop()
{
}