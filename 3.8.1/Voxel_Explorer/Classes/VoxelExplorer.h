//
//  VoxelExplorer.h
//  Voxel_Explorer
//
//  Created by wang haibo on 15/9/24.
//
//

#ifndef __Voxel_Explorer__VoxelExplorer__
#define __Voxel_Explorer__VoxelExplorer__

#include "cocos2d.h"
#include "BaseLevel.h"
#include "Player.hpp"
class VoxelExplorer : public cocos2d::Ref
{
    VoxelExplorer();
    ~VoxelExplorer();
public:
    static VoxelExplorer* getInstance();
    bool init(cocos2d::Layer* pMainLayer);
    void update(float delta);
    void destroy();
    
    bool checkMovable();
    void cameraTrackPlayer();
    
    int getDepth() const { return m_nDepth; }
    void setDepth(int depth) { m_nDepth = depth; }
    
    cocos2d::Layer* getMainLayer() const { return m_pMainLayer; }
    cocos2d::Layer* get3DLayer() const { return m_p3DLayer; }
    cocos2d::Layer* getTerrainTilesLayer() const { return m_pTerrainTilesLayer; }
    cocos2d::Layer* getTerrainDecoratorsLayer() const { return m_pTerrainDecoratorsLayer; }
    cocos2d::Layer* get2DLayer() const { return m_p2DLayer; }
    cocos2d::Layer* getHUDLayer() const { return m_pHUDLayer; }
    cocos2d::Layer* getUILayer() const { return m_pUILayer; }
    
    cocos2d::Camera* getMainCamera() const { return m_pMainCamera; }
    cocos2d::Camera* getScreenCamera() const { return m_pScreenCamera; }
    
    Player* getPlayer() const { return m_pPlayer; }
private:
    bool createLayers();
    bool createLevel();
    bool createCameras();
    bool createPlayer();
private:
    int             m_nDepth;
    BaseLevel*      m_pCurrentLevel;

    cocos2d::Layer*                         m_pMainLayer;
    cocos2d::Layer*                         m_p3DLayer;
    cocos2d::Layer*                         m_pTerrainTilesLayer;
    cocos2d::Layer*                         m_pTerrainDecoratorsLayer;
    cocos2d::Layer*                         m_p2DLayer;
    cocos2d::Layer*                         m_pHUDLayer;
    cocos2d::Layer*                         m_pUILayer;
    
    cocos2d::Camera*                        m_pMainCamera;
    cocos2d::Camera*                        m_pScreenCamera;
    
    Player*                                 m_pPlayer;
};

#endif /* defined(__Voxel_Explorer__VoxelExplorer__) */
