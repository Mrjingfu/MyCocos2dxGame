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
#include "StatisticsManager.hpp"
USING_NS_CC;

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
    m_pTerrainTilesLayer = nullptr;
    m_pFakeShadowLayer = nullptr;
    m_pTerrainPortalsLayer = nullptr;
    m_pTerrainDoorsLayer = nullptr;
    m_pUseableItemsLayer = nullptr;
    m_pBossLayer         = nullptr;
    m_pNPCsLayer         = nullptr;
    m_pMonstersLayer     = nullptr;
    m_pPickableItemsLayer= nullptr;
    m_p2DLayer = nullptr;
    m_pHUDLayer = nullptr;
    m_pUILayer = nullptr;
    
    m_pMainCamera = nullptr;
    
    m_pPlayer = nullptr;
}
VoxelExplorer::~VoxelExplorer()
{
}


bool VoxelExplorer::init(Layer* pMainLayer)
{
    if(pMainLayer == nullptr)
        return false;
    m_pMainLayer = pMainLayer;
    ///lwwhb 临时，之后需要加载。
    if(!RandomDungeon::getInstance()->build())
    {
        CCLOGERROR("RandomDungeon build failed!");
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

void VoxelExplorer::destroy()
{
}
void VoxelExplorer::update(float delta)
{
    RandomDungeon::getInstance()->update(delta);
}
std::string VoxelExplorer::getScreenPickDesc(const cocos2d::Vec2& screenPos, std::string& strIcon)
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
                if (item && ray.intersects(item->getAABB())) {
                    return item->getDesc();
                }
            }
        }
        
        if(m_pMonstersLayer)
        {
            for (auto child : m_pMonstersLayer->getChildren())
            {
                BaseMonster* monster = dynamic_cast<BaseMonster*>(child);
                if (monster && ray.intersects(monster->getAABB())) {
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
                if (npc && ray.intersects(npc->getAABB())) {
                    strIcon = npc->getIconRes();
                    return npc->getDesc();
                }
            }
        }
        if(m_pBossLayer)
        {
            for (auto child : m_pBossLayer->getChildren()) {
                BaseBoss* boss = dynamic_cast<BaseBoss*>(child);
                if(boss && ray.intersects(boss->getAABB())){
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
                if (item && ray.intersects(item->getAABB())) {
                    return item->getDesc();
                }
            }
        }
        
        if(m_pTerrainPortalsLayer)
        {
            for (auto child : m_pTerrainPortalsLayer->getChildren())
            {
                BasePortal* portal = dynamic_cast<BasePortal*>(child);
                if (portal && ray.intersects(portal->getAABB())) {
                    return portal->getDesc();
                }
            }
        }
        
        if(m_pTerrainDoorsLayer)
        {
            for (auto child : m_pTerrainDoorsLayer->getChildren())
            {
                BaseDoor* door = dynamic_cast<BaseDoor*>(child);
                if (door && ray.intersects(door->getAABB())) {
                    return door->getDesc();
                }
            }
        }
        
        if(m_pTerrainTilesLayer)
        {
            for (auto child : m_pTerrainTilesLayer->getChildren())
            {
                TerrainTile* tile = dynamic_cast<TerrainTile*>(child);
                if (tile && ray.intersects(tile->getAABB())) {
                    return tile->getDesc();
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
bool VoxelExplorer::checkBossCanAttack(BaseBoss* boss)
{
    if(boss == nullptr || !(boss->isVisible()))
        return false;
    if(m_pPlayer == nullptr || m_pPlayer->getState() == Player::PS_DEATH || m_pPlayer->isStealth())
        return false;
    Vec2 playerPosInMap = m_pPlayer->getPosInMap();
    Vec2 bossPosInMap = boss->getPosInMap();
    if(playerPosInMap.x == bossPosInMap.x && std::abs(playerPosInMap.y - bossPosInMap.y) <= boss->getAttackRange())
        return true;
    else if(playerPosInMap.y == bossPosInMap.y && std::abs(playerPosInMap.x - bossPosInMap.x) <= boss->getAttackRange())
        return true;
    return false;
}
bool VoxelExplorer::trackToPlayer(Actor* tracker, cocos2d::Vec2& nextPos)
{
    if(tracker == nullptr || m_pPlayer == nullptr || m_pCurrentLevel == nullptr || !(tracker->isVisible()))
       return false;
    Vec2 playerPosInMap = m_pPlayer->getPosInMap();
    Vec2 monsterPosInMap = tracker->getPosInMap();
    return m_pCurrentLevel->getNextPathStep(monsterPosInMap, playerPosInMap, nextPos);
}
bool VoxelExplorer::fleeFromPlayer(Actor* tracker, cocos2d::Vec2& nextPos)
{
    if(tracker == nullptr || m_pPlayer == nullptr || m_pCurrentLevel == nullptr || !(tracker->isVisible()))
        return false;
    return true;
}
bool VoxelExplorer::wanderingAround(Actor* tracker, cocos2d::Vec2& nextPos)
{
    if(tracker == nullptr  || m_pCurrentLevel == nullptr || !(tracker->isVisible()))
        return false;
    Vec2 monsterPosInMap = tracker->getPosInMap();
    Vec2 randomPos = m_pCurrentLevel->getRandomPassableTile();
    return m_pCurrentLevel->getNextPathStep(monsterPosInMap, randomPos, nextPos);
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
            if(boss && areaRect.containsPoint(boss->getPosInMap()))
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
        for (const auto& child : m_pMonstersLayer->getChildren())
        {
            BaseMonster* monster = dynamic_cast<BaseMonster*>(child);
            if(monster && areaRect.containsPoint(monster->getPosInMap()) && monster->getState() != BaseMonster::MS_DEATH)
                monster->setVisited(visited);
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
    if(m_pCurrentLevel && m_pPlayer && m_pBossLayer && m_pTerrainDoorsLayer)
    {
        
//        BaseBoss* boss = nullptr;
//        for (const auto& child : m_pBossLayer->getChildren())
//        {
//            boss = dynamic_cast<BaseBoss*>(child);
//            if(boss)
//                break;
//        }
//        if(!boss)
//            return;
//        if(boss->getState() == BaseBoss::BS_DEATH)
//        {
//            for (const auto& child : m_pTerrainDoorsLayer->getChildren())
//            {
//                BaseDoor* door = dynamic_cast<BaseDoor*>(child);
//                if(door)
//                {
//                    Vec2 pos = door->getPosInMap();
//                    if(m_pCurrentLevel->getTerrainTileAreaType(pos.x, pos.y) == Area::AT_BOSS_ROOM)
//                    {
//                        if(door->isMagicLocked())
//                        {
//                            door->setMagicLocked(false);
//                            return;
//                        }
//                    }
//                }
//            }
//        }
//        else
        {
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
                        if(!door->isMagicLocked())
                        {
                            door->setMagicLocked(true);
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_DOOR_MAGIC_CLOSED);
                        }
                        door->setDoorState(BaseDoor::DS_CLOSED);
                        
                        return;
                    }
                }
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
        m_pCurrentLevel->searchAndCheck(playerPosInMap.x, playerPosInMap.y, searchDistance);
    }
}
void VoxelExplorer::addExplosion(const cocos2d::Vec3& pos)
{
    if(m_p3DLayer)
    {
        auto explosion = PUParticleSystem3D::create("explosionSystem.pu");
        explosion->setCameraMask((unsigned short)CameraFlag::USER1);
        explosion->setPosition3D(pos);
        m_p3DLayer->addChild(explosion);
        explosion->startParticleSystem();
    }
}
void VoxelExplorer::generatePickItem(const cocos2d::Vec2& pos, bool generateItem, int copper, int monsterLevel)
{
    if(m_pPickableItemsLayer && m_pCurrentLevel)
    {
        if(copper > 0)
        {
            
            PlayerProperty::getInstance()->addMoney(copper);
            ///声音
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
        float percent1 = 0.3f;
        float percent2 = 0.3f;
        float percent3 = 1.0f - percent1 - percent2;
        AlisaMethod* am = AlisaMethod::create(percent1, percent2, percent3,-1.0, NULL);
        if(am)
        {
            if(am->getRandomIndex() == 0)
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
            else if(am->getRandomIndex() == 1)
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
            ///声音
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
                    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_FOUND_HIDDEN_DOOR);
                    return;
                }
                else if(door->getDoorState() == BaseDoor::DS_CLOSED)
                {
                    if(door->isMagicLocked())
                    {
                        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_DOOR_MAGIC_LOCKED);
                        return;
                    }
                    else
                    {
                        door->setDoorState(BaseDoor::DS_OPENED);
                        if(m_pCurrentLevel)
                            m_pCurrentLevel->updateAreaFogOfWarByPos(door->getPosInMap());
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
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_NO_BOSS_KEY);
                    }
                    else
                    {
                        if(PlayerProperty::getInstance()->useKey(PickableItem::PIT_KEY_ROOM))
                        {
                            door->setDoorState(BaseDoor::DS_CLOSED);
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_USE_ROOM_KEY);
                        }
                        else
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_NO_ROOM_KEY);
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
                            //声音
                            useableItem->setState(UseableItem::UIS_FADEOUT);
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_USE_COPPER_CHEST_KEY);
                        }
                        else
                        {
                            ///声音
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_NO_COPPER_KEY);
                        }
                    }
                    else if(useableItem->getUseableItemType() == UseableItem::UIT_CHEST_SILVER)
                    {
                        if(PlayerProperty::getInstance()->useKey(PickableItem::PIT_KEY_SILVER))
                        {

                            StatisticsManager::getInstance()->addUserableOpenNum(useableItem->getUseableItemType());
                            ///声音
                            useableItem->setState(UseableItem::UIS_FADEOUT);
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_USE_SILVER_CHEST_KEY);
                        }
                        else
                        {
                            ///声音
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_NO_SILVER_KEY);
                        }
                    }
                    else if(useableItem->getUseableItemType() == UseableItem::UIT_CHEST_GOLD)
                    {
                        if(PlayerProperty::getInstance()->useKey(PickableItem::PIT_KEY_GOLD))
                        {

                            StatisticsManager::getInstance()->addUserableOpenNum(useableItem->getUseableItemType());
                            ///声音
                            useableItem->setState(UseableItem::UIS_FADEOUT);
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_USE_GOLD_CHEST_KEY);

                        }
                        else
                        {
                            ///声音
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_NO_GOLD_KEY);
                        }
                    }
                    return;
                }
                else
                {
                    useableItem->setState(UseableItem::UIS_FADEOUT);
                    StatisticsManager::getInstance()->addUserableOpenNum(useableItem->getUseableItemType());
                    return;
                }
            }
        }
    }
    if(m_pNPCsLayer)
    {
        for (const auto& child : m_pUseableItemsLayer->getChildren())
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
        if(trapType == TerrainTile::TT_TOXIC_TRAP)
        {
            StatisticsManager::getInstance()->addTriggerToxicNum(trapType);
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_TRIGGER_TOXIC_TRAP);
            m_pPlayer->addPlayerBuffer(PB_POISONING);
        }
        else if(trapType == TerrainTile::TT_FIRE_TRAP)
        {
            StatisticsManager::getInstance()->addTriggerToxicNum(trapType);
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_TRIGGER_FIRE_TRAP);
            m_pPlayer->addPlayerBuffer(PB_FIRE);
        }
        else if(trapType == TerrainTile::TT_PARALYTIC_TRAP)
        {
            StatisticsManager::getInstance()->addTriggerToxicNum(trapType);
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_TRIGGER_PARALYTIC_TRAP);
            m_pPlayer->addPlayerBuffer(PB_PARALYTIC);
        }
        else if(trapType == TerrainTile::TT_GRIPPING_TRAP)
        {
            StatisticsManager::getInstance()->addTriggerToxicNum(trapType);
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_TRIGGER_GRIPPING_TRAP);
            m_pPlayer->hurtByGrippingTrap();
        }
        else if(trapType == TerrainTile::TT_SUMMONING_TRAP)
        {
            StatisticsManager::getInstance()->addTriggerToxicNum(trapType);
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_TRIGGER_SUMMONING_TRAP);
            if(!m_pCurrentLevel->createSummoningMonsters(mapPos))
                CCLOG("Handle trigger summoning trap failed!");
        }
        else if(trapType == TerrainTile::TT_WEAK_TRAP)
        {
            StatisticsManager::getInstance()->addTriggerToxicNum(trapType);
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_TRIGGER_WEAK_TRAP);
            m_pPlayer->addPlayerBuffer(PB_WEAK);
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
        }
        else if(trapType == TerrainTile::TT_FIRE_TRAP)
        {
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_FOUND_HIDDEN_FIRE_TRAP);
        }
        else if(trapType == TerrainTile::TT_PARALYTIC_TRAP)
        {
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_FOUND_HIDDEN_PARALYTIC_TRAP);
        }
        else if(trapType == TerrainTile::TT_GRIPPING_TRAP)
        {
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_FOUND_HIDDEN_GRIPPING_TRAP);
        }
        else if(trapType == TerrainTile::TT_SUMMONING_TRAP)
        {
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_FOUND_HIDDEN_SUMMONING_TRAP);
        }
        else if(trapType == TerrainTile::TT_WEAK_TRAP)
        {
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_FOUND_HIDDEN_WEAK_TRAP);
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
                    EaseSineOut* colorTo1 = EaseSineOut::create(TintTo::create(0.35f, Color3B(255,150,255)));
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
void VoxelExplorer::handlePlayerHurt(const cocos2d::Vec2& mapPos, MonsterProperty* monsterProperty)
{
    if(!m_pPlayer || !monsterProperty ||m_pPlayer->getState() == Player::PS_DEATH)
        return;
    
    if(m_pPlayer->getPosInMap() != mapPos)
        return m_pPlayer->attackByMonster(monsterProperty, true);
    
    return m_pPlayer->attackByMonster(monsterProperty, false);
}
void VoxelExplorer::handlePlayerHurtByBoss(const cocos2d::Vec2& mapPos, BossProperty* bossProperty)
{
    if(!m_pPlayer || !bossProperty ||m_pPlayer->getState() == Player::PS_DEATH)
        return;
    
    if(m_pPlayer->getPosInMap() != mapPos)
        return m_pPlayer->attackByBoss(bossProperty, true);
    
    return m_pPlayer->attackByBoss(bossProperty, false);
}
void VoxelExplorer::handlePlayerUseScroll(PickableItem::PickableItemType type)
{
    if(!m_pPlayer)
        return;
    switch (type) {
        case PickableItem::PickableItemType::PIT_SCROLL_TELEPORT:
            {
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
void VoxelExplorer::handlePlayerUseStandardPortal()
{
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
    m_pCurrentLevel->showMap(true);
    
    m_pMainCamera->setPosition3D(m_pPlayer->getPosition3D() + Vec3(0, 5*TerrainTile::CONTENT_SCALE, 4*TerrainTile::CONTENT_SCALE ));
    m_pMainCamera->lookAt(m_pPlayer->getPosition3D() + Vec3(0,0.5f*TerrainTile::CONTENT_SCALE,0));
    m_pPlayer->setState(Player::PS_IDLE);
}
void VoxelExplorer::handleUpstairs()
{
    if(RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nCurrentDepth > 1)
    {
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_GO_DOWNSTAIRS);
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
        RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nCurrentDepth += 1;
        auto scene = GameScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }
    else
    {
        ///加载boss房间
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_GO_BOSSROOM);
    }
}

bool VoxelExplorer::createLayers()
{
    m_p3DLayer = Layer3D::create();
    if(!m_p3DLayer)
        return false;
    m_p3DLayer->setCameraMask((unsigned int)CameraFlag::USER1);
    m_pMainLayer->addChild(m_p3DLayer);
    
    m_pTerrainTilesLayer = Layer::create();
    if(!m_pTerrainTilesLayer)
        return false;
    m_pTerrainTilesLayer->setCameraMask((unsigned int)CameraFlag::USER1);
    m_p3DLayer->addChild(m_pTerrainTilesLayer);
    
    m_pFakeShadowLayer = Layer::create();
    if(!m_pFakeShadowLayer)
        return false;
    m_pFakeShadowLayer->setCameraMask((unsigned int)CameraFlag::USER1);
    m_p3DLayer->addChild(m_pFakeShadowLayer);
    
    m_pTerrainPortalsLayer = Layer::create();
    if(!m_pTerrainPortalsLayer)
        return false;
    m_pTerrainPortalsLayer->setCameraMask((unsigned int)CameraFlag::USER1);
    m_p3DLayer->addChild(m_pTerrainPortalsLayer);
    
    m_pTerrainDoorsLayer = Layer::create();
    if(!m_pTerrainDoorsLayer)
        return false;
    m_pTerrainDoorsLayer->setCameraMask((unsigned int)CameraFlag::USER1);
    m_p3DLayer->addChild(m_pTerrainDoorsLayer);
    
    m_pUseableItemsLayer = Layer::create();
    if(!m_pUseableItemsLayer)
        return false;
    m_pUseableItemsLayer->setCameraMask((unsigned int)CameraFlag::USER1);
    m_p3DLayer->addChild(m_pUseableItemsLayer);
    
    m_pBossLayer = Layer::create();
    if(!m_pBossLayer)
        return false;
    m_pBossLayer->setCameraMask((unsigned int)CameraFlag::USER1);
    m_p3DLayer->addChild(m_pBossLayer);
    
    m_pNPCsLayer = Layer::create();
    if(!m_pNPCsLayer)
        return false;
    m_pNPCsLayer->setCameraMask((unsigned int)CameraFlag::USER1);
    m_p3DLayer->addChild(m_pNPCsLayer);
    
    m_pMonstersLayer = Layer::create();
    if(!m_pMonstersLayer)
        return false;
    m_pMonstersLayer->setCameraMask((unsigned int)CameraFlag::USER1);
    m_p3DLayer->addChild(m_pMonstersLayer);
    
    m_pPickableItemsLayer = Layer::create();
    if(!m_pPickableItemsLayer)
        return false;
    m_pPickableItemsLayer->setCameraMask((unsigned int)CameraFlag::USER1);
    m_p3DLayer->addChild(m_pPickableItemsLayer);
    
    m_p2DLayer = Layer::create();
    if(!m_p2DLayer)
        return false;
    m_pMainLayer->addChild(m_p2DLayer);
    
    m_pHUDLayer = Layer::create();
    if (!m_pHUDLayer)
        return false;
    m_p2DLayer->addChild(m_pHUDLayer);
    
    m_pUILayer = Layer::create();
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
                ///for debug
                //m_pCurrentLevel = new(std::nothrow) SewerBossLevel();
            }
            break;
        case DT_PRISON:
            {
                if(node->isBossDepth())
                    m_pCurrentLevel = new(std::nothrow) PrisonBossLevel();
                else
                    m_pCurrentLevel = new(std::nothrow) PrisonLevel();
                ///for debug
                //m_pCurrentLevel = new(std::nothrow) PrisonBossLevel();
            }
            break;
        case DT_FANE:
            {
                if(node->isBossDepth())
                    m_pCurrentLevel = new(std::nothrow) FaneBossLevel();
                else
                    m_pCurrentLevel = new(std::nothrow) FaneLevel();
                // for debug
                //m_pCurrentLevel = new(std::nothrow) FaneBossLevel();
            }
            break;
        case DT_MINES:
            {
                if(node->isBossDepth())
                    m_pCurrentLevel = new(std::nothrow) MineBossLevel();
                else
                    m_pCurrentLevel = new(std::nothrow) MineLevel();
                //for debug
                //m_pCurrentLevel = new(std::nothrow) MineBossLevel();
            }
            break;
        case DT_CAVE:
            {
                if(node->isBossDepth())
                    m_pCurrentLevel = new(std::nothrow) CaveBossLevel();
                else
                    m_pCurrentLevel = new(std::nothrow) CaveLevel();
                // for debug
                //m_pCurrentLevel = new(std::nothrow) CaveBossLevel();
            }
            break;
        case DT_TOMB:
            {
                if(node->isBossDepth())
                    m_pCurrentLevel = new(std::nothrow) TombBossLevel();
                else
                    m_pCurrentLevel = new(std::nothrow) TombLevel();
                ///for debug
                //m_pCurrentLevel = new(std::nothrow) TombBossLevel();
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
    ///lwwhb 临时
    if (!PlayerProperty::getInstance()->initNewPlayer())
        return false;
    ///
    m_pPlayer = Player::create("chr_sword.c3b");
    if(!m_pPlayer)
        return false;
    m_pPlayer->setPosition3D(Vec3(m_pCurrentLevel->getSpawnPoint().x, -0.5f*TerrainTile::CONTENT_SCALE, -m_pCurrentLevel->getSpawnPoint().y));
    if(node->m_Type == DT_CAVE || node->m_Type == DT_TOMB)
        m_pPlayer->setRotation3D(Vec3(0,-90,0));
    else if(node->m_Type == DT_MINES)
        m_pPlayer->setRotation3D(Vec3(0,0,0));
    else
        m_pPlayer->setRotation3D(Vec3(0,90,0));
    m_pPlayer->addTerrainTileFlag(TileInfo::ATTACKABLE);
    m_p3DLayer->addChild(m_pPlayer);
    
    m_pMainCamera->setPosition3D(m_pPlayer->getPosition3D() + Vec3(0, 5*TerrainTile::CONTENT_SCALE, 4*TerrainTile::CONTENT_SCALE ));
    m_pMainCamera->lookAt(m_pPlayer->getPosition3D() + Vec3(0,0.5f*TerrainTile::CONTENT_SCALE,0));
    m_pPlayer->setState(Player::PS_IDLE);
    return true;
}