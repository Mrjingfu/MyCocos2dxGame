//
//  StandardPortal.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/11/20.
//
//

#include "StandardPortal.hpp"
#include "OutlineEffect3D.h"
#include "UtilityHelper.h"
#include "VoxelExplorer.h"
USING_NS_CC;
StandardPortal* StandardPortal::create(bool canUse)
{
    auto portal = new (std::nothrow) StandardPortal();
    if (portal && portal->initWithFile("8x8x8.c3b") && portal->createFakeShadow())
    {
        portal->m_bIsCanUse = canUse;
        portal->setRotation3D(Vec3(0,45,55));
        portal->setCameraMask((unsigned int)CameraFlag::USER1);
        portal->setLightMask((unsigned int)LightFlag::LIGHT0);
        
        OutlineEffect3D* outline = OutlineEffect3D::create();
        if(canUse)
        {
            Color3B outlineColor = UtilityHelper::randomColor();
            outline->setOutlineColor(Vec3(outlineColor.r/255.0f, outlineColor.g/255.0f, outlineColor.b/255.0f));
        }
        outline->setOutlineWidth(0.03f);
        portal->addEffect(outline, 1);
        
        if(canUse)
        {
            Color3B randomColor = UtilityHelper::randomColor(500,80);
            portal->setColor(randomColor);
            if(!(portal->createCenterModel(canUse, outline)))
                CCLOG("CreateCenterModel failed!");
            RepeatForever* repeat = RepeatForever::create(RotateBy::create(1.0f, Vec3(-90, 90, 0)));
            portal->runAction(repeat);
        }
        else
        {
            if(!(portal->createCenterModel(false, outline)))
                CCLOG("CreateCenterModel failed!");
        }
        
        portal->autorelease();
        return portal;
    }
    CC_SAFE_DELETE(portal);
    return nullptr;
}
StandardPortal::StandardPortal()
{
    m_Type = PT_STANDARD;
}
StandardPortal::~StandardPortal()
{
}
bool StandardPortal::createCenterModel(bool canUse, OutlineEffect3D* outline)
{
    m_pCenterSprite = EffectSprite3D::create("3x3x3.c3b");
    if(m_pCenterSprite)
    {
        m_pCenterSprite->setRotation3D(Vec3(0,45,55));
        m_pCenterSprite->addEffect(outline, 1);
        m_pCenterSprite->setCameraMask((unsigned int)CameraFlag::USER1);
        m_pCenterSprite->setLightMask((unsigned int)LightFlag::LIGHT0);
        this->addChild(m_pCenterSprite);
        if(canUse)
        {
            m_pCenterSprite->setColor(UtilityHelper::randomColor(400,80));
            RepeatForever* repeat = RepeatForever::create(RotateBy::create(1.0f, Vec3(270, -270, 0)));
            m_pCenterSprite->runAction(repeat);
            
            VoxelExplorer::getInstance()->addParticle3DEffectToActor(this, P3D_EFFECT_TYPE::P3D_STANDARD_PORTAL);
        }
        return true;
    }
    return false;
}