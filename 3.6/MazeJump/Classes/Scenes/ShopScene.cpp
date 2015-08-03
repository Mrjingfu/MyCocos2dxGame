//
//  ShopScene.cpp
//  MazeJump
//
//  
//
//

#include "ShopScene.h"
#include "ShopUI.h"
USING_NS_CC;

Scene* ShopScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ShopScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
ShopScene::ShopScene()
{
    m_pMainCamera = nullptr;
}
// on "init" you need to initialize your instance
bool ShopScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    auto shopUi = ShopUI::create();
    addChild(shopUi);
    
    return true;
}