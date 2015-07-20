//
//  LevelSelectScene.cpp
//  MazeJump
//
//  Created by wang haibo on 15/6/23.
//
//

#include "LevelSelectScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
Scene* LevelSelectScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LevelSelectScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
LevelSelectScene::LevelSelectScene()
{
    m_pSkyBox = nullptr;
}
// on "init" you need to initialize your instance
bool LevelSelectScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    m_pSkyBox = Skybox::create("sky_right.png", "sky_left.png", "sky_top.png", "sky_bottom.png", "sky_front.png", "sky_back.png");
    if(!m_pSkyBox)
        return false;
    this->addChild(m_pSkyBox);
    return true;
}