//
//  SmallPortal.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/11/20.
//
//

#include "SmallPortal.hpp"
#include "OutlineEffect3D.h"
#include "UtilityHelper.h"
USING_NS_CC;
SmallPortal* SmallPortal::create(bool canUse)
{
    auto portal = new (std::nothrow) SmallPortal();
    if (portal && portal->initWithFile("8x8x8.c3b") && portal->createFakeShadow())
    {
        portal->m_bIsCanUse = canUse;
        portal->setScale(0.6f);
        portal->setRotation3D(Vec3(0,45,55));
        portal->setCameraMask((unsigned int)CameraFlag::USER1);
        portal->setLightMask((unsigned int)LightFlag::LIGHT0);
        
        OutlineEffect3D* outline = OutlineEffect3D::create();
        outline->setOutlineColor(Vec3(1.0f, 1.0f, 1.0f));
        outline->setOutlineWidth(0.03f);
        portal->addEffect(outline, 1);
        
        if(canUse)
        {
            Color3B randomColor = UtilityHelper::randomColor(500,80);
            portal->setColor(randomColor);
            RepeatForever* repeat = RepeatForever::create(RotateBy::create(1.0f, Vec3(-90, 90, 0)));
            portal->runAction(repeat);
        }
        
        portal->autorelease();
        return portal;
    }
    CC_SAFE_DELETE(portal);
    return nullptr;
}
SmallPortal::SmallPortal()
{
    m_Type = PT_SMALL;
}
SmallPortal::~SmallPortal()
{
}
bool SmallPortal::createCenterModel(bool canUse, OutlineEffect3D* outline)
{
    return true;
}