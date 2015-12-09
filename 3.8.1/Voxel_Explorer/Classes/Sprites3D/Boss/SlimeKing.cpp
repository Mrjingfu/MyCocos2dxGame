//
//  SlimeKing.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/22.
//
//

#include "SlimeKing.hpp"
#include "LevelResourceManager.h"
#include "OutlineEffect3D.h"
#include "VoxelExplorer.h"
#include "SewerBossLevel.hpp"
USING_NS_CC;

SlimeKing* SlimeKing::create(BaseBoss::BossType type)
{
    std::string model = LevelResourceManager::getInstance()->getMonsterModelRes(BOSS_MODEL_NAMES[type]);
    auto boss = new (std::nothrow) SlimeKing();
    if (boss && boss->initWithFile(model) && boss->createFakeShadow())
    {
        boss->m_Type = type;
        boss->setCameraMask((unsigned int)CameraFlag::USER1);
        boss->setLightMask((unsigned int)LightFlag::LIGHT0);
        boss->autorelease();
        return boss;
    }
    CC_SAFE_DELETE(boss);
    return nullptr;
}
SlimeKing::SlimeKing()
{
    m_Type = BT_SLIMEKING;
    
    m_nFOV = 7;
}
SlimeKing::~SlimeKing()
{
}
void SlimeKing::onEnterSkill1()
{
    SewerBossLevel* level = dynamic_cast<SewerBossLevel*>(VoxelExplorer::getInstance()->getCurrentLevel());
    if(level)
    {
        level->createSummoningMonstersBySlimeKing(getPosInMap(), 1);
    }
}
void SlimeKing::onEnterSkill2()
{
    SewerBossLevel* level = dynamic_cast<SewerBossLevel*>(VoxelExplorer::getInstance()->getCurrentLevel());
    if(level)
    {
        level->createSummoningMonstersBySlimeKing(getPosInMap(), 2);
    }

}
void SlimeKing::onEnterSkill3()
{
    SewerBossLevel* level = dynamic_cast<SewerBossLevel*>(VoxelExplorer::getInstance()->getCurrentLevel());
    if(level)
    {
        level->createSummoningMonstersBySlimeKing(getPosInMap(), 3);
    }

}