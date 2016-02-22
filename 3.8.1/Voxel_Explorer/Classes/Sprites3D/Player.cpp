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
#include "StatisticsManager.hpp"
#include "RandomDungeon.hpp"
#include "SimpleAudioEngine.h"
#include "LevelResourceManager.h"
#include "OutlineEffect3D.h"
#include "PlayerFireBallBullet.hpp"
#include "PlayerMagicArrowBullet.hpp"
#include "UtilityHelper.h"
#include "SdkBoxManager.hpp"
USING_NS_CC;
using namespace CocosDenshion;

CChaosNumber Player::m_fSpeedupTime  = 20.0f; ///加速时间
CChaosNumber Player::m_fStealthTime  = 20.0f; ///隐身时间
CChaosNumber Player::m_fStrongerTime = 20.0f; ///强化时间

CChaosNumber Player::m_fFrozenTime   = 20.0f;  ///冰冻时间
CChaosNumber Player::m_fParalyticTime    = 8.0f;   ///麻痹时间
CChaosNumber Player::m_fFireTime     = 10.0f;  ///着火时间

CChaosNumber Player::m_fBlockRateUpTime = 20.0f;    ///格挡率上升时间
CChaosNumber Player::m_fBlockRateUpColdDownTime = 30.0f; ///格挡率上升冷却时间

CChaosNumber Player::m_fFireBallColdDownTime = 1.0f;    ///火球冷却时间
CChaosNumber Player::m_fMagicArrowColdDownTime = 1.0f;  ///魔法箭矢冷却时间

