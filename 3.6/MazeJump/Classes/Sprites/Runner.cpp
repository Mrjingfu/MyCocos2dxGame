//
//  Runner.cpp
//  MazeJump
//
//  Created by wang haibo on 15/7/22.
//
//

#include "Runner.h"
#include "OutlineEffect3D.h"
#include "RunController.h"
USING_NS_CC;

Runner* Runner::create()
{
    auto runner = new (std::nothrow) Runner();
    if (runner && runner->initWithFile("strength.obj"))
    {
        runner->setTexture("IndexColor.png");
        runner->_contentSize = runner->getBoundingBox().size;
        runner->m_fRadius = runner->_contentSize.width*0.5f;
        runner->setState(RS_IDLE);
        
        OutlineEffect3D* outline = OutlineEffect3D::create();
        outline->setOutlineColor(Vec3(0.3f, 0.3f, 0.3f));
        outline->setOutlineWidth(0.03f);
        runner->addEffect(outline, 1);
        
        runner->autorelease();
        return runner;
    }
    CC_SAFE_DELETE(runner);
    return nullptr;
}
Runner::Runner()
{
    m_curState  = RS_UNKNOWN;
    m_fRadius   = 2.5f;
}

void Runner::setState(RunnerState state)
{
    if (m_curState == state)
        return;
    
    ///处理上一个状态退出逻辑
    switch (m_curState) {
        case RunnerState::RS_IDLE:
            onExitIdle();
            break;
        case RunnerState::RS_MOVE_LEFT:
            onExitMoveLeft();
            break;
        case RunnerState::RS_MOVE_RIGHT:
            onExitMoveRight();
            break;
        case RunnerState::RS_MOVE_FORWARD:
            onExitMoveForward();
            break;
        case RunnerState::RS_MOVE_SUPERJUMP:
            onExitMoveSuperJump();
            break;
        default:
            break;
    }
    
    m_curState = state;
    ///处理下一个状态进入逻辑
    switch (m_curState) {
        case RunnerState::RS_IDLE:
            onEnterIdle();
            break;
        case RunnerState::RS_MOVE_LEFT:
            onEnterMoveLeft();
            break;
        case RunnerState::RS_MOVE_RIGHT:
            onEnterMoveRight();
            break;
        case RunnerState::RS_MOVE_FORWARD:
            onEnterMoveForward();
            break;
        case RunnerState::RS_MOVE_SUPERJUMP:
            onEnterMoveSuperJump();
            break;
        default:
            break;
    }
}
void Runner::onEnterIdle()
{
    RunController::getInstance()->cameraTrackPlayer();
}
void Runner::onEnterMoveLeft()
{
    TerrainLayer* terrainLayer = RunController::getInstance()->getTerrainLayer();
    if(terrainLayer)
    {
        float cellRadius = terrainLayer->getCellRadius();
        EaseSineOut* scaleTo1 = EaseSineOut::create(ScaleTo::create(0.05f, 1, 0.9f, 1));
        EaseSineIn* scaleTo2 = EaseSineIn::create(ScaleTo::create(0.1f, 1, 1.0f, 1));
        Sequence* sequenceScale = Sequence::create(scaleTo1, scaleTo2, NULL);
        
        DelayTime* delay = DelayTime::create(0.05f);
        EaseSineOut* ratateTo = EaseSineOut::create(RotateTo::create(0.4f, Vec3(0,90,0)));
        Sequence* sequenceRotate = Sequence::create(delay, ratateTo, NULL);

        
        EaseSineOut* moveUp = EaseSineOut::create(MoveTo::create(0.2f, Vec3(getPositionX() - cellRadius*2, getPositionY() + cellRadius, getPositionZ())));
        EaseSineOut* moveDown = EaseSineOut::create(MoveTo::create(0.2f, Vec3(getPositionX() - cellRadius*2, getPositionY(), getPositionZ())));
        Sequence* sequenceJump = Sequence::create(delay, moveUp, moveDown, NULL);
        Spawn* spawn = Spawn::create(sequenceScale, sequenceRotate, sequenceJump, NULL);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Runner::checkSafe,this));
        Sequence* sequence = Sequence::create(spawn, callFunc, NULL);
        runAction(sequence);
    }
}
void Runner::onEnterMoveRight()
{
    TerrainLayer* terrainLayer = RunController::getInstance()->getTerrainLayer();
    if(terrainLayer)
    {
        float cellRadius = terrainLayer->getCellRadius();
        EaseSineOut* scaleTo1 = EaseSineOut::create(ScaleTo::create(0.05f, 1, 0.9f, 1));
        EaseSineIn* scaleTo2 = EaseSineIn::create(ScaleTo::create(0.1f, 1, 1.0f, 1));
        Sequence* sequenceScale = Sequence::create(scaleTo1, scaleTo2, NULL);
        
        DelayTime* delay = DelayTime::create(0.05f);
        EaseSineOut* ratateTo = EaseSineOut::create(RotateTo::create(0.4f, Vec3(0,-90,0)));
        Sequence* sequenceRotate = Sequence::create(delay, ratateTo, NULL);
        
        EaseSineOut* moveUp = EaseSineOut::create(MoveTo::create(0.2f, Vec3(getPositionX() + cellRadius*2, getPositionY() + cellRadius, getPositionZ())));
        EaseSineOut* moveDown = EaseSineOut::create(MoveTo::create(0.2f, Vec3(getPositionX() + cellRadius*2, getPositionY(), getPositionZ())));
        Sequence* sequenceJump = Sequence::create(delay, moveUp, moveDown, NULL);
        Spawn* spawn = Spawn::create(sequenceScale,sequenceRotate, sequenceJump, NULL);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Runner::checkSafe,this));
        Sequence* sequence = Sequence::create(spawn, callFunc, NULL);
        runAction(sequence);
    }
}
void Runner::onEnterMoveForward()
{
    TerrainLayer* terrainLayer = RunController::getInstance()->getTerrainLayer();
    if(terrainLayer)
    {
        float cellRadius = terrainLayer->getCellRadius();

        EaseSineOut* scaleTo1 = EaseSineOut::create(ScaleTo::create(0.05f, 1, 0.9f, 1));
        EaseSineIn* scaleTo2 = EaseSineIn::create(ScaleTo::create(0.1f, 1, 1.0f,1));
        Sequence* sequenceScale = Sequence::create(scaleTo1, scaleTo2, NULL);
        
        DelayTime* delay = DelayTime::create(0.05f);
        RotateTo* ratateTo = RotateTo::create(0.2f, Vec3(0,0,0));
        Sequence* sequenceRotate = Sequence::create(delay, ratateTo, NULL);
                                                                  
        EaseSineOut* moveUp = EaseSineOut::create(MoveTo::create(0.2f, Vec3(getPositionX(), getPositionY() + cellRadius, getPositionZ() - cellRadius*2)));
        EaseSineOut* moveDown = EaseSineOut::create(MoveTo::create(0.2f, Vec3(getPositionX(), getPositionY(), getPositionZ() - cellRadius*2)));
        Sequence* sequenceJump = Sequence::create(delay, moveUp, moveDown, NULL);
        Spawn* spawn = Spawn::create(sequenceScale, sequenceRotate, sequenceJump, NULL);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Runner::checkSafe,this));
        Sequence* sequence = Sequence::create(spawn, callFunc, NULL);
        runAction(sequence);
    }

}
void Runner::onEnterMoveSuperJump()
{
    TerrainLayer* terrainLayer = RunController::getInstance()->getTerrainLayer();
    if(terrainLayer)
    {
        float cellRadius = terrainLayer->getCellRadius();
        
        EaseSineOut* scaleTo1 = EaseSineOut::create(ScaleTo::create(0.1f, 1, 0.8f, 1));
        EaseSineIn* scaleTo2 = EaseSineIn::create(ScaleTo::create(0.2f, 1, 1.0f,1));
        Sequence* sequenceScale = Sequence::create(scaleTo1, scaleTo2, NULL);
        
        DelayTime* delay = DelayTime::create(0.1f);
        RotateTo* ratateTo = RotateTo::create(0.4f, Vec3(0,0,0));
        Sequence* sequenceRotate = Sequence::create(delay, ratateTo, NULL);
        
        EaseSineOut* moveUp = EaseSineOut::create(MoveTo::create(0.4f, Vec3(getPositionX(), getPositionY() + cellRadius*2, getPositionZ() - cellRadius*4)));
        EaseSineIn* moveDown = EaseSineIn::create(MoveTo::create(0.4f, Vec3(getPositionX(), getPositionY(), getPositionZ() - cellRadius*4)));
        Sequence* sequenceJump = Sequence::create(delay, moveUp, moveDown, NULL);
        Spawn* spawn = Spawn::create(sequenceScale, sequenceRotate, sequenceJump, NULL);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Runner::checkSafe,this));
        Sequence* sequence = Sequence::create(spawn, callFunc, NULL);
        runAction(sequence);
    }

}
void Runner::onExitIdle()
{
}
void Runner::onExitMoveLeft()
{
}
void Runner::onExitMoveRight()
{
}
void Runner::onExitMoveForward()
{
}
void Runner::onExitMoveSuperJump()
{
}
void Runner::checkSafe()
{
    setState(RS_IDLE);
}