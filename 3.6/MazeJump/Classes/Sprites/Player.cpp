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
USING_NS_CC;

Player* Player::create(PlayerType type, GroundLayer* ground)
{
    auto player = new (std::nothrow) Player();
    if (player && player->initWithFile("strength.c3b"))
    {
        player->setTexture("strength.png");
        player->setType(type);
        player->_contentSize = player->getBoundingBox().size;
        player->m_fRadius = player->_contentSize.width*0.5f;
        player->m_pGround = ground;
        
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
    m_Type      = PT_UNKNOWN;
    m_pGround   = nullptr;
}
void Player::setType(PlayerType type)
{
    m_Type = type;
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
    }
}
void Player::onEnterMoveLeft()
{
    if(m_pGround)
    {
        float cellRadius = m_pGround->getCellRadius();
        RotateTo* ratateTo = RotateTo::create(0.25f, Vec3(0,180,0));
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
        RotateTo* ratateTo = RotateTo::create(0.25f, Vec3(0,0,0));
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
        RotateTo* ratateTo = RotateTo::create(0.25f, Vec3(0,90,0));
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
        RotateTo* ratateTo = RotateTo::create(0.25f, Vec3(0,-90,0));
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
            switch (m_Type) {
                case PT_STRENGTH:
                    {
                        if (pNextCell->getType() != GroundCell::CT_NOT && pNextCell->getType() != GroundCell::CT_BOMB)
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
                    break;
                case PT_AGILITY:
                    {
                    }
                    break;
                case PT_FLEXIBLE:
                    {
                    }
                    break;
                default:
                    break;
            }
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
                m_pGround->flipIndexCell(m_nIndexX, m_nIndexY);
                if (m_nNextIndexX < 0)
                    setPlayerState(PlayerState::PS_JUMP_STAY);
                else
                    setPlayerState(PlayerState::PS_CHECK_NEXT_CELL);
            }
            break;
        case PS_MOVE_RIGHT:
            {
                m_nIndexX += 1;
                m_nNextIndexX = m_nIndexX + 1;
                m_nNextIndexY = m_nIndexY;
                m_pGround->flipIndexCell(m_nIndexX, m_nIndexY);
                if (m_nNextIndexX >= m_pGround->getMapSize().width)
                    setPlayerState(PlayerState::PS_JUMP_STAY);
                else
                    setPlayerState(PlayerState::PS_CHECK_NEXT_CELL);
            }
            break;
        case PS_MOVE_DOWN:
            {
                m_nIndexY -= 1;
                m_nNextIndexX = m_nIndexX;
                m_nNextIndexY = m_nIndexY - 1;
                m_pGround->flipIndexCell(m_nIndexX, m_nIndexY);
                if (m_nNextIndexY < 0)
                    setPlayerState(PlayerState::PS_JUMP_STAY);
                else
                    setPlayerState(PlayerState::PS_CHECK_NEXT_CELL);
            }
            break;
        case PS_MOVE_UP:
            {
                m_nIndexY += 1;
                m_nNextIndexX = m_nIndexX;
                m_nNextIndexY = m_nIndexY + 1;
                m_pGround->flipIndexCell(m_nIndexX, m_nIndexY);
                if (m_nNextIndexY >= m_pGround->getMapSize().height)
                    setPlayerState(PlayerState::PS_JUMP_STAY);
                else
                    setPlayerState(PlayerState::PS_CHECK_NEXT_CELL);
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