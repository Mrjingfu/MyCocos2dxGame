//
//  VoxelExplorer.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/9/24.
//
//

#include "VoxelExplorer.h"
#include "TombLevel.h"
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
}
VoxelExplorer::~VoxelExplorer()
{
}


bool VoxelExplorer::init(Layer* pMainLayer)
{
    if(pMainLayer == nullptr)
        return false;
    m_pMainLayer = pMainLayer;
    
    if(!createLevel())
    {
        CCLOG("Create level failed!");
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