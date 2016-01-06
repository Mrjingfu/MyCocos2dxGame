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
    StatisticsManager::getInstance()->resumeSchedu();
    PopupUILayerManager::getInstance()->setParentLayer(this);
}
void GameScene::onExit()
{
    PopupUILayerManager::getInstance()->onExitScene();
    StatisticsManager::getInstance()->pauseSchedu();
    if(!ArchiveManager::getInstance()->saveGame())
        CCLOGERROR("Save Game failed!");
    Layer::onExit();
}
void GameScene::update(float delta)
{
    Layer::update(delta);
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
    
    if(!VoxelExplorer::getInstance()->init(this))
        return false;
   
    DungeonNode* dungeonNode = RandomDungeon::getInstance()->getCurrentDungeonNode();
    if (dungeonNode) {
        StatisticsManager::getInstance()->addArriveDungeon(dungeonNode->getDungeonNodeType());
    }
    
 
    return true;
}