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
#include "StatisticsManager.hpp"
#include "RandomDungeon.hpp"
#include "LoadingLayer.hpp"
#include "SdkBoxManager.hpp"
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
GameScene::GameScene()
{
    timedt = 0.0f;
    isLoading = true;
}
void GameScene::onEnter()
{
    Layer::onEnter();
    scheduleUpdate();
    StatisticsManager::getInstance()->resumeSchedu();
    PopupUILayerManager::getInstance()->setParentLayer(this);
}
void GameScene::onExit()
{
    PopupUILayerManager::getInstance()->onExitScene();
    StatisticsManager::getInstance()->pauseSchedu();
    if(!ArchiveManager::getInstance()->saveGame())
        CCLOGERROR("Save Game failed!");
    unscheduleUpdate();
    Layer::onExit();
}
void GameScene::update(float delta)
{
    Layer::update(delta);
    
    timedt+=delta;
    if (timedt > 3.0f && isLoading)
    {
        if (!VoxelExplorer::getInstance()->init(this)) {
            return ;
        }
        
        DungeonNode* dungeonNode = RandomDungeon::getInstance()->getCurrentDungeonNode();
        if (dungeonNode) {
            StatisticsManager::getInstance()->addArriveDungeon(dungeonNode->getDungeonNodeType());
        }
        loadingLayer->removeFromParentAndCleanup(true);
        isLoading = false;
    }
    
    VoxelExplorer::getInstance()->update(delta);
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
    
    loadingLayer = LoadingLayer::create();
    addChild(loadingLayer);
    
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
    SdkBoxManager::getInstance()->logScreen("GameScene");
#endif
    
    return true;
}
