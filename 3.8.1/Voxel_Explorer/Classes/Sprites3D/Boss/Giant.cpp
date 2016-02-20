//
//  Giant.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/22.
//
//

#include "Giant.hpp"
#include "LevelResourceManager.h"
#include "OutlineEffect3D.h"
#include "VoxelExplorer.h"
#include "CaveBossLevel.hpp"
#include "FakeShadow.hpp"
#include "UtilityHelper.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

Giant* Giant::create(BaseBoss::BossType type)
{
    std::string model = LevelResourceManager::getInstance()->getMonsterModelRes(BOSS_MODEL_NAMES[type]);
    auto boss = new (std::nothrow) Giant();
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
Giant::Giant()
{
    m_Type = BT_GIANT;
    
    m_nFOV = 9;
    
    m_fSkill1Timer = 10.0f;
    m_bInSkill1Stage = false;
    
    m_fSkill2Timer = 15.0f;
    m_bInSkill2Stage = false;
}
Giant::~Giant()
{
}
void Giant::update(float delta)
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
            CaveBossLevel* level = dynamic_cast<CaveBossLevel*>(VoxelExplorer::getInstance()->getCurrentLevel());
            if(level)
            {
                if(level->createTrapsByGiant(getPosInMap(), 1))
                {
                    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_BOSS_SKILL1, this);
                }
            }
            m_fSkill1Timer = 10.0f;
        }
    }
    if(m_bInSkill2Stage)
    {
        m_fSkill2Timer -= delta;
        if(m_fSkill2Timer <= 0)
        {
            CaveBossLevel* level = dynamic_cast<CaveBossLevel*>(VoxelExplorer::getInstance()->getCurrentLevel());
            if(level)
            {
                if(level->createTrapsByGiant(getPosInMap(), 2))
                {
                    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_BOSS_SKILL2, this);
                }
            }
            m_fSkill2Timer = 10.0f;
        }
    }
    if(m_pFakeShadow)
        m_pFakeShadow->setPosition3D(Vec3(getPositionX(),-TerrainTile::CONTENT_SCALE*0.49f,getPositionZ()));
}
void Giant::onEnterSkill1()
{
    m_bInSkill1Stage = true;
    CaveBossLevel* level = dynamic_cast<CaveBossLevel*>(VoxelExplorer::getInstance()->getCurrentLevel());
    if(level)
    {
        level->createTrapsByGiant(getPosInMap(), 1);
    }
}
void Giant::onEnterSkill2()
{
    m_bInSkill1Stage = true;
    m_bInSkill2Stage = true;
    setCascadeColorEnabled(true);
    setColor(Color3B::YELLOW);
    CaveBossLevel* level = dynamic_cast<CaveBossLevel*>(VoxelExplorer::getInstance()->getCurrentLevel());
    if(level)
    {
        level->createTrapsByGiant(getPosInMap(), 2);
    }
    if(getEffectCount() > 0)
    {
        OutlineEffect3D* outline = dynamic_cast<OutlineEffect3D*>(getEffect(0));
        if(outline)
        {
            Vec3 color = Vec3(Color3B::ORANGE.r/255.0f, Color3B::ORANGE.g/255.0f, Color3B::ORANGE.b/255.0f);
            outline->setOutlineColor(color);
        }
    }
}
void Giant::onEnterSkill3()
{
    m_bInSkill1Stage = true;
    m_bInSkill2Stage = true;
    setCascadeColorEnabled(true);
    setColor(Color3B::ORANGE);
    
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
            Vec3 color = Vec3(Color3B::RED.r/255.0f, Color3B::RED.g/255.0f, Color3B::RED.b/255.0f);
            outline->setOutlineColor(color);
        }
    }
}
void Giant::onEnterDeath()
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
    
    CaveBossLevel* level = dynamic_cast<CaveBossLevel*>(VoxelExplorer::getInstance()->getCurrentLevel());
    if(level)
        level->clearBossRoom();
    
    std::string soundName = LevelResourceManager::getInstance()->getMonsterSoundEffectRes(BOSS_MODEL_NAMES[m_Type], "DEATH");
    SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
}
bool Giant::isPlayerInsideBossRoom()
{
    return VoxelExplorer::getInstance()->checkBossRoomDoorClosed();
}