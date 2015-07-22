//
//  TerrainLayer.cpp
//  MazeJump
//
//  Created by wang haibo on 15/7/22.
//
//

#include "TerrainLayer.h"
#include "UtilityHelper.h"
#include "SimpleAudioEngine.h"
#include "MainScene.h"
USING_NS_CC;
using namespace CocosDenshion;
TerrainLayer* TerrainLayer::create()
{
    TerrainLayer *pRet = new(std::nothrow) TerrainLayer();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}
TerrainLayer::TerrainLayer()
{
}

bool TerrainLayer::init()
{
    if ( !Layer::init() )
        return false;
    
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto touchListener = EventListenerTouchAllAtOnce::create();
    if(touchListener == nullptr)
        return false;
    touchListener->onTouchesBegan = CC_CALLBACK_2(TerrainLayer::onTouchesBegan, this);
    touchListener->onTouchesMoved = CC_CALLBACK_2(TerrainLayer::onTouchesMoved, this);
    touchListener->onTouchesEnded = CC_CALLBACK_2(TerrainLayer::onTouchesEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}
void TerrainLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event *event)
{
}
void TerrainLayer::onTouchesMoved(const std::vector<Touch*>& touches, Event *event)
{
}
void TerrainLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event *event)
{
}