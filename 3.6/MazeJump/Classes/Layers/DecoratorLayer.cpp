//
//  DecoratorLayer.cpp
//  MazeJump
//
//  Created by wang haibo on 15/7/20.
//
//

#include "DecoratorLayer.h"
#include "FogEffect3D.h"
#include "EffectSprite3D.h"
USING_NS_CC;

DecoratorLayer::DecoratorLayer()
{
}

bool DecoratorLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    EffectSprite3D* test = EffectSprite3D::create("castle.obj");
    if(!test)
        return false;
    test->setTexture("IndexColor.png");
    test->setContentSize(test->getBoundingBox().size);
    test->setPosition3D(Vec3(20, -100, 30));
    test->setScale(8);
    test->setRotation3D(Vec3(0,0,0));
    
    FogEffect3D* fog = FogEffect3D::create();
    fog->setFogType(FogEffect3D::FT_EXP2);
    fog->setFogColor(Color4F(153.0f/255.0f, 204.0f/255.0f, 1.0f, 1.0f));
    test->setEffect(fog);
    
    addChild(test);
    return true;
}
