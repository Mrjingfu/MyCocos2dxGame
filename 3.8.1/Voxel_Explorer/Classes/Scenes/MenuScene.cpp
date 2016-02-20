//
//  MenuScene.cpp
//  Voxel_Explorer
//
//
//

#include "MenuScene.h"
#include "MenuUILayer.h"
#include "PopupUILayerManager.h"
#include "ArchiveManager.h"
#include "SdkBoxManager.hpp"
#include "LoadingLayer.hpp"
#include "GameCenterController.h"
#include "LevelResourceManager.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

MenuScene::MenuScene()
{
 
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
    GameCenterController::getInstance()->registerGameCenterController();
#endif
    
    cocos2d::Camera* uiCamera = cocos2d::Camera::create();
    uiCamera->setCameraFlag(cocos2d::CameraFlag::USER2);
    this->addChild(uiCamera);
    
    MenuUILayer* menuUiLayer = MenuUILayer::create();
    if(!menuUiLayer->load("menuscene.csb"))
        return false;
    addChild(menuUiLayer);
    
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
    SdkBoxManager::getInstance()->logScreen("MenuScene");
#endif
    
    return true;
}

void MenuScene::onEnter()
{
    Layer::onEnter();
    std::vector<std::string> vecMusic = { "caveamb.mp3", "faneamb.mp3", "mineamb.mp3", "prisonamb.mp3", "seweramb.mp3", "tombamb.mp3"};
    std::string standardMusicName = vecMusic[cocos2d::random(0, (int)(vecMusic.size()-1))];
    SimpleAudioEngine::getInstance()->playBackgroundMusic(standardMusicName.c_str(), true);
    PopupUILayerManager::getInstance()->setParentLayer(this);
    PopupUILayerManager::getInstance()->setSceneType(PopupUILayerManager::eSceneType::ST_MENU);
}
void MenuScene::onExit()
{
    PopupUILayerManager::getInstance()->onExitScene();
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    Layer::onExit();
}
