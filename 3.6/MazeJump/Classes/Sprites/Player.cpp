//
//  Player.cpp
//  MazeJump
//
//  Created by wang haibo on 15/7/3.
//
//

#include "Player.h"
#include "GroundLayer.h"
#include "OutlineEffect3D.h"
#include "GameScene.h"
USING_NS_CC;

Player* Player::create(const std::string& modelPath, GroundLayer* ground)
{
    auto player = new (std::nothrow) Player();
    if (player && player->initWithFile(modelPath))
    {
        player->_contentSize = player->getBoundingBox().size;
        player->m_fRadius = player->_contentSize.width*0.5f;
        player->m_pGround = ground;
        player->setScale(0.375f);
        
        OutlineEffect3D* outline = OutlineEffect3D::create();
        outline->setOutlineColor(Vec3(0.3f, 0.3f, 0.3f));
        outline->setOutlineWidth(0.03f);
        player->addEffect(outline, 1);
        
        player->autorelease();
        return player;
    }
    CC_SAFE_DELETE(player);
    return nullptr;
}
Player::Player()
{
    m_curState  = PS_UNKNOWN;
    m_fRadius   = 2.5f;
    m_pGround   = nullptr;
}
void Player::setPlayerState(PlayerState state)
{
    if (m_curState == state)
        return;
    
    ///处理上一个状态退出逻辑
    switch (m_curState) {
        case PlayerState::PS_IDLE:
            onExitIdle();
            break;
        case PlayerState::PS_MOVE_LEFT:
            onExitMoveLeft();
            break;
        case PlayerState::PS_MOVE_RIGHT:
            onExitMoveRight();
            break;
        case PlayerState::PS_MOVE_UP:
            onExitMoveUp();
            break;
        case PlayerState::PS_MOVE_DOWN:
            onExitMoveDown();
            break;
        case PlayerState::PS_JUMP_STAY:
            onExitJumpStay();
            break;
        case PlayerState::PS_CHECK_NEXT_CELL:
            onExitCheckNextCell();
            break;
        case PlayerState::PS_CHECK_SPEICAL_ART:
            break;
        default:
            break;
    }
    
    m_curState = state;
    ///处理下一个状态进入逻辑
    switch (m_curState) {
        case PlayerState::PS_IDLE:
            onEnterIdle();
            break;
        case PlayerState::PS_MOVE_LEFT:
            onEnterMoveLeft();
            break;
        case PlayerState::PS_MOVE_RIGHT:
            onEnterMoveRight();
            break;
        case PlayerState::PS_MOVE_UP:
            onEnterMoveUp();
            break;
        case PlayerState::PS_MOVE_DOWN:
            onEnterMoveDown();
            break;
        case PlayerState::PS_JUMP_STAY:
            onEnterJumpStay();
            break;
        case PlayerState::PS_CHECK_NEXT_CELL:
            onEnterCheckNextCell();
            break;
        case PlayerState::PS_CHECK_SPEICAL_ART:
            onEnterCheckSpeicalArt();
        default:
            break;
    }
}
void Player::onEnterIdle()
{
    if(m_pGround)
    {
        m_pGround->showArrow();
        m_pGround->checkWinOrLose();
        if (m_pGround->getPlaying()) {
            m_pGround->setRecordState(GroundLayer::RecordState::RD_NEXT);
        }
    }
}
void Player::onEnterMoveLeft()
{
    if(m_pGround)
    {
        float cellRadius = m_pGround->getCellRadius();
        RotateTo* ratateTo = RotateTo::create(0.25f, Vec3(0,0,0));
        EaseSineOut* moveUp = EaseSineOut::create(MoveTo::create(0.25f, Vec3(getPositionX(), getPositionY() + cellRadius, getPositionZ() - cellRadius*2)));
        EaseSineIn* moveDown = EaseSineIn::create(MoveTo::create(0.25f, Vec3(getPositionX(), getPositionY(), getPositionZ() - cellRadius*2)));
        Sequence* sequenceJump = Sequence::create(moveUp, moveDown, NULL);
        Spawn* spawn = Spawn::create(ratateTo, sequenceJump, NULL);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Player::recalculateCells,this));
        Sequence* sequence = Sequence::create(spawn, callFunc, NULL);
        runAction(sequence);
    }
}
void Player::onEnterMoveRight()
{
    if(m_pGround)
    {
        float cellRadius = m_pGround->getCellRadius();
        RotateTo* ratateTo = RotateTo::create(0.25f, Vec3(0,180,0));
        EaseSineOut* moveUp = EaseSineOut::create(MoveTo::create(0.25f, Vec3(getPositionX(), getPositionY() + cellRadius, getPositionZ() + cellRadius*2)));
        EaseSineIn* moveDown = EaseSineIn::create(MoveTo::create(0.25f, Vec3(getPositionX(), getPositionY(), getPositionZ() + cellRadius*2)));
        Sequence* sequenceJump = Sequence::create(moveUp, moveDown, NULL);
        Spawn* spawn = Spawn::create(ratateTo, sequenceJump, NULL);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Player::recalculateCells,this));
        Sequence* sequence = Sequence::create(spawn, callFunc, NULL);
        runAction(sequence);
    }
}
void Player::onEnterMoveUp()
{
    if(m_pGround)
    {
        float cellRadius = m_pGround->getCellRadius();
        RotateTo* ratateTo = RotateTo::create(0.25f, Vec3(0,-90,0));
        EaseSineOut* moveUp = EaseSineOut::create(MoveTo::create(0.25f, Vec3(getPositionX() + cellRadius*2, getPositionY() + cellRadius, getPositionZ())));
        EaseSineIn* moveDown = EaseSineIn::create(MoveTo::create(0.25f, Vec3(getPositionX() + cellRadius*2, getPositionY(), getPositionZ())));
        Sequence* sequenceJump = Sequence::create(moveUp, moveDown, NULL);
        Spawn* spawn = Spawn::create(ratateTo, sequenceJump, NULL);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Player::recalculateCells,this));
        Sequence* sequence = Sequence::create(spawn, callFunc, NULL);
        runAction(sequence);
    }
}
void Player::onEnterMoveDown()
{
    if(m_pGround)
    {
        float cellRadius = m_pGround->getCellRadius();
        RotateTo* ratateTo = RotateTo::create(0.25f, Vec3(0,90,0));
        EaseSineOut* moveUp = EaseSineOut::create(MoveTo::create(0.25f, Vec3(getPositionX() - cellRadius*2, getPositionY() + cellRadius, getPositionZ())));
        EaseSineIn* moveDown = EaseSineIn::create(MoveTo::create(0.25f, Vec3(getPositionX() - cellRadius*2, getPositionY(), getPositionZ())));
        Sequence* sequenceJump = Sequence::create(moveUp, moveDown, NULL);
        Spawn* spawn = Spawn::create(ratateTo, sequenceJump, NULL);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Player::recalculateCells,this));
        Sequence* sequence = Sequence::create(spawn, callFunc, NULL);
        runAction(sequence);
    }
}
void Player::onEnterJumpStay()
{
    if(m_pGround)
    {
        float cellRadius = m_pGround->getCellRadius();
        EaseSineOut* moveUp = EaseSineOut::create(MoveTo::create(0.25f, Vec3(getPositionX(), getPositionY() + cellRadius, getPositionZ())));
        EaseSineIn* moveDown = EaseSineIn::create(MoveTo::create(0.25f, Vec3(getPositionX(), getPositionY(), getPositionZ())));
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Player::jumpFinish,this));
        Sequence* sequence = Sequence::create(moveUp, moveDown, callFunc, NULL);
        runAction(sequence);
    }
}
void Player::onEnterCheckNextCell()
{
    if(m_pGround)
    {
        if(m_nNextIndexX < 0 || m_nNextIndexX >= m_pGround->getMapSize().width)
            return;
        if(m_nNextIndexY < 0 || m_nNextIndexY >= m_pGround->getMapSize().height)
            return;
        GroundCell* pNextCell = m_pGround->getNextCell(m_nNextIndexX, m_nNextIndexY);
        if(pNextCell)
        {

            if (!pNextCell->isWalkCell())
                setPlayerState(PS_JUMP_STAY);
            else
            {
                if(m_nNextIndexY == m_nIndexY)
                {
                    if (m_nNextIndexX > m_nIndexX)
                        setPlayerState(PS_MOVE_RIGHT);
                    else if(m_nNextIndexX < m_nIndexX)
                        setPlayerState(PS_MOVE_LEFT);
                }
                if(m_nNextIndexX == m_nIndexX)
                {
                    if (m_nNextIndexY > m_nIndexY)
                        setPlayerState(PS_MOVE_UP);
                    else if(m_nNextIndexY < m_nIndexY)
                        setPlayerState(PS_MOVE_DOWN);
                }
            }
        }
    }
}
void Player::onEnterCheckSpeicalArt()
{
    GroundCell* currentCell = m_pGround->getNextCell(m_nIndexX, m_nIndexY);
    cocos2d::Size mapSize = m_pGround->getMapSize();
    if (currentCell)
    {
        GroundCell::CellType currentType = currentCell->getType();
        switch (currentType)
        {
            case GroundCell::CellType::CT_CARRY:
                {
                    for (int i = 0; i < mapSize.width ;i++) {
                        for (int j = 0; j < mapSize.height; j++) {
                            GroundCell* checkGroudCell = m_pGround->getNextCell(i, j);
                            if (currentCell->getIndexX()== checkGroudCell->getIndexX() &&
                                currentCell->getIndexY()== checkGroudCell->getIndexY()) {
                                continue;
                            }
                            if (currentType == checkGroudCell->getType() &&
                                currentCell->getCarryProp() == checkGroudCell->getCarryProp())
                                {
                                    
                                    auto jumpByPlayer = JumpBy::create(0.5, Vec2(0, 0), 5, 1);
                                    auto spawnPlayer = Spawn::create( MoveTo::create(0.3f, Vec3(this->getPositionX(), 2, this->getPositionZ())), Sequence::create(ScaleTo::create(0.5f, 0.1f),NULL), NULL);
                                    
                                    runAction(Sequence::create(Sequence::createWithTwoActions(jumpByPlayer, spawnPlayer),CallFuncN::create( CC_CALLBACK_1(Player::carryStar, this, checkGroudCell)),NULL));
                                
                                }
                        }
                    }
                }
                break;
            case GroundCell::CellType::CT_JUMP:
            {
                if(m_nNextIndexX < 0 || m_nNextIndexX >= m_pGround->getMapSize().width)
                    return;
                if(m_nNextIndexY < 0 || m_nNextIndexY >= m_pGround->getMapSize().height)
                    return;
                int targetIndexX = -1;
                int targetIndexY = -1;
                if(m_nNextIndexY == m_nIndexY)
                {
                    targetIndexY = m_nIndexY;
                    if (m_nNextIndexX > m_nIndexX)
                        targetIndexX = m_nNextIndexX + 1;
                    
                    else if(m_nNextIndexX < m_nIndexX)
                        targetIndexX = m_nNextIndexX - 1;

                    if (targetIndexX < 0 || targetIndexX >= m_pGround->getMapSize().width)
                        targetIndexX = m_nIndexX;
                }
                if(m_nNextIndexX == m_nIndexX)
                {
                    targetIndexX = m_nIndexX;
                    if (m_nNextIndexY > m_nIndexY)
                        targetIndexY = m_nNextIndexY + 1;
                    
                    else if(m_nNextIndexY < m_nIndexY)
                         targetIndexY = m_nNextIndexY - 1;
                    if (targetIndexY < 0 || targetIndexY >=m_pGround->getMapSize().width )
                        targetIndexY = m_nIndexY;
                   
                    
                }
                GroundCell* targetCell  = m_pGround->getNextCell(targetIndexX, targetIndexY);
                if (targetCell->getType() == GroundCell::CT_HIDE) {
                    
                    GameScene* gameScene = static_cast<GameScene*>(m_pGround->getParent());
                    EaseSineOut* scaleTo = EaseSineOut::create(ScaleTo::create(1.0f, 0));
                    float cellRadius = m_pGround->getCellRadius();
                    EaseSineOut* moveUp = EaseSineOut::create(MoveTo::create(0.25f, Vec3(getPositionX(), getPositionY() + cellRadius, getPositionZ()-cellRadius)));
                    EaseSineIn* moveDown = EaseSineIn::create(MoveTo::create(0.25f, Vec3(targetCell->getPositionX(), targetCell->getPositionY()+cellRadius, targetCell->getPositionZ())));
                    EaseSineOut* moveTo = EaseSineOut::create(MoveTo::create(1.0f, Vec3(targetCell->getPositionX(), targetCell->getPositionY()+cellRadius-50, targetCell->getPositionZ())));
                    
                    EaseSineOut* fadeOut = EaseSineOut::create(FadeOut::create(1.0f));
                    Spawn* spawn = Spawn::create( moveUp,moveDown,scaleTo,moveTo,fadeOut, NULL);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(GameScene::gameWin,gameScene));
                    Sequence* sequence = Sequence::create(spawn, callFunc, NULL);
                    runAction(sequence);
                }else
                {
                    m_pGround->carryCell(m_nIndexX, m_nIndexY);
                    float cellRadius = m_pGround->getCellRadius();
                    EaseSineOut* moveUp = EaseSineOut::create(MoveTo::create(0.25f, Vec3(getPositionX(), getPositionY() + cellRadius, getPositionZ()-cellRadius)));
                    EaseSineIn* moveDown = EaseSineIn::create(MoveTo::create(0.25f, Vec3(targetCell->getPositionX(), targetCell->getPositionY()+cellRadius, targetCell->getPositionZ())));
                    CallFunc* callFunc = CallFuncN::create( CC_CALLBACK_1(Player::speicaArtFinish, this, targetCell));
                    Sequence* sequence = Sequence::create(moveUp,moveDown, callFunc, NULL);
                    runAction(sequence);
                }
                
            }
                break;
            case GroundCell::CellType::CT_REVIVE:
            {
                
            }
                break;
            default:
                break;
                

        }
    }
    
}
void Player::onExitIdle()
{
}
void Player::onExitMoveLeft()
{
}
void Player::onExitMoveRight()
{
}
void Player::onExitMoveUp()
{
}
void Player::onExitMoveDown()
{
}
void Player::onExitJumpStay()
{
}
void Player::onExitCheckNextCell()
{
}
void Player::onExitCheckSpeicalArt()
{
    
}
void Player::recalculateCells()
{
    if(!m_pGround)
        return;
    switch (m_curState) {
        case PS_MOVE_LEFT:
            {
                m_nIndexX -= 1;
                m_nNextIndexX = m_nIndexX - 1;
                m_nNextIndexY = m_nIndexY;
                GroundCell* nextCell = m_pGround->getNextCell(m_nIndexX, m_nIndexY);
                if (nextCell && nextCell->isSpeicalArtCell()) {
                    setPlayerState(PlayerState::PS_CHECK_SPEICAL_ART);
                }else{
                    m_pGround->flipIndexCell(m_nIndexX, m_nIndexY);
                    if (m_nNextIndexX < 0)
                        setPlayerState(PlayerState::PS_JUMP_STAY);
                    else
                        setPlayerState(PlayerState::PS_CHECK_NEXT_CELL);
                }
                
            }
            break;
        case PS_MOVE_RIGHT:
            {
                m_nIndexX += 1;
                m_nNextIndexX = m_nIndexX + 1;
                m_nNextIndexY = m_nIndexY;
                GroundCell* nextCell = m_pGround->getNextCell(m_nIndexX, m_nIndexY);
                if (nextCell && nextCell->isSpeicalArtCell()) {
                    setPlayerState(PlayerState::PS_CHECK_SPEICAL_ART);
                }else{
                    m_pGround->flipIndexCell(m_nIndexX, m_nIndexY);
                    if (m_nNextIndexX >= m_pGround->getMapSize().width)
                        setPlayerState(PlayerState::PS_JUMP_STAY);
                    else
                        setPlayerState(PlayerState::PS_CHECK_NEXT_CELL);
                }
               
            }
            break;
        case PS_MOVE_DOWN:
            {
                m_nIndexY -= 1;
                m_nNextIndexX = m_nIndexX;
                m_nNextIndexY = m_nIndexY - 1;
                GroundCell* nextCell = m_pGround->getNextCell(m_nIndexX, m_nIndexY);
                if (nextCell && nextCell->isSpeicalArtCell()) {
                    setPlayerState(PlayerState::PS_CHECK_SPEICAL_ART);
                }else{
                    m_pGround->flipIndexCell(m_nIndexX, m_nIndexY);
                    if (m_nNextIndexY < 0)
                        setPlayerState(PlayerState::PS_JUMP_STAY);
                    else
                        setPlayerState(PlayerState::PS_CHECK_NEXT_CELL);
                }
                
            }
            break;
        case PS_MOVE_UP:
            {
                m_nIndexY += 1;
                m_nNextIndexX = m_nIndexX;
                m_nNextIndexY = m_nIndexY + 1;
                GroundCell* nextCell = m_pGround->getNextCell(m_nIndexX, m_nIndexY);
                if (nextCell && nextCell->isSpeicalArtCell()) {
                    setPlayerState(PlayerState::PS_CHECK_SPEICAL_ART);
                }else{
                    m_pGround->flipIndexCell(m_nIndexX, m_nIndexY);
                    if (m_nNextIndexY >= m_pGround->getMapSize().height)
                        setPlayerState(PlayerState::PS_JUMP_STAY);
                    else
                        setPlayerState(PlayerState::PS_CHECK_NEXT_CELL);
                }
                
            }
            break;
        default:
            break;
    }
}
void Player::jumpFinish()
{
    setPlayerState(PlayerState::PS_IDLE);
}
void Player::carryStar(Node* node,GroundCell* cell)
{
    this->setPosition3D(cell->getPosition3D() + Vec3(0,4,0));
    auto jumpByPlayer = JumpBy::create(0.5, Vec2(0, 0), 5, 1);
    m_pGround->carryCell(m_nIndexX, m_nIndexY);
    runAction(Sequence::create(Sequence::createWithTwoActions(ScaleTo::create(0.5f, 0.375f),jumpByPlayer),CallFuncN::create( CC_CALLBACK_1(Player::speicaArtFinish, this, cell)),NULL));
}
void Player::speicaArtFinish(Node* node,GroundCell* cell)
{
    m_pGround->carryCell(cell->getIndexX(), cell->getIndexY());
    m_nIndexX = cell->getIndexX();
    m_nIndexY = cell->getIndexY();
    setPlayerState(PlayerState::PS_IDLE);
}
