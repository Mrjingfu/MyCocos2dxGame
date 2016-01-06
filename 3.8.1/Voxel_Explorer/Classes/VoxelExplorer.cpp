//
//  VoxelExplorer.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/9/24.
//
//

#include "VoxelExplorer.h"
#include "SewerLevel.hpp"
#include "SewerBossLevel.hpp"
#include "PrisonLevel.hpp"
#include "PrisonBossLevel.hpp"
#include "FaneLevel.hpp"
#include "FaneBossLevel.hpp"
#include "MineLevel.hpp"
#include "MineBossLevel.hpp"
#include "CaveLevel.hpp"
#include "CaveBossLevel.hpp"
#include "TombLevel.hpp"
#include "TombBossLevel.hpp"
#include "TerrainTile.hpp"
#include "BaseDoor.hpp"
#include "LevelResourceManager.h"
#include "RandomDungeon.hpp"
#include "PickableItem.hpp"
#include "UseableItem.hpp"
#include "PlayerProperty.hpp"
#include "Layer3D.hpp"
#include "BaseBoss.hpp"
#include "BaseMonster.hpp"
#include "GameFormula.hpp"
#include "Particle3D/CCParticleSystem3D.h"
#include "Particle3D/PU/CCPUParticleSystem3D.h"
#include "AlisaMethod.h"
#include "BasePortal.hpp"
#include "Npc.hpp"
#include "UtilityHelper.h"
#include "GameScene.h"
#include "FakeShadow.hpp"
#include "StandardMonster.hpp"
#include "NpcDataManager.hpp"
#include "RandomEventMgr.hpp"
#include "ScreenShake.hpp"
#include "StatisticsManager.hpp"
#include "SimpleAudioEngine.h"
#include "GameUILayer.h"
USING_NS_CC;
using namespace CocosDenshion;
const std::string P3D_EFFECT_NAMES[] = {
    "P3DN_PLAYER_DEATH",
    "P3DN_PLAYER_LEVELUP",
    "P3DN_PLAYER_USE_POTION_TAKE_EFFECT",
    "P3DN_SMALL_PORTAL",
    "P3DN_STANDARD_PORTAL",
    "P3DN_STRONGER_BUFFER",
    "P3DN_STEALTH_BUFFER",
    "P3DN_SPEEDUP_BUFFER",
    "P3DN_POISIONING_BUFFER",
    "P3DN_PARALYTIC_BUFFER",
    "P3DN_FROZEN_BUFFER",
    "P3DN_WEAK_BUFFER",
    "P3DN_FIRE_BUFFER",
    "P3DN_PLAYER_TELEPORT",
    "P3DN_BOSS_BULLET01",
    "P3DN_BOSS_BULLET01_EXPLOSION",
    "P3DN_BOSS_BULLET02",
    "P3DN_BOSS_BULLET02_EXPLOSION"
};
VoxelExplorer* g_pVoxelExplorerInstance = nullptr;
VoxelExplorer* VoxelExplorer::getInstance()
{
    if( g_pVoxelExplorerInstance == nullptr )
        g_pVoxelExplorerInstance = new VoxelExplorer();
    
    return g_pVoxelExplorerInstance;
}
VoxelExplorer::VoxelExplorer()
{
    m_pCurrentLevel = nullptr;
    
    m_pMainLayer = nullptr;
    m_p3DLayer  = nullptr;
    m_pShakeLayer = nullptr;
    m_pTerrainTilesLayer = nullptr;
    m_pFakeShadowLayer = nullptr;
    m_pTerrainPortalsLayer = nullptr;
    m_pTerrainDoorsLayer = nullptr;
    m_pUseableItemsLayer = nullptr;
    m_pBossLayer         = nullptr;
    m_pNPCsLayer         = nullptr;
    m_pMonstersLayer     = nullptr;
    m_pPickableItemsLayer= nullptr;
    m_pBulletsLayer      = nullptr;
    m_p2DLayer = nullptr;
    m_pHUDLayer = nullptr;
    m_pUILayer = nullptr;
    
    m_pMainCamera = nullptr;
    
    m_pPlayer = nullptr;
    m_bIsGamePause = false;
    m_bHasDownStairs = true;
}
VoxelExplorer::~VoxelExplorer()
{
}


bool VoxelExplorer::init(Layer* pMainLayer)
{
    if(pMainLayer == nullptr)
        return false;
    m_pMainLayer = pMainLayer;
    ValueMap playerData ;
    if(!LevelResourceManager::getInstance()->initLevelRes())
    {
        CCLOGERROR("load level resource failed!");
        return false;
    }
    if(!NpcDataManager::getInstance()->initNpcData())
    {
        CCLOGERROR("load npc data failed!");
        return false;
    }
    if(!createLayers())
    {
        CCLOGERROR("Create layers failed!");
        return false;
    }
    if(!createLights())
    {
        CCLOGERROR("Create lights failed!");
        return false;
    }
    if(!createCameras())
    {
        CCLOGERROR("Create cameras failed!");
        return false;
    }
    if(!createLevel())
    {
        CCLOGERROR("Create level failed!");
        return false;
    }
    if(!createPlayer())
    {
        CCLOGERROR("Create Player failed!");
        return false;
    }
    return true;
}
void VoxelExplorer::update(float delta)
{
    NpcDataManager::getInstance()->update(delta);
}

void VoxelExplorer::gamePause()
{
    if(m_p3DLayer)
    {
        m_bIsGamePause = true;
        m_p3DLayer->pause();
        StatisticsManager::getInstance()->pauseSchedu();
    }

}
void VoxelExplorer::gameResume()
{
    if(m_p3DLayer && m_bIsGamePause)
    {
        m_bIsGamePause = false;
       m_p3DLayer->resume();
        StatisticsManager::getInstance()->resumeSchedu();
    }

}

