//
//  Enemy.h
//  Tone_Skipper
//
//
//

#ifndef __Tone_Skipper__Enemy__
#define __Tone_Skipper__Enemy__

#include "Actor.h"
class Enemy : public Actor
{
public:
    typedef enum {
        ET_NORMAL_SKULL = 0,
        ET_UNKNOWN
    } EnemyType;
    
    typedef enum {
        ES_IDLE = 0,
        ES_PATROL, //巡逻
        ES_PURSUE, //追击
        ES_ATTACK, //攻击
        ES_FIGHT_JUDGE,//战斗判定
        ES_DEATH,//死亡
        ES_UNKNOWN
    } EnemyState;
    
    typedef enum {
        ED_LEFT = 0,
        ED_RIGHT,
        ED_BACK,
        ED_UNKNOWN
    } EnemyDirection;
protected:
    Enemy();
    virtual ~Enemy();
    
    virtual void onEnterIdleState(){};
    virtual void onExitIdleState(){};
    
    virtual void onEnterDeathState(){};
    virtual void onExitDeathState(){};
    
    virtual cocos2d::Rect getBoundingBox() const override;
public:
    virtual void update(float delta) override;
    
    EnemyType getEnemyType() const { return m_EnemyType; }
    EnemyState getEnemyState() const { return m_EnemyState; }
    void setEnemyState(EnemyState state);
    EnemyDirection getEnemyDirection() const { return m_EnemyDirection; }
    void setEnemyDirection(EnemyDirection direction);
    EnemyDirection getEnemyLastDirection() const { return m_EnemyLastDirection;}
   
protected:
    
    EnemyType                  m_EnemyType;
    EnemyState                 m_EnemyState;
    EnemyDirection             m_EnemyDirection;
    EnemyDirection             m_EnemyLastDirection;
    float                      m_MovMaxDistance;
    float                      m_AttachRange;
    float                      m_HatredRange;
};

#endif /* defined(__Tone_Skipper__Enemy__) */
