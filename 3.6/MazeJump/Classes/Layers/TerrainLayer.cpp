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
#include "AlisaMethod.h"
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
    m_fCellBaseRadius     = 4.0f;
    m_nCurrentPatternNum = -1;
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
    for (int i = 0; i<m_TerrainPatternList.size()-1; ++i) {
        TerrainPatternLayer* layer = m_TerrainPatternList.at(i);
        if(layer)
        {
            layer->update(delta);
            if(i == m_nCurrentPatternNum)
                layer->checkCollisionDecorator();
        }
    }
}
void TerrainLayer::setCurrentPatternNum( int num )
{
    if(index < 0)
        return;
    if(m_nCurrentPatternNum != num)
    {
        m_nCurrentPatternNum = num;
        int residueNum = m_nCurrentPatternNum%10;
        if(residueNum == 1)
        {
            int currentDifficultLevel = RunController::getInstance()->getInitDifficultLevel() + m_nCurrentPatternNum/10;
            RunController::getInstance()->setDifficultLevel(currentDifficultLevel);
        }
        if(m_nCurrentPatternNum == 0)
        {
            generatePattern(m_nCurrentPatternNum+1);
            generatePattern(m_nCurrentPatternNum+2);
            generatePattern(m_nCurrentPatternNum+3);
            generatePattern(m_nCurrentPatternNum+4);
        }
        else
            generatePattern(m_nCurrentPatternNum+4);
        collapseCurrentPattern();
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
    TerrainPatternLayer* layer = m_TerrainPatternList.at(m_nCurrentPatternNum);
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
        return false;
    m_TouchBegin = touch->getLocationInView();
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
    {
        if(distanceY>10 && m_TouchEnd.y < m_TouchBegin.y)
            jumpSuper();
        else
            jumpForward();
    }
}
void TerrainLayer::jumpLeft()
{
    CCLOG("jumpLeft");
    Runner* runner = RunController::getInstance()->getMainPlayer();
    if(runner && runner->getState() == Runner::RS_IDLE)
    {
        TerrainPatternLayer* patternLayer = m_TerrainPatternList.at(m_nCurrentPatternNum);
        if(patternLayer)
        {
            if(m_nColumn == -2 &&( patternLayer->getPatternType() == TerrainPatternLayer::PT_DOUBLESIDEBAR
            || patternLayer->getPatternType() == TerrainPatternLayer::PT_CHECKPOINT || patternLayer->getPatternType() == TerrainPatternLayer::PT_LEFTSIDEBAR || patternLayer->getPatternType() == TerrainPatternLayer::PT_STARTER))
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
        TerrainPatternLayer* patternLayer = m_TerrainPatternList.at(m_nCurrentPatternNum);
        if(patternLayer)
        {
            if(m_nColumn == 2 &&( patternLayer->getPatternType() == TerrainPatternLayer::PT_DOUBLESIDEBAR
                                 || patternLayer->getPatternType() == TerrainPatternLayer::PT_CHECKPOINT || patternLayer->getPatternType() == TerrainPatternLayer::PT_RIGHTSIDEBAR || patternLayer->getPatternType() == TerrainPatternLayer::PT_STARTER))
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
    int residueNum = count%10;
    int patternIndex = 1;
    if(residueNum == 1)
    {
        patternIndex = 1;
    }
    else
    {
        if(RunController::getInstance()->getDifficultLevel() == 0)
        {
            int patternBeginIndex = 2;
            int patternEndIndex = 10;
            
            float percent9 = 0.02;
            float percent8 = 0.04;
            float percent7 = 0.06;
            float percent6 = 0.08;
            float percent5 = 0.1;
            float percent4 = 0.12;
            float percent3 = 0.14;
            float percent2 = 0.16;
            float percent1 = 1.0 - percent2 - percent3 - percent4 - percent5 - percent6 - percent7 - percent8 - percent9;
            AlisaMethod* am = AlisaMethod::create(percent1,percent2,percent3,percent4,percent5,percent6,percent7,percent8,percent9,-1.0, NULL);
            if(am)
            {
                patternIndex = am->getRandomIndex() + patternBeginIndex;
                CCASSERT(patternIndex >=patternBeginIndex && patternIndex <= patternEndIndex, "pattern index must between patternBeginIndex and patternEndIndex");
            }
        }
        else
        {
            int patternBeginIndex = RunController::getInstance()->getDifficultLevel() + 1;
            int patternEndIndex = RunController::getInstance()->getDifficultLevel() + 10;
            if(patternEndIndex >= PatternsManager::getInstance()->getMaxPatterns()-1)
            {
                patternBeginIndex = PatternsManager::getInstance()->getMaxPatterns() - 11;
                patternEndIndex = PatternsManager::getInstance()->getMaxPatterns() - 1;
                
                float percent10 = 0.1;
                float percent9 = 0.1;
                float percent8 = 0.1;
                float percent7 = 0.1;
                float percent6 = 0.1;
                float percent5 = 0.1;
                float percent4 = 0.1;
                float percent3 = 0.1;
                float percent2 = 0.1;
                float percent1 = 1.0 - percent2 - percent3 - percent4 - percent5 - percent6 - percent7 - percent8 - percent9 - percent10;
                AlisaMethod* am = AlisaMethod::create(percent1,percent2,percent3,percent4,percent5,percent6,percent7,percent8,percent9,percent10,-1.0, NULL);
                if(am)
                {
                    patternIndex = am->getRandomIndex() + patternBeginIndex;
                    CCASSERT(patternIndex >=patternBeginIndex && patternIndex <= patternEndIndex, "pattern index must between patternBeginIndex and patternEndIndex");
                }
            }
            else
            {
                float percent10 = 0.03;
                float percent9 = 0.03;
                float percent8 = 0.04;
                float percent7 = 0.05;
                float percent6 = 0.06;
                float percent5 = 0.1;
                float percent4 = 0.14;
                float percent3 = 0.3;
                float percent2 = 0.15;
                float percent1 = 1.0 - percent2 - percent3 - percent4 - percent5 - percent6 - percent7 - percent8 - percent9 - percent10;
                AlisaMethod* am = AlisaMethod::create(percent1,percent2,percent3,percent4,percent5,percent6,percent7,percent8,percent9,percent10,-1.0, NULL);
                if(am)
                {
                    patternIndex = am->getRandomIndex() + patternBeginIndex;
                    CCASSERT(patternIndex >=patternBeginIndex && patternIndex <= patternEndIndex, "pattern index must between patternBeginIndex and patternEndIndex");
                }

            }
        }
    }
    TerrainPatternLayer* layer = TerrainPatternLayer::create(patternIndex);
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
void TerrainLayer::collapseCurrentPattern()
{
    TerrainPatternLayer* patternLayer = m_TerrainPatternList.at(m_nCurrentPatternNum);
    if(patternLayer)
    {
        if(patternLayer->getPatternType() == TerrainPatternLayer::PT_STARTER || patternLayer->getPatternType() == TerrainPatternLayer::PT_CHECKPOINT)
            return;
        patternLayer->beginCollapse();
    }
}