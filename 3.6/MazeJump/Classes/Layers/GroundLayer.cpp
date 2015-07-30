//
//  GroundLayer.cpp
//  MazeJump
//
//  Created by wang haibo on 15/6/24.
//
//

#include "GroundLayer.h"
#include "UtilityHelper.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "StepManager.h"
#include "LevelsManager.h"
USING_NS_CC;
using namespace CocosDenshion;
GroundLayer* GroundLayer::create(int level,bool _isPlaying)
{
    GroundLayer *pRet = new(std::nothrow) GroundLayer();
    pRet->setPlaying(_isPlaying);
    if (pRet && pRet->init(level))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}
GroundLayer::GroundLayer()
{
    m_fCellRadius = 5.0f;
    m_Offset = Vec3::ZERO;
    m_pArrowUp = nullptr;
    m_pArrowDown = nullptr;
    m_pArrowLeft = nullptr;
    m_pArrowRight = nullptr;
    m_pCurrentCell = nullptr;
    m_pPlayer = nullptr;
    m_pCamera = nullptr;
    m_Playing = false;
    m_isInit = false;
    m_GroundTouchBegin = Vec2::ZERO;
    m_Level = -1;
}

bool GroundLayer::init(int level)
{
    if ( !Layer::init() )
        return false;
    
    m_Level = level;
    std::string tmxFile = LevelsManager::getInstance()->getLevelName(m_Level);
    TMXMapInfo *mapInfo = TMXMapInfo::create(tmxFile);
    if (!mapInfo || mapInfo->getObjectGroups().size() < 1)
        return false;
    
    m_MapSize = mapInfo->getMapSize();
    
    cocos2d::TMXObjectGroup* objectGroup = mapInfo->getObjectGroups().at(0);
    if(objectGroup->getObjects().size() == m_MapSize.width * m_MapSize.height)
    {
        for (int i = 0; i<m_MapSize.height; i++) {
            for (int j = 0; j<m_MapSize.width; j++) {
                int index = i*m_MapSize.width + j;
                Value value = objectGroup->getObjects().at(index);
                int type = value.asValueMap()["type"].asInt();
                GroundCell* cell = GroundCell::create(level,GroundCell::CellType(type));
                if(cell)
                {
                    
                    m_fCellRadius = cell->getRadius();
                    cell->setPosition3D(Vec3(i*(cell->getRadius())*2, -40, j*(cell->getRadius())*2));
                    cell->setScale(0.0f);
                    cell->setIndexX(j);
                    cell->setIndexY(i);
                    addChild( cell );
                    m_GroundCellList.pushBack(cell);
                    
                    switch (type) {
                        case GroundCell::CT_HIDE:
                            cell->setVisible(false);
                            break;
                        case GroundCell::CT_CARRY:
                            cell->setCarryProp(value.asValueMap()["carryprop"].asInt());
                            break;
                        case GroundCell::CT_REVIVE:
                        {
                            GroundCell* reveiveCell = GroundCell::create(level, GroundCell::CT_NOT);
                            reveiveCell->setPosition3D(Vec3(i*(cell->getRadius())*2, -40, j*(cell->getRadius())*2));
                            reveiveCell->setIndexX(j);
                            reveiveCell->setIndexY(i);
                            cell->setReviveCell(reveiveCell);
                            addChild(reveiveCell);
                            float time = cocos2d::random(1.0f, 2.0f);
                            EaseBackInOut* moveTo = EaseBackInOut::create(MoveTo::create(time, Vec3(i*(reveiveCell->getRadius())*2, 0, j*(reveiveCell->getRadius())*2)));
                            EaseSineIn* scaleTo = EaseSineIn::create(ScaleTo::create(1.0f, 0.9f));
                            Spawn* spawn = Spawn::createWithTwoActions(moveTo, scaleTo);
                            float delayTime = cocos2d::random(0.0f, 0.5f);
                            DelayTime* delay = DelayTime::create(delayTime);
                            Sequence* sequence = Sequence::createWithTwoActions(delay, spawn);
                            reveiveCell->runAction(sequence);
                            reveiveCell->setVisible(false);
                            
                        }

                            break;
                        default:
                            break;
                    }

                    float time = cocos2d::random(1.0f, 2.0f);
                    EaseBackInOut* moveTo = EaseBackInOut::create(MoveTo::create(time, Vec3(i*(cell->getRadius())*2, 0, j*(cell->getRadius())*2)));
                    EaseSineIn* scaleTo = EaseSineIn::create(ScaleTo::create(1.0f, 0.9f));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, scaleTo);
                    float delayTime = cocos2d::random(0.0f, 0.5f);
                    DelayTime* delay = DelayTime::create(delayTime);
                    Sequence* sequence = Sequence::createWithTwoActions(delay, spawn);
                    cell->runAction(sequence);
                }
            }
        }
        m_Offset = Vec3((m_MapSize.width-1)*m_fCellRadius , 0, (m_MapSize.height-1)*m_fCellRadius);
    }
    SimpleAudioEngine::getInstance()->playEffect("stoneroll.wav");
    
    m_pArrowUp = Arrow::create(Arrow::AT_UP);
    if(!m_pArrowUp)
        return false;
    m_pArrowUp->setVisible(false);
    m_pArrowUp->setScale(0.9f);
    addChild(m_pArrowUp);
    
    m_pArrowDown = Arrow::create(Arrow::AT_DOWN);
    if(!m_pArrowDown)
        return false;
    m_pArrowDown->setVisible(false);
    m_pArrowDown->setScale(0.9f);
    m_pArrowDown->setRotation3D(Vec3(0,180,0));
    addChild(m_pArrowDown);
    
    m_pArrowLeft = Arrow::create(Arrow::AT_LEFT);
    if(!m_pArrowLeft)
        return false;
    m_pArrowLeft->setVisible(false);
    m_pArrowLeft->setScale(0.9f);
    m_pArrowLeft->setRotation3D(Vec3(0,90,0));
    addChild(m_pArrowLeft);
    
    m_pArrowRight = Arrow::create(Arrow::AT_RIGHT);
    if(!m_pArrowRight)
        return false;
    m_pArrowRight->setVisible(false);
    m_pArrowRight->setScale(0.9f);
    m_pArrowRight->setRotation3D(Vec3(0,-90,0));
    addChild(m_pArrowRight);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto touchListener = EventListenerTouchAllAtOnce::create();
    if(touchListener == nullptr)
        return false;
    touchListener->onTouchesBegan = CC_CALLBACK_2(GroundLayer::onTouchesBegan, this);
    touchListener->onTouchesMoved = CC_CALLBACK_2(GroundLayer::onTouchesMoved, this);
    touchListener->onTouchesEnded = CC_CALLBACK_2(GroundLayer::onTouchesEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    DelayTime* delay = DelayTime::create(2.5f);
    runAction(Sequence::createWithTwoActions(delay, CallFunc::create(CC_CALLBACK_0(GroundLayer::initEnd,this))));
    
    
    return true;
}
Vector<GroundCell*> GroundLayer::getNeighborCells(GroundCell* currentCell)
{
    Vector<GroundCell*> cells;
    if(currentCell != nullptr)
    {
        ///down
        int indexX = currentCell->getIndexX();
        int indexY = currentCell->getIndexY()-1;
        if(indexY >= 0 && indexY < m_MapSize.height)
        {
            int index = indexY*m_MapSize.height + indexX;
            GroundCell* neighborCell = m_GroundCellList.at(index);
            if(neighborCell && m_pPlayer)
            {
                switch (m_pPlayer->getType()) {
                    case Player::PT_STRENGTH:
                    {
                        if (neighborCell->isWalkCell()) {
                            cells.pushBack(neighborCell);
                        }
                    }
                    break;
                        
                    default:
                        break;
                }
            }
        }
        ////up
        indexX = currentCell->getIndexX();
        indexY = currentCell->getIndexY()+1;
        if(indexY >= 0 && indexY < m_MapSize.height)
        {
            int index = indexY*m_MapSize.height + indexX;
            GroundCell* neighborCell = m_GroundCellList.at(index);
            if(neighborCell && m_pPlayer)
            {
                switch (m_pPlayer->getType()) {
                    case Player::PT_STRENGTH:
                    {
                        if (neighborCell->isWalkCell()) {
                            cells.pushBack(neighborCell);
                        }
                    }
                        break;
                        
                    default:
                        break;
                }
            }
        }
        ///left
        indexX = currentCell->getIndexX() - 1;
        indexY = currentCell->getIndexY();
        if(indexX >= 0 && indexX < m_MapSize.width)
        {
            int index = indexY*m_MapSize.height + indexX;
            GroundCell* neighborCell = m_GroundCellList.at(index);
            if(neighborCell && m_pPlayer)
            {
                switch (m_pPlayer->getType()) {
                    case Player::PT_STRENGTH:
                    {
                        if (neighborCell->isWalkCell()) {
                            cells.pushBack(neighborCell);
                        }
                    }
                        break;
                        
                    default:
                        break;
                }
            }
        }
        ////right
        indexX = currentCell->getIndexX() + 1;
        indexY = currentCell->getIndexY();
        if(indexX >= 0 && indexX < m_MapSize.width)
        {
            int index = indexY*m_MapSize.height + indexX;
            GroundCell* neighborCell = m_GroundCellList.at(index);
            if(neighborCell && m_pPlayer)
            {
                switch (m_pPlayer->getType()) {
                    case Player::PT_STRENGTH:
                    {
                        if (neighborCell->isWalkCell()) {
                            cells.pushBack(neighborCell);
                        }
                    }
                        break;
                        
                    default:
                        break;
                }
            }
        }

    }
    return cells;
}
GroundCell* GroundLayer::getNextCell(int nextIndexX, int nextIndexY)
{
    int nextIndex = nextIndexY*m_MapSize.height + nextIndexX;
    return m_GroundCellList.at(nextIndex);
}

