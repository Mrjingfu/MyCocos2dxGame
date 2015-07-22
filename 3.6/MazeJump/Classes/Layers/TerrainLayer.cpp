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
#include "RunController.h"
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
    m_nTouchCount     = 0;
    m_fCellRadius     = 5.0f;
}

bool TerrainLayer::init()
{
    if ( !Layer::init() )
        return false;
    
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto touchListener = EventListenerTouchOneByOne::create();
    if(touchListener == nullptr)
        return false;
    touchListener->onTouchBegan = CC_CALLBACK_2(TerrainLayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(TerrainLayer::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(TerrainLayer::onTouchEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}
bool TerrainLayer::onTouchBegan(Touch *touch, Event *event)
{
    if(!touch)
        return true;
    m_TouchBegin = touch->getLocationInView();
    if(m_nTouchCount == 0)
    {
        m_nTouchCount = 1;
        scheduleOnce(schedule_selector(TerrainLayer::clearClick), 0.2f);
    }
    else if(m_nTouchCount == 1)
    {
        jumpSuper();
        m_nTouchCount = 0;
    }
    
    return true;
}
void TerrainLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(!touch)
        return;
    m_TouchEnd = touch->getLocationInView();
}

void TerrainLayer::onTouchEnded(Touch *touch, Event *event)
{
    if(!touch)
        return;
    m_TouchEnd = touch->getLocationInView();
}
void TerrainLayer::jumpLeft()
{
    CCLOG("jumpLeft");
    Runner* runner = RunController::getInstance()->getMainPlayer();
    if(runner && runner->getState() == Runner::RS_IDLE)
        runner->setState(Runner::RS_MOVE_LEFT);
}
void TerrainLayer::jumpRight()
{
    CCLOG("jumpRight");
    Runner* runner = RunController::getInstance()->getMainPlayer();
    if(runner && runner->getState() == Runner::RS_IDLE)
        runner->setState(Runner::RS_MOVE_RIGHT);
}
void TerrainLayer::jumpForward()
{
    CCLOG("jumpForward");
    Runner* runner = RunController::getInstance()->getMainPlayer();
    if(runner && runner->getState() == Runner::RS_IDLE)
        runner->setState(Runner::RS_MOVE_FORWARD);
}
void TerrainLayer::jumpSuper()
{
    CCLOG("JumpSuper");
    Runner* runner = RunController::getInstance()->getMainPlayer();
    if(runner && runner->getState() == Runner::RS_IDLE)
        runner->setState(Runner::RS_MOVE_SUPERJUMP);
}
void TerrainLayer::clearClick(float time)
{
    if(m_nTouchCount == 1)
    {
        float distanceX = fabsf(m_TouchEnd.x - m_TouchBegin.x);
        float distanceY = fabsf(m_TouchEnd.y - m_TouchBegin.y);
        if(distanceX>10 && distanceX >= distanceY)
        {
            if(m_TouchEnd.x < m_TouchBegin.x)
                jumpLeft();
            else if(m_TouchEnd.x > m_TouchBegin.x)
                jumpRight();
        }
        else
            jumpForward();
        m_nTouchCount = 0;
    }
}