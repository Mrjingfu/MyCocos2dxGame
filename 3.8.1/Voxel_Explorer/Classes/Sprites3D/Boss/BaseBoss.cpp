//
//  BaseBoss.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/23.
//
//

#include "BaseBoss.hpp"
#include "LevelResourceManager.h"
#include "FakeShadow.hpp"
#include "VoxelExplorer.h"
#include "UtilityHelper.h"
#include "AlisaMethod.h"
#include "GameFormula.hpp"
#include "OutlineEffect3D.h"
#include "SimpleAudioEngine.h"
#include "StatisticsManager.hpp"
USING_NS_CC;
using namespace CocosDenshion;
const std::string BOSS_MODEL_NAMES[] = {
    "BMN_UNKNOWN",
    
    "BMN_SLIMEKING",               ///史莱姆王
    "BMN_WARDEN",                  ///典狱长
    "BMN_ARCHBISHOP",              ///大主教
    "BMN_KOBOLDLEADER",            ///狗头人首领
    "BMN_GIANT",                   ///巨人格鲁尔德
    "BMN_SKELETONKING",            ///骷髅王
    
    "BMN_MAX"
};
const std::string BOSS_STATE_DESC[]
{
    "BSC_UNKNOWN",
    
    "BSC_SLIMEKING",               ///史莱姆王
    "BSC_WARDEN",                  ///典狱长
    "BSC_ARCHBISHOP",              ///大主教
    "BSC_KOBOLDLEADER",            ///狗头人首领
    "BSC_GIANT",                   ///巨人格鲁尔德
    "BSC_SKELETONKING",            ///骷髅王
    
    "BSC_MAX"
};
BaseBoss::BaseBoss()
{
    m_Type = BT_UNKNOWN;
    m_State = BS_UNKNOWN;
    m_LastState = BS_UNKNOWN;
    
    m_bJumpMove = true;
    
    m_pHurtData = new (std::nothrow) HurtData();
    
    m_nFOV = 6;
    m_nAttackRange = 1;
    m_fFirstTrackingTimer = 1;
    m_nFleeRange = 0;
    m_bEnableFlee = false;
    
    m_pBossProperty = new (std::nothrow) BossProperty();
    if(m_pBossProperty)
        m_pBossProperty->adjustByDC();

}
BaseBoss::~BaseBoss()
{
    CC_SAFE_DELETE(m_pHurtData);
    CC_SAFE_DELETE(m_pBossProperty);
}
std::string BaseBoss::getIconRes()
{
    return LevelResourceManager::getInstance()->getMonsterIconRes(BOSS_MODEL_NAMES[m_Type]);
}
std::string BaseBoss::getDesc()
{
    return UtilityHelper::getLocalString(BOSS_MODEL_NAMES[m_Type]);
}
std::string BaseBoss::getBossDescByEvent(const std::string& event)
{
    if(event == EVENT_BOSS_ALERT)
        return UtilityHelper::getLocalString(BOSS_STATE_DESC[m_Type] + "_ALERT");
    else if(event == EVENT_BOSS_SKILL1)
        return UtilityHelper::getLocalString(BOSS_STATE_DESC[m_Type] + "_SKILL1");
    else if(event == EVENT_BOSS_SKILL2)
        return UtilityHelper::getLocalString(BOSS_STATE_DESC[m_Type] + "_SKILL2");
    else if(event == EVENT_BOSS_SKILL3)
        return UtilityHelper::getLocalString(BOSS_STATE_DESC[m_Type] + "_SKILL3");
    else if(event == EVENT_BOSS_DEATH)
        return UtilityHelper::getLocalString(BOSS_STATE_DESC[m_Type] + "_DEATH");
    else
        return "";
}
void BaseBoss::attackedByPlayer(bool miss)
{
    if(!m_pBossProperty || !m_pHurtData)
        return;
    
    m_pHurtData->reset();
    m_pHurtData->m_vPos = this->getPosition3D();
    
    if(miss)
    {
        std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("MISS");
        SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        m_pHurtData->m_bDodge = true;
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_BOSS_HURT, m_pHurtData);
        return;
    }
    
    float percentDodgeRate = m_pBossProperty->getDodgeRate().GetFloatValue();
    float percentHit = 1.0 - percentDodgeRate;
    AlisaMethod* amDodgeRate = AlisaMethod::create(percentDodgeRate,percentHit,-1.0, NULL);
    if(amDodgeRate)
    {
        if(amDodgeRate->getRandomIndex() == 0)
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("MISS");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
            m_pHurtData->m_bDodge = true;
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_BOSS_HURT, m_pHurtData);
            return;
        }
    }
    int attack = PlayerProperty::getInstance()->getRandomAttack().GetLongValue();
    float percentCriticalStrikeRate = PlayerProperty::getInstance()->getCriticalStrikeRate().GetFloatValue();
    float percentNormal = 1.0 - percentCriticalStrikeRate;
    AlisaMethod* amCriticalStrikeRate = AlisaMethod::create(percentCriticalStrikeRate,percentNormal,-1.0, NULL);
    if(amCriticalStrikeRate)
    {
        if(amCriticalStrikeRate->getRandomIndex() == 0)
        {
            attack = attack*2.0f;
            m_pHurtData->m_bCriticalStrike = true;
            
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("CRITICALSTRIKE");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
    }
    
    int defense = m_pBossProperty->getDefense().GetLongValue();
    
    attack = MAX(attack + defense, 0);
    
    float percentBlockRate = m_pBossProperty->getBlockRate().GetFloatValue();
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
    
    int currentHp = m_pBossProperty->getCurrentHP().GetLongValue();
    currentHp = MAX(currentHp - attack , 0);
    CCLOG("Boss: CurrentHp = %d, playerAttack = %d", currentHp, attack);
    m_pHurtData->m_nDamage = -attack;
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_BOSS_HURT, m_pHurtData);
    if(currentHp == 0)
    {
        setState(BS_DEATH);
        CChaosNumber addexp = 0;
        addexp = GameFormula::getKillBossExp(PlayerProperty::getInstance()->getLevel(), PlayerProperty::getInstance()->getLevel()+5);
        PlayerProperty::getInstance()->setExp(PlayerProperty::getInstance()->getExp() + addexp.GetLongValue());
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_BOSS_DEATH, this);
        StatisticsManager::getInstance()->addBossKillNum(m_Type);
    }
    else
    {
        handleSkillStage(currentHp);
        m_pBossProperty->setCurrentHP(currentHp);
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_BOSS_PROPERTY_DIRTY, this);
    }
}
bool BaseBoss::createFakeShadow()
{
    m_pFakeShadow = FakeShadow::create();
    if(!m_pFakeShadow)
        return false;
    m_pFakeShadow->setCameraMask((unsigned int)CameraFlag::USER1);
    m_pFakeShadow->setLightMask((unsigned int)LightFlag::LIGHT0);
    VoxelExplorer::getInstance()->getFakeShadowLayer()->addChild(m_pFakeShadow);
    m_pFakeShadow->setScale(3);
    m_pFakeShadow->setPosition3D(Vec3(getPositionX(),-TerrainTile::CONTENT_SCALE*0.49f,getPositionZ()));
    return true;
}
void BaseBoss::setState(BossState state)
{
    if(m_State == state)
        return;
    if(m_State == BS_DEATH && state != BS_SLEEPING)
        return;
    
    switch (m_State) {
        case BS_SLEEPING:
            onExitSleeping();
            break;
        case BS_WANDERING:
            onExitWandering();
            break;
        case BS_TRACKING:
            onExitTracking();
            break;
        case BS_FLEEING:
            onExitFleeing();
            break;
        case BS_MOVING:
            onExitMoving();
            break;
        case BS_ATTACK:
            onExitAttack();
            break;
        case BS_DEATH:
            onExitDeath();
            break;
        case BS_SKILL1:
            onExitSkill1();
            break;
        case BS_SKILL2:
            onExitSkill2();
            break;
        case BS_SKILL3:
            onExitSkill3();
            break;
        default:
            break;
    }
    
    m_LastState = m_State;
    m_State = state;
    
    switch (m_State) {
        case BS_SLEEPING:
            onEnterSleeping();
            break;
        case BS_WANDERING:
            onEnterWandering();
            break;
        case BS_TRACKING:
            onEnterTracking();
            break;
        case BS_FLEEING:
            onEnterFleeing();
            break;
        case BS_MOVING:
            onEnterMoving();
            break;
        case BS_ATTACK:
            onEnterAttack();
            break;
        case BS_DEATH:
            onEnterDeath();
            break;
        case BS_SKILL1:
            onEnterSkill1();
            break;
        case BS_SKILL2:
            onEnterSkill2();
            break;
        case BS_SKILL3:
            onEnterSkill3();
            break;
        default:
            break;
    }
}
void BaseBoss::onEnter()
{
    Actor::onEnter();
    scheduleUpdate();
}
void BaseBoss::onExit()
{
    unscheduleUpdate();
    Actor::onExit();
}
void BaseBoss::update(float delta)
{
    if(!isVisible())
        return;
    switch (m_State) {
        case BS_SLEEPING:
            {
                if(isPlayerInsideBossRoom() && VoxelExplorer::getInstance()->checkBossAlert(this))
                    setState(BS_TRACKING);
            }
            break;
        case BS_WANDERING:
            {
                setState(BS_MOVING);
            }
            break;
        case BS_TRACKING:
            {
                m_fFirstTrackingTimer -= delta;
                if(m_fFirstTrackingTimer < 0)
                {
                    if(VoxelExplorer::getInstance()->checkBossCanAttack(this))
                        setState(BS_ATTACK);
                    else
                        setState(BS_MOVING);
                }
            }
            break;
        case BS_FLEEING:
            {
                if(VoxelExplorer::getInstance()->checkBossFleeFromPlayer(this))
                    setState(BS_MOVING);
                else if (VoxelExplorer::getInstance()->checkBossCanAttack(this))
                    setState(BS_ATTACK);
                else
                    setState(BS_TRACKING);
            }
            break;
        default:
            break;
    }
    if(m_pFakeShadow)
        m_pFakeShadow->setPosition3D(Vec3(getPositionX(),-TerrainTile::CONTENT_SCALE*0.49f,getPositionZ()));
}

