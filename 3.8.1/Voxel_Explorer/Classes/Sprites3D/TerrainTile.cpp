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
        case TT_DOOR:
        case TT_OPENED_DOOR:
        case TT_LOCKED_DOOR:
        case TT_SECRET_DOOR:
            texName = "tile_standard_1.png";
            break;
        case TT_WALL:
            texName = "tile_wall_1.png";
            break;
        case TT_ENTRANCE:
            texName = "tile_entrance_1.png";
            break;
        case TT_EXIT:
            texName = "tile_exit_1.png";
            break;
        case TT_TUNNEL:
            texName = "tile_tunnel_1.png";
            break;
        case TT_TOXIC_TRAP:
        case TT_HIDE_TOXIC_TRAP:
            texName = "tile_toxic_trap.png";
            break;
        case TT_FIRE_TRAP:
        case TT_HIDE_FIRE_TRAP:
            texName = "tile_fire_trap.png";
            break;
        case TT_PARALYTIC_TRAP:
        case TT_HIDE_PARALYTIC_TRAP:
            texName = "tile_paralytic_trap.png";
            break;
        case TT_GRIPPING_TRAP:
        case TT_HIDE_GRIPPING_TRAP:
            texName = "tile_gripping_trap.png";
            break;
        case TT_SUMMONING_TRAP:
        case TT_HIDE_SUMMONING_TRAP:
            texName = "tile_summoning_trap.png";
            break;
        case TT_WEAK_TRAP:
        case TT_HIDE_WEAK_TRAP:
            texName = "tile_weak_trap.png";
            break;
        default:
            break;
    }
    if (tile && tile->initWithFile("16x16x16.c3b"))
    {
        auto tex = Director::getInstance()->getTextureCache()->addImage(texName);
        if(tex)
            tex->setAliasTexParameters();
        tile->setTexture(tex);
        tile->setCameraMask((unsigned int)CameraFlag::USER1);
        tile->autorelease();
        return tile;
    }
    CC_SAFE_DELETE(tile);
    return nullptr;
}
TerrainTile::TerrainTile()
{
    m_Type = TT_CHASM;
}
TerrainTile::~TerrainTile()
{
}