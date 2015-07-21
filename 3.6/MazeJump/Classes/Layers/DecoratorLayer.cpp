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

DecoratorLayer* DecoratorLayer::create(const std::string& modelFile, const cocos2d::Color4F& fogColor)
{
    DecoratorLayer *pRet = new(std::nothrow) DecoratorLayer();
    if (pRet && pRet->init(modelFile, fogColor))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}


DecoratorLayer::DecoratorLayer()
{
}
bool DecoratorLayer::init(const std::string& modelFile, const cocos2d::Color4F& fogColor)
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    EffectSprite3D* test = EffectSprite3D::create(modelFile);
    if(!test)
        return false;
    test->setTexture("IndexColor.png");
    test->setContentSize(test->getBoundingBox().size);
    test->setPosition3D(Vec3(-10, -100, 0));
    test->setScale(4);
    test->setRotation3D(Vec3(0,0,0));
    
    FogEffect3D* fog = FogEffect3D::create();
    fog->setFogType(FogEffect3D::FT_EXP2);
    fog->setFogColor(fogColor);
    test->setEffect(fog);
    
    addChild(test);
    return true;
}
