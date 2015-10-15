//
//  StandardDoor.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/13.
//
//

#include "StandardDoor.hpp"
USING_NS_CC;
StandardDoor* StandardDoor::create(bool show)
{
    auto tile = new (std::nothrow) StandardDoor();
    if (tile && tile->initWithFile("16x16x16.c3b"))
    {
        tile->setTexture("tile_wall_1.png");
        tile->setCameraMask((unsigned int)CameraFlag::USER1);
        tile->setLightMask((unsigned int)LightFlag::LIGHT0);
        tile->setVisible(show);
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
bool StandardDoor::createFakeDoor()
{
    m_pFakeDoor = Sprite3D::create("door.c3b");
    if(!m_pFakeDoor)
        return false;
    m_pFakeDoor->setCameraMask((unsigned int)CameraFlag::USER1);
    m_pFakeDoor->setPosition3D(Vec3(getPositionX(), -TerrainTile::CONTENT_SCALE, getPositionZ()));
    this->getParent()->addChild(m_pFakeDoor);
    return true;
}