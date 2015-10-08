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
    m_pTerrainDecoratorsLayer = nullptr;
    m_p2DLayer = nullptr;
    m_pHUDLayer = nullptr;
    m_pUILayer = nullptr;
    
    m_pMainCamera = nullptr;
    
    m_pTestPlayer = nullptr;
}
VoxelExplorer::~VoxelExplorer()
{
}


bool VoxelExplorer::init(Layer* pMainLayer)
{
    if(pMainLayer == nullptr)
        return false;
    m_pMainLayer = pMainLayer;
    
    if(!createLayers())
    {
        CCLOG("Create layers failed!");
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
    
    m_pTerrainDecoratorsLayer = Layer::create();
    if(!m_pTerrainDecoratorsLayer)
        return false;
    m_pTerrainDecoratorsLayer->setCameraMask((unsigned int)CameraFlag::USER1);
    m_p3DLayer->addChild(m_pTerrainDecoratorsLayer);
    
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
bool VoxelExplorer::createPlayer()
{
    if(!m_pCurrentLevel || !m_p3DLayer)
        return false;
    m_pTestPlayer = TestPlayer::create("girl1.c3b");
    if(!m_pTestPlayer)
        return false;
    m_pTestPlayer->setPosition3D(Vec3(m_pCurrentLevel->getSpawnPoint().x, m_pCurrentLevel->getSpawnPoint().y, 0));
    m_p3DLayer->addChild(m_pTestPlayer);
                                 
    m_pMainCamera = Camera::create();
    if(!m_pMainCamera)
        return false;
    m_pMainCamera->setCameraFlag(CameraFlag::USER1);
    m_p3DLayer->addChild(m_pMainCamera);
    
    m_pMainCamera->setPosition3D(Vec3(m_pCurrentLevel->getSpawnPoint().x, m_pCurrentLevel->getSpawnPoint().y, 0) + Vec3(0, -10*cosf(M_PI/3)*TerrainTile::CONTENT_SCALE, TerrainTile::CONTENT_SCALE*10*sinf(M_PI/3)));
    m_pMainCamera->lookAt(m_pTestPlayer->getPosition3D());
    
    //    auto size = Director::getInstance()->getWinSize();
    //    float zeye = Director::getInstance()->getZEye();
    //    m_pMainCamera = Camera::createPerspective(60, (GLfloat)size.width / size.height, 10, zeye + size.height);
    //    if(!m_pMainCamera)
    //        return false;
    //
    //    Vec3 eye = m_pGameLayer->getPlayer()->getPosition3D() + m_CamOffset;
    //    Vec3 center = m_pGameLayer->getPlayer()->getPosition3D();
    //
    //    m_pMainCamera->setPosition3D(eye);
    //    m_pMainCamera->lookAt(center, Vec3::UNIT_Y);
    //
    //    m_pMainCamera->setCameraFlag(CameraFlag::USER1);
    //    pMainLayer->addChild(m_pMainCamera);
    return true;
}