//
//  SkeletonKing.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/22.
//
//

#include "SkeletonKing.hpp"
#include "LevelResourceManager.h"
#include "OutlineEffect3D.h"
#include "VoxelExplorer.h"
#include "TombBossLevel.hpp"
#include "FakeShadow.hpp"
#include "UtilityHelper.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

SkeletonKing* SkeletonKing::create(BaseBoss::BossType type)
{
    std::string model = LevelResourceManager::getInstance()->getMonsterModelRes(BOSS_MODEL_NAMES[type]);
    auto boss = new (std::nothrow) SkeletonKing();
    if (boss && boss->initWithFile(model) && boss->createFakeShadow())
    {
        boss->m_Type = type;
        boss->setCameraMask((unsigned int)CameraFlag::USER1);
        boss->setLightMask((unsigned int)LightFlag::LIGHT0 |(unsigned int)LightFlag::LIGHT1|(unsigned int)LightFlag::LIGHT2);
        
        OutlineEffect3D* outline = OutlineEffect3D::create();
        outline->setOutlineColor(Vec3(1.0f, 1.0f, 1.0f));
        outline->setOutlineWidth(0.03f);
        boss->addEffect(outline, 1);
        
        boss->autorelease();
        return boss;
    }
    CC_SAFE_DELETE(boss);
    return nullptr;
}
SkeletonKing::SkeletonKing()
{
    m_Type = BT_SKELETONKING;
    
    m_nFOV = 15;
    
    m_fSkill1Timer = 20.0f;
    m_bInSkill1Stage = false;
    
    m_fSkill3Timer = 10.0f;
    m_bInSkill3Stage = false;
}
SkeletonKing::~SkeletonKing()
{
}
void SkeletonKing::onEnter()
{
    BaseBoss::onEnter();
    if(m_pBossProperty)
        m_pBossProperty->addAttackAddBuffer(PlayerBuffer::PB_FIRE);
}
void SkeletonKing::update(float delta)
{
    if(!isVisible())
        return;
    if(VoxelExplorer::getInstance()->isPlayerDeath() && m_State != BS_SLEEPING)
    {
        setState(BS_SLEEPING);
        return;
    }
    switch (m_State) {
        case BS_SLEEPING:
            {
                if(isPlayerInsideBossRoom() && VoxelExplorer::getInstance()->checkBossAlert(this))
                    setState(BS_TRACKING);
            }
            break;
        case BS_WANDERING:
            {
                setState(BS_MOVING);
            }
            break;
        case BS_TRACKING:
            {
                m_fFirstTrackingTimer -= delta;
                if(m_fFirstTrackingTimer < 0)
                {
                    if(VoxelExplorer::getInstance()->checkBossCanAttack(this))
                        setState(BS_ATTACK);
                    else
                        setState(BS_MOVING);
                }
            }
            break;
        case BS_FLEEING:
            {
                if(VoxelExplorer::getInstance()->checkBossFleeFromPlayer(this))
                    setState(BS_MOVING);
                else if (VoxelExplorer::getInstance()->checkBossCanAttack(this))
                    setState(BS_ATTACK);
                else
                    setState(BS_TRACKING);
            }
            break;
        default:
            break;
    }
    if(m_bInSkill1Stage)
    {
        m_fSkill1Timer -= delta;
        if(m_fSkill1Timer <= 0)
        {
            TombBossLevel* level = dynamic_cast<TombBossLevel*>(VoxelExplorer::getInstance()->getCurrentLevel());
            if(level)
            {
                if(level->createSummoningMonstersBySkeletonKing(getPosInMap(), 1))
                {
                    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_BOSS_SKILL1, this);
                }
            }
            m_fSkill1Timer = 20.0f;
        }
    }
    
    if(m_bInSkill3Stage)
    {
        m_fSkill3Timer -= delta;
        if(m_fSkill3Timer <= 0)
        {
            TombBossLevel* level = dynamic_cast<TombBossLevel*>(VoxelExplorer::getInstance()->getCurrentLevel());
            if(level)
            {
                Vec2 transPos = level->getRandomPassableTileInBossRoom();
                removeTerrainTileFlag(TileInfo::ATTACKABLE);
                addTerrainTileFlagByPos(TileInfo::ATTACKABLE, transPos);
                Vec3 pos = Vec3(transPos.x*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -transPos.y*TerrainTile::CONTENT_SCALE);
                EaseSineOut* fadeOut = EaseSineOut::create(FadeOut::create(0.5f));
                CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(SkeletonKing::setPosition3D,this, pos));
                EaseSineOut* fadeIn = EaseSineOut::create(FadeIn::create(0.5f));
                CallFunc* callBack2 = CallFunc::create(CC_CALLBACK_0(SkeletonKing::onLand,this, true));
                Sequence* sequence = Sequence::create(fadeOut, callBack, fadeIn, callBack2, nullptr);
                runAction(sequence);
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_BOSS_SKILL3, this);
            }
            m_fSkill3Timer = 10.0f;
        }
    }

    if(m_pFakeShadow)
        m_pFakeShadow->setPosition3D(Vec3(getPositionX(),-TerrainTile::CONTENT_SCALE*0.49f,getPositionZ()));
}

