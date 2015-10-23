//
//  TerrainTile.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/8.
//
//

#include "TerrainTile.hpp"
#include "LevelResourceManager.h"
USING_NS_CC;
const char* TERRAIN_TILES_NAME[] = {
    "TTN_CHASM",
    "TTN_STANDARD",
    "TTN_WALL",
    "TTN_ENTRANCE",
    "TTN_EXIT",
    "TTN_TUNNEL",
    "TTN_DOOR",
    "TTN_OPENED_DOOR"
    "TTN_LOCKED_DOOR",
    "TTN_SECRET_DOOR",
    
    "TTN_TOXIC_TRAP",
    "TTN_HIDE_TOXIC_TRAP",
    "TTN_FIRE_TRAP",
    "TTN_HIDE_FIRE_TRAP",
    "TTN_PARALYTIC_TRAP",
    "TTN_HIDE_PARALYTIC_TRAP",
    "TTN_GRIPPING_TRAP",
    "TTN_HIDE_GRIPPING_TRAP",
    "TTN_SUMMONING_TRAP",
    "TTN_HIDE_SUMMONING_TRAP",
    "TTN_WEAK_TRAP",
    "TTN_HIDE_WEAK_TRAP",
    
    "TTN_MAX"
};

TerrainTile* TerrainTile::create(TileType type)
{
    auto tile = new (std::nothrow) TerrainTile();
    if (tile && tile->initWithFile("16x16x16.c3b"))
    {
        std::string texName = LevelResourceManager::getInstance()->getTerrainTileRes(TERRAIN_TILES_NAME[type]);
        if(!texName.empty())
        {
            auto tex = Director::getInstance()->getTextureCache()->addImage(texName);
            if(tex)
                tex->setAliasTexParameters();
            tile->setTexture(tex);
        }
        tile->setCameraMask((unsigned int)CameraFlag::USER1);
        tile->setLightMask((unsigned int)LightFlag::LIGHT0);
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