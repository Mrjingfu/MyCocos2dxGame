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
#include "PlayerProperty.hpp"
#include "AlisaMethod.h"
#include "FakeShadow.hpp"
#include "RandomDungeon.hpp"
USING_NS_CC;

CChaosNumber Player::m_fSpeedupTime  = 20.0f; ///加速时间
CChaosNumber Player::m_fStealthTime  = 20.0f; ///隐身时间
CChaosNumber Player::m_fStrongerTime = 20.0f; ///强化时间

CChaosNumber Player::m_fFrozenTime   = 20.0f;  ///冰冻时间
CChaosNumber Player::m_fParalyticTime    = 8.0f;   ///麻痹时间
CChaosNumber Player::m_fFireTime     = 10.0f;  ///着火时间

Player* Player::create(const std::string& modelPath)
{
    auto player = new (std::nothrow) Player();
    if (player && player->initWithFile(modelPath) && player->createPlayerLight() && player->createFakeShadow())
    {
        player->_contentSize = player->getBoundingBox().size;
        player->setCameraMask((unsigned int)CameraFlag::USER1);
        player->setLightMask((unsigned int)LightFlag::LIGHT0 |(unsigned int)LightFlag::LIGHT1|(unsigned int)LightFlag::LIGHT2);
        player->refreshPlayerBuffer();
        player->autorelease();
        return player;
    }
    CC_SAFE_DELETE(player);
    return nullptr;
}
Player::Player()
{
    m_curState  = PS_UNKNOWN;
    m_pPlayerLight = nullptr;
    m_pFakeShadow = nullptr;
    m_bStealth = false;
    
    m_fSecondTimer = 1.0f;
    
    m_pHurtData = new (std::nothrow) HurtData();
}
Player::~Player()
{
    CC_SAFE_DELETE(m_pHurtData);
}
std::string Player::getIconRes()
{
    return "chr_sword.png";
}
std::string Player::getDesc()
{
    return "Main Player";
}

