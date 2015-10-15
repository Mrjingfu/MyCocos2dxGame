//
//  Player.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/9.
//
//

#include "Player.hpp"
#include "TerrainTile.hpp"
#include "VoxelExplorer.h"
USING_NS_CC;

Player* Player::create(const std::string& modelPath)
{
    auto player = new (std::nothrow) Player();
    if (player && player->initWithFile(modelPath) && player->createPlayerLight())
    {
        player->_contentSize = player->getBoundingBox().size;
        player->setCameraMask((unsigned int)CameraFlag::USER1);
        player->autorelease();
        return player;
    }
    CC_SAFE_DELETE(player);
    return nullptr;
}
Player::Player()
{
    m_curState  = PS_UNKNOWN;
}
Player::~Player()
{
}
void Player::onEnter()
{
    Actor::onEnter();
    scheduleUpdate();
}
void Player::onExit()
{
    unscheduleUpdate();
    Actor::onExit();
}
void Player::update(float delta)
{
    if(m_pPlayerLight)
        m_pPlayerLight->setPosition3D(Vec3(getPositionX(),TerrainTile::CONTENT_SCALE*2,getPositionZ()));
}
void Player::setState(PlayerState state)
{
    if (m_curState == state)
        return;
    
    ///处理上一个状态退出逻辑
    switch (m_curState) {
        case PlayerState::PS_IDLE:
            onExitIdle();
            break;
        case PlayerState::PS_PREPARE_TO_JUMP:
            onExitPrepareToJump();
            break;
        case PlayerState::PS_JUMPLOCAL:
            onExitJumpLocal();
            break;
        case PlayerState::PS_JUMPMOVE:
            onExitJumpMove();
            break;
        case PlayerState::PS_DROP:
            onExitDrop();
            break;
        case PlayerState::PS_DEATH:
            onExitDeath();
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
        case PlayerState::PS_PREPARE_TO_JUMP:
            onEnterPrepareToJump();
            break;
        case PlayerState::PS_JUMPLOCAL:
            onEnterJumpLocal();
            break;
        case PlayerState::PS_JUMPMOVE:
            onEnterJumpMove();
            break;
        case PlayerState::PS_DROP:
            onEnterDrop();
            break;
        case PlayerState::PS_DEATH:
            onEnterDeath();
            break;
        default:
            break;
    }
}
void Player::rotateToLeft()
{
    if(getActionByTag(1))
        return;
    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(0.2f, Vec3(0,-90,0)));
    rotateTo->setTag(1);
    this->runAction(rotateTo);
    Actor::rotateToLeft();
}
void Player::rotateToRight()
{
    if(getActionByTag(2))
        return;
    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(0.2f, Vec3(0,90,0)));
    rotateTo->setTag(2);
    this->runAction(rotateTo);
    Actor::rotateToRight();
}
void Player::rotateToForward()
{
    if(getActionByTag(3))
        return;
    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(0.2f, Vec3(0,180,0)));
    rotateTo->setTag(3);
    this->runAction(rotateTo);
    Actor::rotateToForward();
}
void Player::rotateToBack()
{
    if(getActionByTag(4))
        return;
    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(0.2f, Vec3(0,0,0)));
    rotateTo->setTag(4);
    this->runAction(rotateTo);
    Actor::rotateToBack();
}
void Player::onEnterIdle()
{
}
void Player::onEnterPrepareToJump()
{
    EaseSineOut* scaleTo = EaseSineOut::create(ScaleTo::create(0.2f, 1.0f, 0.8f, 1.0f));
    this->runAction(scaleTo);
}
void Player::onEnterJumpLocal()
{
    ScaleTo* scaleTo = ScaleTo::create(0.1f, 1.0f, 1.0f, 1.0f);
    EaseSineOut* moveUp = EaseSineOut::create(MoveTo::create(0.1f, Vec3(getPositionX(), getPositionY() + TerrainTile::CONTENT_SCALE*0.5f, getPositionZ())));
    EaseSineOut* moveDown = EaseSineOut::create(MoveTo::create(0.1f, Vec3(getPositionX(), getPositionY(), getPositionZ())));
    Sequence* sequenceJump = Sequence::create(moveUp, moveDown, NULL);
    Spawn* spawn = Spawn::create(scaleTo, sequenceJump, NULL);
    CallFunc* callback = CallFunc::create(CC_CALLBACK_0(Player::onLand,this));
    Sequence* sequence = Sequence::create(spawn, callback, NULL);
    this->runAction(sequence);
}
void Player::onEnterJumpMove()
{
    Vec3 dir = Vec3::ZERO;
    switch (m_dir) {
        case AD_FORWARD:
            dir = Vec3(0, 0, -TerrainTile::CONTENT_SCALE);
            break;
        case AD_BACK:
            dir = Vec3(0, 0, TerrainTile::CONTENT_SCALE);
            break;
        case AD_LEFT:
            dir = Vec3(-TerrainTile::CONTENT_SCALE, 0, 0);
            break;
        case AD_RIGHT:
            dir = Vec3(TerrainTile::CONTENT_SCALE, 0, 0);
            break;
        default:
            break;
    }
    ScaleTo* scaleTo = ScaleTo::create(0.1f, 1.0f, 1.0f, 1.0f);
    EaseSineOut* moveUp = EaseSineOut::create(MoveTo::create(0.1f, Vec3(getPositionX(), getPositionY() + TerrainTile::CONTENT_SCALE*0.5f, getPositionZ()) + dir));
    EaseSineOut* moveDown = EaseSineOut::create(MoveTo::create(0.1f, Vec3(getPositionX(), getPositionY(), getPositionZ()) + dir));
    Sequence* sequenceJump = Sequence::create(moveUp, moveDown, NULL);
    Spawn* spawn = Spawn::create(scaleTo, sequenceJump, NULL);
    CallFunc* callback = CallFunc::create(CC_CALLBACK_0(Player::onLand,this));
    Sequence* sequence = Sequence::create(spawn, callback, NULL);
    this->runAction(sequence);
}
void Player::onEnterDrop()
{
}
void Player::onEnterDeath()
{
}

void Player::onExitIdle()
{
}
void Player::onExitPrepareToJump()
{
}
void Player::onExitJumpLocal()
{
}
void Player::onExitJumpMove()
{
}
void Player::onExitDrop()
{
}
void Player::onExitDeath()
{
}
void Player::onLand()
{
    setState(PS_IDLE);
    VoxelExplorer::getInstance()->cameraTrackPlayer();
}
bool Player::createPlayerLight()
{
    m_pPlayerLight = PointLight::create(getPosition3D()+Vec3(0,TerrainTile::CONTENT_SCALE*2,0), Color3B::WHITE, TerrainTile::CONTENT_SCALE*5);
    if(!m_pPlayerLight)
        return false;
    VoxelExplorer::getInstance()->get3DLayer()->addChild(m_pPlayerLight);
    return true;
}