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

Scene* GameScene::createScene(int difficultLevel)
{
    GameScene *pRet = new(std::nothrow) GameScene(difficultLevel);
    auto scene = Scene::create();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        scene->addChild(pRet);
        return scene;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
GameScene::GameScene(int difficultLevel):m_nDifficultLevel(difficultLevel)
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
    if(!GameController::getInstance()->init(this,m_nDifficultLevel))
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
//    StepManager::getInstance()->setLevelStep(LevelsManager::getInstance()->getCurrentLevel(),StepManager::LEVEL_WIN);
//    LevelsManager::getInstance()->setCurrentLevel(LevelsManager::getInstance()->getCurrentLevel()+1);
//    GameController::getInstance()->destroy();
//    GameController::getInstance()->init(this,m_nDifficultLevel);
}
void GameScene::gameLose()
{
    CCLOG("gameLose");
//    GameController::getInstance()->destroy();
//    GameController::getInstance()->init(this,m_nDifficultLevel);
}
void GameScene::gameRecordEnd()
{
    //测试
//    LevelsManager::getInstance()->setCurrentLevel(LevelsManager::getInstance()->getCurrentLevel()+1);
//    GameController::getInstance()->destroy();
//    GameController::getInstance()->init(this,m_nDifficultLevel);
}