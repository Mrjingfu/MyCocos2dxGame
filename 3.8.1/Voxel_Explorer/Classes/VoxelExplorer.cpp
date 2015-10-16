//
//  VoxelExplorer.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/9/24.
//
//

#include "VoxelExplorer.h"
#include "TombLevel.h"
#include "TerrainTile.hpp"
#include "BaseDoor.hpp"
#include "LevelResourceManager.h"
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
    m_nDepth = 1;
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
    
    if (!LevelResourceManager::getInstance()->initLevelRes(Value(m_nDepth).asString())) {
        CCLOG("load level resource failed!");
        return false;
    }
    
    if(!createLayers())
    {
        CCLOG("Create layers failed!");
        return false;
    }
    if(!createLights())
    {
        CCLOG("Create lights failed!");
        return false;
    }
    if(!createCameras())
    {
        CCLOG("Create cameras failed!");
        return false;
    }
    if(!createLevel())
    {
        CCLOG("Create level failed!");
        return false;
    }
    if(!createPlayer())
    {
        CCLOG("Create Player failed!");
        return false;
    }
    return true;
}
void VoxelExplorer::update(float delta)
{
}
void VoxelExplorer::destroy()
{
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
    switch (m_nDepth) {
        case 1:
            m_pCurrentLevel = new(std::nothrow) TombLevel();
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