void BaseBoss::onEnterSleeping()
{
    m_bEnableFlee = false;
}
void BaseBoss::onExitSleeping()
{
}
void BaseBoss::onEnterWandering()
{
}
void BaseBoss::onExitWandering()
{
}
void BaseBoss::onEnterTracking()
{
    if(m_LastState == BS_SLEEPING)
    {
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_BOSS_ALERT, this);
        m_fFirstTrackingTimer = 2;
    }
    else if(m_LastState == BS_FLEEING)
    {
        if(VoxelExplorer::getInstance()->checkBossFleeFromPlayer(this))
            setState(BS_FLEEING);
    }
}
void BaseBoss::onExitTracking()
{
    m_fFirstTrackingTimer = 0;
}

void BaseBoss::onEnterFleeing()
{
}
void BaseBoss::onExitFleeing()
{
}

void BaseBoss::onEnterMoving()
{
    if(m_LastState == BS_TRACKING)
    {
        if(VoxelExplorer::getInstance()->trackToPlayer(this, m_NextPos))
            moveToNext(m_NextPos);
        else
            setState(BS_WANDERING);
    }
    else if(m_LastState == BS_WANDERING)
    {
        if(VoxelExplorer::getInstance()->wanderingAround(this, m_NextPos))
            moveToNext(m_NextPos);
        else
            setState(BS_WANDERING);
    }
    else if(m_LastState == BS_FLEEING)
    {
        if(VoxelExplorer::getInstance()->fleeFromPlayer(this, m_BackPos))
            moveToNext(m_BackPos);
        else
            setState(BS_WANDERING);
    }
}
void BaseBoss::onExitMoving()
{
    setPositionY(-0.5f*TerrainTile::CONTENT_SCALE);
    setOpacity(255);
    this->stopAllActions();
}

