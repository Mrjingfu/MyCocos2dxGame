//
//  MainScene.cpp
//  MazeJump
//
//  Created by wang haibo on 15/7/22.
//
//

#include "MainScene.h"
#include "TerrainLayer.h"
#include "RunController.h"
#include "UIManager.h"
USING_NS_CC;
Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
MainScene::MainScene()
{
}
// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
        return false;
    return true;
}
void MainScene::onEnter()
{
    Layer::onEnter();
    
    scheduleUpdate();
    
    if(RunController::getInstance()->isInMazeJump())
        RunController::getInstance()->reset();
    else
    {
        if(!RunController::getInstance()->init(this))
            CCLOGERROR("RunController init failed!");
    }
}
void MainScene::onExit()
{
        UIManager::getInstance()->destory();
    if(!RunController::getInstance()->isInMazeJump())
        RunController::getInstance()->destroy();
    unscheduleUpdate();
    Layer::onExit();
}
void MainScene::update(float delta)
{
    RunController::getInstance()->update(delta);
}
void MainScene::gameWin()
{
    CCLOG("gameWin");
}
void MainScene::gameLose()
{
    CCLOG("gameLose");
}