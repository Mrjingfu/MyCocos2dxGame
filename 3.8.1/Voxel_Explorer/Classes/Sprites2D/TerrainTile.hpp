//
//  TerrainTile.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/8.
//
//

#ifndef TerrainTile_hpp
#define TerrainTile_hpp

#include "cocos2d.h"
class TerrainTile : public cocos2d::Sprite
{
public:
    typedef enum
    {
        TT_UNKNOWN = 0,
        TT_STANDARD,
        TT_MAX
    }
    TileType;
    static const int CONTENT_SCALE = 16;
    static TerrainTile* create(TileType type);
    TerrainTile();
    virtual ~TerrainTile();
    
    TileType getType() const { return m_Type; }
    void setType(TileType type) { m_Type = type; }
protected:
    TileType        m_Type;
};

#endif /* TerrainTile_hpp */
