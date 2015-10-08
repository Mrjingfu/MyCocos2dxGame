//
//  Enemy.h
//  Tone_Skipper
//
//
//

#ifndef __Tone_Skipper__Enemy__
#define __Tone_Skipper__Enemy__

#include "Actor.h"

class EnemyState;
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
    } EnemyStateType;
    
    typedef enum {
        ED_LEFT = 0,
        ED_RIGHT,
        ED_BACK,
        ED_UNKNOWN
    } EnemyDirection;
protected:
    Enemy();
    virtual ~Enemy();
    
    virtual void onCollision(){};
public:
    virtual void update(float delta) override;
    
    EnemyType getEnemyType() const { return m_EnemyType; }
    EnemyDirection getEnemyDirection() const { return m_EnemyDirection; }
    void setEnemyDirection(EnemyDirection direction);
    EnemyDirection getEnemyLastDirection() const { return m_EnemyLastDirection;}
    
    float getMaxXSpeed(){return m_fMaxXSpeed;}
    float getMaxYSpeed(){return m_fMaxYSpeed;}
    
    cocos2d::Animation* getIdleAnimation() const {return m_pIdleAnimation;}
    cocos2d::Animation* getWalkAnimation() const {return m_pWalkAnimation;}
    
    HueSprite* getEnemySprite(){return m_pSprite;};
    EnemyState* getEnemyState() const { return m_pEnemyState; }
    void setEnemyState(EnemyStateType stateType);
    
    virtual cocos2d::Rect getBoundingBox() const override;
private:
    void updatePosition(float delta);
    EnemyState* createState(EnemyStateType stateType);
protected:
    cocos2d::Animation*       m_pIdleAnimation;
    cocos2d::Animation*       m_pWalkAnimation;
    EnemyState*                 m_pEnemyState;
    
    EnemyType                  m_EnemyType;
    EnemyDirection             m_EnemyDirection;
    EnemyDirection             m_EnemyLastDirection;
    float                      m_MovMaxDistance;
    float                      m_AttachRange;
    float                      m_HatredRange;
};

#endif /* defined(__Tone_Skipper__Enemy__) */
