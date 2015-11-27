//
//  NpcDataManager.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/11/26.
//
//

#include "NpcDataManager.hpp"
USING_NS_CC;
NpcDataManager* g_pNpcDataManagerInstance = nullptr;
NpcDataManager* NpcDataManager::getInstance()
{
    if( g_pNpcDataManagerInstance == nullptr )
        g_pNpcDataManagerInstance = new NpcDataManager();
    
    return g_pNpcDataManagerInstance;
}
NpcDataManager::NpcDataManager()
{
}
NpcDataManager::~NpcDataManager()
{
}
bool NpcDataManager::initNpcData()
{
    return true;
}
void NpcDataManager::clearNpcData()
{
}