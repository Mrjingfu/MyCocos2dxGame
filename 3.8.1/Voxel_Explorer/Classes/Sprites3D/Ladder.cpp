//
//  Ladder.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/11/25.
//
//

#include "Ladder.hpp"
#include "TerrainTile.hpp"
USING_NS_CC;

Ladder* Ladder::create()
{
    auto shadow = new (std::nothrow) Ladder();
    if (shadow && shadow->initWithFile("ladder.c3b"))
    {
        shadow->_contentSize = shadow->getBoundingBox().size;
        shadow->setCameraMask((unsigned int)CameraFlag::USER1);
        shadow->setLightMask(((unsigned int)LightFlag::LIGHT0));
        shadow->autorelease();
        return shadow;
    }
    CC_SAFE_DELETE(shadow);
    return nullptr;
}
Ladder::Ladder()
{
}
Ladder::~Ladder()
{
}
Vec2 Ladder::getPosInMap()
{
    return Vec2( (int)(getPositionX()/TerrainTile::CONTENT_SCALE+0.5f), int(-getPositionZ() /TerrainTile::CONTENT_SCALE+0.5f));
}
void Ladder::setVisited(bool visited)
{
    setVisible(visited);
    unsigned int lightmask = getLightMask();
    if (visited)
        lightmask = lightmask | (unsigned int)LightFlag::LIGHT1;
    else
        lightmask = lightmask &~ (unsigned int)LightFlag::LIGHT1;
    setLightMask(lightmask);
}