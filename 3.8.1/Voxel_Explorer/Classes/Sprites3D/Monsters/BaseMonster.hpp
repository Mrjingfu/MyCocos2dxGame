//
//  BaseMonster.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/22.
//
//

#ifndef BaseMonster_hpp
#define BaseMonster_hpp

#include "Actor.hpp"
#include "TerrainTile.hpp"
#include "MonsterProperty.hpp"
#include "EventConst.h"
extern const std::string MONSTER_MODEL_NAMES[];
class BaseMonster : public Actor
{
public:
    typedef enum{
        MT_UNKNOWN = 0,
        
        //SEWER_BEGIN
        MT_RAT,             ///老鼠
        MT_BAT,             ///蝙蝠
        MT_SNAKE,           ///蛇
        MT_SPIDER,          ///蜘蛛
        MT_SLIME,           ///史莱姆
        //SEWER_END
        
        //PRISON_BEGIN
        MT_ALLIP,           ///怨魂
        MT_PRISONER,        ///囚犯
        MT_PRISONGUARD,     ///监狱守卫
        MT_TORTURE,         ///拷问者
        MT_MOB,             ///暴徒
        //PRISON_END
        
        //FANE_BEGIN
        MT_BELIEVER,        ///信徒
        MT_GATEKEEPER,      ///看门人
        MT_APOLOGIST,       ///辩护者
        MT_ADJUDICATOR,     ///审判者
        MT_PRIEST,          ///牧师
        //FANE_END
        
        //MINES_BEGIN
        MT_DEATHMINER,      ///死亡矿工
        MT_KOBOLD,          ///狗头人
        MT_OOZE,            ///软泥怪
        MT_SHADOW,          ///阴影怪
        MT_ANKHEG,          ///掘地虫
        //MINES_END

        //CAVE_BEGIN
        MT_WOLF,            ///狼
        MT_BEAR,            ///熊
        MT_GOBLIN,          ///地精
        MT_DINOSAUR,        ///恐龙
        MT_GNOLL,           ///豺狼人
        //CAVE_END
        
        //TOMB_BEGIN
        MT_SKELETON,        ///骷髅
        MT_ZOMBIE,          ///僵尸
        MT_GARGOYLE,        ///石像鬼
        MT_GHOST,           ///幽灵
        MT_GHOUL,           ///食尸鬼
        //TOMB_END

        MT_MAX
    } MonsterType;
    typedef enum{
        MS_UNKNOWN,
        MS_SLEEPING,        ///沉睡
        MS_WANDERING,       ///徘徊
        MS_TRACKING,        ///追踪
        MS_FLEEING,         ///逃跑
        MS_PASSIVE,         ///被动
        MS_CONFUSING,       ///迷惑
        MS_MOVING,          ///移动
        MS_ATTACK,
        MS_DEATH,
        MS_MAX
    } MonsterState;
public:
    std::string getIconRes();
    virtual std::string getDesc();
    
    MonsterState getState() const { return m_State; }
    void setState(MonsterState state);
    
    MonsterProperty* getMonsterProperty() const { return m_pMonsterProperty; }
    void attackedByPlayer(bool miss);
    
    MonsterType getMonsterType() const { return m_Type; }
    
    int getMonsterFOV() const { return m_nFOV; }
    void setMonsterFOV(int fov) { m_nFOV = fov; }
    
    int getAttackRange() const { return m_nAttackRange; }
protected:
    BaseMonster();
    virtual ~BaseMonster();
    
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
    
    virtual void onEnterSleeping();
    virtual void onExitSleeping();
    
    virtual void onEnterWandering();
    virtual void onExitWandering();
    
    virtual void onEnterTracking();
    virtual void onExitTracking();
    
    virtual void onEnterFleeing();
    virtual void onExitFleeing();
    
    virtual void onEnterPassive();
    virtual void onExitPassive();
    
    virtual void onEnterConfusing();
    virtual void onExitConfusing();
    
    virtual void onEnterMoving();
    virtual void onExitMoving();
    
    virtual void onEnterAttack();
    virtual void onExitAttack();
    
    virtual void onEnterDeath();
    virtual void onExitDeath();
    
    virtual void setActorDir( ActorDir dir );
private:
    void onLand();
    void moveToNext(const cocos2d::Vec2& next);
    void doAttack();
protected:
    MonsterType         m_Type;
    MonsterState        m_State;
    MonsterState        m_LastState;
    
    MonsterProperty*    m_pMonsterProperty;
    bool                m_bJumpMove;        ///是否为跳跃移动，否则则是蠕动移动
    
    HurtData*           m_pHurtData;
    
    int                 m_nFOV;             ///怪物视野
    int                 m_nAttackRange;     ///攻击范围
    float               m_fConfusingTimer;  ///迷惑时间计时器
    float               m_fFirstTrackingTimer;  ///由睡眠状态进入追踪状态的反应时间
    float               m_fWanderingDelayTimer; ////巡逻时每次移动前的延迟
};

#endif /* BaseMonster_hpp */
