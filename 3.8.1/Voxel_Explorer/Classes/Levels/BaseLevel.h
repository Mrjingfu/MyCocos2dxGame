//
//  BaseLevel.h
//  Voxel_Explorer
//
//  Created by wang haibo on 15/9/24.
//
//

#ifndef __Voxel_Explorer__BaseLevel__
#define __Voxel_Explorer__BaseLevel__

#include "cocos2d.h"
class BaseLevel : public cocos2d::Ref
{
protected:
    BaseLevel();
public:
    typedef enum{
        LT_STANDARD,
        LT_MAX
    }
    LEVEL_TYPE;
    
    typedef enum{
        LBT_NONE = 0,
        LBT_CHASM,          ///鸿沟
        LBT_MAX
    }
    LEVEL_BOUNDARY_TYPE;
    
    static const int WIDTH = 32;
    static const int HEIGHT = 48;
    static const int LENGTH = WIDTH*HEIGHT;
    
    void create();
    
    LEVEL_TYPE getLevelType() const;
    void setLevelType(LEVEL_TYPE type);
    
    cocos2d::Vec2 getSpawnPoint() const { return  m_spawnPoint; }
protected:
    virtual bool build() = 0;
    virtual void decorate() = 0;
    virtual void createMobs() = 0;
    virtual void createItems() = 0;

    virtual void showDebug(bool show) = 0;
protected:
    LEVEL_TYPE           m_Type;
    LEVEL_BOUNDARY_TYPE  m_BoundaryType;
    
    cocos2d::Vec2        m_spawnPoint;
    
    cocos2d::DrawNode*   m_pDebugDrawNode;
};

#endif /* defined(__Voxel_Explorer__BaseLevel__) */
