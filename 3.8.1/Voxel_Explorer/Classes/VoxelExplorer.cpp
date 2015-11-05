//
//  VoxelExplorer.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/9/24.
//
//

#include "VoxelExplorer.h"
#include "SewerLevel.hpp"
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
#include "Particle3D/CCParticleSystem3D.h"
#include "Particle3D/PU/CCPUParticleSystem3D.h"
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
    m_pTerrainDoorsLayer = nullptr;
    m_pUseableItemsLayer = nullptr;
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
    if(!RandomDungeon::getInstance()->build())
    {
        CCLOGERROR("RandomDungeon build failed!");
        return false;
    }
    if (!LevelResourceManager::getInstance()->initLevelRes()) {
        CCLOGERROR("load level resource failed!");
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
}
void VoxelExplorer::destroy()
{
    LevelResourceManager::getInstance()->clearLevelRes();
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
        cocos2d::Size size = m_pPlayer->getContentSize();
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
bool VoxelExplorer::checkMonsterAlert(BaseMonster* monster)
{
    if(monster == nullptr || !(monster->isVisible()))
        return false;
    if(m_pPlayer == nullptr || m_pPlayer->getState() == Player::PS_DEATH || m_pPlayer->isStealth())
        return false;
    Vec2 playerPosInMap = m_pPlayer->getPosInMap();
    Vec2 monsterPosInMap = monster->getPosInMap();
    if(std::abs(playerPosInMap.x - monsterPosInMap.x) > monster->getMonsterFOV() && std::abs(playerPosInMap.y - monsterPosInMap.y) > monster->getMonsterFOV())
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
    CCASSERT(playerPosInMap != monsterPosInMap, "");
    if(playerPosInMap.x == monsterPosInMap.x && std::abs(playerPosInMap.y - monsterPosInMap.y) <= monster->getAttackRange())
        return true;
    else if(playerPosInMap.y == monsterPosInMap.y && std::abs(playerPosInMap.x - monsterPosInMap.x) <= monster->getAttackRange())
        return true;
    return false;
}
void VoxelExplorer::attackedByMonster(BaseMonster* monster)
{
    if(m_pPlayer == nullptr || m_pPlayer->getState() == Player::PS_DEATH)
        return;
}
bool VoxelExplorer::trackToPlayer(BaseMonster* monster, cocos2d::Vec2& nextPos)
{
    if(monster == nullptr || m_pPlayer == nullptr || m_pCurrentLevel == nullptr || !(monster->isVisible()))
       return false;
    Vec2 playerPosInMap = m_pPlayer->getPosInMap();
    Vec2 monsterPosInMap = monster->getPosInMap();
    return m_pCurrentLevel->getNextPathStep(monsterPosInMap, playerPosInMap, nextPos);
}
bool VoxelExplorer::fleeFromPlayer(BaseMonster* monster, cocos2d::Vec2& nextPos)
{
    if(monster == nullptr || m_pPlayer == nullptr || !(monster->isVisible()))
        return false;
    return true;
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
    
    if(m_pMonstersLayer)
    {
        for (const auto& child : m_pMonstersLayer->getChildren())
        {
            Actor* monster = dynamic_cast<Actor*>(child);
            if(monster && areaRect.containsPoint(monster->getPosInMap()))
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
void VoxelExplorer::searchAndCheck()    ///侦查
{
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

void VoxelExplorer::handleDoor(const cocos2d::Vec2& mapPos)
{
    if(m_pTerrainDoorsLayer && m_pPlayer)
    {
        for (const auto& child : m_pTerrainDoorsLayer->getChildren())
        {
            BaseDoor* door = dynamic_cast<BaseDoor*>(child);
            if(door && door->getPosInMap() == mapPos)
            {
                if(door->getDoorState() == BaseDoor::DS_HIDE)
                {
                    door->setDoorState(BaseDoor::DS_CLOSED);
                    return;
                }
                else if(door->getDoorState() == BaseDoor::DS_CLOSED)
                {
                    door->setDoorState(BaseDoor::DS_OPENED);
                    if(m_pCurrentLevel)
                        m_pCurrentLevel->updateAreaFogOfWarByPos(door->getPosInMap());
                    return;
                }
                else if(door->getDoorState() == BaseDoor::DS_LOCKED)
                {
                    ////检查角色钥匙如果有责开启
                    door->setDoorState(BaseDoor::DS_CLOSED);
                    return;
                }
            }
        }

    }
}
void VoxelExplorer::handleTriggerTrap(const cocos2d::Vec2& mapPos)     ///触发机关
{
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
                    if(PlayerProperty::getInstance()->addItemToBag(item->getPickableItemType()))
                    {
                        item->setState(PickableItem::PIS_FADEOUT);
                        return;
                    }
                }
            }
        }
    }
}
void VoxelExplorer::handleMonsterHurt(const cocos2d::Vec2& mapPos)
{
    if(m_pMonstersLayer && m_pPlayer)
    {
        for (const auto& child : m_pMonstersLayer->getChildren())
        {
            BaseMonster* monster = dynamic_cast<BaseMonster*>(child);
            if(monster && monster->getPosInMap() == mapPos)
            {
                if(monster->getState() != BaseMonster::MS_DEATH)
                {
                    monster->attackedByPlayer();
                    return;
                }
            }
            else
            {
                BaseBoss* boss = dynamic_cast<BaseBoss*>(child);
                if(boss && boss->getPosInMap() == mapPos)
                {
                    if(boss->getState() != BaseBoss::BS_DEATH)
                    {
                        boss->attackedByPlayer();
                        return;
                    }
                }
            }
        }
    }
}
void VoxelExplorer::handlePlayerHurt(const cocos2d::Vec2& mapPos, MonsterProperty* monsterProperty)
{
    if(!m_pPlayer || m_pPlayer->getPosInMap() != mapPos)
        return;
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
    AmbientLight* ambLight = AmbientLight::create(Color3B(50, 50, 50));
    if(!ambLight)
        return false;
    ambLight->setLightFlag(LightFlag::LIGHT1);
    m_p3DLayer->addChild(ambLight);
    
    DirectionLight* directionLight = DirectionLight::create(Vec3(-2, -4, -3), Color3B(50, 50, 50));
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
        case DT_PRISON:
        case DT_FANE:
        case DT_MINES:
        case DT_CAVE:
        case DT_TOMB:
            
        case DT_DWARF_CASTLE:
        case DT_MAGA_TOWER:
        case DT_ORC_FORTRESS:
        case DT_ELF_FOREST:
        case DT_TROLL_TEMPLE:
            
        case DT_BEHOLDER_CASTLE:
        case DT_WARP_SPACE:
        case DT_DRAGON_LAIR:
        case DT_LICH_TOMB:
            m_pCurrentLevel = new(std::nothrow) SewerLevel();
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
    m_pPlayer = Player::create("chr_sword.c3b");
    if(!m_pPlayer)
        return false;
    cocos2d::Size size = m_pPlayer->getContentSize();
    m_pPlayer->setPosition3D(Vec3(m_pCurrentLevel->getSpawnPoint().x, -0.5f*TerrainTile::CONTENT_SCALE, -m_pCurrentLevel->getSpawnPoint().y));
    m_pPlayer->setRotation3D(Vec3(0,90,0));
    m_p3DLayer->addChild(m_pPlayer);
    
    m_pMainCamera->setPosition3D(m_pPlayer->getPosition3D() + Vec3(0, 5*TerrainTile::CONTENT_SCALE, 4*TerrainTile::CONTENT_SCALE ));
    m_pMainCamera->lookAt(m_pPlayer->getPosition3D() + Vec3(0,0.5f*TerrainTile::CONTENT_SCALE,0));
    m_pPlayer->setState(Player::PS_IDLE);
    return true;
}