void BaseBoss::onEnterAttack()
{
    doAttack();
}
void BaseBoss::onExitAttack()
{
}

void BaseBoss::onEnterDeath()
{
    if(getEffectCount() > 0)
    {
        OutlineEffect3D* outline = dynamic_cast<OutlineEffect3D*>(getEffect(0));
        if(outline)
        {
            Color3B outlineColor = UtilityHelper::randomColor();
            outline->setOutlineColor(Vec3(outlineColor.r/255.0f, outlineColor.g/255.0f, outlineColor.b/255.0f));
        }
    }
    this->stopAllActions();
    removeTerrainTileFlag(TileInfo::ATTACKABLE);
    removeTerrainTileFlagByPos(TileInfo::ATTACKABLE, m_NextPos);
    removeTerrainTileFlagByPos(TileInfo::ATTACKABLE, m_BackPos);
    this->setVisible(false);
    if(m_pFakeShadow)
        m_pFakeShadow->setVisible(false);
    VoxelExplorer::getInstance()->addExplosion(getPosition3D());
    VoxelExplorer::getInstance()->generatePickItemByBoss(getPosInMap(), m_pBossProperty->getValueCopper().GetLongValue());
}
void BaseBoss::onExitDeath()
{
}
void BaseBoss::onEnterSkill1()
{
}
void BaseBoss::onExitSkill1()
{
}
void BaseBoss::onEnterSkill2()
{
}
void BaseBoss::onExitSkill2()
{
}
void BaseBoss::onEnterSkill3()
{
}
void BaseBoss::onExitSkill3()
{
}
void BaseBoss::setActorDir( ActorDir dir )
{
    if(m_dir == dir)
        return;
    m_dir = dir;
    EaseSineOut* rotateTo = nullptr;
    switch (m_dir) {
        case AD_FORWARD:
            rotateTo = EaseSineOut::create(RotateTo::create(0.2f, Vec3(0,180,0)));
            break;
        case AD_LEFT:
            rotateTo = EaseSineOut::create(RotateTo::create(0.2f, Vec3(0,-90,0)));
            break;
        case AD_RIGHT:
            rotateTo = EaseSineOut::create(RotateTo::create(0.2f, Vec3(0,90,0)));
            break;
        case AD_BACK:
            rotateTo = EaseSineOut::create(RotateTo::create(0.2f, Vec3(0,0,0)));
            break;
        default:
            break;
    }
    this->runAction(rotateTo);
}