void SkeletonKing::onEnterSkill1()
{
    m_bInSkill1Stage = true;
    TombBossLevel* level = dynamic_cast<TombBossLevel*>(VoxelExplorer::getInstance()->getCurrentLevel());
    if(level)
    {
        level->createSummoningMonstersBySkeletonKing(getPosInMap(), 1);
    }
    onLand(true);
}
void SkeletonKing::onEnterSkill2()
{
    m_bInSkill1Stage = true;
    setCascadeColorEnabled(true);
    setColor(Color3B::YELLOW);
    
    Vec3 oriScale = Vec3(getScaleX(), getScaleY(), getScaleZ());
    EaseSineOut* scaleTo = EaseSineOut::create(ScaleTo::create(0.5f, oriScale.x*1.2f, oriScale.y*1.2f, oriScale.z*1.2f));
    this->runAction(scaleTo);
    
    if(m_pBossProperty)
        m_pBossProperty->setFactor(1.5f);
    
    if(getEffectCount() > 0)
    {
        OutlineEffect3D* outline = dynamic_cast<OutlineEffect3D*>(getEffect(0));
        if(outline)
        {
            Vec3 color = Vec3(Color3B::ORANGE.r/255.0f, Color3B::ORANGE.g/255.0f, Color3B::ORANGE.b/255.0f);
            outline->setOutlineColor(color);
        }
    }
    onLand(true);
}
void SkeletonKing::onEnterSkill3()
{
    m_bInSkill1Stage = true;
    m_bInSkill3Stage = true;
    setCascadeColorEnabled(true);
    setColor(Color3B::ORANGE);
    
    TombBossLevel* level = dynamic_cast<TombBossLevel*>(VoxelExplorer::getInstance()->getCurrentLevel());
    if(level)
    {
        Vec2 transPos = level->getRandomPassableTileInBossRoom();
        removeTerrainTileFlag(TileInfo::ATTACKABLE);
        addTerrainTileFlagByPos(TileInfo::ATTACKABLE, transPos);
        Vec3 pos = Vec3(transPos.x*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -transPos.y*TerrainTile::CONTENT_SCALE);
        EaseSineOut* fadeOut = EaseSineOut::create(FadeOut::create(0.5f));
        CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(SkeletonKing::setPosition3D,this, pos));
        EaseSineOut* fadeIn = EaseSineOut::create(FadeIn::create(0.5f));
        CallFunc* callBack2 = CallFunc::create(CC_CALLBACK_0(SkeletonKing::onLand,this, true));
        Sequence* sequence = Sequence::create(fadeOut, callBack, fadeIn, callBack2, nullptr);
        runAction(sequence);
    }
    
    if(getEffectCount() > 0)
    {
        OutlineEffect3D* outline = dynamic_cast<OutlineEffect3D*>(getEffect(0));
        if(outline)
        {
            Vec3 color = Vec3(Color3B::RED.r/255.0f, Color3B::RED.g/255.0f, Color3B::RED.b/255.0f);
            outline->setOutlineColor(color);
        }
    }
}
void SkeletonKing::onEnterDeath()
{
    setScale(1.0f);
    if(m_pBossProperty)
        m_pBossProperty->setFactor(1.0f);
    if(getEffectCount() > 0)
    {
        OutlineEffect3D* outline = dynamic_cast<OutlineEffect3D*>(getEffect(0));
        if(outline)
        {
            Color3B outlineColor = UtilityHelper::randomColor();
            outline->setOutlineColor(Vec3(outlineColor.r/255.0f, outlineColor.g/255.0f, outlineColor.b/255.0f));
        }
    }
    this->stopAllActions();
    removeTerrainTileFlag(TileInfo::ATTACKABLE);
    removeTerrainTileFlagByPos(TileInfo::ATTACKABLE, m_NextPos);
    this->setVisible(false);
    if(m_pFakeShadow)
        m_pFakeShadow->setVisible(false);
    VoxelExplorer::getInstance()->addParticle3DEffect(getPosition3D(), P3D_EFFECT_TYPE::P3D_PLAYER_DEATH);
    VoxelExplorer::getInstance()->generatePickItemByBoss(getPosInMap(), (int)m_pBossProperty->getValueCopper().GetLongValue());
    
    TombBossLevel* level = dynamic_cast<TombBossLevel*>(VoxelExplorer::getInstance()->getCurrentLevel());
    if(level)
        level->clearBossRoom();
    
    std::string soundName = LevelResourceManager::getInstance()->getMonsterSoundEffectRes(BOSS_MODEL_NAMES[m_Type], "DEATH");
    SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
}

bool SkeletonKing::isPlayerInsideBossRoom()
{
    return VoxelExplorer::getInstance()->checkBossRoomDoorClosed();
}