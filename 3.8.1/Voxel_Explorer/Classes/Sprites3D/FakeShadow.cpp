//
//  FakeShadow.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/11/25.
//
//

#include "FakeShadow.hpp"
#include "TerrainTile.hpp"
USING_NS_CC;

FakeShadow* FakeShadow::create()
{
    auto shadow = new (std::nothrow) FakeShadow();
    if (shadow && shadow->initWithFile("fakeshadow.c3b"))
    {
        shadow->_contentSize = shadow->getBoundingBox().size;
        shadow->setCameraMask((unsigned int)CameraFlag::USER1);
        shadow->setLightMask(((unsigned int)LightFlag::LIGHT0));
        //shadow->setForceDepthWrite(true);
        shadow->autorelease();
        return shadow;
    }
    CC_SAFE_DELETE(shadow);
    return nullptr;
}
FakeShadow::FakeShadow()
{
}
FakeShadow::~FakeShadow()
{
}
Vec2 FakeShadow::getPosInMap()
{
    return Vec2( (int)(getPositionX()/TerrainTile::CONTENT_SCALE+0.5f), int(-getPositionZ() /TerrainTile::CONTENT_SCALE+0.5f));
}
void FakeShadow::setVisited(bool visited)
{
    setVisible(visited);
    unsigned int lightmask = getLightMask();
    if (visited)
        lightmask = lightmask | (unsigned int)LightFlag::LIGHT1;
    else
        lightmask = lightmask &~ (unsigned int)LightFlag::LIGHT1;
    setLightMask(lightmask);
}