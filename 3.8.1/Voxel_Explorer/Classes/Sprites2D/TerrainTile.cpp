//
//  TerrainTile.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/8.
//
//

#include "TerrainTile.hpp"
USING_NS_CC;

TerrainTile* TerrainTile::create(TileType type)
{
    auto tile = new (std::nothrow) TerrainTile();
    std::string texName;
    switch (type) {
        case TT_STANDARD:
            texName = "tile_brick.png";
            break;
        default:
            break;
    }
    if (tile && tile->initWithFile(texName))
    {
        tile->setCameraMask((unsigned int)CameraFlag::USER1);
        tile->autorelease();
        return tile;
    }
    CC_SAFE_DELETE(tile);
    return nullptr;
}
TerrainTile::TerrainTile()
{
    m_Type = TT_UNKNOWN;
}
TerrainTile::~TerrainTile()
{
}