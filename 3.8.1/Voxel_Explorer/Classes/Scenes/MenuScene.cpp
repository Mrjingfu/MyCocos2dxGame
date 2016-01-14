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
USING_NS_CC;

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
    PopupUILayerManager::getInstance()->setParentLayer(this);
}
void MenuScene::onExit()
{
    PopupUILayerManager::getInstance()->onExitScene();
    Layer::onExit();
}