void BaseBoss::onLand(bool updateMiniMap)
{
    CCLOG("boss onland pos = %f,%f", getPosInMap().x, getPosInMap().y);
    if(m_LastState == BS_WANDERING)
    {
        if(VoxelExplorer::getInstance()->checkBossAlert(this))
        {
            if(VoxelExplorer::getInstance()->trackToPlayer(this, m_NextPos))
                setState(BS_TRACKING);
            else if(VoxelExplorer::getInstance()->fleeFromPlayer(this, m_BackPos))
                setState(BS_FLEEING);
            else
                setState(BS_WANDERING);
        }
        else
            setState(BS_WANDERING);
    }
    else
    {
        if(m_bEnableFlee)
            setState(BS_FLEEING);
        else
            setState(BS_TRACKING);
    }
    if(isVisible() && updateMiniMap)
        VoxelExplorer::getInstance()->updateMiniMap();
}
void BaseBoss::moveToNext(const cocos2d::Vec2& next)
{
    CCLOG("Boss posx = %f, posy = %f", getPosInMap().x, getPosInMap().y);
    CCLOG("Boss next posx = %f, posy = %f", next.x, next.y);
    
    Vec2 vd = next - getPosInMap();
    if(std::abs(vd.x) > std::abs(vd.y))
    {
        if(next.x > getPosInMap().x)
            setActorDir(AD_RIGHT);
        else
            setActorDir(AD_LEFT);
    }
    else
    {
        if(next.y > getPosInMap().y)
            setActorDir(AD_FORWARD);
        else
            setActorDir(AD_BACK);
    }
    this->removeTerrainTileFlag(TileInfo::ATTACKABLE);
    this->addTerrainTileFlagByPos(TileInfo::ATTACKABLE, next);
    Vec3 oriScale = Vec3(getScaleX(), getScaleY(), getScaleZ());
    if(m_bJumpMove)
    {
        ScaleTo* scaleTo1 = ScaleTo::create(0.1f, oriScale.x, oriScale.y*0.8f, oriScale.z);
        ScaleTo* scaleTo2 = ScaleTo::create(0.1f, oriScale.x, oriScale.y, oriScale.z);
        EaseSineOut* moveUp = EaseSineOut::create(MoveTo::create(0.1f, Vec3((next.x + getPosInMap().x)*TerrainTile::CONTENT_SCALE*0.5f, getPositionY() + TerrainTile::CONTENT_SCALE*0.5f, -(next.y + getPosInMap().y)*TerrainTile::CONTENT_SCALE*0.5f)));
        EaseSineOut* moveDown = EaseSineOut::create(MoveTo::create(0.1f, Vec3(next.x*TerrainTile::CONTENT_SCALE, getPositionY(), -next.y*TerrainTile::CONTENT_SCALE)));
        Sequence* sequenceJump = Sequence::create(moveUp, moveDown, NULL);
        Spawn* spawn = Spawn::create(scaleTo2, sequenceJump, NULL);
        DelayTime* delay = DelayTime::create(0.3f);
        CallFunc* callback = CallFunc::create(CC_CALLBACK_0(BaseBoss::onLand,this, true));
        Sequence* sequence = Sequence::create(scaleTo1, spawn, delay, callback, NULL);
        this->runAction(Speed::create(sequence, m_pBossProperty->getFactor().GetFloatValue()));
    }
    else
    {
        ScaleTo* scaleTo1 = ScaleTo::create(0.25f, oriScale.x, oriScale.y, oriScale.z*0.8f);
        ScaleTo* scaleTo2 = ScaleTo::create(0.25f, oriScale.x, oriScale.y, oriScale.z);
        EaseBackIn* move = EaseBackIn::create(MoveTo::create(0.5f, Vec3(next.x*TerrainTile::CONTENT_SCALE, getPositionY(), -next.y*TerrainTile::CONTENT_SCALE)));
        Sequence* sequenceScale = Sequence::create(scaleTo1, scaleTo2, NULL);
        Spawn* spawn = Spawn::create(move, sequenceScale, NULL);
        CallFunc* callback = CallFunc::create(CC_CALLBACK_0(BaseBoss::onLand,this, true));
        Sequence* sequence = Sequence::create(spawn, callback, NULL);
        this->runAction(Speed::create(sequence, m_pBossProperty->getFactor().GetFloatValue()));
    }
}
void BaseBoss::doAttack()
{
    Vec3 dir = Vec3::ZERO;
    Vec2 playerPos = VoxelExplorer::getInstance()->getPlayer()->getPosInMap();
    CCLOG("boss===== pos %f, %f", getPosInMap().x, getPosInMap().y);
    CCLOG("attack===== pos %f, %f", playerPos.x, playerPos.y);
    Vec2 vd = playerPos - getPosInMap();
    if(std::abs(vd.x) > std::abs(vd.y))
    {
        if(playerPos.x > getPosInMap().x)
        {
            dir = Vec3(TerrainTile::CONTENT_SCALE, 0, 0);
            setActorDir(AD_RIGHT);
        }
        else
        {
            dir = Vec3(-TerrainTile::CONTENT_SCALE, 0, 0);
            setActorDir(AD_LEFT);
        }
    }
    else
    {
        if(playerPos.y > getPosInMap().y)
        {
            dir = Vec3(0, 0, -TerrainTile::CONTENT_SCALE);
            setActorDir(AD_FORWARD);
        }
        else
        {
            dir = Vec3(0, 0, TerrainTile::CONTENT_SCALE);
            setActorDir(AD_BACK);
        }
    }
    
    handleAttackStyle(playerPos, dir);
}
void BaseBoss::handleAttackStyle(const cocos2d::Vec2& playerPos, const cocos2d::Vec3& dir)
{
    if(m_bJumpMove)
    {
        EaseSineOut* moveUp = EaseSineOut::create(MoveTo::create(0.1f, Vec3(getPositionX(), getPositionY() + TerrainTile::CONTENT_SCALE*0.25f, getPositionZ()) + dir*0.4f));
        CallFunc* callback = CallFunc::create(CC_CALLBACK_0(VoxelExplorer::handlePlayerHurtByBoss,VoxelExplorer::getInstance(),playerPos, this));
        EaseSineOut* moveDown = EaseSineOut::create(MoveTo::create(0.1f, getPosition3D()));
        Sequence* sequenceJump = Sequence::create(moveUp, callback, moveDown, NULL);
        CallFunc* callback2 = CallFunc::create(CC_CALLBACK_0(BaseBoss::onLand,this, false));
        DelayTime* delay = DelayTime::create(0.8f);
        Sequence* sequence = Sequence::create(sequenceJump, delay, callback2, NULL);
        this->runAction(Speed::create(sequence, m_pBossProperty->getFactor().GetFloatValue()));
    }
    else
    {
        Vec3 oriScale = Vec3(getScaleX(), getScaleY(), getScaleZ());
        ScaleTo* scaleTo1 = ScaleTo::create(0.5f, oriScale.x, oriScale.y, oriScale.z*0.8f);
        ScaleTo* scaleTo2 = ScaleTo::create(0.5f, oriScale.x, oriScale.y, oriScale.z);
        CallFunc* callback = CallFunc::create(CC_CALLBACK_0(VoxelExplorer::handlePlayerHurtByBoss,VoxelExplorer::getInstance(),playerPos, this));
        EaseBackIn* moveTo1 = EaseBackIn::create(MoveTo::create(0.5f, getPosition3D() + dir*0.4f));
        EaseBackIn* moveTo2 = EaseBackIn::create(MoveTo::create(0.5f, getPosition3D()));
        Sequence* sequenceScale = Sequence::create(scaleTo1, scaleTo2, NULL);
        Sequence* sequenceMove = Sequence::create(moveTo1, callback, moveTo2, NULL);
        Spawn* spawn = Spawn::create(sequenceMove, sequenceScale, NULL);
        CallFunc* callback2 = CallFunc::create(CC_CALLBACK_0(BaseBoss::onLand,this, false));
        Sequence* sequence = Sequence::create(spawn, callback2, NULL);
        this->runAction(Speed::create(sequence, m_pBossProperty->getFactor().GetFloatValue()));
    }
}
void BaseBoss::handleSkillStage(int currentHp)
{
    if((m_pBossProperty->getCurrentHP() > m_pBossProperty->getMaxHP() * 0.75f) && (currentHp <= m_pBossProperty->getMaxHP() * 0.75f))
    {
        setState(BS_SKILL1);
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_BOSS_SKILL1, this);
    }
    else if((m_pBossProperty->getCurrentHP() > m_pBossProperty->getMaxHP() * 0.5f) && (currentHp <= m_pBossProperty->getMaxHP() * 0.5f))
    {
        setState(BS_SKILL2);
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_BOSS_SKILL2, this);
    }
    else if ((m_pBossProperty->getCurrentHP() > m_pBossProperty->getMaxHP() * 0.25f) && (currentHp <= m_pBossProperty->getMaxHP() * 0.25f))
    {
        setState(BS_SKILL3);
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_BOSS_SKILL3, this);
    }
}