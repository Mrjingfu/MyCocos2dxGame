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
    m_pItemsLayer        = nullptr;
    m_pMonstersLayer     = nullptr;
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
bool VoxelExplorer::checkMovable()
{
    if(!m_pCurrentLevel || !m_pPlayer)
        return false;
    return m_pCurrentLevel->checkMovable(m_pPlayer);
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
void VoxelExplorer::searchAndCheck()    ///侦查
{
}
void VoxelExplorer::handlDoor(const cocos2d::Vec2& mapPos)
{
    if(m_pTerrainDoorsLayer && m_pPlayer)
    {
        for (const auto& child : m_pTerrainDoorsLayer->getChildren())
        {
            BaseDoor* door = static_cast<BaseDoor*>(child);
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
void VoxelExplorer::handlTriggerTrap(const cocos2d::Vec2& mapPos)     ///处罚机关
{
}
bool VoxelExplorer::createLayers()
{
    m_p3DLayer = Layer::create();
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
    
    m_pItemsLayer = Layer::create();
    if(!m_pItemsLayer)
        return false;
    m_pItemsLayer->setCameraMask((unsigned int)CameraFlag::USER1);
    m_p3DLayer->addChild(m_pItemsLayer);
    
    m_pMonstersLayer = Layer::create();
    if(!m_pMonstersLayer)
        return false;
    m_pMonstersLayer->setCameraMask((unsigned int)CameraFlag::USER1);
    m_p3DLayer->addChild(m_pMonstersLayer);
    
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
    DirectionLight* directionLight = DirectionLight::create(Vec3(-2, -4, -3), Color3B(50, 0, 50));
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