void Player::onEnter()
{
    Actor::onEnter();
    scheduleUpdate();
    addTerrainTileFlag(TileInfo::ATTACKABLE);
}
void Player::onExit()
{
    unscheduleUpdate();
    Actor::onExit();
}
void Player::update(float delta)
{
    if(m_curState != PS_DEATH)
        updatePlayerBuffer(delta);
    PlayerProperty::getInstance()->update(delta);
    if(m_pPlayerLight)
        m_pPlayerLight->setPosition3D(Vec3(getPositionX(),TerrainTile::CONTENT_SCALE*2,getPositionZ()));
    if(m_pFakeShadow)
        m_pFakeShadow->setPosition3D(Vec3(getPositionX(),-TerrainTile::CONTENT_SCALE*0.49f,getPositionZ()));
}
void Player::refreshPlayerBuffer()
{
    int bufferFlag = PlayerProperty::getInstance()->getPlayerBuffer();
    if((bufferFlag & PB_SPEEDUP) != 0)
    {
        ///增加拖尾或粒子
    }
    if((bufferFlag & PB_STEALTH) != 0)
    {
        setOpacity(127);
    }
    if((bufferFlag & PB_STRONGER) != 0)
    {
        ///增大
        setScale(1.5f);
    }

    if((bufferFlag & PB_POISONING) != 0)
    {
        auto tex = Director::getInstance()->getTextureCache()->addImage("chr_sword_green.png");
        if(tex)
            tex->setAliasTexParameters();
        setTexture(tex);
    }
    

    if((bufferFlag & PB_FROZEN) != 0)
    {
        auto tex = Director::getInstance()->getTextureCache()->addImage("chr_sword_blue.png");
        if(tex)
            tex->setAliasTexParameters();
        setTexture(tex);
    }
    

    if((bufferFlag & PB_PARALYTIC) != 0)
    {
        auto tex = Director::getInstance()->getTextureCache()->addImage("chr_sword_gray.png");
        if(tex)
            tex->setAliasTexParameters();
        setTexture(tex);
    }
    

    if((bufferFlag & PB_WEAK) != 0)
    {
        auto tex = Director::getInstance()->getTextureCache()->addImage("chr_sword_yellow.png");
        if(tex)
            tex->setAliasTexParameters();
        setTexture(tex);
    }

    if((bufferFlag & PB_FIRE) != 0)
    {
        auto tex = Director::getInstance()->getTextureCache()->addImage("chr_sword_red.png");
        if(tex)
            tex->setAliasTexParameters();
        setTexture(tex);
    }
}
void Player::addPlayerBuffer(PlayerBuffer buff)
{
    int bufferFlag = PlayerProperty::getInstance()->getPlayerBuffer();
    if(buff == PB_SPEEDUP)
    {
        if((bufferFlag & PB_SPEEDUP) != 0)
            m_fSpeedupTime = 20.0f;
        else
        {
            ///增加拖尾或粒子
            PlayerProperty::getInstance()->addPlayerBuffer(buff);
        }
    }
    else if(buff == PB_STEALTH)
    {
        if((bufferFlag & PB_STEALTH) != 0)
            m_fStealthTime = 20.0f;
        else
        {
            ///渐变
            EaseSineOut* fadeTo = EaseSineOut::create(FadeTo::create(1.0f, 127));
            this->runAction(fadeTo);
            PlayerProperty::getInstance()->addPlayerBuffer(buff);
        }
       
    }
    else if(buff == PB_STRONGER)
    {
        if((bufferFlag & PB_STRONGER) != 0)
            m_fStrongerTime = 20.0f;
        else
        {
            ///增大
            EaseSineOut* fadeTo = EaseSineOut::create(ScaleTo::create(1.0f, 1.5f));
            this->runAction(fadeTo);
            PlayerProperty::getInstance()->addPlayerBuffer(buff);
        }
    }
    else if(buff == PB_POISONING)
    {
        if((bufferFlag & PB_POISONING) == 0)
        {
            auto tex = Director::getInstance()->getTextureCache()->addImage("chr_sword_green.png");
            if(tex)
                tex->setAliasTexParameters();
            setTexture(tex);
            PlayerProperty::getInstance()->addPlayerBuffer(buff);
        }
    }
    else if(buff == PB_FROZEN)
    {
        if((bufferFlag & PB_FROZEN) == 0)
        {
            m_fFrozenTime = 20.0f;
            auto tex = Director::getInstance()->getTextureCache()->addImage("chr_sword_blue.png");
            if(tex)
                tex->setAliasTexParameters();
            setTexture(tex);
            PlayerProperty::getInstance()->addPlayerBuffer(buff);
        }
    }
    else if(buff == PB_PARALYTIC)
    {
        if((bufferFlag & PB_PARALYTIC) == 0)
        {
            m_fParalyticTime = 8.0f;
            auto tex = Director::getInstance()->getTextureCache()->addImage("chr_sword_gray.png");
            if(tex)
                tex->setAliasTexParameters();
            setTexture(tex);
            PlayerProperty::getInstance()->addPlayerBuffer(buff);
        }
    }
    else if(buff == PB_WEAK)
    {
        if((bufferFlag & PB_WEAK) == 0)
        {
            auto tex = Director::getInstance()->getTextureCache()->addImage("chr_sword_yellow.png");
            if(tex)
                tex->setAliasTexParameters();
            setTexture(tex);
            PlayerProperty::getInstance()->addPlayerBuffer(buff);
        }
    }
    else if(buff == PB_FIRE)
    {
        if((bufferFlag & PB_FIRE) == 0)
        {
            m_fFireTime = 10.0f;
            auto tex = Director::getInstance()->getTextureCache()->addImage("chr_sword_red.png");
            if(tex)
                tex->setAliasTexParameters();
            setTexture(tex);
            PlayerProperty::getInstance()->addPlayerBuffer(buff);
        }
    }
}
void Player::removePlayerBuffer(PlayerBuffer buff)
{
    int bufferFlag = PlayerProperty::getInstance()->getPlayerBuffer();
    if(buff == PB_POISONING)
    {
        if((bufferFlag & PB_POISONING) == 0)
        {
            std::string texName = "chr_sword.png";
            if((bufferFlag & PB_WEAK) != 0)
                texName = "chr_sword_yellow.png";
            else if((bufferFlag & PB_PARALYTIC) != 0)
                texName = "chr_sword_gray.png";
            else if((bufferFlag & PB_FIRE) != 0)
                texName = "chr_sword_red.png";
            else if((bufferFlag & PB_FROZEN) != 0)
                texName = "chr_sword_blue.png";
            auto tex = Director::getInstance()->getTextureCache()->addImage(texName);
            if(tex)
                tex->setAliasTexParameters();
            setTexture(tex);
        }
    }
    else if(buff == PB_WEAK)
    {
        if((bufferFlag & PB_WEAK) == 0)
        {
            std::string texName = "chr_sword.png";
            if((bufferFlag & PB_POISONING) != 0)
                texName = "chr_sword_green.png";
            else if((bufferFlag & PB_PARALYTIC) != 0)
                texName = "chr_sword_gray.png";
            else if((bufferFlag & PB_FIRE) != 0)
                texName = "chr_sword_red.png";
            else if((bufferFlag & PB_FROZEN) != 0)
                texName = "chr_sword_blue.png";
            auto tex = Director::getInstance()->getTextureCache()->addImage(texName);
            if(tex)
                tex->setAliasTexParameters();
            setTexture(tex);
            
        }
    }
    PlayerProperty::getInstance()->removePlayerBuffer(buff);
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
        case PlayerState::PS_ATTACK:
            onExitAttack();
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
        case PlayerState::PS_ATTACK:
            onEnterAttack();
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
void Player::setStealth(bool stealth)
{
    if(m_bStealth != stealth)
    {
        m_bStealth = stealth;
        if(m_bStealth)
        {
            EaseSineOut* fadeTo = EaseSineOut::create(FadeTo::create(1.0f, 127));
            this->runAction(fadeTo);
        }
        else
        {
            EaseSineOut* fadeTo = EaseSineOut::create(FadeTo::create(1.0f, 255));
            this->runAction(fadeTo);
        }
    }
}
bool Player::isParalytic()
{
    return (PlayerProperty::getInstance()->getPlayerBuffer() & PB_PARALYTIC) != 0;
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
void Player::attackByMonster(MonsterProperty* monsterProperty, bool miss)
{
    ///for debug
    return;
    
    if(!monsterProperty || !m_pHurtData)
        return;
    
    m_pHurtData->reset();
    m_pHurtData->m_vPos = this->getPosition3D();
    if(miss)
    {
        m_pHurtData->m_bDodge = true;
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_HURT, m_pHurtData);
        return;
    }
    
    float percentDodgeRate = PlayerProperty::getInstance()->getDodgeRate().GetFloatValue();
    float percentHit = 1.0 - percentDodgeRate;
    AlisaMethod* amDodgeRate = AlisaMethod::create(percentDodgeRate,percentHit,-1.0, NULL);
    if(amDodgeRate)
    {
        if(amDodgeRate->getRandomIndex() == 0)
        {
            m_pHurtData->m_bDodge = true;
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_HURT, m_pHurtData);
            return;
        }
    }
    int attack = monsterProperty->getRandomAttack().GetLongValue();
    float percentCriticalStrikeRate = monsterProperty->getCriticalStrikeRate().GetFloatValue();
    float percentNormal = 1.0 - percentCriticalStrikeRate;
    AlisaMethod* amCriticalStrikeRate = AlisaMethod::create(percentCriticalStrikeRate,percentNormal,-1.0, NULL);
    if(amCriticalStrikeRate)
    {
        if(amCriticalStrikeRate->getRandomIndex() == 0)
        {
            attack = attack*2.0f;
            m_pHurtData->m_bCriticalStrike = true;
        }
    }
    
    int defense = PlayerProperty::getInstance()->getDefense().GetLongValue();
    
    attack = MAX(attack + defense, 0);
    
    float percentBlockRate = PlayerProperty::getInstance()->getBlockRate().GetFloatValue();
    float percentNull = 1.0 - percentBlockRate;
    AlisaMethod* amBlockRate = AlisaMethod::create(percentBlockRate,percentNull,-1.0, NULL);
    if(amBlockRate)
    {
        if(amBlockRate->getRandomIndex() == 0)
        {
            attack = attack*0.5f;
            m_pHurtData->m_bBlocked = true;
        }
    }
    
    int currentHp = PlayerProperty::getInstance()->getCurrentHP().GetLongValue();
    currentHp = MAX(currentHp - attack , 0);
    CCLOG("Player: CurrentHp = %d, monsterAttack = %d", currentHp, attack);
    m_pHurtData->m_nDamage = -attack;
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_HURT, m_pHurtData);
    if(currentHp == 0)
    {
        setState(PS_DEATH);
        PlayerProperty::getInstance()->setCurrentHP(currentHp);
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_DEATH, this);
    }
    else
    {
        PlayerProperty::getInstance()->setCurrentHP(currentHp);
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_PROPERTY_DIRTY, this);
    }
}
void Player::attackByBoss(BossProperty* bossProperty, bool miss)
{
    //for debug
    return;
    
    if(!bossProperty || !m_pHurtData)
        return;
    
    m_pHurtData->reset();
    m_pHurtData->m_vPos = this->getPosition3D();
    if(miss)
    {
        m_pHurtData->m_bDodge = true;
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_HURT, m_pHurtData);
        return;
    }
    
    float percentDodgeRate = PlayerProperty::getInstance()->getDodgeRate().GetFloatValue();
    float percentHit = 1.0 - percentDodgeRate;
    AlisaMethod* amDodgeRate = AlisaMethod::create(percentDodgeRate,percentHit,-1.0, NULL);
    if(amDodgeRate)
    {
        if(amDodgeRate->getRandomIndex() == 0)
        {
            m_pHurtData->m_bDodge = true;
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_HURT, m_pHurtData);
            return;
        }
    }
    int attack = bossProperty->getRandomAttack().GetLongValue();
    float percentCriticalStrikeRate = bossProperty->getCriticalStrikeRate().GetFloatValue();
    float percentNormal = 1.0 - percentCriticalStrikeRate;
    AlisaMethod* amCriticalStrikeRate = AlisaMethod::create(percentCriticalStrikeRate,percentNormal,-1.0, NULL);
    if(amCriticalStrikeRate)
    {
        if(amCriticalStrikeRate->getRandomIndex() == 0)
        {
            attack = attack*2.0f;
            m_pHurtData->m_bCriticalStrike = true;
        }
    }
    
    int defense = PlayerProperty::getInstance()->getDefense().GetLongValue();
    
    attack = MAX(attack + defense, 0);
    
    float percentBlockRate = PlayerProperty::getInstance()->getBlockRate().GetFloatValue();
    float percentNull = 1.0 - percentBlockRate;
    AlisaMethod* amBlockRate = AlisaMethod::create(percentBlockRate,percentNull,-1.0, NULL);
    if(amBlockRate)
    {
        if(amBlockRate->getRandomIndex() == 0)
        {
            attack = attack*0.5f;
            m_pHurtData->m_bBlocked = true;
        }
    }
    
    int currentHp = PlayerProperty::getInstance()->getCurrentHP().GetLongValue();
    currentHp = MAX(currentHp - attack , 0);
    CCLOG("Player: CurrentHp = %d, bossAttack = %d", currentHp, attack);
    m_pHurtData->m_nDamage = -attack;
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_HURT, m_pHurtData);
    if(currentHp == 0)
    {
        setState(PS_DEATH);
        PlayerProperty::getInstance()->setCurrentHP(currentHp);
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_DEATH, this);
    }
    else
    {
        PlayerProperty::getInstance()->setCurrentHP(currentHp);
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_PROPERTY_DIRTY, this);
    }
}
void Player::hurtByGrippingTrap()
{
    if(!m_pHurtData)
        return;
    
    m_pHurtData->reset();
    m_pHurtData->m_vPos = this->getPosition3D();
    
    int attack = PlayerProperty::getInstance()->getMaxHP() * cocos2d::random(0.2f, 0.5f);
    int currentHp = PlayerProperty::getInstance()->getCurrentHP().GetLongValue();
    currentHp = MAX(currentHp - attack , 0);
    CCLOG("Player: CurrentHp = %d, GrippingTrap Attack = %d", currentHp, attack);
    
    m_pHurtData->m_nDamage = -attack;
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_HURT, m_pHurtData);
    if(currentHp == 0)
    {
        setState(PS_DEATH);
        PlayerProperty::getInstance()->setCurrentHP(currentHp);
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_DEATH, this);
    }
    else
    {
        PlayerProperty::getInstance()->setCurrentHP(currentHp);
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_PROPERTY_DIRTY, this);
    }
}
void Player::onEnterIdle()
{
    EaseSineOut* scaleTo = EaseSineOut::create(ScaleTo::create(0.1f, 1.0f, 1.0f, 1.0f));
    this->runAction(scaleTo);
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
    EaseSineOut* moveDown = EaseSineOut::create(MoveTo::create(0.1f, getPosition3D()));
    Sequence* sequenceJump = Sequence::create(moveUp, moveDown, NULL);
    Spawn* spawn = Spawn::create(scaleTo, sequenceJump, NULL);
    CallFunc* callback = CallFunc::create(CC_CALLBACK_0(Player::onLand,this,true));
    Sequence* sequence = Sequence::create(spawn, callback, NULL);
    
    int bufferFlag = PlayerProperty::getInstance()->getPlayerBuffer();
    if((bufferFlag & PlayerBuffer::PB_SPEEDUP) != 0)
        this->runAction(Speed::create(sequence, 2.0f));
    else if((bufferFlag & PlayerBuffer::PB_FROZEN) != 0)
        this->runAction(Speed::create(sequence, 0.5f));
    else
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
    Vec3 playerNextPos = getPosition3D() + dir;
    Vec2 nextPosInMap = Vec2((int)(playerNextPos.x/TerrainTile::CONTENT_SCALE), (int)(-playerNextPos.z /TerrainTile::CONTENT_SCALE));
    removeTerrainTileFlag(TileInfo::ATTACKABLE);
    addTerrainTileFlagByPos(TileInfo::ATTACKABLE, nextPosInMap);
    ScaleTo* scaleTo = ScaleTo::create(0.1f, 1.0f, 1.0f, 1.0f);
    EaseSineOut* moveUp = EaseSineOut::create(MoveTo::create(0.1f, Vec3(getPositionX(), getPositionY() + TerrainTile::CONTENT_SCALE*0.5f, getPositionZ()) + dir));
    EaseSineOut* moveDown = EaseSineOut::create(MoveTo::create(0.1f, Vec3(getPositionX(), getPositionY(), getPositionZ()) + dir));
    Sequence* sequenceJump = Sequence::create(moveUp, moveDown, NULL);
    Spawn* spawn = Spawn::create(scaleTo, sequenceJump, NULL);
    CallFunc* callback = CallFunc::create(CC_CALLBACK_0(Player::onLand,this,true));
    Sequence* sequence = Sequence::create(spawn, callback, NULL);
    
    int bufferFlag = PlayerProperty::getInstance()->getPlayerBuffer();
    if((bufferFlag & PlayerBuffer::PB_SPEEDUP) != 0)
        this->runAction(Speed::create(sequence, 2.0f));
    else if((bufferFlag & PlayerBuffer::PB_FROZEN) != 0)
        this->runAction(Speed::create(sequence, 0.5f));
    else
        this->runAction(sequence);
}
void Player::onEnterAttack()
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
    EaseSineOut* moveUp = EaseSineOut::create(MoveTo::create(0.1f, Vec3(getPositionX(), getPositionY() + TerrainTile::CONTENT_SCALE*0.25f, getPositionZ()) + dir*0.4f));
    Vec3 monsterPos = getPosition3D() + dir;
    Vec2 posInMap = Vec2((int)(monsterPos.x/TerrainTile::CONTENT_SCALE), (int)(-monsterPos.z /TerrainTile::CONTENT_SCALE));
    CallFunc* callback = CallFunc::create(CC_CALLBACK_0(VoxelExplorer::handleMonsterHurt,VoxelExplorer::getInstance(),posInMap));
    EaseSineOut* moveDown = EaseSineOut::create(MoveTo::create(0.1f, getPosition3D()));
    Sequence* sequenceJump = Sequence::create(moveUp, callback, moveDown, NULL);
    Spawn* spawn = Spawn::create(scaleTo, sequenceJump, NULL);
    CallFunc* callback2 = CallFunc::create(CC_CALLBACK_0(Player::onLand,this,false));
    Sequence* sequence = Sequence::create(spawn, callback2, NULL);
    
    int bufferFlag = PlayerProperty::getInstance()->getPlayerBuffer();
    if((bufferFlag & PlayerBuffer::PB_SPEEDUP) != 0)
        this->runAction(Speed::create(sequence, 2.0f));
    else if((bufferFlag & PlayerBuffer::PB_FROZEN) != 0)
        this->runAction(Speed::create(sequence, 0.5f));
    else
        this->runAction(sequence);
}
void Player::onEnterDrop()
{
}
void Player::onEnterDeath()
{
    auto tex = Director::getInstance()->getTextureCache()->addImage("chr_sword.png");
    if(tex)
        tex->setAliasTexParameters();
    setTexture(tex);
    PlayerProperty::getInstance()->resetPlayerBuffer();
    this->stopAllActions();
    removeTerrainTileFlag(TileInfo::ATTACKABLE);
    if(m_pFakeShadow)
        m_pFakeShadow->setVisible(false);
    this->setVisible(false);
    VoxelExplorer::getInstance()->addExplosion(getPosition3D());
    VoxelExplorer::getInstance()->updateMiniMap();
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
void Player::onExitAttack()
{
}
void Player::onExitDrop()
{
}
void Player::onExitDeath()
{
}
void Player::onLand(bool triggerTrap)
{
    setState(PS_IDLE);
    VoxelExplorer::getInstance()->cameraTrackPlayer();
    VoxelExplorer::getInstance()->checkPickItem();
    VoxelExplorer::getInstance()->checkUpdateFogOfWar();
    if(triggerTrap)
        VoxelExplorer::getInstance()->checkTriggerTrap();
    VoxelExplorer::getInstance()->updateMiniMap();
   // if(RandomDungeon::getInstance()->getCurrentDungeonNode()->isBossDepth())
        VoxelExplorer::getInstance()->updateBossRoomDoor();
    CCLOG("player x = %d   y = %d", (int)getPosInMap().x, (int)getPosInMap().y);
}
void Player::updatePlayerBuffer(float delta)
{
    int bufferFlag = PlayerProperty::getInstance()->getPlayerBuffer();
    if((bufferFlag & PB_SPEEDUP) != 0)
    {
        m_fSpeedupTime = m_fSpeedupTime - delta;
        if(m_fSpeedupTime <= 0)
            removePlayerBuffer(PB_SPEEDUP);
    }
    if((bufferFlag & PB_STEALTH) != 0)
    {
        m_fStealthTime = m_fStealthTime - delta;
        if(m_fStealthTime <= 0)
        {
            ///渐变
            EaseSineOut* fadeTo = EaseSineOut::create(FadeTo::create(1.0f, 255));
            this->runAction(fadeTo);
            removePlayerBuffer(PB_STEALTH);
        }
    }
    if((bufferFlag & PB_STRONGER) != 0)
    {
        m_fStrongerTime = m_fStrongerTime - delta;
        if(m_fStrongerTime <= 0)
        {
            ///缩小
            EaseSineOut* fadeTo = EaseSineOut::create(ScaleTo::create(1.0f, 1.0f));
            this->runAction(fadeTo);
            removePlayerBuffer(PB_STRONGER);
        }
    }
    if((bufferFlag & PB_FROZEN) != 0)
    {
        m_fFrozenTime = m_fFrozenTime - delta;
        if(m_fFrozenTime <= 0)
        {
            std::string texName = "chr_sword.png";
            if((bufferFlag & PB_POISONING) != 0)
                texName = "chr_sword_green.png";
            else if((bufferFlag & PB_WEAK) != 0)
                texName = "chr_sword_yellow.png";
            else if((bufferFlag & PB_PARALYTIC) != 0)
                texName = "chr_sword_gray.png";
            else if((bufferFlag & PB_FIRE) != 0)
                texName = "chr_sword_red.png";
            auto tex = Director::getInstance()->getTextureCache()->addImage(texName);
            if(tex)
                tex->setAliasTexParameters();
            setTexture(tex);
            removePlayerBuffer(PB_FROZEN);
        }
    }
    if((bufferFlag & PB_PARALYTIC) != 0)
    {
        m_fParalyticTime = m_fParalyticTime - delta;
        if(m_fParalyticTime <= 0)
        {
            std::string texName = "chr_sword.png";
            if((bufferFlag & PB_POISONING) != 0)
                texName = "chr_sword_green.png";
            else if((bufferFlag & PB_WEAK) != 0)
                texName = "chr_sword_yellow.png";
            else if((bufferFlag & PB_FIRE) != 0)
                texName = "chr_sword_red.png";
            else if((bufferFlag & PB_FROZEN) != 0)
                texName = "chr_sword_blue.png";
            auto tex = Director::getInstance()->getTextureCache()->addImage(texName);
            if(tex)
                tex->setAliasTexParameters();
            setTexture(tex);
            removePlayerBuffer(PB_PARALYTIC);
        }
    }
    if((bufferFlag & PB_FIRE) != 0)
    {
        m_fFireTime = m_fFireTime - delta;
        if(m_fFireTime <= 0)
        {
            std::string texName = "chr_sword.png";
            if((bufferFlag & PB_POISONING) != 0)
                texName = "chr_sword_green.png";
            else if((bufferFlag & PB_WEAK) != 0)
                texName = "chr_sword_yellow.png";
            else if((bufferFlag & PB_PARALYTIC) != 0)
                texName = "chr_sword_gray.png";
            else if((bufferFlag & PB_FROZEN) != 0)
                texName = "chr_sword_blue.png";
            auto tex = Director::getInstance()->getTextureCache()->addImage(texName);
            if(tex)
                tex->setAliasTexParameters();
            setTexture(tex);
            removePlayerBuffer(PB_FIRE);
        }
        else
        {
            m_fSecondTimer = m_fSecondTimer - delta;
            if(m_fSecondTimer <=0)
            {
                m_pHurtData->reset();
                m_pHurtData->m_vPos = this->getPosition3D();
                
                int deltaHp = PlayerProperty::getInstance()->getMaxHP() * 0.05f;
                int currentHp = PlayerProperty::getInstance()->getCurrentHP().GetLongValue();
                currentHp = MAX(currentHp - deltaHp , 0);
                m_pHurtData->m_nDamage = - deltaHp;
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_HURT, m_pHurtData);
                if(currentHp == 0)
                {
                    setState(PS_DEATH);
                    PlayerProperty::getInstance()->setCurrentHP(currentHp);
                    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_DEATH, this);
                }
                else
                {
                    PlayerProperty::getInstance()->setCurrentHP(currentHp);
                    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_PROPERTY_DIRTY, this);
                }
                m_fSecondTimer = 1.0f;
            }
        }
    }
    if((bufferFlag & PB_POISONING) != 0)
    {
        m_fSecondTimer = m_fSecondTimer - delta;
        if(m_fSecondTimer <=0)
        {
            m_pHurtData->reset();
            m_pHurtData->m_vPos = this->getPosition3D();
            
            int currentHp = PlayerProperty::getInstance()->getCurrentHP().GetLongValue();
            currentHp = MAX(currentHp - 5 , 0);
            m_pHurtData->m_nDamage = - 5;
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_HURT, m_pHurtData);
            if(currentHp == 0)
            {
                setState(PS_DEATH);
                PlayerProperty::getInstance()->setCurrentHP(currentHp);
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_DEATH, this);
            }
            else
            {
                PlayerProperty::getInstance()->setCurrentHP(currentHp);
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_PROPERTY_DIRTY, this);
            }
            m_fSecondTimer = 1.0f;
        }
    }
}
bool Player::createPlayerLight()
{
    m_pPlayerLight = PointLight::create(getPosition3D()+Vec3(0,TerrainTile::CONTENT_SCALE*0.5f,0), Color3B::WHITE, 0.5f*TerrainTile::CONTENT_SCALE*PlayerProperty::getInstance()->getLightDistance().GetLongValue());
    if(!m_pPlayerLight)
        return false;
    m_pPlayerLight->setLightFlag(LightFlag::LIGHT0);
    VoxelExplorer::getInstance()->get3DLayer()->addChild(m_pPlayerLight);
    
    AmbientLight* ambLight = AmbientLight::create(Color3B(50, 50, 50));
    if(!ambLight)
        return false;
    ambLight->setLightFlag(LightFlag::LIGHT2);
    VoxelExplorer::getInstance()->get3DLayer()->addChild(ambLight);
    return true;
}
bool Player::createFakeShadow()
{
    m_pFakeShadow = FakeShadow::create();
    if(!m_pFakeShadow)
        return false;
    m_pFakeShadow->setCameraMask((unsigned int)CameraFlag::USER1);
    m_pFakeShadow->setLightMask((unsigned int)LightFlag::LIGHT0);
    VoxelExplorer::getInstance()->getFakeShadowLayer()->addChild(m_pFakeShadow);
    m_pFakeShadow->setScale(2);
    m_pFakeShadow->setPosition3D(Vec3(getPositionX(),-TerrainTile::CONTENT_SCALE*0.49f,getPositionZ()));
    return true;
}