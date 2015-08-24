//
//  ToneSkipperScene.cpp
//  Tone_Skipper
//
//  Created by wang haibo on 15/8/24.
//
//

#include "ToneSkipperScene.h"
USING_NS_CC;

Scene* ToneSkipperScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ToneSkipperScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
ToneSkipperScene::ToneSkipperScene()
{
}
// on "init" you need to initialize your instance
bool ToneSkipperScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    return true;
}

void ToneSkipperScene::onEnter()
{
    Layer::onEnter();
    scheduleUpdate();
}
void ToneSkipperScene::onExit()
{
    unscheduleUpdate();
    Layer::onExit();
}
void ToneSkipperScene::update(float delta)
{
    
}