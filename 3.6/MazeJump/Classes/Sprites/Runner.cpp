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
#include "AudioEngine.h"
USING_NS_CC;
using namespace experimental;

Runner* Runner::create()
{
    auto runner = new (std::nothrow) Runner();
    if (runner && runner->initWithFile("strength.c3b"))
    {
        runner->_contentSize = runner->getBoundingBox().size;
        runner->m_fRadius = runner->_contentSize.width*0.5f;
        runner->setPositionY(4);
        runner->setOpacity(0);
        
        OutlineEffect3D* outline = OutlineEffect3D::create();
        outline->setOutlineColor(Vec3(0.3f, 0.3f, 0.3f));
        outline->setOutlineWidth(0.03f);
        runner->addEffect(outline, 1);
        
        runner->setLightMask((unsigned int)LightFlag::LIGHT0);

        runner->autorelease();
        return runner;
    }
    CC_SAFE_DELETE(runner);
    return nullptr;
}
Runner::Runner()
{
    m_curState  = RS_UNKNOWN;
    m_dir       = RD_FORWARD;
    m_fRadius   = 2.5f;
    m_pRibbonTrail = nullptr;
    m_pFakeShadow  = nullptr;
    m_bSpeedUp      = false;
}
Runner::~Runner()
{
    if(m_pRibbonTrail)
    {
        m_pRibbonTrail->removeFromParentAndCleanup(true);
        m_pRibbonTrail = nullptr;
    }
    if(m_pFakeShadow)
    {
        m_pFakeShadow->removeFromParentAndCleanup(true);
        m_pFakeShadow = nullptr;
    }
}
void Runner::update(float delta)
{
    if(m_curState == RS_IDLE && (!isSpeedUp()))
    {
        bool isDrop = RunController::getInstance()->getTerrainLayer()->checkRunnerDrop();
        if(isDrop)
            setState(RS_MOVE_DROP);
    }
    if(m_pRibbonTrail)
        m_pRibbonTrail->update(delta);
    if(m_pFakeShadow)
    {
        Mat4 trans = getNodeToWorldTransform();
        Vec3 pos;
        trans.getTranslation(&pos);
        m_pFakeShadow->setPositionX(pos.x);
        m_pFakeShadow->setPositionZ(pos.z);
    }
}
void Runner::setRibbonTrail(const std::string& file)
{
    if(m_pRibbonTrail)
    {
        m_pRibbonTrail->removeFromParentAndCleanup(true);
        m_pRibbonTrail = nullptr;
    }
    m_pRibbonTrail = RibbonTrail::create(file, 5, 30);
    if(m_pRibbonTrail)
    {
        m_pRibbonTrail->setCameraMask((unsigned short)CameraFlag::USER1);
        this->addChild(m_pRibbonTrail);
        m_pRibbonTrail->getTrail()->addNode(this);
        if(getParent() != nullptr)
            m_pRibbonTrail->getTrail()->setAttachedNode(getParent());
    }
    else
        CCLOG("create ribbon trail with texture %s failed!", file.c_str());
}
void Runner::setFakeShadow(cocos2d::Layer* ownerLayer)
{
    if(!ownerLayer)
        return;
    if(m_pFakeShadow)
    {
        m_pFakeShadow->removeFromParentAndCleanup(true);
        m_pFakeShadow = nullptr;
    }
    m_pFakeShadow = Sprite3D::create("fakeshadow.c3b");
    if(m_pFakeShadow)
    {
        m_pFakeShadow->setCameraMask((unsigned short)CameraFlag::USER1);
        ownerLayer->addChild(m_pFakeShadow, 1);
        
        Mat4 trans = getNodeToWorldTransform();
        Vec3 pos;
        trans.getTranslation(&pos);
        m_pFakeShadow->setPositionX(pos.x);
        m_pFakeShadow->setPositionZ(pos.z);
        
        m_pFakeShadow->setPositionY(pos.y - m_fRadius*getScale());
        
        m_pFakeShadow->setForceDepthWrite(true);
        m_pFakeShadow->setOpacity(0);
        DelayTime* delay = DelayTime::create(1.0f);
        EaseSineOut* fadeIn = EaseSineOut::create(FadeIn::create(0.5f));
        Sequence* sequence = Sequence::create(delay, fadeIn, NULL);
        m_pFakeShadow->runAction(sequence);
    }
    else
        CCLOG("create fake shadow failed!");
}
void Runner::setSpeedUp(bool speedUp)
{
    if(m_bSpeedUp != speedUp)
        m_bSpeedUp = speedUp;
}
void Runner::onCollision(TerrainCell* cell)
{
}
const AABB& Runner::getModifyAABB()
{
    m_modifyAABB = getAABB();
    m_modifyAABB.merge(AABB(Vec3(m_modifyAABB._min)+Vec3(0,-1.0f, 0), Vec3(m_modifyAABB._max)));
    return m_modifyAABB;
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
        case RunnerState::RS_MOVE_JUMPLOCAL:
            onExitMoveJumpLocal();
            break;
        case RunnerState::RS_MOVE_DROP:
            onExitMoveDrop();
            break;
        case RunnerState::RS_DEATH:
            onExitDeath();
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
        case RunnerState::RS_MOVE_JUMPLOCAL:
            onEnterMoveJumpLocal();
            break;
        case RunnerState::RS_MOVE_DROP:
            onEnterMoveDrop();
            break;
        case RunnerState::RS_DEATH:
            onEnterDeath();
            break;
        default:
            break;
    }
}
void Runner::onEnterIdle()
{
    TerrainLayer* layer = RunController::getInstance()->getTerrainLayer();
    if(layer)
    {
        float x = getPositionX();
        float z = getPositionZ() - layer->getCellBaseRadius()*6;
        int colunm = x / (layer->getCellBaseRadius()*2);
        int row = -z / (layer->getCellBaseRadius()*2);
        int currentPatternCount = row/5;
        layer->setCurrentColumn(colunm);
        layer->setCurrentRow(row);
        layer->setCurrentPatternNum(currentPatternCount);
        
        if(m_pFakeShadow)
            m_pFakeShadow->setVisible(true);
    }
}
void Runner::onEnterMoveLeft()
{
    TerrainLayer* terrainLayer = RunController::getInstance()->getTerrainLayer();
    if(terrainLayer)
    {
        AudioEngine::play2d("jump.wav", false, 0.3f);
        float cellRadius = terrainLayer->getCellBaseRadius();
        EaseSineOut* scaleTo1 = EaseSineOut::create(ScaleTo::create(0.05f, 1, 0.8f, 1));
        EaseSineIn* scaleTo2 = EaseSineIn::create(ScaleTo::create(0.05f, 1, 1.0f, 1));
        Sequence* sequenceScale = Sequence::create(scaleTo1, scaleTo2, NULL);
        
        DelayTime* delay = DelayTime::create(0.05f);
        EaseSineOut* ratateTo = EaseSineOut::create(RotateTo::create(0.2f, Vec3(0,90,0)));
        Sequence* sequenceRotate = Sequence::create(delay, ratateTo, NULL);

        
        EaseSineOut* moveUp = EaseSineOut::create(MoveTo::create(0.1f, Vec3(getPositionX() - cellRadius*2, getPositionY() + cellRadius*1.5, getPositionZ())));
        EaseSineOut* moveDown = EaseSineOut::create(MoveTo::create(0.1f, Vec3(getPositionX() - cellRadius*2, getPositionY(), getPositionZ())));
        Sequence* sequenceJump = Sequence::create(delay, moveUp, moveDown, NULL);
        Spawn* spawn = Spawn::create(sequenceScale, sequenceRotate, sequenceJump, NULL);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Runner::checkSafe,this));
        Sequence* sequence = Sequence::create(spawn, callFunc, NULL);
        if (m_bSpeedUp)
            runAction(Speed::create(sequence, 2.0f));
        else
            runAction(sequence);
        m_dir = RD_LEFT;
    }
}
void Runner::onEnterMoveRight()
{
    TerrainLayer* terrainLayer = RunController::getInstance()->getTerrainLayer();
    if(terrainLayer)
    {
        AudioEngine::play2d("jump.wav", false, 0.3f);
        float cellRadius = terrainLayer->getCellBaseRadius();
        EaseSineOut* scaleTo1 = EaseSineOut::create(ScaleTo::create(0.05f, 1, 0.8f, 1));
        EaseSineIn* scaleTo2 = EaseSineIn::create(ScaleTo::create(0.05f, 1, 1.0f, 1));
        Sequence* sequenceScale = Sequence::create(scaleTo1, scaleTo2, NULL);
        
        DelayTime* delay = DelayTime::create(0.05f);
        EaseSineOut* ratateTo = EaseSineOut::create(RotateTo::create(0.2f, Vec3(0,-90,0)));
        Sequence* sequenceRotate = Sequence::create(delay, ratateTo, NULL);
        
        EaseSineOut* moveUp = EaseSineOut::create(MoveTo::create(0.1f, Vec3(getPositionX() + cellRadius*2, getPositionY() + cellRadius*1.5, getPositionZ())));
        EaseSineOut* moveDown = EaseSineOut::create(MoveTo::create(0.1f, Vec3(getPositionX() + cellRadius*2, getPositionY(), getPositionZ())));
        Sequence* sequenceJump = Sequence::create(delay, moveUp, moveDown, NULL);
        Spawn* spawn = Spawn::create(sequenceScale,sequenceRotate, sequenceJump, NULL);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Runner::checkSafe,this));
        Sequence* sequence = Sequence::create(spawn, callFunc, NULL);
        if (m_bSpeedUp)
            runAction(Speed::create(sequence, 2.0f));
        else
            runAction(sequence);
        m_dir = RD_RIGHT;
    }
}
void Runner::onEnterMoveForward()
{
    TerrainLayer* terrainLayer = RunController::getInstance()->getTerrainLayer();
    if(terrainLayer)
    {
        AudioEngine::play2d("jump.wav", false, 0.3f);
        float cellRadius = terrainLayer->getCellBaseRadius();

        EaseSineOut* scaleTo1 = EaseSineOut::create(ScaleTo::create(0.05f, 1, 0.8f, 1));
        EaseSineIn* scaleTo2 = EaseSineIn::create(ScaleTo::create(0.05f, 1, 1.0f,1));
        Sequence* sequenceScale = Sequence::create(scaleTo1, scaleTo2, NULL);
        
        DelayTime* delay = DelayTime::create(0.05f);
        RotateTo* ratateTo = RotateTo::create(0.1f, Vec3(0,0,0));
        Sequence* sequenceRotate = Sequence::create(delay, ratateTo, NULL);
                                                                  
        EaseSineOut* moveUp = EaseSineOut::create(MoveTo::create(0.1f, Vec3(getPositionX(), getPositionY() + cellRadius*1.5, getPositionZ() - cellRadius*2)));
        EaseSineOut* moveDown = EaseSineOut::create(MoveTo::create(0.1f, Vec3(getPositionX(), getPositionY(), getPositionZ() - cellRadius*2)));
        Sequence* sequenceJump = Sequence::create(delay, moveUp, moveDown, NULL);
        Spawn* spawn = Spawn::create(sequenceScale, sequenceRotate, sequenceJump, NULL);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Runner::checkSafe,this));
        Sequence* sequence = Sequence::create(spawn, callFunc, NULL);
        if (m_bSpeedUp)
            runAction(Speed::create(sequence, 2.0f));
        else
            runAction(sequence);
        m_dir = RD_FORWARD;
    }

}
void Runner::onEnterMoveSuperJump()
{
    TerrainLayer* terrainLayer = RunController::getInstance()->getTerrainLayer();
    if(terrainLayer)
    {
        AudioEngine::play2d("superjump.wav", false, 0.3f);
        float cellRadius = terrainLayer->getCellBaseRadius();
        this->stopAllActions();
        EaseSineOut* scaleTo1 = EaseSineOut::create(ScaleTo::create(0.05f, 1, 0.6f, 1));
        EaseSineIn* scaleTo2 = EaseSineIn::create(ScaleTo::create(0.015f, 1, 1.0f,1));
        Sequence* sequenceScale = Sequence::create(scaleTo1, scaleTo2, NULL);
        
        DelayTime* delay = DelayTime::create(0.05f);
        RotateTo* ratateTo = RotateTo::create(0.15f, Vec3(0,0,0));
        Sequence* sequenceRotate = Sequence::create(delay, ratateTo, NULL);
        EaseSineOut* rotateBy = nullptr;
        if(m_dir == RD_FORWARD)
            rotateBy = EaseSineOut::create(RotateBy::create(0.35f, Vec3(-360,0,0)));
        else if(m_dir == RD_LEFT)
            rotateBy = EaseSineOut::create(RotateBy::create(0.35f, Vec3(-360,-90,0)));
        else if(m_dir == RD_RIGHT)
            rotateBy = EaseSineOut::create(RotateBy::create(0.35f, Vec3(-360,90,0)));
        Spawn* spawnRotateBy = Spawn::create(sequenceRotate, rotateBy, NULL);
        
        EaseSineOut* moveUp = EaseSineOut::create(MoveTo::create(0.15f, Vec3(getPositionX(), getPositionY() + cellRadius*3, getPositionZ() - cellRadius*4)));
        EaseSineIn* moveDown = EaseSineIn::create(MoveTo::create(0.15f, Vec3(getPositionX(), getPositionY(), getPositionZ() - cellRadius*4)));
        Sequence* sequenceJump = Sequence::create(delay, moveUp, moveDown, NULL);
        Spawn* spawn = Spawn::create(sequenceScale, spawnRotateBy, sequenceJump, NULL);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Runner::checkSafe,this));
        Sequence* sequence = Sequence::create(spawn, callFunc, NULL);
        if (m_bSpeedUp)
            runAction(Speed::create(sequence, 2.0f));
        else
            runAction(sequence);
        m_dir = RD_FORWARD;
    }
}
void Runner::onEnterMoveJumpLocal()
{
    TerrainLayer* terrainLayer = RunController::getInstance()->getTerrainLayer();
    if(terrainLayer)
    {
        AudioEngine::play2d("jump.wav", false, 0.3f);
        float cellRadius = terrainLayer->getCellBaseRadius();
        
        EaseSineOut* scaleTo1 = EaseSineOut::create(ScaleTo::create(0.05f, 1, 0.9f, 1));
        EaseSineIn* scaleTo2 = EaseSineIn::create(ScaleTo::create(0.05f, 1, 1.0f,1));
        Sequence* sequenceScale = Sequence::create(scaleTo1, scaleTo2, NULL);
        
        DelayTime* delay = DelayTime::create(0.05f);
        
        EaseSineOut* moveUp = EaseSineOut::create(MoveTo::create(0.1f, Vec3(getPositionX(), getPositionY() + cellRadius*1.5, getPositionZ())));
        EaseSineOut* moveDown = EaseSineOut::create(MoveTo::create(0.1f, Vec3(getPositionX(), getPositionY(), getPositionZ())));
        Sequence* sequenceJump = Sequence::create(delay, moveUp, moveDown, NULL);
        Spawn* spawn = Spawn::create(sequenceScale, sequenceJump, NULL);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Runner::checkSafe,this));
        Sequence* sequence = Sequence::create(spawn, callFunc, NULL);
        if (m_bSpeedUp)
            runAction(Speed::create(sequence, 2.0f));
        else
            runAction(sequence);
    }
}
void Runner::onEnterMoveDrop()
{
    AudioEngine::play2d("drop.wav");
    EaseSineOut* moveTo = EaseSineOut::create(MoveTo::create(1.0f, Vec3(getPositionX(), -50, getPositionZ())));
    EaseSineOut* scaleTo = EaseSineOut::create(ScaleTo::create(1.0, 0.8f));
    DelayTime* delayTime = DelayTime::create(0.5f);
    EaseSineOut* fadeOut = EaseSineOut::create(FadeOut::create(0.5f));
    Sequence* sequece = Sequence::create(delayTime, fadeOut, NULL);
    Spawn* spawn = Spawn::create(moveTo, scaleTo, sequece, NULL);
    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(RunController::setGameState,RunController::getInstance(), RunController::RGS_GAMEOVER));
    Sequence* sequence = Sequence::create(spawn, callFunc, NULL);
    runAction(sequence);
    if(m_pFakeShadow)
        m_pFakeShadow->setVisible(false);
}
void Runner::onEnterDeath()
{
    AudioEngine::play2d("hit.wav", false, 0.5);
    RunController::getInstance()->addPlayerExplosion();
    if(m_pFakeShadow)
        m_pFakeShadow->setVisible(false);
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
void Runner::onExitMoveJumpLocal()
{
}
void Runner::onExitMoveDrop()
{
}
void Runner::onExitDeath()
{
}
void Runner::checkSafe()
{
    setState(RS_IDLE);
    if(isSpeedUp())
        RunController::getInstance()->cameraTrackPlayer();
    else
    {
        bool isDrop = RunController::getInstance()->getTerrainLayer()->checkRunnerDrop();
        if(isDrop)
            setState(RS_MOVE_DROP);
        else
            RunController::getInstance()->cameraTrackPlayer();
    }
}
void Runner::fadeIn()
{
    setPositionY(4);
    setState(RS_IDLE);
    DelayTime* delay = DelayTime::create(1.0f);
    EaseSineOut* fadeIn = EaseSineOut::create(FadeIn::create(0.5f));
    CallFunc* callback = CallFunc::create(CC_CALLBACK_0(RunController::setGameState, RunController::getInstance(), RunController::RGS_NORMAL));
    Sequence* sequence = Sequence::create(delay, fadeIn, callback, NULL);
    runAction(sequence);
}
void Runner::fadeOut()
{
    RunController::getInstance()->setGameState(RunController::RGS_FROZEN);
    EaseSineOut* fadeOut = EaseSineOut::create(FadeOut::create(0.5f));
    runAction(fadeOut);
}