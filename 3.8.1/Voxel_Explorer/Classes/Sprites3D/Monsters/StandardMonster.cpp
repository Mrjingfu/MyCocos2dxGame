//
//  StandardMonster.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/22.
//
//

#include "StandardMonster.hpp"
#include "LevelResourceManager.h"
#include "OutlineEffect3D.h"
#include "UtilityHelper.h"
USING_NS_CC;

StandardMonster* StandardMonster::create(BaseMonster::MonsterType type, bool elite)
{
    std::string model = LevelResourceManager::getInstance()->getMonsterModelRes(MONSTER_MODEL_NAMES[type]);
    auto monster = new (std::nothrow) StandardMonster();
    if (monster && monster->initWithFile(model) && monster->createFakeShadow())
    {
        if(elite)
        {
            monster->m_pMonsterProperty->setElite(elite);
            monster->m_pMonsterProperty->adjustByDC();
        }
        monster->m_Type = type;
        monster->setCameraMask((unsigned int)CameraFlag::USER1);
        monster->setLightMask((unsigned int)LightFlag::LIGHT0);
        monster->setActorDir(cocos2d::random(AD_FORWARD, AD_BACK));
        
        switch (monster->m_Type) {
            case MT_RAT:
                monster->setScale(0.8f);
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
                break;
                
            case MT_ALLIP:
                monster->setOpacity(100);
                break;
            case MT_PRISONER:
            case MT_PRISONGUARD:
            case MT_TORTURE:
            case MT_MOB:
                break;
                
            case MT_GATEKEEPER:
                break;
            case MT_BELIEVER:
            case MT_APOLOGIST:
            case MT_ADJUDICATOR:
            case MT_PRIEST:
                monster->setScale(0.9f);
                break;
                
            case MT_DEATHMINER:
            case MT_KOBOLD:
                break;
            case MT_OOZE:
            case MT_SHADOW:
            case MT_ANKHEG:
                monster->setScale(0.8f);
                monster->m_bJumpMove = false;
                break;
                
            case MT_WOLF:
            case MT_BEAR:
            case MT_GNOLL:
                monster->setScale(0.8f);
                break;
            case MT_GOBLIN:
                monster->setScale(0.5f);
                break;
            case MT_DINOSAUR:
                monster->setScale(0.9f);
                break;
                
            case MT_SKELETON:
            case MT_ZOMBIE:
            case MT_GHOUL:
                monster->setScale(0.8f);
                break;
            case MT_GARGOYLE:
                monster->setPositionY(TerrainTile::CONTENT_SCALE*0.25f);
                monster->m_bJumpMove = false;
                break;
            case MT_GHOST:
                monster->m_bJumpMove = false;
                break;
            default:
                break;
        }
        if(monster->m_pMonsterProperty && monster->m_pMonsterProperty->isElite())
        {
            monster->setScale(monster->getScale() + 0.2f);
            
            OutlineEffect3D* outline = OutlineEffect3D::create();
            Color3B outlineColor = UtilityHelper::randomColor();
            outline->setOutlineColor(Vec3(outlineColor.r/255.0f, outlineColor.g/255.0f, outlineColor.b/255.0f));
            outline->setOutlineWidth(0.03f);
            monster->addEffect(outline, 1);
        }
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