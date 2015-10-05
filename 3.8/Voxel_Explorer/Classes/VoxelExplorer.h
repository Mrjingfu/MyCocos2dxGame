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
class VoxelExplorer : public cocos2d::Ref
{
    VoxelExplorer();
    ~VoxelExplorer();
public:
    static VoxelExplorer* getInstance();
    bool init(cocos2d::Layer* pMainLayer);
    void update(float delta);
    void destroy();
    
    bool createLevel();
    
    cocos2d::Layer* getMainLayer() const { return m_pMainLayer; }
private:
    int             m_nDepth;
    BaseLevel*      m_pCurrentLevel;

    cocos2d::Layer*                         m_pMainLayer;
};

#endif /* defined(__Voxel_Explorer__VoxelExplorer__) */
