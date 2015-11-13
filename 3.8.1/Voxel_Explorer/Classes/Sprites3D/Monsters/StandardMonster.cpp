//
//  StandardMonster.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/22.
//
//

#include "StandardMonster.hpp"
#include "LevelResourceManager.h"
USING_NS_CC;

StandardMonster* StandardMonster::create(BaseMonster::MonsterType type)
{
    std::string model = LevelResourceManager::getInstance()->getMonsterRes(MONSTER_MODEL_NAMES[type]);
    auto monster = new (std::nothrow) StandardMonster();
    if (monster && monster->initWithFile(model))
    {
        monster->m_Type = type;
        monster->setCameraMask((unsigned int)CameraFlag::USER1);
        monster->setLightMask((unsigned int)LightFlag::LIGHT0);
        monster->setActorDir(cocos2d::random(AD_FORWARD, AD_BACK));
        
        switch (monster->m_Type) {
            case MT_RAT:
                monster->setScale(0.8f);
                monster->m_bJumpMove = true;
                break;
            case MT_BAT:
                monster->setScale(0.8f);
                monster->setPositionY(TerrainTile::CONTENT_SCALE*0.25f);
                monster->m_bJumpMove = false;
                break;
            case MT_SNAKE:
                monster->setScale(0.8f);
                monster->m_bJumpMove = false;
                break;
            case MT_SPIDER:
            case MT_SLIME:
                monster->setScale(0.5f);
                monster->m_bJumpMove = true;
                break;
            default:
                break;
        }
        if(monster->m_pMonsterProperty && monster->m_pMonsterProperty->isElite())
            monster->setScale(monster->getScale() + 0.2f);
        monster->autorelease();
        return monster;
    }
    CC_SAFE_DELETE(monster);
    return nullptr;
}

StandardMonster::StandardMonster()
{
}
StandardMonster::~StandardMonster()
{
}