//
//  GameScene.cpp
//  MazeJump
//
//  Created by wang haibo on 15/6/23.
//
//

#include "GameScene.h"
#include "GroundLayer.h"
#include "LevelsManager.h"
#include "StepManager.h"
#include "AudioEngine.h"
#include "GameConst.h"
#include "SdkBoxManager.h"
USING_NS_CC;
using namespace experimental;

Scene* GameScene::createScene(int difficultLevel,GameController::MAZE_MODE mazeMode)
{
    GameScene *pRet = new(std::nothrow) GameScene(difficultLevel,mazeMode);
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
GameScene::GameScene(int difficultLevel,GameController::MAZE_MODE mazeMode):m_nDifficultLevel(difficultLevel),m_mazeMode(mazeMode)
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
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
    SdkBoxManager::getInstance()->logScreen("GameScene");
#endif
    return true;
}
void GameScene::onEnter()
{
    Layer::onEnter();
    scheduleUpdate();
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ground_ui.plist", "ground_ui.png");
    m_nBgID = AudioEngine::play2d("loop.wav",true, 0.5);
    if(!GameController::getInstance()->init(this,m_nDifficultLevel,m_mazeMode))
        CCLOGERROR("GameController init failed!");
    
    
}
void GameScene::onExit()
{
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("ground_ui.plist");
    AudioEngine::stop(m_nBgID);
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
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_MAZEJUMP_WIN);

}
void GameScene::gameLose()
{
    CCLOG("gameLose");
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_MAZEJUMP_LOSE);
}
void GameScene::gameRecordEnd()
{
    CCLOG("gameRecordEnd");
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_MAZEJUMP_RECORD_END);
}