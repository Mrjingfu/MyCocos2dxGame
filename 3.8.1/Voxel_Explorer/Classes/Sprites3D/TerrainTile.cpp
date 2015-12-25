//
//  TerrainTile.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/8.
//
//

#include "TerrainTile.hpp"
#include "LevelResourceManager.h"
#include "RandomDungeon.hpp"
#include "UtilityHelper.h"
#include "VoxelExplorer.h"
USING_NS_CC;
const std::string TERRAIN_TILES_NAME[] = {
    "TTN_CHASM",
    "TTN_STANDARD",
    "TTN_WALL",
    "TTN_ENTRANCE",
    "TTN_EXIT",
    "TTN_STANDARD_PORTAL", ///标准传送门
    "TTN_SMALL_PORTAL",    ///小传送门
    "TTN_TUNNEL",
    "TTN_DOOR",
    "TTN_OPENED_DOOR",
    "TTN_LOCKED_DOOR",
    "TTN_LOCKED_BOSS_DOOR",
    "TTN_LOCKED_MAGIC_DOOR",
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
        if((type == TerrainTile::TT_ENTRANCE) && (RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nCurrentDepth == 1))
            texName = LevelResourceManager::getInstance()->getTerrainTileRes(TERRAIN_TILES_NAME[TerrainTile::TT_STANDARD]);
        else if((type == TerrainTile::TT_EXIT) && (RandomDungeon::getInstance()->getCurrentDungeonNode()->isLastDepth()))
            texName = LevelResourceManager::getInstance()->getTerrainTileRes(TERRAIN_TILES_NAME[TerrainTile::TT_STANDARD]);
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
}
TerrainTile::~TerrainTile()
{
}

std::string TerrainTile::getDesc()
{
    return VoxelExplorer::getInstance()->getCurrentLevel()->getTerrainTileInfoDesc(getPosInMap().x, getPosInMap().y);
}
void TerrainTile::setVisited(bool visited)
{
    setVisible(visited);
    unsigned int lightmask = getLightMask();
    if (visited)
        lightmask = lightmask | (unsigned int)LightFlag::LIGHT1;
    else
        lightmask = lightmask &~ (unsigned int)LightFlag::LIGHT1;
    setLightMask(lightmask);
}
cocos2d::Vec2 TerrainTile::getPosInMap()
{
    return Vec2( (int)(getPositionX()/TerrainTile::CONTENT_SCALE), int(-getPositionZ() /TerrainTile::CONTENT_SCALE));
}