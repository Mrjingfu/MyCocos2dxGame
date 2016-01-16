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
USING_NS_CC;

Scene* MenuScene::createScene(bool isFirst)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuScene::create(isFirst);
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
MenuScene* MenuScene::create(bool isFirst )
{
    MenuScene* menu = new(std::nothrow) MenuScene(isFirst);
    if (menu && menu->init()) {
        menu->autorelease();
        return menu;
    }else
    {
        CC_SAFE_DELETE(menu);
        return nullptr;
    }
    
}
MenuScene::MenuScene(bool isFirst):m_bIsFirst(isFirst)
{
    timedt = 0.0f;
    isLoading = true;
    loadingLayer = nullptr;
}
void MenuScene::update(float delta)
{
    Layer::update(delta);
    
    timedt+=delta;
    if (timedt > 3.0f && isLoading)
    {
        loadMenuLayer();
        isLoading = false;
        if (loadingLayer)
            loadingLayer->removeFromParentAndCleanup(true);
        
    }

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
    
 
    if (m_bIsFirst) {
        loadMenuLayer();
    }else
    {
        loadingLayer = LoadingLayer::create();
        addChild(loadingLayer);
    }
    
    
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
    SdkBoxManager::getInstance()->logScreen("MenuScene");
#endif
    
    return true;
}
void MenuScene::loadMenuLayer()
{
    MenuUILayer* menuUiLayer = MenuUILayer::create();
    if(!menuUiLayer->load("menuscene.csb"))
        return ;
    addChild(menuUiLayer);
    
}
void MenuScene::onEnter()
{
    Layer::onEnter();
    if (!m_bIsFirst)
        scheduleUpdate();
    PopupUILayerManager::getInstance()->setParentLayer(this);
}
void MenuScene::onExit()
{
    PopupUILayerManager::getInstance()->onExitScene();
    if (!m_bIsFirst)
        unscheduleUpdate();
    Layer::onExit();
}