std::string VoxelExplorer::getScreenPickDesc(const cocos2d::Vec2& screenPos, std::string& strIcon, ValueMap& event, bool& isTraps, bool& isCanRemove, cocos2d::Vec2& checkpos)
{
    if(m_pMainCamera && m_p3DLayer)
    {
        cocos2d::Ray ray;
        UtilityHelper::getCameraToViewportRay(m_pMainCamera, m_p3DLayer->convertToNodeSpace(screenPos), &ray);
        
        if(m_pPlayer)
        {
            if (ray.intersects(m_pPlayer->getAABB())) {
                strIcon = m_pPlayer->getIconRes();
                return m_pPlayer->getDesc();
            }
        }
        
        
        if(m_pPickableItemsLayer)
        {
            for (auto child : m_pPickableItemsLayer->getChildren())
            {
                PickableItem* item = dynamic_cast<PickableItem*>(child);
                if (item && item->isVisible() && ray.intersects(item->getAABB())) {
                    return item->getDesc();
                }
            }
        }
        
        if(m_pMonstersLayer)
        {
            for (auto child : m_pMonstersLayer->getChildren())
            {
                BaseMonster* monster = dynamic_cast<BaseMonster*>(child);
                if (monster && monster->isVisible() && ray.intersects(monster->getAABB())) {
                    strIcon = monster->getIconRes();
                    return monster->getDesc();
                }
            }
        }
        if(m_pNPCsLayer)
        {
            for (auto child : m_pNPCsLayer->getChildren())
            {
                Npc* npc = dynamic_cast<Npc*>(child);
                if (npc && npc->isVisible() && ray.intersects(npc->getAABB())) {
                    strIcon = npc->getIconRes();
                    return npc->getDesc();
                }
            }
        }
        if(m_pBossLayer)
        {
            for (auto child : m_pBossLayer->getChildren()) {
                BaseBoss* boss = dynamic_cast<BaseBoss*>(child);
                if(boss && boss->isVisible() && ray.intersects(boss->getAABB())){
                    strIcon = boss->getIconRes();
                    return boss->getDesc();
                }
            }
        }
        if(m_pUseableItemsLayer)
        {
            for (auto child : m_pUseableItemsLayer->getChildren())
            {
                UseableItem* item = dynamic_cast<UseableItem*>(child);
                if (item && item->isVisible() && ray.intersects(item->getAABB())) {
                    return item->getDesc();
                }
            }
        }
        
        if(m_pTerrainPortalsLayer)
        {
            for (auto child : m_pTerrainPortalsLayer->getChildren())
            {
                BasePortal* portal = dynamic_cast<BasePortal*>(child);
                if (portal && portal->isVisible() && ray.intersects(portal->getAABB())) {
                    return portal->getDesc();
                }
            }
        }
        
        if(m_pTerrainDoorsLayer)
        {
            for (auto child : m_pTerrainDoorsLayer->getChildren())
            {
                BaseDoor* door = dynamic_cast<BaseDoor*>(child);
                if (door && door->isVisible() && ray.intersects(door->getAABB())) {
                    return door->getDesc();
                }
            }
        }
        
        if(m_pTerrainTilesLayer)
        {
            for (auto child : m_pTerrainTilesLayer->getChildren())
            {
                TerrainTile* tile = dynamic_cast<TerrainTile*>(child);
                if (tile && tile->isVisible() && ray.intersects(tile->getAABB())) {
                    
                    TerrainTile::TileType type = m_pCurrentLevel->getTerrainTileType(tile->getPosInMap().x, tile->getPosInMap().y);
                    if(type != TerrainTile::TT_STANDARD  && type != TerrainTile::TT_WALL)
                    {
                        Area::AREA_TYPE areaType = m_pCurrentLevel->getTerrainTileAreaType(tile->getPosInMap().x, tile->getPosInMap().y);
 

                        if(type == TerrainTile::TT_TOXIC_TRAP ||
                            type == TerrainTile::TT_FIRE_TRAP ||
                            type == TerrainTile::TT_PARALYTIC_TRAP ||
                            type == TerrainTile::TT_GRIPPING_TRAP ||
                            type == TerrainTile::TT_SUMMONING_TRAP ||
                            type == TerrainTile::TT_WEAK_TRAP)
                        {
                            isTraps = true;
                            isCanRemove = true;
                            checkpos = tile->getPosInMap();
                            if(areaType == Area::AT_ENTRANCE
                               || areaType == Area::AT_EXIT
                               || areaType == Area::AT_BOSS_EXIT
                               || areaType == Area::AT_BOSS_ROOM
                               || areaType >= Area::AT_SPECIAL_EQUIPMENT_SHOP)
                                isCanRemove = false;
                        }
                        m_pCurrentLevel->setTerrainTileSearched(tile->getPosInMap().x, tile->getPosInMap().y);
                        return tile->getDesc();
                    }
                    else
                    {
                        if(m_pCurrentLevel->isTerrainTileSearched(tile->getPosInMap().x, tile->getPosInMap().y))
                        {
                            m_pCurrentLevel->setTerrainTileSearched(tile->getPosInMap().x, tile->getPosInMap().y);
                            return tile->getDesc();
                        }
                        else
                        {
                            float percent1 = 0.1f;
                            float percent2 = 1.0f - percent1;
                            bool found = false;
                            AlisaMethod* am = AlisaMethod::create(percent1, percent2, -1.0, NULL);
                            if(am)
                            {
                                if(am->getRandomIndex() == 0)
                                    found = true;
                            }
                            if(found)
                            {
                                ValueMap* randEvent = RandomEventMgr::getInstance()->getRandomEvent();
                                if(randEvent->at("HAS_READED").asBool())
                                {
                                    m_pCurrentLevel->setTerrainTileSearched(tile->getPosInMap().x, tile->getPosInMap().y);
                                    return tile->getDesc();
                                }
                                else
                                {
                                    bool foundWall = (type == TerrainTile::TT_WALL);
                                    if(foundWall)
                                    {
                                        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_FOUND_HIDDEN_MSG);
                                        StatisticsManager::getInstance()->addHideInfoNum(StatisticsManager::eHideInfoType::HIT_MSG);
                                        std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("SECRET_FOUND");
                                        SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
                                        randEvent->at("HAS_READED") = true;
                                        m_pCurrentLevel->setTerrainTileSearched(tile->getPosInMap().x, tile->getPosInMap().y);
                                        event = *randEvent;
                                        return randEvent->at("EVENT_DESC").asString();
                                    }
                                    else
                                    {
                                        if(randEvent && randEvent->at("EVENT_TYPE").asInt() != (int)RANDOM_EVENT_TYPE::RET_WALL_STANDARD)
                                        {
                                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_FOUND_HIDDEN_MSG);
                                            StatisticsManager::getInstance()->addHideInfoNum(StatisticsManager::eHideInfoType::HIT_MSG);
                                            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("SECRET_FOUND");
                                            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
                                            randEvent->at("HAS_READED") = true;
                                            m_pCurrentLevel->setTerrainTileSearched(tile->getPosInMap().x, tile->getPosInMap().y);
                                            event = *randEvent;
                                            return randEvent->at("EVENT_DESC").asString();
                                        }
                                        else
                                        {
                                            m_pCurrentLevel->setTerrainTileSearched(tile->getPosInMap().x, tile->getPosInMap().y);
                                            return tile->getDesc();
                                        }
                                    }
                                }
                            }
                            else
                            {
                                m_pCurrentLevel->setTerrainTileSearched(tile->getPosInMap().x, tile->getPosInMap().y);
                                return tile->getDesc();
                            }
                        }
                    }
                }
            }
        }
    }
    return UtilityHelper::getLocalString(TERRAIN_TILES_NAME[TerrainTile::TT_CHASM]);
}
bool VoxelExplorer::checkMovable(TileInfo& info)
{
    if(!m_pCurrentLevel || !m_pPlayer)
        return false;
    return m_pCurrentLevel->checkMovable(m_pPlayer, info);
}
void VoxelExplorer::cameraTrackPlayer()
{
    if(m_pPlayer && m_pMainCamera)
    {
        Vec3 camPos = m_pPlayer->getPosition3D() + Vec3(0, 5*TerrainTile::CONTENT_SCALE, 4*TerrainTile::CONTENT_SCALE );
        Vec3 targetLookAt = m_pPlayer->getPosition3D() + Vec3(0,0.5f*TerrainTile::CONTENT_SCALE,0);
        EaseSineOut* moveTo = EaseSineOut::create(MoveTo::create(0.4f, camPos));
        m_pMainCamera->runAction(moveTo);
    }
}
void VoxelExplorer::checkPickItem()
{
    if(!m_pCurrentLevel || !m_pPlayer)
        return;
    int flag = m_pCurrentLevel->getTerrainTileFlag(m_pPlayer->getPosInMap().x, m_pPlayer->getPosInMap().y);
    if(flag & TileInfo::PICKABLE)
        handlePickItem(m_pPlayer->getPosInMap());
}
void VoxelExplorer::checkUpdateFogOfWar()
{
    if(!m_pCurrentLevel || !m_pPlayer)
        return;
    m_pCurrentLevel->updateAreaFogOfWarByPos(m_pPlayer->getPosInMap());
    updateStatisticsAreaDatas();
}
void VoxelExplorer::checkTriggerTrap()
{
    if(!m_pCurrentLevel || !m_pPlayer)
        return;
    m_pCurrentLevel->updateTrapTileByPos(m_pPlayer->getPosInMap());
}
bool VoxelExplorer::checkMonsterAlert(BaseMonster* monster)
{
    if(monster == nullptr || !(monster->isVisible()))
        return false;
    if(m_pPlayer == nullptr || m_pPlayer->getState() == Player::PS_DEATH || m_pPlayer->isStealth())
        return false;
    Vec2 playerPosInMap = m_pPlayer->getPosInMap();
    Vec2 monsterPosInMap = monster->getPosInMap();
    if(std::abs(playerPosInMap.x - monsterPosInMap.x) > monster->getMonsterFOV() || std::abs(playerPosInMap.y - monsterPosInMap.y) > monster->getMonsterFOV())
        return false;
    return true;
}
bool VoxelExplorer::checkBossAlert(BaseBoss* boss)
{
    if(boss == nullptr || !(boss->isVisible()))
        return false;
    if(m_pPlayer == nullptr || m_pPlayer->getState() == Player::PS_DEATH || m_pPlayer->isStealth())
        return false;
    
    Vec2 playerPosInMap = m_pPlayer->getPosInMap();
    Vec2 bossPosInMap = boss->getPosInMap();
    if(std::abs(playerPosInMap.x - bossPosInMap.x) > boss->getMonsterFOV() || std::abs(playerPosInMap.y - bossPosInMap.y) > boss->getMonsterFOV())
        return false;
    
    return true;
}
bool VoxelExplorer::checkMonsterCanAttack(BaseMonster* monster)
{
    if(monster == nullptr || !(monster->isVisible()))
        return false;
    if(m_pPlayer == nullptr || m_pPlayer->getState() == Player::PS_DEATH || m_pPlayer->isStealth())
        return false;
    Vec2 playerPosInMap = m_pPlayer->getPosInMap();
    Vec2 monsterPosInMap = monster->getPosInMap();
    if(playerPosInMap.x == monsterPosInMap.x && std::abs(playerPosInMap.y - monsterPosInMap.y) <= monster->getAttackRange())
        return true;
    else if(playerPosInMap.y == monsterPosInMap.y && std::abs(playerPosInMap.x - monsterPosInMap.x) <= monster->getAttackRange())
        return true;
    return false;
}
bool VoxelExplorer::checkBossFleeFromPlayer(BaseBoss* boss)
{
    if(boss == nullptr || !(boss->isVisible()))
        return false;
    if(m_pPlayer == nullptr || m_pPlayer->getState() == Player::PS_DEATH || m_pPlayer->isStealth())
        return false;
    Vec2 playerPosInMap = m_pPlayer->getPosInMap();
    Vec2 bossPosInMap = boss->getPosInMap();

    if(std::abs(playerPosInMap.y - bossPosInMap.y) <= boss->getFleeRange() && std::abs(playerPosInMap.x - bossPosInMap.x) <= boss->getFleeRange())
        return true;
    return false;
}
bool VoxelExplorer::checkBossCanAttack(BaseBoss* boss)
{
    if(boss == nullptr || !(boss->isVisible()))
        return false;
    if(m_pPlayer == nullptr || m_pPlayer->getState() == Player::PS_DEATH || m_pPlayer->isStealth())
        return false;
    Vec2 playerPosInMap = m_pPlayer->getPosInMap();
    Vec2 bossPosInMap = boss->getPosInMap();
    if(std::abs(playerPosInMap.y - bossPosInMap.y) > boss->getAttackRange() || std::abs(playerPosInMap.x - bossPosInMap.x) > boss->getAttackRange())
        return false;
    return true;
}
bool VoxelExplorer::trackToPlayer(Actor* tracker, cocos2d::Vec2& nextPos)
{
    if(tracker == nullptr || m_pPlayer == nullptr || m_pCurrentLevel == nullptr || !(tracker->isVisible()))
       return false;
    Vec2 playerPosInMap = m_pPlayer->getPosInMap();
    Vec2 trackerPosInMap = tracker->getPosInMap();
    return m_pCurrentLevel->getNextPathStep(trackerPosInMap, playerPosInMap, nextPos);
}
bool VoxelExplorer::fleeFromPlayer(Actor* runaway, cocos2d::Vec2& nextPos)
{
    if(runaway == nullptr || runaway == nullptr || m_pCurrentLevel == nullptr || !(runaway->isVisible()))
        return false;
    Vec2 playerPosInMap = m_pPlayer->getPosInMap();
    Vec2 runawayPosInMap = runaway->getPosInMap();
    return m_pCurrentLevel->getBackPathStep(runawayPosInMap, playerPosInMap, nextPos);
}
bool VoxelExplorer::wanderingAround(Actor* wanderer, cocos2d::Vec2& nextPos)
{
    if(wanderer == nullptr  || m_pCurrentLevel == nullptr || !(wanderer->isVisible()))
        return false;
    Vec2 wandererPosInMap = wanderer->getPosInMap();
    Vec2 randomPosInMap = m_pCurrentLevel->getRandomPassableTile();
    return m_pCurrentLevel->getNextPathStep(wandererPosInMap, randomPosInMap, nextPos);
}
void VoxelExplorer::updateFogOfWar(const cocos2d::Rect& areaRect, bool visited)
{
    if(m_pTerrainTilesLayer)
    {
        for (const auto& child : m_pTerrainTilesLayer->getChildren())
        {
            TerrainTile* tile = dynamic_cast<TerrainTile*>(child);
            if(tile && areaRect.containsPoint(tile->getPosInMap()))
                tile->setVisited(visited);
        }
    }
    if(m_pFakeShadowLayer)
        for (const auto& child : m_pTerrainTilesLayer->getChildren())
        {
            FakeShadow* fakeShadow = dynamic_cast<FakeShadow*>(child);
            if(fakeShadow && areaRect.containsPoint(fakeShadow->getPosInMap()))
                fakeShadow->setVisited(visited);
        }
    if(m_pTerrainPortalsLayer)
    {
        for (const auto& child : m_pTerrainPortalsLayer->getChildren())
        {
            BasePortal* portal = dynamic_cast<BasePortal*>(child);
            if(portal && areaRect.containsPoint(portal->getPosInMap()))
                portal->setVisited(visited);
        }
    }
    if(m_pTerrainDoorsLayer)
    {
        for (const auto& child : m_pTerrainDoorsLayer->getChildren())
        {
            Actor* door = dynamic_cast<Actor*>(child);
            if(door && areaRect.containsPoint(door->getPosInMap()))
                door->setVisited(visited);
        }
    }
    
    if(m_pUseableItemsLayer)
    {
        for (const auto& child : m_pUseableItemsLayer->getChildren())
        {
            Actor* item = dynamic_cast<Actor*>(child);
            if(item && areaRect.containsPoint(item->getPosInMap()))
                item->setVisited(visited);
        }
    }
    
    if(m_pBossLayer)
    {
        for (const auto& child : m_pBossLayer->getChildren())
        {
            BaseBoss* boss = dynamic_cast<BaseBoss*>(child);
            if(boss && areaRect.containsPoint(boss->getPosInMap()) && boss->getState() != BaseBoss::BS_DEATH)
                boss->setVisited(visited);
        }
    }
    
    if(m_pNPCsLayer)
    {
        for (const auto& child : m_pNPCsLayer->getChildren())
        {
            Npc* npc = dynamic_cast<Npc*>(child);
            if(npc && areaRect.containsPoint(npc->getPosInMap()))
                npc->setVisited(visited);
        }
    }
    
    if(m_pMonstersLayer)
    {
        bool makeAlert = false;
        for (const auto& child : m_pMonstersLayer->getChildren())
        {
            BaseMonster* monster = dynamic_cast<BaseMonster*>(child);
            if(monster && areaRect.containsPoint(monster->getPosInMap()) && monster->getState() != BaseMonster::MS_DEATH)
            {
                if(monster->getState() == BaseMonster::MS_SLEEPING && !monster->isVisible())
                {
                    if(!makeAlert)
                    {
                        std::string soundName = LevelResourceManager::getInstance()->getMonsterSoundEffectRes(MONSTER_MODEL_NAMES[monster->getMonsterType()], "ALERT");
                        SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
                        makeAlert = true;
                    }
                }
                monster->setVisited(visited);
            }
        }
    }
    
    if(m_pPickableItemsLayer)
    {
        for (const auto& child : m_pPickableItemsLayer->getChildren())
        {
            Actor* item = dynamic_cast<Actor*>(child);
            if(item && areaRect.containsPoint(item->getPosInMap()))
                item->setVisited(visited);
        }
    }
}
void VoxelExplorer::updateMiniMap()
{
    if(m_pCurrentLevel && m_pCurrentLevel->hasShowMap())
        m_pCurrentLevel->showMap(true);
}
void VoxelExplorer::updateBossRoomDoor()
{
    if(m_pCurrentLevel && m_pPlayer && m_pTerrainDoorsLayer && m_pBossLayer && m_pBossLayer->getChildrenCount() > 0)
    {
        
        BaseBoss* boss = dynamic_cast<BaseBoss*>(m_pBossLayer->getChildren().at(0));
        if(!boss || boss->getState() == BaseBoss::BS_DEATH)
            return;
        
        for (const auto& child : m_pTerrainDoorsLayer->getChildren())
        {
            BaseDoor* door = dynamic_cast<BaseDoor*>(child);
            if(door)
            {
                Vec2 pos = door->getPosInMap();
                Vec2 playerPos = m_pPlayer->getPosInMap();
                if(pos == playerPos)
                    return;
                if(m_pCurrentLevel->getTerrainTileAreaType(pos.x, pos.y) == Area::AT_BOSS_ROOM
                       && m_pCurrentLevel->getTerrainTileAreaType(playerPos.x, playerPos.y) == Area::AT_BOSS_ROOM)
                {
                    if(!door->isMagicLocked() && (door->getDoorState() == BaseDoor::DS_OPENED))
                    {
                        door->setMagicLocked(true);
                        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_DOOR_MAGIC_CLOSED);
                        door->setDoorState(BaseDoor::DS_CLOSED);
                        
                        if(m_pCurrentLevel)
                            m_pCurrentLevel->playBGBossMusic();
                    }
                        
                    return;
                }
            }
        }
    }
}
bool VoxelExplorer::checkBossRoomDoorClosed()
{
    if(m_pCurrentLevel && m_pPlayer && m_pTerrainDoorsLayer)
    {
        for (const auto& child : m_pTerrainDoorsLayer->getChildren())
        {
            BaseDoor* door = dynamic_cast<BaseDoor*>(child);
            if(door)
            {
                if(door->isMagicLocked() && (door->getDoorState() == BaseDoor::DS_CLOSED))
                    return true;
            }
        }
    }
    return false;
}
void VoxelExplorer::clearBoosRoom()
{
    if(m_pCurrentLevel && m_pPlayer && m_pTerrainDoorsLayer)
    {
        for (const auto& child : m_pTerrainDoorsLayer->getChildren())
        {
            BaseDoor* door = dynamic_cast<BaseDoor*>(child);
            if(door)
            {
                if(door->isMagicLocked() && (door->getDoorState() == BaseDoor::DS_CLOSED))
                {
                    door->setMagicLocked(false);
                    break;
                }
            }
        }
        for (const auto& child : m_pMonstersLayer->getChildren())
        {
            BaseMonster* monster = dynamic_cast<BaseMonster*>(child);
            if(monster && monster->getState() != BaseMonster::MS_DEATH)
            {
                Vec2 monsterPos = monster->getPosInMap();
                if(m_pCurrentLevel->getTerrainTileAreaType(monsterPos.x, monsterPos.y) == Area::AT_BOSS_ROOM)
                    monster->setState(BaseMonster::MS_DEATH);
            }
        }
    }
}
void VoxelExplorer::searchAndCheck()    ///侦查
{
    if(m_pPlayer && m_pCurrentLevel)
    {
        Vec2 playerPosInMap = m_pPlayer->getPosInMap();
        int searchDistance = PlayerProperty::getInstance()->getSearchDistance();
        if(!m_pCurrentLevel->searchAndCheck(playerPosInMap.x, playerPosInMap.y, searchDistance))
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("SEARCH");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
        else
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("SECRET_FOUND");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
    }
}
void VoxelExplorer::shakeScreen()     ////屏幕晃动
{
    if(m_pShakeLayer)
    {
        ScreenShake* shake = ScreenShake::create(0.5f, 0.8, 0.2, 0.8);
        m_pShakeLayer->runAction(shake);
    }
}
void VoxelExplorer::updateStatisticsAreaDatas()
{
    if (m_pCurrentLevel->checkAllAreaBeExplored())
    {
        StatisticsManager::getInstance()->decreaseExploreAllAreaNum();
        StatisticsManager::getInstance()->addExploreAllAreaNum();
    }
}
void VoxelExplorer::setPlayerLightColor(const cocos2d::Color3B& color)
{
    if(m_pPlayer && m_pPlayer->getPlayerLight())
    {
        if(m_pPlayer->getPlayerLight()->getColor() != color)
            m_pPlayer->getPlayerLight()->setColor(color);
    }
}
void VoxelExplorer::updateTerrainTile(int x, int y, TerrainTile::TileType type)
{
    if(m_pTerrainTilesLayer)
    {
        for (const auto& child : m_pTerrainTilesLayer->getChildren())
        {
            TerrainTile* tile = dynamic_cast<TerrainTile*>(child);
            if(tile)
            {
                Vec2 pos = tile->getPosInMap();
                if(pos == Vec2(x, y))
                {
                    std::string tileTex = LevelResourceManager::getInstance()->getTerrainTileRes(TERRAIN_TILES_NAME[type]);
                    if(!tileTex.empty())
                        tile->setTexture(tileTex);
                    return;
                }
            }
        }
    }
}
void VoxelExplorer::addParticle3DEffect(const cocos2d::Vec3& pos, P3D_EFFECT_TYPE type)
{
    if(m_p3DLayer)
    {
        std::string res = LevelResourceManager::getInstance()->getParticles3DRes(P3D_EFFECT_NAMES[type]);
        auto effect = PUParticleSystem3D::create(res);
        effect->setCameraMask((unsigned short)CameraFlag::USER1);
        effect->setName(P3D_EFFECT_NAMES[type]);
        effect->setPosition3D(pos);
        m_p3DLayer->addChild(effect);
        effect->startParticleSystem();
    }
}
void VoxelExplorer::addParticle3DEffectToPlayer(P3D_EFFECT_TYPE type, bool keepLocal)
{
    if(m_pPlayer)
    {
        PUParticleSystem3D* effect = dynamic_cast<PUParticleSystem3D*>(m_pPlayer->getChildByName(P3D_EFFECT_NAMES[type]));
        if(!effect)
        {
            std::string res = LevelResourceManager::getInstance()->getParticles3DRes(P3D_EFFECT_NAMES[type]);
            effect = PUParticleSystem3D::create(res);
            effect->setCameraMask((unsigned short)CameraFlag::USER1);
            effect->setName(P3D_EFFECT_NAMES[type]);
            effect->setKeepLocal(keepLocal);
            m_pPlayer->addChild(effect);
        }
        effect->startParticleSystem();
    }
}
void VoxelExplorer::removeParticle3D3DEffectFromPlayer(P3D_EFFECT_TYPE type)
{
    if(m_pPlayer)
    {
        PUParticleSystem3D* effect = dynamic_cast<PUParticleSystem3D*>(m_pPlayer->getChildByName(P3D_EFFECT_NAMES[type]));
        if(effect)
            effect->stopParticleSystem();
    }
}
void VoxelExplorer::addParticle3DEffectToActor(Actor* actor, P3D_EFFECT_TYPE type)
{
    if(actor)
    {
        std::string res = LevelResourceManager::getInstance()->getParticles3DRes(P3D_EFFECT_NAMES[type]);
        auto effect = PUParticleSystem3D::create(res);
        effect->setCameraMask((unsigned short)CameraFlag::USER1);
        effect->setName(P3D_EFFECT_NAMES[type]);
        effect->setKeepLocal(true);
        actor->addChild(effect);
        effect->startParticleSystem();
    }
}
void VoxelExplorer::generatePickItem(const cocos2d::Vec2& pos, bool generateItem, int copper, int monsterLevel)
{
    if(m_pPickableItemsLayer && m_pCurrentLevel)
    {
        if(copper > 0)
        {
            PlayerProperty::getInstance()->addMoney(copper);
        }
        if(generateItem)
        {
            PickableItem::PickableItemType type = PickableItem::generatePickItemByMonsterLevel(monsterLevel);
            if(type == PickableItem::PIT_UNKNOWN)
                return;
            PickableItem* item = PickableItem::create(type, monsterLevel);
            if(item)
            {
                item->setPosition3D(Vec3(pos.x*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -pos.y*TerrainTile::CONTENT_SCALE));
                item->setVisited(true);
                VoxelExplorer::getInstance()->getPickableItemsLayer()->addChild(item);
                item->setState(PickableItem::PIS_BEGIN_GENERATE);
            }
        }
    }
}
void VoxelExplorer::generatePickItemByUseableItem(const cocos2d::Vec2& pos, UseableItem::UseableItemType type)
{
    CChaosNumber dc = RandomDungeon::getInstance()->getDifficultClass();
    CChaosNumber nodeDepth = RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nNodeDepth;
    CChaosNumber currentDepth = RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nCurrentDepth;
    CChaosNumber level = (dc-1)*30 + (nodeDepth-1)*5 + cocos2d::random(0, (int)currentDepth.GetLongValue()) + 1;
    
    if(type <= UseableItem::UIT_CHEST_GOLD)
    {
        if(type == UseableItem::UIT_CHEST_GOLD || type == UseableItem::UIT_CHEST_NO_LOCK_GOLD)
            PlayerProperty::getInstance()->addMoney(10000);
        else if(type == UseableItem::UIT_CHEST_SILVER || type == UseableItem::UIT_CHEST_NO_LOCK_SILVER)
            PlayerProperty::getInstance()->addMoney(2500);
        else
            PlayerProperty::getInstance()->addMoney(50);
        
        PickableItem::PickableItemType pitType = PickableItem::generatePickItemByUseableLevel(level, type);
        if(pitType == PickableItem::PIT_UNKNOWN)
            return;
        PickableItem* item = PickableItem::create(pitType, level);
        if(item)
        {
            item->setPosition3D(Vec3(pos.x*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -pos.y*TerrainTile::CONTENT_SCALE));
            item->setVisited(true);
            VoxelExplorer::getInstance()->getPickableItemsLayer()->addChild(item);
            item->setState(PickableItem::PIS_BEGIN_GENERATE);
        }
    }
    else
    {
        PlayerProperty::getInstance()->addMoney(cocos2d::random(5, 30));
        float percent1 = 0.1f;
        float percent2 = 0.3f;
        float percent3 = 1.0f - percent1 - percent2;
        AlisaMethod* am = AlisaMethod::create(percent1, percent2, percent3,-1.0, NULL);
        if(am)
        {
            int randIndex = am->getRandomIndex();
            if(randIndex == 0)
            {
                if(m_pPickableItemsLayer)
                {
                    PickableItem::PickableItemType pitType = PickableItem::generatePickItemByUseableLevel(level, type);
                    if(pitType == PickableItem::PIT_UNKNOWN)
                        return;
                    PickableItem* item = PickableItem::create(pitType, level);
                    if(item)
                    {
                        item->setPosition3D(Vec3(pos.x*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -pos.y*TerrainTile::CONTENT_SCALE));
                        item->setVisited(true);
                        m_pPickableItemsLayer->addChild(item);
                        item->setState(PickableItem::PIS_BEGIN_GENERATE);
                    }
                }
            }
            else if(randIndex == 1)
            {
                if(m_pMonstersLayer)
                {
                    std::vector<BaseMonster::MonsterType> monsterTypes = {BaseMonster::MT_RAT, BaseMonster::MT_SPIDER, BaseMonster::MT_SNAKE, BaseMonster::MT_KOBOLD, BaseMonster::MT_ZOMBIE, BaseMonster::MT_SKELETON };
                    int randType = cocos2d::random(0, (int)(monsterTypes.size()-1));
                    StandardMonster* monster = StandardMonster::create(monsterTypes[randType]);
                    if(monster)
                    {
                        monster->setPosition3D(Vec3(pos.x*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -pos.y*TerrainTile::CONTENT_SCALE));
                        monster->setVisited(true);
                        monster->addTerrainTileFlag(TileInfo::ATTACKABLE);
                        m_pMonstersLayer->addChild(monster);
                        monster->setState(BaseMonster::MS_TRACKING);
                    }
                }
            }
        }
    }
}
void VoxelExplorer::generatePickItemByBoss(const cocos2d::Vec2& pos, int copper)
{
    if(m_pPickableItemsLayer && m_pCurrentLevel)
    {
        if(copper > 0)
        {
            PlayerProperty::getInstance()->addMoney(copper);
        }
        PickableItem* item = PickableItem::create(PickableItem::PIT_KEY_BOSS, 1);
        if(item)
        {
            item->setPosition3D(Vec3(pos.x*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -pos.y*TerrainTile::CONTENT_SCALE));
            item->setVisited(true);
            VoxelExplorer::getInstance()->getPickableItemsLayer()->addChild(item);
            item->setState(PickableItem::PIS_BEGIN_GENERATE);
        }
    }
}
void VoxelExplorer::handleDoor(const cocos2d::Vec2& mapPos)
{
    if(m_pTerrainDoorsLayer && m_pPlayer && m_pCurrentLevel)
    {
        for (const auto& child : m_pTerrainDoorsLayer->getChildren())
        {
            BaseDoor* door = dynamic_cast<BaseDoor*>(child);
            if(door && door->getPosInMap() == mapPos)
            {
                if(door->getDoorState() == BaseDoor::DS_HIDE)
                {
                    door->setDoorState(BaseDoor::DS_CLOSED);
                    m_pCurrentLevel->setTerrainTileType(mapPos.x, mapPos.y, TerrainTile::TT_DOOR);
                    
                    std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("SECRET_FOUND");
                    SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
                    
                    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_FOUND_HIDDEN_DOOR);
                    PlayerProperty::getInstance()->setExp(PlayerProperty::getInstance()->getExp() + 100);
                    StatisticsManager::getInstance()->addHideInfoNum(StatisticsManager::eHideInfoType::HIT_DOOR);
                    return;
                }
                else if(door->getDoorState() == BaseDoor::DS_CLOSED)
                {
                    if(door->isMagicLocked())
                    {
                        std::string soundName = LevelResourceManager::getInstance()->getDungeonSoundEffectRes("DOOR_LOCKED");
                        SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
                        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_DOOR_MAGIC_LOCKED);
                        return;
                    }
                    else
                    {
                        door->setDoorState(BaseDoor::DS_OPENED);
                        if(m_pCurrentLevel)
                        {
                            m_pCurrentLevel->updateAreaFogOfWarByPos(door->getPosInMap());
                            updateStatisticsAreaDatas();
                        }
                        return;
                    }
                }
                else if(door->getDoorState() == BaseDoor::DS_LOCKED)
                {
                    if(door->getOpenType() == DoorOpenType::DOT_BOSS)
                    {
                        if(PlayerProperty::getInstance()->useKey(PickableItem::PIT_KEY_BOSS))
                        {
                            door->setDoorState(BaseDoor::DS_CLOSED);
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_USE_BOSS_KEY);
                        }
                        else
                        {
                            std::string soundName = LevelResourceManager::getInstance()->getDungeonSoundEffectRes("DOOR_LOCKED");
                            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_NO_BOSS_KEY);
                        }
                    }
                    else
                    {
                        if(PlayerProperty::getInstance()->useKey(PickableItem::PIT_KEY_ROOM))
                        {
                            door->setDoorState(BaseDoor::DS_CLOSED);
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_USE_ROOM_KEY);
                        }
                        else
                        {
                            std::string soundName = LevelResourceManager::getInstance()->getDungeonSoundEffectRes("DOOR_LOCKED");
                            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_NO_ROOM_KEY);
                        }
                    }
                    return;
                }
            }
        }

    }
}
void VoxelExplorer::handleUseUseableItem(const cocos2d::Vec2& mapPos)
{
    if(!m_pPlayer || !m_pCurrentLevel)
        return;
    if(m_pUseableItemsLayer)
    {
        for (const auto& child : m_pUseableItemsLayer->getChildren())
        {
            UseableItem* useableItem = dynamic_cast<UseableItem*>(child);
            if(useableItem && useableItem->getPosInMap() == mapPos)
            {
                if(useableItem->getUseableItemType() <= UseableItem::UIT_CHEST_NO_LOCK_GOLD)
                {
                    StatisticsManager::getInstance()->addUserableOpenNum(useableItem->getUseableItemType());
                    m_pCurrentLevel->createSiegeMonsters(useableItem->getPosInMap());
                    
                    std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("CHEST_UNLOCKED");
                    SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
                    
                    useableItem->setState(UseableItem::UIS_FADEOUT);
                    return;
                }
                else if(useableItem->getUseableItemType() <= UseableItem::UIT_CHEST_GOLD)
                {
                    if(useableItem->getUseableItemType() == UseableItem::UIT_CHEST_COPPER)
                    {
                        if(PlayerProperty::getInstance()->useKey(PickableItem::PIT_KEY_COPPER))
                        {

                            StatisticsManager::getInstance()->addUserableOpenNum(useableItem->getUseableItemType());

                            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("CHEST_UNLOCKED");
                            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
                
                            useableItem->setState(UseableItem::UIS_FADEOUT);
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_USE_COPPER_CHEST_KEY);
                        }
                        else
                        {

                            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("CHEST_LOCKED");
                            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_NO_COPPER_KEY);
                        }
                    }
                    else if(useableItem->getUseableItemType() == UseableItem::UIT_CHEST_SILVER)
                    {
                        if(PlayerProperty::getInstance()->useKey(PickableItem::PIT_KEY_SILVER))
                        {

                            StatisticsManager::getInstance()->addUserableOpenNum(useableItem->getUseableItemType());
                            
                            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("CHEST_UNLOCKED");
                            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
                            
                            useableItem->setState(UseableItem::UIS_FADEOUT);
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_USE_SILVER_CHEST_KEY);
                        }
                        else
                        {
                            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("CHEST_LOCKED");
                            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_NO_SILVER_KEY);
                        }
                    }
                    else if(useableItem->getUseableItemType() == UseableItem::UIT_CHEST_GOLD)
                    {
                        if(PlayerProperty::getInstance()->useKey(PickableItem::PIT_KEY_GOLD))
                        {

                            StatisticsManager::getInstance()->addUserableOpenNum(useableItem->getUseableItemType());
                            
                            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("CHEST_UNLOCKED");
                            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
                            
                            useableItem->setState(UseableItem::UIS_FADEOUT);
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_USE_GOLD_CHEST_KEY);

                        }
                        else
                        {
                            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("CHEST_LOCKED");
                            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
                            
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_NO_GOLD_KEY);
                        }
                    }
                    return;
                }
                else
                {
                    int rand = cocos2d::random(0, 2);
                    if(rand == 0)
                    {
                        std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("JAR_FRAGMENTATION0");
                        SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
                    }
                    else if(rand == 1)
                    {
                        std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("JAR_FRAGMENTATION1");
                        SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
                    }
                    else
                    {
                        std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("JAR_FRAGMENTATION2");
                        SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
                    }
                    useableItem->setState(UseableItem::UIS_FADEOUT);
                    StatisticsManager::getInstance()->addUserableOpenNum(useableItem->getUseableItemType());
                    return;
                }
            }
        }
    }
    if(m_pNPCsLayer)
    {
        for (const auto& child : m_pNPCsLayer->getChildren())
        {
            Npc* npc = dynamic_cast<Npc*>(child);
            if(npc && npc->getPosInMap() == mapPos)
            {
                npc->setState(Npc::NPCS_ANSWER);
                return;
            }
        }
    }
}
void VoxelExplorer::handleTriggerTrap(const cocos2d::Vec2& mapPos, TerrainTile::TileType trapType)     ///触发机关
{
    if(m_pPlayer && m_pMonstersLayer && m_pCurrentLevel)
    {
        bool trigged = false;
        if(trapType == TerrainTile::TT_TOXIC_TRAP)
        {
            int bufferFlag = PlayerProperty::getInstance()->getPlayerBuffer();
            if((bufferFlag & PB_POISONING) == 0)
            {
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_TRIGGER_TOXIC_TRAP);
                m_pPlayer->addPlayerBuffer(PB_POISONING);
                
                trigged = true;
            }
        }
        else if(trapType == TerrainTile::TT_FIRE_TRAP)
        {
            int bufferFlag = PlayerProperty::getInstance()->getPlayerBuffer();
            if((bufferFlag & PB_FIRE) == 0)
            {
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_TRIGGER_FIRE_TRAP);
                m_pPlayer->addPlayerBuffer(PB_FIRE);
                trigged = true;
            }
        }
        else if(trapType == TerrainTile::TT_PARALYTIC_TRAP)
        {
            int bufferFlag = PlayerProperty::getInstance()->getPlayerBuffer();
            if((bufferFlag & PB_PARALYTIC) == 0)
            {
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_TRIGGER_PARALYTIC_TRAP);
                m_pPlayer->addPlayerBuffer(PB_PARALYTIC);
                trigged = true;
            }
        }
        else if(trapType == TerrainTile::TT_GRIPPING_TRAP)
        {
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_TRIGGER_GRIPPING_TRAP);
            m_pPlayer->hurtByGrippingTrap();
            trigged = true;
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("TRIGGER_GRIPPING_TRAP");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
        else if(trapType == TerrainTile::TT_SUMMONING_TRAP)
        {
            if(m_pPlayer->getLastPosInMap() != m_pPlayer->getPosInMap())
            {
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_TRIGGER_SUMMONING_TRAP);
                if(!m_pCurrentLevel->createSummoningMonsters(mapPos))
                    CCLOG("Handle trigger summoning trap failed!");
                trigged = true;
                std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("TRIGGER_SUMMONING_TRAP");
                SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
            }
        }
        else if(trapType == TerrainTile::TT_WEAK_TRAP)
        {
            int bufferFlag = PlayerProperty::getInstance()->getPlayerBuffer();
            if((bufferFlag & PB_WEAK) == 0)
            {
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_TRIGGER_WEAK_TRAP);
                m_pPlayer->addPlayerBuffer(PB_WEAK);
                trigged = true;
            }
        }
        
        if(m_pTerrainTilesLayer && trigged)
        {
            for (const auto& child : m_pTerrainTilesLayer->getChildren())
            {
                TerrainTile* tile = dynamic_cast<TerrainTile*>(child);
                if(tile && (mapPos == tile->getPosInMap()))
                {
                    std::string texName = LevelResourceManager::getInstance()->getTerrainTileRes(TERRAIN_TILES_NAME[trapType]);
                    if(!texName.empty())
                    {
                        auto tex = Director::getInstance()->getTextureCache()->addImage(texName);
                        if(tex)
                            tex->setAliasTexParameters();
                        tile->setTexture(tex);
                    }

                }
            }
        }
    }
}
void VoxelExplorer::handleShowSecretDoor(const cocos2d::Vec2& mapPos)
{
    if(m_pPlayer && m_pTerrainDoorsLayer)
    {
        for (const auto& child : m_pTerrainDoorsLayer->getChildren())
        {
            BaseDoor* door = dynamic_cast<BaseDoor*>(child);
            if(door && door->getPosInMap() == mapPos)
            {
                if(door->getDoorState() == BaseDoor::DS_HIDE)
                {
                    door->setDoorState(BaseDoor::DS_CLOSED);
                    m_pCurrentLevel->setTerrainTileType(mapPos.x, mapPos.y, TerrainTile::TT_DOOR);
                    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_FOUND_HIDDEN_DOOR);
                    PlayerProperty::getInstance()->setExp(PlayerProperty::getInstance()->getExp() + 100);
                }
            }
        }
    }
}
void VoxelExplorer::handleShowHiddenTrap(const cocos2d::Vec2& mapPos, TerrainTile::TileType trapType) ///显示隐藏机关
{
    if(m_pPlayer)
    {
        if(trapType == TerrainTile::TT_TOXIC_TRAP)
        {
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_FOUND_HIDDEN_TOXIC_TRAP);
            PlayerProperty::getInstance()->setExp(PlayerProperty::getInstance()->getExp() + 100);
            StatisticsManager::getInstance()->addHideInfoNum(StatisticsManager::eHideInfoType::HIT_TRAP);
        }
        else if(trapType == TerrainTile::TT_FIRE_TRAP)
        {
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_FOUND_HIDDEN_FIRE_TRAP);
            PlayerProperty::getInstance()->setExp(PlayerProperty::getInstance()->getExp() + 100);
             StatisticsManager::getInstance()->addHideInfoNum(StatisticsManager::eHideInfoType::HIT_TRAP);
        }
        else if(trapType == TerrainTile::TT_PARALYTIC_TRAP)
        {
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_FOUND_HIDDEN_PARALYTIC_TRAP);
            PlayerProperty::getInstance()->setExp(PlayerProperty::getInstance()->getExp() + 100);
             StatisticsManager::getInstance()->addHideInfoNum(StatisticsManager::eHideInfoType::HIT_TRAP);
        }
        else if(trapType == TerrainTile::TT_GRIPPING_TRAP)
        {
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_FOUND_HIDDEN_GRIPPING_TRAP);
            PlayerProperty::getInstance()->setExp(PlayerProperty::getInstance()->getExp() + 100);
             StatisticsManager::getInstance()->addHideInfoNum(StatisticsManager::eHideInfoType::HIT_TRAP);
        }
        else if(trapType == TerrainTile::TT_SUMMONING_TRAP)
        {
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_FOUND_HIDDEN_SUMMONING_TRAP);
            PlayerProperty::getInstance()->setExp(PlayerProperty::getInstance()->getExp() + 100);
             StatisticsManager::getInstance()->addHideInfoNum(StatisticsManager::eHideInfoType::HIT_TRAP);
        }
        else if(trapType == TerrainTile::TT_WEAK_TRAP)
        {
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_FOUND_HIDDEN_WEAK_TRAP);
            PlayerProperty::getInstance()->setExp(PlayerProperty::getInstance()->getExp() + 100);
             StatisticsManager::getInstance()->addHideInfoNum(StatisticsManager::eHideInfoType::HIT_TRAP);
        }
        if(m_pTerrainTilesLayer)
        {
            for (const auto& child : m_pTerrainTilesLayer->getChildren())
            {
                TerrainTile* tile = dynamic_cast<TerrainTile*>(child);
                if(tile && (mapPos == tile->getPosInMap()))
                {
                    std::string texName = LevelResourceManager::getInstance()->getTerrainTileRes(TERRAIN_TILES_NAME[trapType]);
                    if(!texName.empty())
                    {
                        auto tex = Director::getInstance()->getTextureCache()->addImage(texName);
                        if(tex)
                            tex->setAliasTexParameters();
                        tile->setTexture(tex);
                    }
                }
            }
        }
    }
}
void VoxelExplorer::handleShowSearchEffect(const cocos2d::Vec2& mapPos)
{
    if(m_pPlayer && m_pTerrainTilesLayer)
    {
        for (const auto& child : m_pTerrainTilesLayer->getChildren())
        {
            TerrainTile* tile = dynamic_cast<TerrainTile*>(child);
            if(tile)
            {
                if(tile->getPosInMap() == mapPos)
                {
                    EaseSineOut* colorTo1 = EaseSineOut::create(TintTo::create(0.35f, Color3B(255, 128, 255)));
                    EaseSineOut* colorTo2 = EaseSineOut::create(TintTo::create(0.35f, Color3B::WHITE));
                    Sequence* sequence = Sequence::create(colorTo1, colorTo2, nullptr);
                    tile->runAction(sequence);
                }
            }
        }
    }
}
void VoxelExplorer::handlePickItem(const cocos2d::Vec2& mapPos)        ///拾取道具
{
    if(m_pPickableItemsLayer && m_pPlayer)
    {
        for (const auto& child : m_pPickableItemsLayer->getChildren())
        {
            PickableItem* item = dynamic_cast<PickableItem*>(child);
            if(item && item->getPosInMap() == mapPos)
            {
                if(item->getState() == PickableItem::PIS_IDLE)
                {
                    if(PlayerProperty::getInstance()->addItemToBag(item->getPickableItemType(), item->getLevel()))
                    {
                        item->setState(PickableItem::PIS_FADEOUT);
                    }
                }
            }
        }
    }
}
void VoxelExplorer::handleMonsterHurt(const cocos2d::Vec2& mapPos)
{
    if(!m_pPlayer)
        return;
    if(m_pMonstersLayer)
    {
        for (const auto& child : m_pMonstersLayer->getChildren())
        {
            BaseMonster* monster = dynamic_cast<BaseMonster*>(child);
            if(monster && (monster->getPosInMap() == mapPos || monster->getPosInMap().distance(mapPos) < 1))
            {
                if(monster->getState() != BaseMonster::MS_DEATH)
                {
                    monster->attackedByPlayer(false);
                    return;
                }
            }
        }
    }
    
    if(m_pBossLayer)
    {
        for (const auto& child : m_pBossLayer->getChildren())
        {
            BaseBoss* boss = dynamic_cast<BaseBoss*>(child);
            if(boss && (boss->getPosInMap() == mapPos || boss->getPosInMap().distance(mapPos) < 1))
            {
                if(boss->getState() != BaseBoss::BS_DEATH)
                {
                    boss->attackedByPlayer(false);
                    return;
                }
            }
        }
    }
}
void VoxelExplorer::handlePlayerHurt(const cocos2d::Vec2& mapPos, BaseMonster* monster)
{
    if(!m_pPlayer || !monster ||m_pPlayer->getState() == Player::PS_DEATH)
        return;
    
    if(m_pPlayer->getPosInMap() != mapPos)
    {
        std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("MISS");
        SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        return m_pPlayer->attackByMonster(monster->getMonsterProperty(), true);
    }
    std::string soundName = LevelResourceManager::getInstance()->getMonsterSoundEffectRes(MONSTER_MODEL_NAMES[monster->getMonsterType()], "ATTACK");
    SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    return m_pPlayer->attackByMonster(monster->getMonsterProperty(), false);
}
void VoxelExplorer::handlePlayerHurtByBoss(const cocos2d::Vec2& mapPos, BaseBoss* boss)
{
    if(!m_pPlayer || !boss ||m_pPlayer->getState() == Player::PS_DEATH)
        return;
    
    if(m_pPlayer->getPosInMap() != mapPos)
    {
        return m_pPlayer->attackByBoss(boss->getBossProperty(), true);
    }
    std::string soundName = LevelResourceManager::getInstance()->getMonsterSoundEffectRes(BOSS_MODEL_NAMES[boss->getBossType()], "ATTACK");
    SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    return m_pPlayer->attackByBoss(boss->getBossProperty(), false);
}
void VoxelExplorer::handlePlayerUseScroll(PickableItem::PickableItemType type)
{
    if(!m_pPlayer && m_pPlayer->getState() == Player::PS_DEATH)
        return;
    switch (type) {
        case PickableItem::PickableItemType::PIT_SCROLL_TELEPORT:
            {
                m_pPlayer->removeTerrainTileFlag(TileInfo::ATTACKABLE);
                cocos2d::Vec2 pos = m_pCurrentLevel->getRandomVisitedTranspotTile(m_pPlayer->getPosInMap());
                m_pPlayer->setPosition3D(Vec3(pos.x*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -pos.y*TerrainTile::CONTENT_SCALE));
                m_pPlayer->addTerrainTileFlag(TileInfo::ATTACKABLE);
                
                updateMiniMap();
                
                m_pMainCamera->setPosition3D(m_pPlayer->getPosition3D() + Vec3(0, 5*TerrainTile::CONTENT_SCALE, 4*TerrainTile::CONTENT_SCALE ));
                m_pMainCamera->lookAt(m_pPlayer->getPosition3D() + Vec3(0,0.5f*TerrainTile::CONTENT_SCALE,0));
                m_pPlayer->setState(Player::PS_IDLE);
                
                VoxelExplorer::getInstance()->addParticle3DEffect(Vec3(pos.x*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -pos.y*TerrainTile::CONTENT_SCALE), P3D_PLAYER_TELEPORT);
            }
            break;
        case PickableItem::PickableItemType::PIT_SCROLL_SPEED:
            m_pPlayer->addPlayerBuffer(PB_SPEEDUP);
            break;
        case PickableItem::PickableItemType::PIT_SCROLL_STEALTH:
            m_pPlayer->addPlayerBuffer(PB_STEALTH);
            break;
        case PickableItem::PickableItemType::PIT_SCROLL_STRONGER:
            m_pPlayer->addPlayerBuffer(PB_STRONGER);
            break;
        case PickableItem::PickableItemType::PIT_SCROLL_DESTINY:
            {
                DestinyScrollType randType = (DestinyScrollType)cocos2d::random((int)DST_ADDMONEY, (int)DST_WEAK);
                switch (randType) {
                    case DST_ADDMONEY:
                        {
                            int money = cocos2d::random(1000, 5000);
                            PlayerProperty::getInstance()->addMoney(money);
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_DESTINY_ADDMONEY);
                        }
                        break;
                    case DST_TRANSPORT:
                        {
                            m_pPlayer->removeTerrainTileFlag(TileInfo::ATTACKABLE);
                            cocos2d::Vec2 pos = m_pCurrentLevel->getRandomVisitedTranspotTile(m_pPlayer->getPosInMap());
                            m_pPlayer->setPosition3D(Vec3(pos.x*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -pos.y*TerrainTile::CONTENT_SCALE));
                            m_pPlayer->addTerrainTileFlag(TileInfo::ATTACKABLE);
                            
                            updateMiniMap();
                            
                            m_pMainCamera->setPosition3D(m_pPlayer->getPosition3D() + Vec3(0, 5*TerrainTile::CONTENT_SCALE, 4*TerrainTile::CONTENT_SCALE ));
                            m_pMainCamera->lookAt(m_pPlayer->getPosition3D() + Vec3(0,0.5f*TerrainTile::CONTENT_SCALE,0));
                            m_pPlayer->setState(Player::PS_IDLE);
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_DESTINY_TRANSPORT);
                        }
                        break;
                    case DST_STRONGER:
                        {
                            m_pPlayer->addPlayerBuffer(PB_STRONGER);
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_DESTINY_STRONGER);
                        }
                        break;
                    case DST_STEALTH:
                        {
                            m_pPlayer->addPlayerBuffer(PB_STEALTH);
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_DESTINY_STEALTH);
                        }
                        break;
                    case DST_SPEEDUP:
                        {
                            m_pPlayer->addPlayerBuffer(PB_SPEEDUP);
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_DESTINY_SPEEDUP);
                        }
                        break;
                    case DST_POISIONING:
                        {
                            m_pPlayer->addPlayerBuffer(PB_POISONING);
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_DESTINY_POISIONING);
                        }
                        break;
                    case DST_FIRE:
                        {
                            m_pPlayer->addPlayerBuffer(PB_FIRE);
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_DESTINY_FIRE);
                        }
                        break;
                    case DST_FROZEN:
                        {
                            m_pPlayer->addPlayerBuffer(PB_FROZEN);
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_DESTINY_FROZEN);
                        }
                        break;
                    case DST_WEAK:
                        {
                            m_pPlayer->addPlayerBuffer(PB_WEAK);
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_DESTINY_WEAK);
                        }
                        break;
                    default:
                        break;
                }
            }
            break;
        default:
            break;
    }
}
void VoxelExplorer::handlePlayerUsePotion(PickableItem::PickableItemType type)
{
    if(!m_pPlayer)
        return;
    switch (type) {
        case PickableItem::PickableItemType::PIT_POTION_DETOXIFICATION:
            m_pPlayer->removePlayerBuffer(PB_POISONING);
            break;
        case PickableItem::PickableItemType::PIT_POTION_SPECIFIC:
            {
                m_pPlayer->removePlayerBuffer(PB_FROZEN);
                m_pPlayer->removePlayerBuffer(PB_PARALYTIC);
                m_pPlayer->removePlayerBuffer(PB_FIRE);
            }
            break;
        case PickableItem::PickableItemType::PIT_POTION_HEALING:
            m_pPlayer->removePlayerBuffer(PB_WEAK);
            break;
        case PickableItem::PickableItemType::PIT_POTION_UNIVERSAL:
            {
                m_pPlayer->removePlayerBuffer(PB_POISONING);
                m_pPlayer->removePlayerBuffer(PB_FROZEN);
                m_pPlayer->removePlayerBuffer(PB_PARALYTIC);
                m_pPlayer->removePlayerBuffer(PB_FIRE);
                m_pPlayer->removePlayerBuffer(PB_WEAK);
            }
            break;
        default:
            break;
    }
}
void VoxelExplorer::handlePlayerUseStandardPortal(const cocos2d::Vec2& pos)
{
    if(RandomDungeon::getInstance()->getCurrentDungeonNode()->isLastDepth())
    {
        ///加载boss房间
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_GO_BOSSROOM);
        RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nCurrentDepth += 1;
        m_bHasDownStairs = true;
        auto scene = GameScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }
    else if(RandomDungeon::getInstance()->getCurrentDungeonNode()->isBossDepth())
    {
        if(m_pCurrentLevel)
            m_pCurrentLevel->handleUseStandardPortal(pos);
    }
    else
    {
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_STANDARD_PROTAL_NO_ENERGY);
    }
}
void VoxelExplorer::handlePlayerUseSmallPortal()
{
    if(!m_pCurrentLevel)
        return;
    if(!m_pPlayer && m_pPlayer->getState() == Player::PS_DEATH)
        return;
    
    m_pPlayer->removeTerrainTileFlag(TileInfo::ATTACKABLE);
    cocos2d::Vec2 pos = m_pCurrentLevel->getRandomTranspotTile();
    m_pPlayer->setPosition3D(Vec3(pos.x*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -pos.y*TerrainTile::CONTENT_SCALE));
    m_pPlayer->addTerrainTileFlag(TileInfo::ATTACKABLE);
    
    m_pCurrentLevel->updateAreaFogOfWarByPos(pos, true);
    updateStatisticsAreaDatas();
    updateMiniMap();
    
    m_pMainCamera->setPosition3D(m_pPlayer->getPosition3D() + Vec3(0, 5*TerrainTile::CONTENT_SCALE, 4*TerrainTile::CONTENT_SCALE ));
    m_pMainCamera->lookAt(m_pPlayer->getPosition3D() + Vec3(0,0.5f*TerrainTile::CONTENT_SCALE,0));
    m_pPlayer->setState(Player::PS_IDLE);
    
    VoxelExplorer::getInstance()->addParticle3DEffect(Vec3(pos.x*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -pos.y*TerrainTile::CONTENT_SCALE), P3D_PLAYER_TELEPORT);
    std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("USE_SCROLL");
    SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_USE_SMALL_PROTAL);
}
void VoxelExplorer::handleUpstairs()
{
    if(RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nCurrentDepth > 1)
    {
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_GO_DOWNSTAIRS);
        m_bHasDownStairs = false;
        RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nCurrentDepth -= 1;
        auto scene = GameScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }
    else
    {
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_GO_UPSTAIRS_FORBIDDEN);
    }
}
void VoxelExplorer::handleDownstairs()
{
    if(RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nCurrentDepth < RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nTotalNum)
    {
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_GO_DOWNSTAIRS);
        m_bHasDownStairs = true;
        RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nCurrentDepth += 1;
        auto scene = GameScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }
    else if(RandomDungeon::getInstance()->getCurrentDungeonNode()->isLastDepth())
    {
        ///加载boss房间
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_GO_BOSSROOM);
        RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nCurrentDepth += 1;
         m_bHasDownStairs = true;
        auto scene = GameScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }
}
void VoxelExplorer::handleGoChasm()
{
    if(!m_pPlayer || !m_pCurrentLevel)
        return;
    if(m_pPlayer->getState() == Player::PS_DEATH)
        return;
    ///跳入深渊处理
    if(RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nCurrentDepth < RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nTotalNum)
    {
        float percent1 = 0.7f;
        float percent2 = 1.0f - percent1;
        AlisaMethod* am = AlisaMethod::create(percent1, percent2,-1.0, NULL);
        if(am)
        {
            int randIndex = am->getRandomIndex();
            if(randIndex == 0)
            {
                m_pPlayer->fallAndDie();
                StatisticsManager::getInstance()->addRoleDeadNum(StatisticsManager::eRoleDeadType::RET_FAIL);
            }
            else
            {
                StatisticsManager::getInstance()->addNotFailDeadNum();
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_FALL_DOWNSTAIRS);
                m_bHasDownStairs = true;
                RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nCurrentDepth += 1;
                auto scene = GameScene::createScene();
                Director::getInstance()->replaceScene(scene);
            }
        }
    }
    else
    {
        m_pPlayer->fallAndDie();
        StatisticsManager::getInstance()->addRoleDeadNum(StatisticsManager::eRoleDeadType::RET_FAIL);
    }
}
void VoxelExplorer::handleRemoveTrap(const cocos2d::Vec2& mapPos)
{
    if(m_pCurrentLevel)
    {
        if(m_pTerrainTilesLayer)
        {
            for (const auto& child : m_pTerrainTilesLayer->getChildren())
            {
                TerrainTile* tile = dynamic_cast<TerrainTile*>(child);
                if(tile && (mapPos == tile->getPosInMap()))
                {
                    TerrainTile::TileType tileType = m_pCurrentLevel->getTerrainTileType(mapPos.x, mapPos.y);
                    
                    if(tileType == TerrainTile::TT_TOXIC_TRAP
                       || tileType == TerrainTile::TT_FIRE_TRAP
                       || tileType == TerrainTile::TT_PARALYTIC_TRAP
                       || tileType == TerrainTile::TT_GRIPPING_TRAP
                       || tileType == TerrainTile::TT_SUMMONING_TRAP
                       || tileType == TerrainTile::TT_WEAK_TRAP)
                    {
                        std::string texName = LevelResourceManager::getInstance()->getTerrainTileRes(TERRAIN_TILES_NAME[TerrainTile::TT_STANDARD]);
                        if(!texName.empty())
                        {
                            auto tex = Director::getInstance()->getTextureCache()->addImage(texName);
                            if(tex)
                                tex->setAliasTexParameters();
                            tile->setTexture(tex);
                        }
                        m_pCurrentLevel->setTerrainTileType(mapPos.x, mapPos.y, TerrainTile::TT_STANDARD);
                        PlayerProperty::getInstance()->setExp(PlayerProperty::getInstance()->getExp() + 50);
                    }
                }
            }
        }
    }
}
bool VoxelExplorer::createLayers()
{
    m_p3DLayer = Layer3D::create();
    if(!m_p3DLayer)
        return false;
    m_p3DLayer->setCameraMask((unsigned int)CameraFlag::USER1);
    m_pMainLayer->addChild(m_p3DLayer);
    
    m_pShakeLayer = Layer::create();
    if(!m_pShakeLayer)
        return false;
    m_pShakeLayer->setCameraMask((unsigned int)CameraFlag::USER1);
    m_p3DLayer->addChild(m_pShakeLayer);
    
    m_pTerrainTilesLayer = Layer::create();
    if(!m_pTerrainTilesLayer)
        return false;
    m_pTerrainTilesLayer->setCameraMask((unsigned int)CameraFlag::USER1);
    m_pShakeLayer->addChild(m_pTerrainTilesLayer);
    
    m_pFakeShadowLayer = Layer::create();
    if(!m_pFakeShadowLayer)
        return false;
    m_pFakeShadowLayer->setCameraMask((unsigned int)CameraFlag::USER1);
    m_pShakeLayer->addChild(m_pFakeShadowLayer);
    
    m_pTerrainPortalsLayer = Layer::create();
    if(!m_pTerrainPortalsLayer)
        return false;
    m_pTerrainPortalsLayer->setCameraMask((unsigned int)CameraFlag::USER1);
    m_pShakeLayer->addChild(m_pTerrainPortalsLayer);
    
    m_pTerrainDoorsLayer = Layer::create();
    if(!m_pTerrainDoorsLayer)
        return false;
    m_pTerrainDoorsLayer->setCameraMask((unsigned int)CameraFlag::USER1);
    m_pShakeLayer->addChild(m_pTerrainDoorsLayer);
    
    m_pUseableItemsLayer = Layer::create();
    if(!m_pUseableItemsLayer)
        return false;
    m_pUseableItemsLayer->setCameraMask((unsigned int)CameraFlag::USER1);
    m_pShakeLayer->addChild(m_pUseableItemsLayer);
    
    m_pBossLayer = Layer::create();
    if(!m_pBossLayer)
        return false;
    m_pBossLayer->setCameraMask((unsigned int)CameraFlag::USER1);
    m_pShakeLayer->addChild(m_pBossLayer);
    
    m_pNPCsLayer = Layer::create();
    if(!m_pNPCsLayer)
        return false;
    m_pNPCsLayer->setCameraMask((unsigned int)CameraFlag::USER1);
    m_pShakeLayer->addChild(m_pNPCsLayer);
    
    m_pMonstersLayer = Layer::create();
    if(!m_pMonstersLayer)
        return false;
    m_pMonstersLayer->setCameraMask((unsigned int)CameraFlag::USER1);
    m_pShakeLayer->addChild(m_pMonstersLayer);
    
    m_pPickableItemsLayer = Layer::create();
    if(!m_pPickableItemsLayer)
        return false;
    m_pPickableItemsLayer->setCameraMask((unsigned int)CameraFlag::USER1);
    m_pShakeLayer->addChild(m_pPickableItemsLayer);
    
    m_pBulletsLayer = Layer::create();
    if(!m_pBulletsLayer)
        return false;
    m_pBulletsLayer->setCameraMask((unsigned int)CameraFlag::USER1);
    m_pShakeLayer->addChild(m_pBulletsLayer);
    
    m_p2DLayer = Layer::create();
    if(!m_p2DLayer)
        return false;
    m_pMainLayer->addChild(m_p2DLayer);
    
    m_pHUDLayer = Layer::create();
    if (!m_pHUDLayer)
        return false;
    m_p2DLayer->addChild(m_pHUDLayer);
    
    m_pUILayer = GameUILayer::create();
    if (!m_pUILayer)
        return false;
    m_p2DLayer->addChild(m_pUILayer);
    return true;
}
bool VoxelExplorer::createLights()
{
    if(!m_p3DLayer)
        return false;
    AmbientLight* ambLight = AmbientLight::create(Color3B(30, 30, 30));
    if(!ambLight)
        return false;
    ambLight->setLightFlag(LightFlag::LIGHT1);
    m_p3DLayer->addChild(ambLight);
    
    DirectionLight* directionLight = DirectionLight::create(Vec3(-2, -4, -3), Color3B(30, 30, 30));
    if(!directionLight)
        return false;
    directionLight->setLightFlag(LightFlag::LIGHT1);
    m_p3DLayer->addChild(directionLight);

    return true;
}
bool VoxelExplorer::createLevel()
{
    DungeonNode* node = RandomDungeon::getInstance()->getCurrentDungeonNode();
    if(!node)
        return false;
    switch (node->m_Type) {
        case DT_SEWER:
            {
                if(node->isBossDepth())
                    m_pCurrentLevel = new(std::nothrow) SewerBossLevel();
                else
                    m_pCurrentLevel = new(std::nothrow) SewerLevel();
            }
            break;
        case DT_PRISON:
            {
                if(node->isBossDepth())
                    m_pCurrentLevel = new(std::nothrow) PrisonBossLevel();
                else
                    m_pCurrentLevel = new(std::nothrow) PrisonLevel();
            }
            break;
        case DT_FANE:
            {
                if(node->isBossDepth())
                    m_pCurrentLevel = new(std::nothrow) FaneBossLevel();
                else
                    m_pCurrentLevel = new(std::nothrow) FaneLevel();
            }
            break;
        case DT_MINES:
            {
                if(node->isBossDepth())
                    m_pCurrentLevel = new(std::nothrow) MineBossLevel();
                else
                    m_pCurrentLevel = new(std::nothrow) MineLevel();
            }
            break;
        case DT_CAVE:
            {
                if(node->isBossDepth())
                    m_pCurrentLevel = new(std::nothrow) CaveBossLevel();
                else
                    m_pCurrentLevel = new(std::nothrow) CaveLevel();
            }
            break;
        case DT_TOMB:
            {
                if(node->isBossDepth())
                    m_pCurrentLevel = new(std::nothrow) TombBossLevel();
                else
                    m_pCurrentLevel = new(std::nothrow) TombLevel();
            }
            break;
        case DT_DWARF_CASTLE:
        case DT_MAGA_TOWER:
        case DT_ORC_FORTRESS:
        case DT_ELF_FOREST:
        case DT_TROLL_TEMPLE:
            
        case DT_BEHOLDER_CASTLE:
        case DT_WARP_SPACE:
        case DT_DRAGON_LAIR:
        case DT_LICH_TOMB:
            break;
        default:
            break;
    }
    if(!m_pCurrentLevel)
        return false;
    m_pCurrentLevel->create();
    m_pCurrentLevel->playBGStandardMusic();
    return true;
}
bool VoxelExplorer::createCameras()
{
    m_pMainCamera = Camera::create();
    if(!m_pMainCamera)
        return false;
    m_pMainCamera->setCameraFlag(CameraFlag::USER1);
    m_p3DLayer->addChild(m_pMainCamera);
    
    m_pScreenCamera = Camera::create();
    if(!m_pScreenCamera)
        return false;
    m_pScreenCamera->setCameraFlag(CameraFlag::USER2);
    m_p2DLayer->addChild(m_pScreenCamera);
    return true;
}
bool VoxelExplorer::createPlayer()
{
    if(!m_pCurrentLevel || !m_p3DLayer)
        return false;
    DungeonNode* node = RandomDungeon::getInstance()->getCurrentDungeonNode();
    if(!node)
        return false;
    
    if(node->isBossDepth() || node->isFirstDepth())
    {
        if(m_bHasDownStairs)
        {
            VoxelExplorer::getInstance()->addParticle3DEffect(Vec3(m_pCurrentLevel->getSpawnPoint().x, -0.5f*TerrainTile::CONTENT_SCALE, -m_pCurrentLevel->getSpawnPoint().y), P3D_PLAYER_TELEPORT);
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("USE_SCROLL");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
    }
    
    m_pPlayer = Player::create("chr_sword.c3b");
    if(!m_pPlayer)
        return false;
    if(!PlayerProperty::getInstance()->refreshAfterCreatePlayer())
    {
        CCLOGERROR("refreshAfterCreatePlayer  failed!");
        return false;
    }
    if(m_bHasDownStairs)
    {
        m_pPlayer->setPosition3D(Vec3(m_pCurrentLevel->getSpawnPoint().x, -0.5f*TerrainTile::CONTENT_SCALE, -m_pCurrentLevel->getSpawnPoint().y));
        if(node->m_Type == DT_CAVE || node->m_Type == DT_TOMB)
            m_pPlayer->setRotation3D(Vec3(0,-90,0));
        else if(node->m_Type == DT_MINES)
            m_pPlayer->setRotation3D(Vec3(0,0,0));
        else
            m_pPlayer->setRotation3D(Vec3(0,90,0));
    }
    else
    {
        m_pPlayer->setPosition3D(Vec3(m_pCurrentLevel->getReturnPoint().x, -0.5f*TerrainTile::CONTENT_SCALE, -m_pCurrentLevel->getReturnPoint().y));
        if(node->m_Type == DT_CAVE || node->m_Type == DT_TOMB)
            m_pPlayer->setRotation3D(Vec3(0,90,0));
        else if(node->m_Type == DT_MINES)
            m_pPlayer->setRotation3D(Vec3(0,0,0));
        else
            m_pPlayer->setRotation3D(Vec3(0,-90,0));
    }
    m_pPlayer->addTerrainTileFlag(TileInfo::ATTACKABLE);
    m_p3DLayer->addChild(m_pPlayer);
    
    m_pMainCamera->setPosition3D(m_pPlayer->getPosition3D() + Vec3(0, 5*TerrainTile::CONTENT_SCALE, 4*TerrainTile::CONTENT_SCALE ));
    m_pMainCamera->lookAt(m_pPlayer->getPosition3D() + Vec3(0,0.5f*TerrainTile::CONTENT_SCALE,0));
    m_pPlayer->setState(Player::PS_IDLE);
    
    return true;
}