void GroundLayer::flipIndexCell(int indexX, int indexY)
{
    if(indexX < 0 || indexX >= m_MapSize.width)
        return;
    if(indexY < 0 || indexY >= m_MapSize.height)
        return;
    
    int index = indexY*m_MapSize.width + indexX;
    m_pCurrentCell = m_GroundCellList.at(index);
    if(m_pCurrentCell && m_pPlayer)
    {
        RotateTo* ratateTo = nullptr;
        switch (m_pPlayer->getPlayerState()) {
            case Player::PS_MOVE_LEFT:
                ratateTo = RotateTo::create(0.3f, Vec3(-180,0,0));
                break;
            case Player::PS_MOVE_RIGHT:
                ratateTo = RotateTo::create(0.3f, Vec3(180,0,0));
                break;
            case Player::PS_MOVE_UP:
                ratateTo = RotateTo::create(0.3f, Vec3(0,0,180));
                break;
            case Player::PS_MOVE_DOWN:
                ratateTo = RotateTo::create(0.3f, Vec3(0,0,-180));
                break;
            default:
                break;
        }
        SimpleAudioEngine::getInstance()->playEffect("stoneflip.wav");
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(GroundLayer::setCurrentCellTypeOK,this));
        Sequence* sequence = Sequence::create(ratateTo, callFunc, NULL);
        GroundCell* reviceCell = m_pCurrentCell->getReviveCell();
        if (reviceCell)
        {
            if (m_pCurrentCell->getType() == GroundCell::CT_NOT && reviceCell->getType() == GroundCell::CT_NOT)
                reviceCell->runAction(sequence);
            else
                m_pCurrentCell->runAction(sequence);
        }else
            m_pCurrentCell->runAction(sequence);
        
    }
}
void GroundLayer::carryCell(int indexX,int indexY)
{
    if(indexX < 0 || indexX >= m_MapSize.width)
        return;
    if(indexY < 0 || indexY >= m_MapSize.height)
        return;
    
    int index = indexY*m_MapSize.width + indexX;
    m_pCurrentCell = m_GroundCellList.at(index);
    if (!m_pCurrentCell->isWalkCell()) {
        return;
    }
    RotateTo* ratateTo = RotateTo::create(0.5f, Vec3(180,0,0));
    m_pCurrentCell->setType(GroundCell::CT_OK);
    m_pCurrentCell->runAction(ratateTo);

}
void GroundLayer::setCurrentCellTypeOK()
{
    if(m_pCurrentCell)
    {
        if (m_pCurrentCell->getType() == GroundCell::CT_REVIVE) {
            m_pCurrentCell->setType(GroundCell::CT_NOT);
            m_pCurrentCell->getReviveCell()->setVisible(true);
            m_pCurrentCell->setVisible(false);
        }else
            m_pCurrentCell->setType(GroundCell::CT_OK);
        
        if(m_pPlayer == nullptr)
        {
            m_pPlayer = Player::create(Player::PT_STRENGTH, this);
            if(m_pPlayer)
            {
                m_pPlayer->setIndexX(m_pCurrentCell->getIndexX());
                m_pPlayer->setIndexY(m_pCurrentCell->getIndexY());
                m_pPlayer->setCameraMask((unsigned short)CameraFlag::USER1);
                m_pPlayer->setPosition3D(m_pCurrentCell->getPosition3D());
                m_pPlayer->setScale(0.9f);
                m_pPlayer->setPositionY(4.0f);
                m_pPlayer->setPlayerState(Player::PS_IDLE);
                addChild(m_pPlayer);
            }
        }
    }
}
void GroundLayer::checkWinOrLose()
{
    
    if(!m_pCurrentCell || !m_pPlayer)
        return;
    GroundCell* cell = m_pCurrentCell->getReviveCell();
    if(!cell && m_pCurrentCell->getType() == GroundCell::CT_NOT)
        return;
    
   
    if(m_pPlayer->getPlayerState() != Player::PS_IDLE)
        return;
    GameScene* gameScene = static_cast<GameScene*>(getParent());
    if(!gameScene)
        return;
    Vector<GroundCell*> neighborCells = getNeighborCells(m_pCurrentCell);
    for (int i = 0; i < neighborCells.size(); ++i) {
        GroundCell* cell = neighborCells.at(i);
        if(cell && cell->isWalkCell())
            return;
    }
    bool win = true;
    for (int i = 0; i<m_GroundCellList.size(); ++i) {
        GroundCell* cell = m_GroundCellList.at(i);
        if (!cell || cell->getType() == GroundCell::CT_NOT) {
            win = false;
            break;
        }
    }
    if (m_Playing) {
        setRecordState(RD_END);
        return;
    }
    if(win)
    {
           // EaseBackInOut* scaleTo = EaseBackInOut::create(ScaleTo::create(1.0f, 1.8f));
            DelayTime* delay = DelayTime::create(2.0f);
            CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(GameScene::gameWin,gameScene));
            Sequence* sequence = Sequence::create(callFunc, delay, NULL);
            this->runAction(sequence);
        
    }
    else
    {
        //EaseBackInOut* scaleTo = EaseBackInOut::create(ScaleTo::create(1.0f, 0.0f));
        DelayTime* delay = DelayTime::create(2.0f);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(GameScene::gameLose,gameScene));
        Sequence* sequence = Sequence::create(callFunc, delay, NULL);
        this->runAction(sequence);
    }
    
}
void GroundLayer::showArrow()
{
    Vector<GroundCell*> neighborCells = getNeighborCells(m_pCurrentCell);
    for (int i = 0; i < neighborCells.size(); ++i) {
        GroundCell* cell = neighborCells.at(i);
        if(cell)
        {
            if(cell->getIndexY() == m_pCurrentCell->getIndexY())
            {
                if (cell->getIndexX() > m_pCurrentCell->getIndexX()) {
                    m_pArrowRight->setVisible(true);
                    m_pArrowRight->setIndexX(cell->getIndexX());
                    m_pArrowRight->setIndexY(cell->getIndexY());
                    m_pArrowRight->setPosition3D(cell->getPosition3D() + Vec3(0,2,0));
                    
                }
                else if(cell->getIndexX() < m_pCurrentCell->getIndexX()) {
                    m_pArrowLeft->setVisible(true);
                    m_pArrowLeft->setIndexX(cell->getIndexX());
                    m_pArrowLeft->setIndexY(cell->getIndexY());
                    m_pArrowLeft->setPosition3D(cell->getPosition3D() + Vec3(0,2,0));
                    

                }
            }
            if(cell->getIndexX() == m_pCurrentCell->getIndexX())
            {
                if (cell->getIndexY() > m_pCurrentCell->getIndexY()) {
                    m_pArrowUp->setVisible(true);
                    m_pArrowUp->setIndexX(cell->getIndexX());
                    m_pArrowUp->setIndexY(cell->getIndexY());
                    m_pArrowUp->setPosition3D(cell->getPosition3D() + Vec3(0,2,0));
                    
                }
                else if(cell->getIndexY() < m_pCurrentCell->getIndexY()) {
                    m_pArrowDown->setVisible(true);
                    m_pArrowDown->setIndexX(cell->getIndexX());
                    m_pArrowDown->setIndexY(cell->getIndexY());
                    m_pArrowDown->setPosition3D(cell->getPosition3D() + Vec3(0,2,0));
                    
                }
            }
        }
    }
}
void GroundLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event *event)
{
    if (!m_isInit) {
        return;
    }
    
    if (m_Playing) {
        return;
    }
    if(touches.size() > 0)
    {
        m_GroundTouchBegin = convertToNodeSpace(touches[0]->getLocation());
        Ray ray;
        UtilityHelper::getCameraToViewportRay(m_pCamera, m_GroundTouchBegin, &ray);
        if(m_pCurrentCell == nullptr)
        {
            for (int i = 0; i< m_GroundCellList.size(); i++) {
                GroundCell* cell = m_GroundCellList.at(i);
                if(cell)
                {
                    if(ray.intersects(cell->getAABB()) && cell->getType() == GroundCell::CT_NOT)
                    {
                        seleckStartRolePlace(i);
                        break;
                    }
                }
            }
        }
        
    }
}
void GroundLayer::onTouchesMoved(const std::vector<Touch*>& touches, Event *event)
{
    
}
void GroundLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event *event)
{
    if (m_Playing) {
        return;
    }
    auto localTouchEnd = convertToNodeSpace(touches[0]->getLocation());
    float distanceX = fabsf(localTouchEnd.x - m_GroundTouchBegin.x);
    float distanceY = fabsf(localTouchEnd.y - m_GroundTouchBegin.y);
    if(distanceX>10 && distanceX >= distanceY)
    {
        if(localTouchEnd.x < m_GroundTouchBegin.x)
        {
            CCLOG("向左移动");
            checkSildeHandle(true, false, false, false);
        }
        
        else if(localTouchEnd.x > m_GroundTouchBegin.x)
        {
            CCLOG("向右移动");
            checkSildeHandle(false, false, false, true);
        }
        
    }
    if (distanceY >10 && distanceX <= distanceY) {
         if (localTouchEnd.y < m_GroundTouchBegin.y)
         {
             CCLOG("向下移动");
             checkSildeHandle(false, false, true, false);
         }
        
        else if (localTouchEnd.y > m_GroundTouchBegin.y)
        {
            CCLOG("向上移动");
            checkSildeHandle(false, true, false, false);
        }
        
    }
}
void GroundLayer::seleckStartRolePlace(int index)
{
    if(m_pCurrentCell == nullptr)
    {
        auto cell = m_GroundCellList.at(index);
        
        StepManager::getInstance()->setStep(index, Arrow::AT_UNKNOWN);
        
        m_pCurrentCell = cell;
        SimpleAudioEngine::getInstance()->playEffect("stoneflip.wav");
        RotateTo* ratateTo = RotateTo::create(0.5f, Vec3(180,0,0));
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(GroundLayer::setCurrentCellTypeOK,this));
        Sequence* sequence = Sequence::create(ratateTo, callFunc, NULL);
        cell->runAction(sequence);
    }

}
void GroundLayer::checkSildeHandle( bool isTouchDown , bool isToucLeft,bool isToucRight , bool isToucUp  )
{
    bool isCheckTouchDown = false;
    bool isCheckToucLeft = false;
    bool isCheckToucRight = false;
    bool isCheckToucUp = false;
    
    CCLOG("isTouchDown:%d , isToucLeft:%d, isToucRight:%d , isToucUp:%d", isTouchDown ,  isToucLeft, isToucRight ,  isToucUp);
    CCLOG("m_pArrowDown isVisible:%d ",m_pArrowDown->isVisible());
    CCLOG("m_pArrowLeft isVisible:%d",m_pArrowLeft->isVisible());
    CCLOG("m_pArrowRight isVisible:%d",m_pArrowRight->isVisible());
    CCLOG("m_pArrowUp isVisible:%d",m_pArrowUp->isVisible());
    if (m_pArrowDown || m_pArrowLeft || m_pArrowRight || m_pArrowUp) {

        if(isTouchDown && m_pArrowDown->isVisible()
                && m_pArrowDown->getType() == Arrow::AT_DOWN)
           isCheckTouchDown = true;
        
        if(isToucLeft && m_pArrowLeft->isVisible()
                && m_pArrowLeft->getType() == Arrow::AT_LEFT)
            isCheckToucLeft = true;
        
        if(isToucRight && m_pArrowRight->isVisible()
                && m_pArrowRight->getType() == Arrow::AT_RIGHT)
            isCheckToucRight= true;
        
        if (isToucUp && m_pArrowUp->isVisible()
                && m_pArrowUp->getType() == Arrow::AT_UP)
            isCheckToucUp = true;
        

    }

    if (isCheckTouchDown || isCheckToucLeft || isCheckToucRight || isCheckToucUp) {
        m_pArrowDown->setVisible(false);
        m_pArrowLeft->setVisible(false);
        m_pArrowRight->setVisible(false);
        m_pArrowUp->setVisible(false);
        
    }
    if (m_pPlayer) {
        
        int index = m_pCurrentCell->getIndexY()*m_MapSize.height + m_pCurrentCell->getIndexX();
       
        if (isCheckTouchDown){
            StepManager::getInstance()->setStep(index, Arrow::AT_DOWN);
            m_pPlayer->setPlayerState(Player::PS_MOVE_DOWN);
        }
        if (isCheckToucLeft){
            StepManager::getInstance()->setStep(index, Arrow::AT_LEFT);
            m_pPlayer->setPlayerState(Player::PS_MOVE_LEFT);
        }
        if (isCheckToucRight){
            StepManager::getInstance()->setStep(index, Arrow::AT_RIGHT);
            m_pPlayer->setPlayerState(Player::PS_MOVE_RIGHT);
        }
        if (isCheckToucUp){
            StepManager::getInstance()->setStep(index, Arrow::AT_UP);
            m_pPlayer->setPlayerState(Player::PS_MOVE_UP);
        }
    }
}
void GroundLayer::initEnd()
{
    m_isInit = true;
    setRecordState(RD_START);
}
void GroundLayer::playRecord()
{
    
        if (recordSteps.size() > 0) {
            
            Value step = recordSteps.front();
            
            CCLOG("step 位置:%d,方向:%d",step.asValueVector()[0].asInt(),step.asValueVector()[1].asInt());
            switch (step.asValueVector()[1].asInt()) {
                case Arrow::AT_UNKNOWN:
                    seleckStartRolePlace(step.asValueVector()[0].asInt());
                    break;
                case Arrow::AT_DOWN:
                    checkSildeHandle(true,false,false,false);
                    break;
                case Arrow::AT_LEFT:
                    checkSildeHandle(false,true,false,false);
                    break;
                case Arrow::AT_RIGHT:
                    checkSildeHandle(false,false,true,false);
                    break;
                case Arrow::AT_UP:
                    checkSildeHandle(false,false,false,true);
                    break;
                default:
                    break;
            }
            recordSteps.erase(recordSteps.begin());
            
        }
}
void GroundLayer::setRecordState(RecordState state)
{
    if (!m_Playing)
        return;
    switch (state) {
        case RD_START:
            recordSteps = StepManager::getInstance()->getLevelWinSteps(m_Level);
            playRecord();
            break;
        case RD_NEXT:
            playRecord();
            break;
        case RD_END:
        {
            GameScene* gameScene = static_cast<GameScene*>(getParent());
            if (!gameScene) {
                return;
            }
            DelayTime* delay = DelayTime::create(2.0f);
            CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(GameScene::gameRecordEnd,gameScene));
            Sequence* sequence = Sequence::create(callFunc, delay, NULL);
            this->runAction(sequence);
        }
            break;
        default:
            break;
    }
}