//
//  GameActor.h
//  Geometry-Wars
//
//  Created by wang haibo on 15/2/5.
//
//

#ifndef __Geometry_Wars__GameActor__
#define __Geometry_Wars__GameActor__

#include "cocos2d.h"

typedef enum {
    AS_UNDERCONTROL = 0,
    AS_TRACK,
    AS_IDLE,
    AS_DEAD,
    AS_CHARGE,
    AS_FLEE,
    AS_BLINK,
    AS_UNKNOWN
} ActorState;

class GameActor : public cocos2d::Node
{
public:
    typedef enum{
        AT_ENEMY,
        AT_PLAYER,
        AT_ENEMY_BULLET,
        AT_PLAYER_BULLET,
        AT_LASER,
        AT_ITEM,
        AT_UNKNOWN
    } ActorType;
protected:
    GameActor();
    virtual ~GameActor();
    
    virtual void onEnterUnderControl(){};
    virtual void onExitUnderControl(){};
    
    virtual void onEnterTrack(){};
    virtual void onExitTrack(){};
    
    virtual void onEnterIdle(){};
    virtual void onExitIdle(){};
    
    virtual void onEnterDead(){};
    virtual void onExitDead(){};
    
    virtual void onEnterCharge(){};
    virtual void onExitCharge(){};
    
    virtual void onEnterFlee(){};
    virtual void onExitFlee(){};
    
    virtual void onEnterBlink(){};
    virtual void onExitBlink(){};
public:
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta){};
    
    void loadModel(const std::string& texName);
    void loadModel(const std::string& texName, const cocos2d::Rect& rect);
    
    void setType(ActorType type) {m_type = type;}
    int getType() const {return m_type;}
    
    cocos2d::Vec2 getDirection() const { return m_Direction; }
    void setDirection(const cocos2d::Vec2& dir) {
        m_Direction = dir;
        m_Direction.normalize();
    }
    
    cocos2d::Vec2 getOrientation() const { return m_Orientation; }
    void setOrientation(const cocos2d::Vec2& orientation) {
        m_Orientation = orientation;
        m_Orientation.normalize();
    }
    
    float getRadius() {
        caculateRadius();
        return m_fRadius;
    }
    void setRadius(float radius) { m_fRadius = radius; }
    
    float getMaxSpeed() const { return m_fMaxSpeed; }
    void setMaxSpeed(float maxSpeed){ m_fMaxSpeed = maxSpeed; }
    
    cocos2d::Vec2 getVelocity() const { return m_Velocity; }
    void setVelocity(const cocos2d::Vec2& velocity){
        m_Velocity = velocity;
    }
    
    cocos2d::Node* getModel() const { return m_pModel; }
    
    void setBounce(bool bounce);

    virtual void caculateRadius();
    virtual void updateOrientation();
    
    ActorState getActorState() const { return m_curState; }
    void setActorState(ActorState state);
protected:
    cocos2d::Sprite*    m_pModel;
    cocos2d::Vec2       m_Direction;            ///指示移动方向
    cocos2d::Vec2       m_Orientation;          ///朝向
    float               m_fAccel;               ///加速度
    float               m_fMaxSpeed;            ///最大速度
    cocos2d::Vec2       m_Velocity;             ///当前速度
    ActorType           m_type;
    float               m_fRadius;              ///半径
    bool                m_bBounce;              ///是否碰撞了
    
    ActorState          m_curState;             ///Actor当前状态
};

#endif /* defined(__Geometry_Wars__GameActor__) */
