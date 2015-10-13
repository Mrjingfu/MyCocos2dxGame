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
#include "Area.h"
struct TileInfo
{
    TerrainTile::TileType m_Type;
    Area::AREA_TYPE     m_AreaType;
    bool    m_bVisited;
    bool    m_bMapped;
    int     m_nX;
    int     m_nY;
    TileInfo()
    {
        m_Type = TerrainTile::TT_CHASM;
        m_AreaType = Area::AT_UNKNOWN;
        m_bVisited = false;
        m_bMapped = false;
        m_nX = -1;
        m_nY = -1;
    }
};
class BaseLevel : public cocos2d::Ref
{
    friend class Area;
protected:
    BaseLevel();
public:
    typedef enum{
        LT_STANDARD,
        LT_MAX
    }
    LEVEL_TYPE;
    
    typedef enum{
        LFT_NONE = 0,
        LFT_CHASM,          ///鸿沟
        LFT_MAX
    }
    LEVEL_FEELING_TYPE;
    
    void create();
    
    LEVEL_TYPE getLevelType() const;
    void setLevelType(LEVEL_TYPE type);
    
    int getWidth() const { return m_nWidth; }
    int getHeight() const { return m_nHeight; }
    int getLength() const { return m_nLenght; }
    
    cocos2d::Vec2 getSpawnPoint() const { return  m_spawnPoint; }
    
    void generateTerrainTiles(int x, int y , int width, int height, TerrainTile::TileType tileType, Area::AREA_TYPE areaType);
    
protected:
    virtual bool build() = 0;
    virtual bool createRenderObjs() = 0;
    virtual bool decorate() = 0;
    virtual bool createMobs() = 0;
    virtual bool createItems() = 0;

    virtual void showMap(bool show) = 0;
protected:
    LEVEL_TYPE           m_Type;
    LEVEL_FEELING_TYPE   m_FeelingType;
    std::vector<TileInfo> m_Map;
    
    cocos2d::Vec2        m_spawnPoint;
    
    cocos2d::DrawNode*   m_pMapDrawNode;
    cocos2d::DrawNode*   m_pDebugDrawNode;
    
    int                 m_nWidth;
    int                 m_nHeight;
    int                 m_nLenght;
};

#endif /* defined(__Voxel_Explorer__BaseLevel__) */