Player* Player::create(const std::string& modelPath)
{
    auto player = new (std::nothrow) Player();
    if (player && player->initWithFile(modelPath) && player->createPlayerLight() && player->createFakeShadow())
    {
        player->_contentSize = player->getBoundingBox().size;
        player->setCameraMask((unsigned int)CameraFlag::USER1);
        player->setLightMask((unsigned int)LightFlag::LIGHT0 |(unsigned int)LightFlag::LIGHT1|(unsigned int)LightFlag::LIGHT2);
        
        OutlineEffect3D* outline = OutlineEffect3D::create();
        outline->setOutlineColor(Vec3(0.1f, 0.1f, 0.1f));
        outline->setOutlineWidth(0.05f);
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
    m_pPlayerLight = nullptr;
    m_pFakeShadow = nullptr;
    m_bStealth = false;
    
    m_pBlockRateUpNode = nullptr;
    
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
    return UtilityHelper::getLocalString("PLAYER_DESC");
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
        VoxelExplorer::getInstance()->addParticle3DEffectToPlayer(P3D_EFFECT_TYPE::P3D_SPEEDUP_BUFFER, false);
    }
    if((bufferFlag & PB_STEALTH) != 0)
    {
        setOpacity(127);
        setStealth(true);
        VoxelExplorer::getInstance()->addParticle3DEffectToPlayer(P3D_EFFECT_TYPE::P3D_STEALTH_BUFFER, true);
    }
    if((bufferFlag & PB_STRONGER) != 0)
    {
        VoxelExplorer::getInstance()->addParticle3DEffectToPlayer(P3D_EFFECT_TYPE::P3D_STRONGER_BUFFER, true);
    }

    if((bufferFlag & PB_POISONING) != 0)
    {
        auto tex = Director::getInstance()->getTextureCache()->addImage("chr_sword_green.png");
        if(tex)
            tex->setAliasTexParameters();
        setTexture(tex);
        VoxelExplorer::getInstance()->removeParticle3D3DEffectFromPlayer(P3D_EFFECT_TYPE::P3D_POISIONING_BUFFER);
    }
    

    if((bufferFlag & PB_FROZEN) != 0)
    {
        auto tex = Director::getInstance()->getTextureCache()->addImage("chr_sword_blue.png");
        if(tex)
            tex->setAliasTexParameters();
        setTexture(tex);
        VoxelExplorer::getInstance()->addParticle3DEffectToPlayer(P3D_EFFECT_TYPE::P3D_FROZEN_BUFFER, false);
    }
    

    if((bufferFlag & PB_PARALYTIC) != 0)
    {
        auto tex = Director::getInstance()->getTextureCache()->addImage("chr_sword_gray.png");
        if(tex)
            tex->setAliasTexParameters();
        setTexture(tex);
        VoxelExplorer::getInstance()->addParticle3DEffectToPlayer(P3D_EFFECT_TYPE::P3D_PARALYTIC_BUFFER, true);
    }
    

    if((bufferFlag & PB_WEAK) != 0)
    {
        auto tex = Director::getInstance()->getTextureCache()->addImage("chr_sword_yellow.png");
        if(tex)
            tex->setAliasTexParameters();
        setTexture(tex);
        VoxelExplorer::getInstance()->addParticle3DEffectToPlayer(P3D_EFFECT_TYPE::P3D_WEAK_BUFFER, true);
    }

    if((bufferFlag & PB_FIRE) != 0)
    {
        auto tex = Director::getInstance()->getTextureCache()->addImage("chr_sword_red.png");
        if(tex)
            tex->setAliasTexParameters();
        setTexture(tex);
        VoxelExplorer::getInstance()->addParticle3DEffectToPlayer(P3D_EFFECT_TYPE::P3D_FIRE_BUFFER, false);
    }
    
    if((bufferFlag & PB_BLOCKRATEUP) != 0)
    {
        addBlockRateUpEffectNode();
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
            m_fSpeedupTime = 20.0f;
            PlayerProperty::getInstance()->addPlayerBuffer(buff);
            VoxelExplorer::getInstance()->addParticle3DEffectToPlayer(P3D_EFFECT_TYPE::P3D_SPEEDUP_BUFFER, false);
            StatisticsManager::getInstance()->addSpeedUpNum();
        }
        std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("BUFFER_SPEEDUP");
        SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
    else if(buff == PB_STEALTH)
    {
        if((bufferFlag & PB_STEALTH) != 0)
            m_fStealthTime = 20.0f;
        else
        {
            m_fStealthTime = 20.0f;
            setStealth(true);
            PlayerProperty::getInstance()->addPlayerBuffer(buff);
            VoxelExplorer::getInstance()->addParticle3DEffectToPlayer(P3D_EFFECT_TYPE::P3D_STEALTH_BUFFER, true);
            StatisticsManager::getInstance()->addStealthNum();
        }
        std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("BUFFER_STEALTH");
        SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
    else if(buff == PB_STRONGER)
    {
        if((bufferFlag & PB_STRONGER) != 0)
            m_fStrongerTime = 20.0f;
        else
        {
            m_fStrongerTime = 20.0f;
            PlayerProperty::getInstance()->addPlayerBuffer(buff);
            VoxelExplorer::getInstance()->addParticle3DEffectToPlayer(P3D_EFFECT_TYPE::P3D_STRONGER_BUFFER, true);
            StatisticsManager::getInstance()->addStrongNum();
        }
        std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("BUFFER_STRONGER");
        SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
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
            VoxelExplorer::getInstance()->addParticle3DEffectToPlayer(P3D_EFFECT_TYPE::P3D_POISIONING_BUFFER, false);
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("BUFFER_POISONING");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
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
            VoxelExplorer::getInstance()->addParticle3DEffectToPlayer(P3D_EFFECT_TYPE::P3D_FROZEN_BUFFER, false);
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("BUFFER_FROZEN");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
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
            VoxelExplorer::getInstance()->addParticle3DEffectToPlayer(P3D_EFFECT_TYPE::P3D_PARALYTIC_BUFFER, true);
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("BUFFER_PARALYTIC");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
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
            VoxelExplorer::getInstance()->addParticle3DEffectToPlayer(P3D_EFFECT_TYPE::P3D_WEAK_BUFFER, true);
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("BUFFER_WEAK");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
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
            VoxelExplorer::getInstance()->addParticle3DEffectToPlayer(P3D_EFFECT_TYPE::P3D_FIRE_BUFFER, false);
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("BUFFER_FIRE");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
    }
    else if(buff == PB_BLOCKRATEUP)
    {
        if((bufferFlag & PB_BLOCKRATEUP) == 0)
        {
            m_fBlockRateUpTime = 20.0f;
            PlayerProperty::getInstance()->addPlayerBuffer(buff);
            addBlockRateUpEffectNode();
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("BLOCK_RATEUP");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
    }
}
void Player::removePlayerBuffer(PlayerBuffer buff)
{
    int bufferFlag = PlayerProperty::getInstance()->getPlayerBuffer();
    if(buff == PB_STRONGER)
    {
        if((bufferFlag & PB_STRONGER) != 0)
        {
            PlayerProperty::getInstance()->removePlayerBuffer(buff);
            VoxelExplorer::getInstance()->removeParticle3D3DEffectFromPlayer(P3D_EFFECT_TYPE::P3D_STRONGER_BUFFER);
        }
    }
    else if(buff == PB_STEALTH)
    {
        if((bufferFlag & PB_STEALTH) != 0)
        {
            setStealth(false);
            PlayerProperty::getInstance()->removePlayerBuffer(buff);
            VoxelExplorer::getInstance()->removeParticle3D3DEffectFromPlayer(P3D_EFFECT_TYPE::P3D_STEALTH_BUFFER);
        }
    }
    else if(buff == PB_SPEEDUP)
    {
        if((bufferFlag & PB_SPEEDUP) != 0)
        {
            PlayerProperty::getInstance()->removePlayerBuffer(buff);
            VoxelExplorer::getInstance()->removeParticle3D3DEffectFromPlayer(P3D_EFFECT_TYPE::P3D_SPEEDUP_BUFFER);
        }
    }
    else if(buff == PB_POISONING)
    {
        if((bufferFlag & PB_POISONING) != 0)
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
            PlayerProperty::getInstance()->removePlayerBuffer(buff);
            VoxelExplorer::getInstance()->removeParticle3D3DEffectFromPlayer(P3D_EFFECT_TYPE::P3D_POISIONING_BUFFER);
            if(m_curState != PlayerState::PS_DEATH)
                StatisticsManager::getInstance()->addPoisonRecoverNum();
        }
    }
    else if(buff == PB_WEAK)
    {
        if((bufferFlag & PB_WEAK) != 0)
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
            PlayerProperty::getInstance()->removePlayerBuffer(buff);
            VoxelExplorer::getInstance()->removeParticle3D3DEffectFromPlayer(P3D_EFFECT_TYPE::P3D_WEAK_BUFFER);
            if(m_curState != PlayerState::PS_DEATH)
                StatisticsManager::getInstance()->addWeakRecoverNum();
        }
    }
    else if(buff == PB_PARALYTIC)
    {
        if((bufferFlag & PB_PARALYTIC) != 0)
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
            PlayerProperty::getInstance()->removePlayerBuffer(buff);
            VoxelExplorer::getInstance()->removeParticle3D3DEffectFromPlayer(P3D_EFFECT_TYPE::P3D_PARALYTIC_BUFFER);
        }
    }
    else if(buff == PB_FIRE)
    {
        if((bufferFlag & PB_FIRE) != 0)
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
            PlayerProperty::getInstance()->removePlayerBuffer(buff);
            VoxelExplorer::getInstance()->removeParticle3D3DEffectFromPlayer(P3D_EFFECT_TYPE::P3D_FIRE_BUFFER);
        }
    }
    else if(buff == PB_FROZEN)
    {
        if((bufferFlag & PB_FROZEN) != 0)
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
            PlayerProperty::getInstance()->removePlayerBuffer(buff);
            VoxelExplorer::getInstance()->removeParticle3D3DEffectFromPlayer(P3D_EFFECT_TYPE::P3D_FROZEN_BUFFER);
        }
    }
    else if(buff == PB_BLOCKRATEUP)
    {
        if((bufferFlag & PB_BLOCKRATEUP) != 0)
        {
            PlayerProperty::getInstance()->removePlayerBuffer(buff);
            removeBlockRateUpEffectNode();
        }
    }
    else
        PlayerProperty::getInstance()->removePlayerBuffer(buff);
}
void Player::resetPlayerBuffer()
{
    int bufferFlag = PlayerProperty::getInstance()->getPlayerBuffer();
    if((bufferFlag & PB_STRONGER) != 0)
    {
        removePlayerBuffer(PB_STRONGER);
    }
    if((bufferFlag & PB_STEALTH) != 0)
    {
        setOpacity(255);
        removePlayerBuffer(PB_STEALTH);
    }
    if((bufferFlag & PB_SPEEDUP) != 0)
    {
        removePlayerBuffer(PB_SPEEDUP);
    }
    if((bufferFlag & PB_POISONING) != 0)
    {
        removePlayerBuffer(PB_POISONING);
    }
    if((bufferFlag & PB_WEAK) != 0)
    {
        removePlayerBuffer(PB_WEAK);
    }
    if((bufferFlag & PB_PARALYTIC) != 0)
    {
        removePlayerBuffer(PB_PARALYTIC);
    }
    if((bufferFlag & PB_FIRE) != 0)
    {
        removePlayerBuffer(PB_FIRE);
    }
    if((bufferFlag & PB_FROZEN) != 0)
    {
        removePlayerBuffer(PB_FROZEN);
    }
    if((bufferFlag & PB_BLOCKRATEUP) != 0)
    {
        removePlayerBuffer(PB_BLOCKRATEUP);
    }
    PlayerProperty::getInstance()->resetPlayerBuffer();
    
    auto tex = Director::getInstance()->getTextureCache()->addImage("chr_sword.png");
    if(tex)
        tex->setAliasTexParameters();
    setTexture(tex);
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
    if(!monsterProperty || !m_pHurtData)
        return;
    
    m_pHurtData->reset();
    m_pHurtData->m_vPos = this->getPosition3D();
    if(miss)
    {
        m_pHurtData->m_bDodge = true;
        StatisticsManager::getInstance()->addDodgeTotalNum();
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_HURT, m_pHurtData);
        std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("MISS");
        SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
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
            StatisticsManager::getInstance()->addDodgeTotalNum();
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_HURT, m_pHurtData);
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("MISS");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
            return;
        }
    }
    int attack = (int)monsterProperty->getRandomAttack().GetLongValue();
    float percentCriticalStrikeRate = monsterProperty->getCriticalStrikeRate().GetFloatValue();
    float percentNormal = 1.0 - percentCriticalStrikeRate;
    AlisaMethod* amCriticalStrikeRate = AlisaMethod::create(percentCriticalStrikeRate,percentNormal,-1.0, NULL);
    if(amCriticalStrikeRate)
    {
        if(amCriticalStrikeRate->getRandomIndex() == 0)
        {
            attack = attack*2.0f;
            m_pHurtData->m_bCriticalStrike = true;
            VoxelExplorer::getInstance()->shakeScreen();
            StatisticsManager::getInstance()->addCriticalTotalNum();
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("CRITICALSTRIKE");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
    }
    
    int defense = (int)PlayerProperty::getInstance()->getDefense().GetLongValue();
    
    attack = MAX(attack - defense, cocos2d::random(1, 3));
    
    float percentBlockRate = PlayerProperty::getInstance()->getBlockRate().GetFloatValue();
    float percentNull = 1.0 - percentBlockRate;
    AlisaMethod* amBlockRate = AlisaMethod::create(percentBlockRate,percentNull,-1.0, NULL);
    if(amBlockRate)
    {
        if(amBlockRate->getRandomIndex() == 0)
        {
            attack = attack*0.5f;
            m_pHurtData->m_bBlocked = true;
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("BLOCK");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
    }
    
    int currentHp = (int)PlayerProperty::getInstance()->getCurrentHP().GetLongValue();
    currentHp = MAX(currentHp - attack , 0);
    CCLOG("Player: CurrentHp = %d, monsterAttack = %d", currentHp, attack);
    m_pHurtData->m_nDamage = -attack;
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_HURT, m_pHurtData);
    if(currentHp == 0)
    {
        setState(PS_DEATH);
        StatisticsManager::getInstance()->addRoleDeadNum(StatisticsManager::eRoleDeadType::RET_MONSTER_ATTACK);
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM ==CC_PLATFORM_ANDROID )
        SdkBoxManager::getInstance()->logEvent("Player", "Death", "AttackByMonster", 1);
#endif
    }
    else
    {
        PlayerProperty::getInstance()->setCurrentHP(currentHp);
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_PROPERTY_DIRTY, this);
    }
}
void Player::attackByBoss(BossProperty* bossProperty, bool miss)
{
    if(!bossProperty || !m_pHurtData)
        return;
    
    m_pHurtData->reset();
    m_pHurtData->m_vPos = this->getPosition3D();
    if(miss)
    {
        m_pHurtData->m_bDodge = true;
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_HURT, m_pHurtData);
        std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("MISS");
        SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
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
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("MISS");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
            return;
        }
    }
    int attack = (int)bossProperty->getRandomAttack().GetLongValue();
    float percentCriticalStrikeRate = bossProperty->getCriticalStrikeRate().GetFloatValue();
    float percentNormal = 1.0 - percentCriticalStrikeRate;
    AlisaMethod* amCriticalStrikeRate = AlisaMethod::create(percentCriticalStrikeRate,percentNormal,-1.0, NULL);
    if(amCriticalStrikeRate)
    {
        if(amCriticalStrikeRate->getRandomIndex() == 0)
        {
            attack = attack*2.0f;
            m_pHurtData->m_bCriticalStrike = true;
            VoxelExplorer::getInstance()->shakeScreen();
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("CRITICALSTRIKE");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
    }
    
    int defense = (int)PlayerProperty::getInstance()->getDefense().GetLongValue();
    
    attack = MAX(attack - defense, cocos2d::random(1, 5));
    
    float percentBlockRate = PlayerProperty::getInstance()->getBlockRate().GetFloatValue();
    float percentNull = 1.0 - percentBlockRate;
    AlisaMethod* amBlockRate = AlisaMethod::create(percentBlockRate,percentNull,-1.0, NULL);
    if(amBlockRate)
    {
        if(amBlockRate->getRandomIndex() == 0)
        {
            attack = attack*0.5f;
            m_pHurtData->m_bBlocked = true;
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("BLOCK");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
    }
    
    int currentHp = (int)PlayerProperty::getInstance()->getCurrentHP().GetLongValue();
    currentHp = MAX(currentHp - attack , 0);
    CCLOG("Player: CurrentHp = %d, bossAttack = %d", currentHp, attack);
    m_pHurtData->m_nDamage = -attack;
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_HURT, m_pHurtData);
    if(currentHp == 0)
    {
        setState(PS_DEATH);
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM ==CC_PLATFORM_ANDROID )
        SdkBoxManager::getInstance()->logEvent("Player", "Death", "AttackByBoss", 1);
#endif
    }
    else
    {
        float percentHit = 0.15f;
        float percentLose = 1.0 - percentHit;
        AlisaMethod* amDodgeRate = AlisaMethod::create(percentHit,percentLose,-1.0, NULL);
        if(amDodgeRate)
        {
            if(amDodgeRate->getRandomIndex() == 0)
            {
                if((bossProperty->getAttackAddBuffer() & PB_POISONING) != 0)
                {
                    if((PlayerProperty::getInstance()->getPlayerBuffer() & PB_POISONING) == 0)
                    {
                        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_TRIGGER_TOXIC_TRAP);
                        addPlayerBuffer(PB_POISONING);
                    }
                    
                }
                else if((bossProperty->getAttackAddBuffer() & PB_FROZEN) != 0)
                {
                    if((PlayerProperty::getInstance()->getPlayerBuffer() & PB_FROZEN) == 0)
                    {
                        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_TRIGGER_FROZEN_TRAP);
                        addPlayerBuffer(PB_FROZEN);
                    }
                }
                else if((bossProperty->getAttackAddBuffer() & PB_PARALYTIC) != 0)
                {
                    if((PlayerProperty::getInstance()->getPlayerBuffer() & PB_PARALYTIC) == 0)
                    {
                        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_TRIGGER_PARALYTIC_TRAP);
                        addPlayerBuffer(PB_PARALYTIC);
                    }
                }
                else if((bossProperty->getAttackAddBuffer() & PB_WEAK) != 0)
                {
                    if((PlayerProperty::getInstance()->getPlayerBuffer() & PB_WEAK) == 0)
                    {
                        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_TRIGGER_WEAK_TRAP);
                        addPlayerBuffer(PB_WEAK);
                    }
                }
                else if((bossProperty->getAttackAddBuffer() & PB_FIRE) != 0)
                {
                    if((PlayerProperty::getInstance()->getPlayerBuffer() & PB_FIRE) == 0)
                    {
                        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_TRIGGER_FIRE_TRAP);
                        addPlayerBuffer(PB_FIRE);
                    }
                }

            }
        }
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
    int currentHp = (int)PlayerProperty::getInstance()->getCurrentHP().GetLongValue();
    currentHp = MAX(currentHp - attack , 0);
    CCLOG("Player: CurrentHp = %d, GrippingTrap Attack = %d", currentHp, attack);
    
    m_pHurtData->m_nDamage = -attack;
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_HURT, m_pHurtData);
    if(currentHp == 0)
    {
        setState(PS_DEATH);
        StatisticsManager::getInstance()->addRoleDeadNum(StatisticsManager::eRoleDeadType::RET_TRIGGER_GRIPPING_TRAP);
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM ==CC_PLATFORM_ANDROID )
        SdkBoxManager::getInstance()->logEvent("Player", "Death", "TriggerGrippingTrap", 1);
