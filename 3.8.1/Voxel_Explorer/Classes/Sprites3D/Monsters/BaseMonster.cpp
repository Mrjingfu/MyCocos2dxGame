//
//  BaseMonster.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/22.
//
//

#include "BaseMonster.hpp"
#include "BaseLevel.h"
#include "AlisaMethod.h"
#include "PlayerProperty.hpp"
#include "VoxelExplorer.h"
#include "GameFormula.hpp"
#include "UtilityHelper.h"
#include "LevelResourceManager.h"
#include "FakeShadow.hpp"
#include "StatisticsManager.hpp"
USING_NS_CC;
const std::string MONSTER_MODEL_NAMES[] = {
    "MMN_UNKNOWN",
    
    //SEWER_BEGIN
    "MMN_RAT",             ///老鼠
    "MMN_BAT",             ///蝙蝠
    "MMN_SNAKE",           ///蛇
    "MMN_SPIDER",          ///蜘蛛
    "MMN_SLIME",           ///史莱姆
    //SEWER_END
    
    //PRISON_BEGIN
    "MMN_ALLIP",           ///怨魂
    "MMN_PRISONER",        ///囚犯
    "MMN_PRISONGUARD",     ///监狱守卫
    "MMN_TORTURE",         ///拷问者
    "MMN_MOB",             ///暴徒
    //PRISON_END
    
    //FANE_BEGIN
    "MMN_BELIEVER",        ///信徒
    "MMN_GATEKEEPER",      ///看门人
    "MMN_APOLOGIST",       ///辩护者
    "MMN_ADJUDICATOR",     ///审判者
    "MMN_PRIEST",          ///牧师
    //FANE_END
    
    //MINES_BEGIN
    "MMN_DEATHMINER",      ///死亡矿工
    "MMN_KOBOLD",          ///狗头人
    "MMN_OOZE",            ///软泥怪
    "MMN_SHADOW",          ///阴影怪
    "MMN_ANKHEG",          ///掘地虫
    //MINES_END
    
    //CAVE_BEGIN
    "MMN_WOLF",            ///狼
    "MMN_BEAR",            ///熊
    "MMN_GOBLIN",          ///地精
    "MMN_DINOSAUR",        ///恐龙
    "MMN_GNOLL",           ///豺狼人
    //CAVE_END
    
    //TOMB_BEGIN
    "MMN_SKELETON",        ///骷髅
    "MMN_ZOMBIE",          ///僵尸
    "MMN_GARGOYLE",        ///石像鬼
    "MMN_GHOST",           ///幽灵
    "MMN_GHOUL",           ///食尸鬼
    //TOMB_END
    
    "MMN_MAX"
};
BaseMonster::BaseMonster()
{
    m_Type = MT_UNKNOWN;
    m_State = MS_UNKNOWN;
    m_LastState = MS_UNKNOWN;
    m_bJumpMove = true;
    
    m_pHurtData = new (std::nothrow) HurtData();
    
    m_nFOV = 4;
    m_nAttackRange = 1;
    m_fConfusingTimer = 3.0f;
    m_fFirstTrackingTimer = cocos2d::random(1.0f, 1.5f);
    m_fWanderingDelayTimer = cocos2d::random(0.02f, 0.05f); ////巡逻时每次移动前的延迟
    
    m_pMonsterProperty = new (std::nothrow) MonsterProperty();
    if(m_pMonsterProperty)
        m_pMonsterProperty->adjustByDC();
}
BaseMonster::~BaseMonster()
{
    CC_SAFE_DELETE(m_pHurtData);
    CC_SAFE_DELETE(m_pMonsterProperty);
}
std::string BaseMonster::getIconRes()
{
    return LevelResourceManager::getInstance()->getMonsterIconRes(MONSTER_MODEL_NAMES[m_Type]);
}
std::string BaseMonster::getDesc()
{
    CC_ASSERT(m_pMonsterProperty != nullptr);
    if(m_pMonsterProperty->isElite())
    {
        return UtilityHelper::getLocalString(MONSTER_MODEL_NAMES[m_Type]) + UtilityHelper::getLocalString("MONSTER_ELITE");
    }
    return UtilityHelper::getLocalString(MONSTER_MODEL_NAMES[m_Type]);
}
void BaseMonster::attackedByPlayer(bool miss)
{
    if(!m_pMonsterProperty || !m_pHurtData)
        return;
    
    m_pHurtData->reset();
    m_pHurtData->m_vPos = this->getPosition3D();
    
    if(miss)
    {
        m_pHurtData->m_bDodge = true;
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_MONSTER_HURT, m_pHurtData);
        return;
    }
    
    float percentDodgeRate = m_pMonsterProperty->getDodgeRate().GetFloatValue();
    float percentHit = 1.0 - percentDodgeRate;
    AlisaMethod* amDodgeRate = AlisaMethod::create(percentDodgeRate,percentHit,-1.0, NULL);
    if(amDodgeRate)
    {
        if(amDodgeRate->getRandomIndex() == 0)
        {
            m_pHurtData->m_bDodge = true;
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_MONSTER_HURT, m_pHurtData);
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
        }
    }
        
    int defense = m_pMonsterProperty->getDefense().GetLongValue();
        
    attack = MAX(attack + defense, 0);
        
    float percentBlockRate = m_pMonsterProperty->getBlockRate().GetFloatValue();
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
        
    int currentHp = m_pMonsterProperty->getCurrentHP().GetLongValue();
    currentHp = MAX(currentHp - attack , 0);
    CCLOG("Monster: CurrentHp = %d, playerAttack = %d", currentHp, attack);
    m_pHurtData->m_nDamage = -attack;
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_MONSTER_HURT, m_pHurtData);
    if(currentHp == 0)
    {
        setState(MS_DEATH);
        CChaosNumber addexp = 0;
        if(m_pMonsterProperty->isElite())
            addexp = GameFormula::getKillEliteMonsterExp(PlayerProperty::getInstance()->getLevel(), m_pMonsterProperty->getLevel());
        else
            addexp = GameFormula::getKillNormalMonsterExp(PlayerProperty::getInstance()->getLevel(), m_pMonsterProperty->getLevel());
        PlayerProperty::getInstance()->setExp(PlayerProperty::getInstance()->getExp() + addexp.GetLongValue());
        StatisticsManager::getInstance()->addMonsterKillNum(this->getMonsterType());
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_MONSTER_DEATH, this);
    }
    else
    {
        m_pMonsterProperty->setCurrentHP(currentHp);
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_MONSTER_PROPERTY_DIRTY, this);
    }
}
void BaseMonster::setState(MonsterState state)
{
    if(m_State == state)
        return;
    if(m_State == MS_DEATH && state != MS_SLEEPING)
        return;
        
    switch (m_State) {
        case MS_SLEEPING:
            onExitSleeping();
            break;
        case MS_WANDERING:
            onExitWandering();
            break;
        case MS_TRACKING:
            onExitTracking();
            break;
        case MS_FLEEING:
            onExitFleeing();
            break;
        case MS_PASSIVE:
            onExitPassive();
            break;
        case MS_CONFUSING:
            onExitConfusing();
            break;
        case MS_MOVING:
            onExitMoving();
            break;
        case MS_ATTACK:
            onExitAttack();
            break;
        case MS_DEATH:
            onExitDeath();
            break;
        default:
            break;
    }
    
    m_LastState = m_State;
    m_State = state;
    
    switch (m_State) {
        case MS_SLEEPING:
            onEnterSleeping();
            break;
        case MS_WANDERING:
            onEnterWandering();
            break;
        case MS_TRACKING:
            onEnterTracking();
            break;
        case MS_FLEEING:
            onEnterFleeing();
            break;
        case MS_PASSIVE:
            onEnterPassive();
            break;
        case MS_CONFUSING:
            onEnterConfusing();
            break;
        case MS_MOVING:
            onEnterMoving();
            break;
        case MS_ATTACK:
            onEnterAttack();
            break;
        case MS_DEATH:
            onEnterDeath();
            break;
        default:
            break;
    }

}
void BaseMonster::onEnter()
{
    Actor::onEnter();
    scheduleUpdate();
    addTerrainTileFlag(TileInfo::ATTACKABLE);
}
void BaseMonster::onExit()
{
    unscheduleUpdate();
    Actor::onExit();
}
void BaseMonster::update(float delta)
{
    if(!isVisible())
        return;
    switch (m_State) {
        case MS_SLEEPING:
            {
                if(VoxelExplorer::getInstance()->checkMonsterAlert(this))
                    setState(MS_TRACKING);
            }
            break;
        case MS_TRACKING:
            {
                m_fFirstTrackingTimer -= delta;
                if(m_fFirstTrackingTimer < 0)
                {
                    if(!VoxelExplorer::getInstance()->checkMonsterAlert(this))
                        setState(MS_CONFUSING);
                    else
                    {
                        if(VoxelExplorer::getInstance()->checkMonsterCanAttack(this))
                            setState(MS_ATTACK);
                        else
                            setState(MS_MOVING);
                    }
                }
            }
            break;
        case MS_CONFUSING:
            {
                if(VoxelExplorer::getInstance()->checkMonsterAlert(this))
                    setState(MS_TRACKING);
                else
                {
                    m_fConfusingTimer -= delta;
                    if(m_fConfusingTimer < 0)
                        setState(MS_WANDERING);
                }
            }
            break;
        case MS_WANDERING:
            {
                m_fWanderingDelayTimer -= delta;
                if(m_fWanderingDelayTimer < 0)
                    setState(MS_MOVING);
            }
            break;

        default:
            break;
    }
    if(m_pFakeShadow)
        m_pFakeShadow->setPosition3D(Vec3(getPositionX(),-TerrainTile::CONTENT_SCALE*0.49f,getPositionZ()));
}

