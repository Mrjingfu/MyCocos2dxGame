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
#include "PatternsManager.h"
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
    m_fCellBaseRadius     = 4.0f;
    m_nCurrentPatternIndex = -1;
    m_nColumn = 0;
    m_nRow = -3;
}

bool TerrainLayer::init()
{
    if ( !Layer::init() )
        return false;
    
    if(!generateStartPoint())
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
void TerrainLayer::update(float delta)
{
    for (TerrainPatternLayer* layer : m_TerrainPatternList) {
        if(layer)
            layer->update(delta);
    }
}
void TerrainLayer::setCurrentPatternIndex( int index )
{
    if(index < 0)
        return;
    if(m_nCurrentPatternIndex != index)
    {
        m_nCurrentPatternIndex = index;
        if(m_nCurrentPatternIndex == 0)
        {
            generatePattern(m_nCurrentPatternIndex+1);
            generatePattern(m_nCurrentPatternIndex+2);
            generatePattern(m_nCurrentPatternIndex+3);
        }
        else
            generatePattern(m_nCurrentPatternIndex+3);
    }
}
void TerrainLayer::setCurrentColumn( int column )
{
    if(m_nColumn != column)
        m_nColumn = column;
}
void TerrainLayer::setCurrentRow( int row )
{
    if(m_nRow != row)
        m_nRow = row;
}
bool TerrainLayer::checkRunnerDrop()
{
    TerrainPatternLayer* layer = m_TerrainPatternList.at(m_nCurrentPatternIndex);
    if(layer)
    {
        bool drop = layer->checkRunnerDrop();
        if(drop)
            return true;
    }
    return false;
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
    {
        TerrainPatternLayer* patternLayer = m_TerrainPatternList.at(m_nCurrentPatternIndex);
        if(patternLayer)
        {
            if(m_nColumn == -2 &&( patternLayer->getPatternType() == TerrainPatternLayer::PT_DOUBLESIDEBAR
            || patternLayer->getPatternType() == TerrainPatternLayer::PT_LEFTSIDEBAR || patternLayer->getPatternType() == TerrainPatternLayer::PT_STARTER))
                runner->setState(Runner::RS_MOVE_JUMPLOCAL);
            else
                runner->setState(Runner::RS_MOVE_LEFT);
        }
    }
}
void TerrainLayer::jumpRight()
{
    CCLOG("jumpRight");
    Runner* runner = RunController::getInstance()->getMainPlayer();
    if(runner && runner->getState() == Runner::RS_IDLE)
    {
        TerrainPatternLayer* patternLayer = m_TerrainPatternList.at(m_nCurrentPatternIndex);
        if(patternLayer)
        {
            if(m_nColumn == 2 &&( patternLayer->getPatternType() == TerrainPatternLayer::PT_DOUBLESIDEBAR
                                 || patternLayer->getPatternType() == TerrainPatternLayer::PT_RIGHTSIDEBAR || patternLayer->getPatternType() == TerrainPatternLayer::PT_STARTER))
                runner->setState(Runner::RS_MOVE_JUMPLOCAL);
            else
                runner->setState(Runner::RS_MOVE_RIGHT);
        }
    }
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
void TerrainLayer::jumpLocal()
{
    CCLOG("jumpLocal");
    Runner* runner = RunController::getInstance()->getMainPlayer();
    if(runner && runner->getState() == Runner::RS_IDLE)
        runner->setState(Runner::RS_MOVE_JUMPLOCAL);
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
bool TerrainLayer::generateStartPoint()
{
    TerrainPatternLayer* layer = TerrainPatternLayer::create(0);
    if(!layer)
        return false;
    layer->setCameraMask((unsigned short)CameraFlag::USER1);
    addChild(layer);
    m_TerrainPatternList.pushBack(layer);
    return true;
}
void TerrainLayer::generatePattern(int count)
{
    TerrainPatternLayer* layer = TerrainPatternLayer::create(1);
    if(!layer)
        return;
    layer->setCameraMask((unsigned short)CameraFlag::USER1);
    addChild(layer);
    if(count == 0)
        layer->setPositionZ(0);
    else
        layer->setPositionZ(-count*5*m_fCellBaseRadius*2 + m_fCellBaseRadius*2);
    m_TerrainPatternList.pushBack(layer);
}