#endif
    }
    else
    {
        PlayerProperty::getInstance()->setCurrentHP(currentHp);
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_PROPERTY_DIRTY, this);
    }
}
void Player::fallAndDie()
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
    removeTerrainTileFlag(TileInfo::ATTACKABLE);
    ScaleTo* scaleTo = ScaleTo::create(0.1f, 1.0f, 1.0f, 1.0f);
    EaseSineOut* moveUp = EaseSineOut::create(MoveTo::create(0.1f, Vec3(getPositionX(), getPositionY() + TerrainTile::CONTENT_SCALE*0.5f, getPositionZ()) + dir));
    EaseSineOut* moveDown = EaseSineOut::create(MoveTo::create(0.2f, Vec3(getPositionX(), getPositionY() - TerrainTile::CONTENT_SCALE, getPositionZ()) + dir));
    EaseSineOut* fadeOut = EaseSineOut::create(FadeOut::create(0.3f));
    Sequence* sequenceJump = Sequence::create(moveUp, moveDown, NULL);
    Spawn* spawn = Spawn::create(scaleTo, sequenceJump, fadeOut, NULL);
    CallFunc* callback = CallFunc::create(CC_CALLBACK_0(Player::onFallDie,this));
    Sequence* sequence = Sequence::create(spawn, callback, NULL);
    int bufferFlag = PlayerProperty::getInstance()->getPlayerBuffer();
    if((bufferFlag & PlayerBuffer::PB_SPEEDUP) != 0)
        this->runAction(Speed::create(sequence, 2.0f));
    else if((bufferFlag & PlayerBuffer::PB_FROZEN) != 0)
        this->runAction(Speed::create(sequence, 0.5f));
    else
        this->runAction(sequence);
}
void Player::healedbyNurse()
{
    removePlayerBuffer(PlayerBuffer::PB_FIRE);
    removePlayerBuffer(PlayerBuffer::PB_FROZEN);
    removePlayerBuffer(PlayerBuffer::PB_POISONING);
    removePlayerBuffer(PlayerBuffer::PB_PARALYTIC);
    removePlayerBuffer(PlayerBuffer::PB_WEAK);
    auto tex = Director::getInstance()->getTextureCache()->addImage("chr_sword.png");
    if(tex)
        tex->setAliasTexParameters();
    setTexture(tex);
    PlayerProperty::getInstance()->healedbyNurse();
    
    VoxelExplorer::getInstance()->addParticle3DEffectToPlayer(P3D_PLAYER_USE_POTION_TAKE_EFFECT);
    
    std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("USE_SCROLL");
    SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
}
void Player::useSkillToAttack(PlayerSkill skill)
{
    if(skill == PlayerSkill::PS_FIREBALL)
    {
        if(VoxelExplorer::getInstance()->getBulletsLayer())
        {
            Actor* nearestEnemy = VoxelExplorer::getInstance()->getNearestEnemy();
            PlayerFireBallBullet* bullet = PlayerFireBallBullet::create(this, nearestEnemy);
            if(bullet)
            {
                bullet->setPosition3D(getPosition3D() + Vec3(0, TerrainTile::CONTENT_SCALE*0.5f, 0));
                bullet->setBulletState(BaseBullet::BS_NORMAL);
                VoxelExplorer::getInstance()->getBulletsLayer()->addChild(bullet);
                
                std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("FIRE_BALL");
                SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
            }
        }
    }
    else if(skill == PlayerSkill::PS_MAGICARROW)
    {
        if(VoxelExplorer::getInstance()->getBulletsLayer())
        {
            Vec3 dir;
            switch (m_dir) {
                case Actor::AD_FORWARD:
                    dir = Vec3(0,0,-1);
                    break;
                case Actor::AD_LEFT:
                    dir = Vec3(-1,0,0);
                    break;
                case Actor::AD_RIGHT:
                    dir = Vec3(1,0,0);
                    break;
                case Actor::AD_BACK:
                    dir = Vec3(0,0,1);
                    break;
                default:
                    break;
            }

            Actor* nearestEnemy = VoxelExplorer::getInstance()->getNearestEnemy();
            if(nearestEnemy)
            {
                dir = nearestEnemy->getPosition3D() - getPosition3D();
                dir.normalize();
            }
            PlayerMagicArrowBullet* bullet = PlayerMagicArrowBullet::create(this, dir);
            if(bullet)
            {
                bullet->setPosition3D(getPosition3D() + Vec3(0, TerrainTile::CONTENT_SCALE*0.5f, 0));
                bullet->setBulletState(BaseBullet::BS_NORMAL);
                VoxelExplorer::getInstance()->getBulletsLayer()->addChild(bullet);
            }
            
            Quaternion rotRight = Quaternion(Vec3::UNIT_Y, M_PI/12);
            Vec3 rightDir = rotRight*dir;
            rightDir.normalize();
            
            PlayerMagicArrowBullet* bullet1 = PlayerMagicArrowBullet::create(this, rightDir);
            if(bullet1)
            {
                bullet1->setPosition3D(getPosition3D() + Vec3(0, TerrainTile::CONTENT_SCALE*0.5f, 0));
                bullet1->setBulletState(BaseBullet::BS_NORMAL);
                VoxelExplorer::getInstance()->getBulletsLayer()->addChild(bullet1);
            }
            
            Quaternion rotLeft = Quaternion(Vec3::UNIT_Y, -M_PI/12);
            Vec3 leftDir = rotLeft*dir;
            leftDir.normalize();
            
            PlayerMagicArrowBullet* bullet2 = PlayerMagicArrowBullet::create(this, leftDir);
            if(bullet2)
            {
                bullet2->setPosition3D(getPosition3D() + Vec3(0, TerrainTile::CONTENT_SCALE*0.5f, 0));
                bullet2->setBulletState(BaseBullet::BS_NORMAL);
                VoxelExplorer::getInstance()->getBulletsLayer()->addChild(bullet2);
            }
            
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("MAGIC_ARROW");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
    }
}
void Player::onEnterIdle()
{
    EaseSineOut* scaleTo = EaseSineOut::create(ScaleTo::create(0.1f, 1.0f, 1.0f, 1.0f));
    this->runAction(scaleTo);
    if(m_pFakeShadow)
        m_pFakeShadow->setVisible(true);
    this->setVisible(true);

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
    CallFunc* callback = CallFunc::create(CC_CALLBACK_0(Player::onLand,this,false));
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
    CallFunc* callback = CallFunc::create(CC_CALLBACK_0(Player::onLand,this, false));
    Sequence* sequence = Sequence::create(spawn, callback, NULL);
    
    int bufferFlag = PlayerProperty::getInstance()->getPlayerBuffer();
    if((bufferFlag & PlayerBuffer::PB_SPEEDUP) != 0)
        this->runAction(Speed::create(sequence, 2.0f));
    else if((bufferFlag & PlayerBuffer::PB_FROZEN) != 0)
        this->runAction(Speed::create(sequence, 0.5f));
    else
        this->runAction(sequence);
    
    StatisticsManager::getInstance()->addStepNum();
}
void Player::onEnterAttack()
{
    removePlayerBuffer(PB_STEALTH);
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
    CallFunc* callback2 = CallFunc::create(CC_CALLBACK_0(Player::onLand,this, true));
    Sequence* sequence = Sequence::create(spawn, callback2, NULL);
    
    int bufferFlag = PlayerProperty::getInstance()->getPlayerBuffer();
    if((bufferFlag & PlayerBuffer::PB_SPEEDUP) != 0)
        this->runAction(Speed::create(sequence, 2.0f));
    else if((bufferFlag & PlayerBuffer::PB_FROZEN) != 0)
        this->runAction(Speed::create(sequence, 0.5f));
    else
        this->runAction(sequence);
}

void Player::onEnterDeath()
{
    this->stopAllActions();
    removeTerrainTileFlag(TileInfo::ATTACKABLE);
    PlayerProperty::getInstance()->setCurrentHP(0);
    resetPlayerBuffer();
    if(m_pFakeShadow)
        m_pFakeShadow->setVisible(false);
    this->setVisible(false);
    VoxelExplorer::getInstance()->addParticle3DEffect(getPosition3D(), P3D_EFFECT_TYPE::P3D_PLAYER_DEATH);
    VoxelExplorer::getInstance()->updateMiniMap();
    
    std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("PLAYER_DEATH");
    SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
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
void Player::onExitDeath()
{
}
void Player::onLand(bool isAttack)
{
    setState(PS_IDLE);
    VoxelExplorer::getInstance()->cameraTrackPlayer();
    VoxelExplorer::getInstance()->checkPickItem();
    VoxelExplorer::getInstance()->checkUpdateFogOfWar();
    VoxelExplorer::getInstance()->checkTriggerTrap();
    VoxelExplorer::getInstance()->updateMiniMap();
    
    if(RandomDungeon::getInstance()->getCurrentDungeonNode()->isBossDepth())
        VoxelExplorer::getInstance()->updateBossRoomDoor();
    
    CCLOG("player lastPos x = %d   y = %d", (int)m_LastPosInMap.x, (int)m_LastPosInMap.y);
    CCLOG("player Pos x = %d   y = %d", (int)getPosInMap().x, (int)getPosInMap().y);
    m_LastPosInMap = getPosInMap();
    if(!isAttack)
    {
        if(VoxelExplorer::getInstance()->getCurrentLevel())
        {
            std::string soundName = LevelResourceManager::getInstance()->getDungeonSoundEffectRes("STEP_STANDARD");
            TerrainTile::TileType type = VoxelExplorer::getInstance()->getCurrentLevel()->getTerrainTileType(getPosInMap().x, getPosInMap().y);
            if(type == TerrainTile::TT_TUNNEL)
                soundName = LevelResourceManager::getInstance()->getDungeonSoundEffectRes("STEP_TUNNEL");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
    }
    
    if(isStealth())
    {
        VoxelExplorer::getInstance()->addParticle3DEffectToPlayer(P3D_EFFECT_TYPE::P3D_STEALTH_BUFFER, true);
    }
}
void Player::onFallDie()
{
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_FALL_AND_DIE);
    setState(Player::PS_DEATH);
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
            removePlayerBuffer(PB_STEALTH);
    }
    if((bufferFlag & PB_STRONGER) != 0)
    {
        m_fStrongerTime = m_fStrongerTime - delta;
        if(m_fStrongerTime <= 0)
            removePlayerBuffer(PB_STRONGER);
    }
    if((bufferFlag & PB_FROZEN) != 0)
    {
        m_fFrozenTime = m_fFrozenTime - delta;
        if(m_fFrozenTime <= 0)
            removePlayerBuffer(PB_FROZEN);
    }
    if((bufferFlag & PB_PARALYTIC) != 0)
    {
        m_fParalyticTime = m_fParalyticTime - delta;
        if(m_fParalyticTime <= 0)
            removePlayerBuffer(PB_PARALYTIC);
    }
    if((bufferFlag & PB_FIRE) != 0)
    {
        m_fFireTime = m_fFireTime - delta;
        if(m_fFireTime <= 0)
            removePlayerBuffer(PB_FIRE);
        else
        {
            m_fSecondTimer = m_fSecondTimer - delta;
            if(m_fSecondTimer <=0)
            {
                m_pHurtData->reset();
                m_pHurtData->m_vPos = this->getPosition3D();
                
                int deltaHp = PlayerProperty::getInstance()->getMaxHP() * 0.05f;
                int currentHp = (int)PlayerProperty::getInstance()->getCurrentHP().GetLongValue();
                currentHp = MAX(currentHp - deltaHp , 0);
                m_pHurtData->m_nDamage = - deltaHp;
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_HURT, m_pHurtData);
                if(currentHp == 0)
                {
                    setState(PS_DEATH);
                    StatisticsManager::getInstance()->addRoleDeadNum(StatisticsManager::eRoleDeadType::RET_BUFFER_FIRE);
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM ==CC_PLATFORM_ANDROID )
                    SdkBoxManager::getInstance()->logEvent("Player", "Death", "KilledByBufferFire", 1);
#endif
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
            
            int currentHp = (int)PlayerProperty::getInstance()->getCurrentHP().GetLongValue();
            currentHp = MAX(currentHp - 5 , 0);
            m_pHurtData->m_nDamage = - 5;
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_HURT, m_pHurtData);
            if(currentHp == 0)
            {
                setState(PS_DEATH);
                StatisticsManager::getInstance()->addRoleDeadNum(StatisticsManager::eRoleDeadType::RET_BUFFER_POISONING);
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM ==CC_PLATFORM_ANDROID )
                SdkBoxManager::getInstance()->logEvent("Player", "Death", "KilledByBufferPoisoning", 1);
#endif
            }
            else
            {
                PlayerProperty::getInstance()->setCurrentHP(currentHp);
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_PROPERTY_DIRTY, this);
            }
            m_fSecondTimer = 1.0f;
        }
    }
    if((bufferFlag & PB_BLOCKRATEUP) != 0)
    {
        m_fBlockRateUpTime = m_fBlockRateUpTime - delta;
        if(m_fBlockRateUpTime <= 0)
            removePlayerBuffer(PB_BLOCKRATEUP);
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
void Player::addBlockRateUpEffectNode()
{
    if(!m_pBlockRateUpNode)
    {
        m_pBlockRateUpNode = Node::create();
        if(m_pBlockRateUpNode)
        {
            auto tex = Director::getInstance()->getTextureCache()->addImage("item_color.png");
            if(tex)
                tex->setAliasTexParameters();
            std::string model = LevelResourceManager::getInstance()->getItemModelRes(PICKABLE_ITEM_NAMES[PickableItem::PIT_SHIELD_EAGLESHIELD]);
            Sprite3D* shield1 = Sprite3D::create(model);
            if(shield1)
            {
                shield1->setTexture(tex);
                shield1->setScale(0.2f);
                shield1->setCascadeOpacityEnabled(true);
                shield1->setOpacity(200);
                shield1->setPositionZ(TerrainTile::CONTENT_SCALE*0.5f);
                shield1->setCameraMask((unsigned int)CameraFlag::USER1);
                shield1->setLightMask((unsigned int)LightFlag::LIGHT0 |(unsigned int)LightFlag::LIGHT1|(unsigned int)LightFlag::LIGHT2);
            }
            Sprite3D* shield2 = Sprite3D::create(model);
            if(shield2)
            {
                shield2->setTexture(tex);
                shield2->setScale(0.2f);
                shield2->setCascadeOpacityEnabled(true);
                shield2->setOpacity(200);
                shield2->setRotation3D(Vec3(0,60,0));
                shield2->setPositionX(-TerrainTile::CONTENT_SCALE*0.4f);
                shield2->setPositionZ(-TerrainTile::CONTENT_SCALE*0.3f);
                shield2->setCameraMask((unsigned int)CameraFlag::USER1);
                shield2->setLightMask((unsigned int)LightFlag::LIGHT0 |(unsigned int)LightFlag::LIGHT1|(unsigned int)LightFlag::LIGHT2);
            }
            
            Sprite3D* shield3 = Sprite3D::create(model);
            if(shield3)
            {
                shield3->setTexture(tex);
                shield3->setScale(0.2f);
                shield3->setCascadeOpacityEnabled(true);
                shield3->setOpacity(200);
                shield3->setRotation3D(Vec3(0,-60,0));
                shield3->setPositionX(TerrainTile::CONTENT_SCALE*0.4f);
                shield3->setPositionZ(-TerrainTile::CONTENT_SCALE*0.3f);
                shield3->setCameraMask((unsigned int)CameraFlag::USER1);
                shield3->setLightMask((unsigned int)LightFlag::LIGHT0 |(unsigned int)LightFlag::LIGHT1|(unsigned int)LightFlag::LIGHT2);
            }
            m_pBlockRateUpNode->addChild(shield1);
            m_pBlockRateUpNode->addChild(shield2);
            m_pBlockRateUpNode->addChild(shield3);
            
        }
        this->addChild(m_pBlockRateUpNode);
        m_pBlockRateUpNode->setScale(0.0f);
    }
        m_pBlockRateUpNode->stopActionByTag(2);
        m_pBlockRateUpNode->setScale(0.0f);
        EaseSineOut* scaleTo = EaseSineOut::create(ScaleTo::create(0.5f, 1.0f));
        RotateBy* rotateBy = RotateBy::create(1.0f, Vec3(0,200,0));
        Spawn* spawn = Spawn::create(scaleTo, rotateBy, nullptr);
        RepeatForever* repeat = RepeatForever::create(spawn);
        repeat->setTag(1);
        m_pBlockRateUpNode->runAction(repeat);
    
}
void Player::removeBlockRateUpEffectNode()
{
    if(m_pBlockRateUpNode)
    {
        m_pBlockRateUpNode->stopActionByTag(1);
        EaseSineOut* scaleTo = EaseSineOut::create(ScaleTo::create(0.5f, 0.0f));
        RotateBy* rotateBy = RotateBy::create(1.0f, Vec3(0,200,0));
        Spawn* spawn = Spawn::create(scaleTo, rotateBy, nullptr);
        RepeatForever* repeat = RepeatForever::create(spawn);
        repeat->setTag(2);
        m_pBlockRateUpNode->runAction(repeat);
    }
}