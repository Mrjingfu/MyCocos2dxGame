//
//  GameScene.cpp
//  MazeJump
//
//  Created by wang haibo on 15/6/23.
//
//

#include "GameScene.h"
#include "GroundLayer.h"
#include "GameController.h"
#include "LevelsManager.h"
#include "StepManager.h"
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
    return true;
}
void GameScene::onEnter()
{
    Layer::onEnter();
    scheduleUpdate();
    if(!GameController::getInstance()->init(this))
        CCLOGERROR("GameController init failed!");
}
void GameScene::onExit()
{
    GameController::getInstance()->destroy();
    unscheduleUpdate();
    Layer::onExit();
}
void GameScene::update(float delta)
{
    GameController::getInstance()->update(delta);
}
void GameScene::gameWin()
{
    CCLOG("gameWin");
    LevelsManager::getInstance()->setCurrentLevel(LevelsManager::getInstance()->getCurrentLevel()+1);
    GameController::getInstance()->destroy();
    GameController::getInstance()->init(this);
    StepManager::getInstance()->setLevelStep(LevelsManager::getInstance()->getCurrentLevel());
    StepManager::getInstance()->printfStep(LevelsManager::getInstance()->getCurrentLevel());
    
}
void GameScene::gameLose()
{
    CCLOG("gameLose");
    GameController::getInstance()->destroy();
    GameController::getInstance()->init(this);
    StepManager::getInstance()->setLevelStep(LevelsManager::getInstance()->getCurrentLevel());
    StepManager::getInstance()->printfStep(LevelsManager::getInstance()->getCurrentLevel());
}