//
//  GameScene.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/9/24.
//
//

#include "GameScene.h"
#include "VoxelExplorer.h"
#include "GameUILayer.h"
#include "PopupUILayerManager.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
void GameScene::onEnter()
{
    Layer::onEnter();
    PopupUILayerManager::getInstance()->setParentLayer(this);
}
void GameScene::onExit()
{
    PopupUILayerManager::getInstance()->onExitScene();
    Layer::onExit();
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    if(!VoxelExplorer::getInstance()->init(this))
        return false;
   
    auto mainUi = GameUILayer::create();
    mainUi->load("gameScene.csb");
    mainUi->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    
    VoxelExplorer::getInstance()->get2DLayer()->addChild(mainUi);
    return true;
}