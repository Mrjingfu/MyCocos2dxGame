//
//  ShopScene.cpp
//  MazeJump
//
//  
//
//

#include "ShopScene.h"
#include "ShopUI.h"
USING_NS_CC;

Scene* ShopScene::createScene(const std::string& tip)
{
    ShopScene *pRet = new(std::nothrow) ShopScene(tip);
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
ShopScene::ShopScene(const std::string& tip):m_tip(tip)
{
    m_pMainCamera = nullptr;
}
// on "init" you need to initialize your instance
bool ShopScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    auto shopUi = ShopUI::create(m_tip);
    addChild(shopUi);
    
    return true;
}