void BaseMonster::onEnterSleeping()
{
    if(m_pMonsterProperty && m_pMonsterProperty->isElite())
    {
        EaseSineOut* tintTo1 = EaseSineOut::create(TintTo::create(1.0f, Color3B::GRAY));
        EaseSineOut* tintTo2 = EaseSineOut::create(TintTo::create(1.0f, Color3B::WHITE));
        Sequence* sequence = Sequence::create(tintTo1, tintTo2, nil);
        RepeatForever* repeat = RepeatForever::create(sequence);
        this->runAction(repeat);
    }
}
void BaseMonster::onExitSleeping()
{
}

void BaseMonster::onEnterWandering()
{
    m_fWanderingDelayTimer = cocos2d::random(0.02f, 0.05f);
}
void BaseMonster::onExitWandering()
{
    m_fWanderingDelayTimer = 0;
}

void BaseMonster::onEnterTracking()
{
    if(m_LastState == MS_SLEEPING || m_LastState == MS_CONFUSING || m_LastState == MS_WANDERING)
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_MONSTER_ALERT, this);
    if(m_LastState == MS_SLEEPING)
    {
        unsigned int lightmask = getLightMask();
        lightmask = lightmask | (unsigned int)LightFlag::LIGHT2;
        setLightMask(lightmask);
        m_fFirstTrackingTimer = cocos2d::random(1.0f, 1.5f);
    }
}
void BaseMonster::onExitTracking()
{
    m_fFirstTrackingTimer = 0;
}

