//
//  HelpScene.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/5/14.
//
//

#include "HelpScene.h"
#include "HelpInfoUI.h"
USING_NS_CC;

Scene* HelpScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelpScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
HelpScene::HelpScene()
{
    m_pHelpInfoUI = nullptr;
}
// on "init" you need to initialize your instance
bool HelpScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    m_pHelpInfoUI = HelpInfoUI::create();
    if(!m_pHelpInfoUI)
        return false;
    addChild(m_pHelpInfoUI);
    
    return true;
}