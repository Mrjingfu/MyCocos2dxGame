//
//  Logo.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/4/14.
//
//

#include "Logo.h"
USING_NS_CC;

Scene* Logo::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Logo::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
Logo::Logo()
{
}
// on "init" you need to initialize your instance
bool Logo::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    m_pLogo = Sprite::create("logo.png");
    if(!m_pLogo)
        return false;
    addChild(m_pLogo);
    return true;
}

void Logo::onEnter()
{
    Layer::onEnter();
    scheduleUpdate();
}
void Logo::onExit()
{
    unscheduleUpdate();
    Layer::onExit();
}
void Logo::update(float delta)
{
}