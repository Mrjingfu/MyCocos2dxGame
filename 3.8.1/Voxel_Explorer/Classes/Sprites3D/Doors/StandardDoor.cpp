//
//  StandardDoor.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/13.
//
//

#include "StandardDoor.hpp"
USING_NS_CC;
StandardDoor* StandardDoor::create()
{
    auto tile = new (std::nothrow) StandardDoor();
    if (tile && tile->initWithFile("door.c3b"))
    {
        tile->setCameraMask((unsigned int)CameraFlag::USER1);
        tile->autorelease();
        return tile;
    }
    CC_SAFE_DELETE(tile);
    return nullptr;
}
StandardDoor::StandardDoor()
{
}
StandardDoor::~StandardDoor()
{
}
bool StandardDoor::createFakeDoor(TerrainTile::TileType type)
{
    return true;
}