void BaseMonster::onEnterFleeing()
{
}
void BaseMonster::onExitFleeing()
{
}

void BaseMonster::onEnterPassive()
{
}
void BaseMonster::onExitPassive()
{
}
void BaseMonster::onEnterConfusing()
{
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_MONSTER_CONFUSING, this);
}
void BaseMonster::onExitConfusing()
{
    m_fConfusingTimer = 3.0f;
}
void BaseMonster::onEnterMoving()
{
    if(m_LastState == MS_TRACKING)
    {
        Vec2 next;
        if(VoxelExplorer::getInstance()->trackToPlayer(this, next))
            moveToNext(next);
        else
            setState(MS_WANDERING);
    }
    else if(m_LastState == MS_WANDERING)
    {
        Vec2 next;
        if(VoxelExplorer::getInstance()->wanderingAround(this, next))
            moveToNext(next);
        else
            setState(MS_WANDERING);
    }
}
void BaseMonster::onExitMoving()
{
}
void BaseMonster::onEnterAttack()
{
    doAttack();
}
void BaseMonster::onExitAttack()
{
}

void BaseMonster::onEnterDeath()
{
    this->stopAllActions();
    removeTerrainTileFlag(TileInfo::ATTACKABLE);
    this->setVisible(false);
    if(m_pFakeShadow)
        m_pFakeShadow->setVisible(false);
    VoxelExplorer::getInstance()->addExplosion(getPosition3D());
    bool generateItem = GameFormula::generatePickItemByMonster(m_pMonsterProperty->isElite(), false);
    VoxelExplorer::getInstance()->generatePickItem(getPosInMap(), generateItem, m_pMonsterProperty->getValueCopper().GetLongValue(), m_pMonsterProperty->getLevel().GetLongValue());
}
void BaseMonster::onExitDeath()
{
}
void BaseMonster::setActorDir( ActorDir dir )
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
void BaseMonster::onLand()
{
    CCLOG("monster onland pos = %f,%f", getPosInMap().x, getPosInMap().y);
    if(m_LastState == MS_WANDERING)
    {
        if(VoxelExplorer::getInstance()->checkMonsterAlert(this))
        {
            Vec2 next;
            if(VoxelExplorer::getInstance()->trackToPlayer(this, next))
                setState(MS_TRACKING);
            else
                setState(MS_WANDERING);
        }
        else
            setState(MS_WANDERING);
    }
    else
        setState(MS_TRACKING);
    if(isVisible())
        VoxelExplorer::getInstance()->updateMiniMap();
}
void BaseMonster::moveToNext(const cocos2d::Vec2& next)
{
    CCLOG("monster posx = %f, posy = %f", getPosInMap().x, getPosInMap().y);
    CCLOG("monster track posx = %f, posy = %f", next.x, next.y);
    
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
        CallFunc* callback = CallFunc::create(CC_CALLBACK_0(BaseMonster::onLand,this));
        Sequence* sequence = Sequence::create(scaleTo1, spawn, delay, callback, NULL);
        this->runAction(sequence);
    }
    else
    {
        ScaleTo* scaleTo1 = ScaleTo::create(0.25f, oriScale.x, oriScale.y, oriScale.z*0.8f);
        ScaleTo* scaleTo2 = ScaleTo::create(0.25f, oriScale.x, oriScale.y, oriScale.z);
        EaseBackIn* move = EaseBackIn::create(MoveTo::create(0.5f, Vec3(next.x*TerrainTile::CONTENT_SCALE, getPositionY(), -next.y*TerrainTile::CONTENT_SCALE)));
        Sequence* sequenceScale = Sequence::create(scaleTo1, scaleTo2, NULL);
        Spawn* spawn = Spawn::create(move, sequenceScale, NULL);
        CallFunc* callback = CallFunc::create(CC_CALLBACK_0(BaseMonster::onLand,this));
        Sequence* sequence = Sequence::create(spawn, callback, NULL);
        this->runAction(sequence);
    }
}
void BaseMonster::doAttack()
{
    Vec3 dir = Vec3::ZERO;
    Vec2 playerPos = VoxelExplorer::getInstance()->getPlayer()->getPosInMap();
    CCLOG("monster===== pos %f, %f", getPosInMap().x, getPosInMap().y);
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
    
    if(m_bJumpMove)
    {
        EaseSineOut* moveUp = EaseSineOut::create(MoveTo::create(0.1f, Vec3(getPositionX(), getPositionY() + TerrainTile::CONTENT_SCALE*0.25f, getPositionZ()) + dir*0.4f));
        CallFunc* callback = CallFunc::create(CC_CALLBACK_0(VoxelExplorer::handlePlayerHurt,VoxelExplorer::getInstance(),playerPos, m_pMonsterProperty));
        EaseSineOut* moveDown = EaseSineOut::create(MoveTo::create(0.1f, getPosition3D()));
        Sequence* sequenceJump = Sequence::create(moveUp, callback, moveDown, NULL);
        CallFunc* callback2 = CallFunc::create(CC_CALLBACK_0(BaseMonster::setState,this, MS_TRACKING));
        DelayTime* delay = DelayTime::create(0.7f);
        Sequence* sequence = Sequence::create(sequenceJump, delay, callback2, NULL);
        this->runAction(sequence);
    }
    else
    {
        Vec3 oriScale = Vec3(getScaleX(), getScaleY(), getScaleZ());
        ScaleTo* scaleTo1 = ScaleTo::create(0.5f, oriScale.x, oriScale.y, oriScale.z*0.8f);
        ScaleTo* scaleTo2 = ScaleTo::create(0.5f, oriScale.x, oriScale.y, oriScale.z);
        CallFunc* callback = CallFunc::create(CC_CALLBACK_0(VoxelExplorer::handlePlayerHurt,VoxelExplorer::getInstance(),playerPos, m_pMonsterProperty));
        EaseBackIn* moveTo1 = EaseBackIn::create(MoveTo::create(0.5f, getPosition3D() + dir*0.4f));
        EaseBackIn* moveTo2 = EaseBackIn::create(MoveTo::create(0.5f, getPosition3D()));
        Sequence* sequenceScale = Sequence::create(scaleTo1, scaleTo2, NULL);
        Sequence* sequenceMove = Sequence::create(moveTo1, callback, moveTo2, NULL);
        Spawn* spawn = Spawn::create(sequenceMove, sequenceScale, NULL);
        CallFunc* callback2 = CallFunc::create(CC_CALLBACK_0(BaseMonster::setState,this,MS_TRACKING));
        Sequence* sequence = Sequence::create(spawn, callback2, NULL);
        this->runAction(sequence);
    }
}

bool BaseMonster::createFakeShadow()
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