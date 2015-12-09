//
//  BaseBoss.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/23.
//
//

#ifndef BaseBoss_hpp
#define BaseBoss_hpp

#include "Actor.hpp"
#include "TerrainTile.hpp"
#include "BossProperty.hpp"
#include "EventConst.h"
extern const std::string BOSS_MODEL_NAMES[];
class FakeShadow;
class BaseBoss : public Actor
{
public:
    typedef enum{
        BT_UNKNOWN = 0,

        BT_SLIMEKING,               ///史莱姆王
        BT_WARDEN,                  ///典狱长
        BT_ARCHBISHOP,              ///大主教
        BT_KOBOLDLEADER,            ///狗头人首领
        BT_GIANT,                   ///巨人格鲁尔德
        BT_SKELETONKING,            ///骷髅王
        
        BT_MAX
    } BossType;
    typedef enum{
        BS_UNKNOWN,
        BS_SLEEPING,        ///沉睡
        BS_WANDERING,       ///巡逻
        BS_TRACKING,        ///追踪
        BS_FLEEING,         ///逃跑
        BS_MOVING,          ///移动
        BS_ATTACK,
        BS_DEATH,
        BS_SKILL1,          ///第一阶段技能
        BS_SKILL2,          ///第二阶段技能
        BS_SKILL3,          ///第三阶段技能
        BS_MAX
    } BossState;
    
    BossState getState() const { return m_State; }
    void setState(BossState state);
    
    BossProperty* getBossProperty() const { return m_pBossProperty; }
    BossType getBossType() const { return m_Type; }
    
    int getMonsterFOV() const { return m_nFOV; }
    void setMonsterFOV(int fov) { m_nFOV = fov; }
    
    int getAttackRange() const { return m_nAttackRange; }
    
    void attackedByPlayer(bool miss);
    bool createFakeShadow();
    
    std::string getIconRes();
    virtual std::string getDesc();
protected:
    BaseBoss();
    virtual ~BaseBoss();
    
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
    
    virtual void onEnterMoving();
    virtual void onExitMoving();
    
    virtual void onEnterAttack();
    virtual void onExitAttack();
    
    virtual void onEnterDeath();
    virtual void onExitDeath();
    
    virtual void onEnterSkill1();
    virtual void onExitSkill1();
    virtual void onEnterSkill2();
    virtual void onExitSkill2();
    virtual void onEnterSkill3();
    virtual void onExitSkill3();
    
    virtual void setActorDir( ActorDir dir );
    
    virtual void handleAttackStyle(const cocos2d::Vec2& playerPos, const cocos2d::Vec3& dir);
    virtual void handleSkillStage(int currentHp);
private:
    void onLand();
    void moveToNext(const cocos2d::Vec2& next);
    void doAttack();
protected:
    BossType         m_Type;
    BossState        m_State;
    BossState        m_LastState;
    
    BossProperty*    m_pBossProperty;
    bool             m_bJumpMove;        ///是否为跳跃移动，否则则是蠕动移动
    
    HurtData*        m_pHurtData;
    
    int              m_nFOV;             ///怪物视野
    int              m_nAttackRange;     ///攻击范围
    float            m_fFirstTrackingTimer;  ///由睡眠状态进入追踪状态的反应时间
    
    FakeShadow*      m_pFakeShadow;
};

#endif /* BaseBoss_hpp */
