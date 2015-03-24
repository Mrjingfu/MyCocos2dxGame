//
//  Enemies.h
//  Geometry-Wars
//
//  Created by wang haibo on 15/3/9.
//
//

#ifndef __Geometry_Wars__Enemies__
#define __Geometry_Wars__Enemies__

#include "GameActor.h"

class Enemy : public GameActor
{
    friend class ActorsManager;
public:
    typedef enum{
        ET_UNKNOWN = 0,         ///未知
        ET_CIRCLE,              ///线性追踪
        ET_CIRCLE_COLORED,      ///死后分裂CIRCLE，死后有几率掉落屏幕炸弹
        ET_TRIANGLE,            ///快速追踪，
        ET_TRIANGLE_COLORED,    ///快速追踪，会长距离直线冲锋，死后有几率掉落防护罩
        ET_DIAMOND,             ///躲避攻击，射击发射子弹
        ET_DIAMOND_COLORED,     ///躲避攻击，每5秒分裂DIAMOND， 死后有几率掉落武器强化道具
        ET_HEXAGON,             ///成对出现，拉扯激光
        ET_HEXAGON_COLORED,     ///单独出现，生成HEXAGON,编制激光，死后生成黑洞静力场，死后有几率掉落武器强化道具
        ET_STAR,                ///慢速躲避，五星旋转弹幕
        ET_STAR_COLORED,        ///慢速躲避，快速五星旋转弹幕， 死后几率五方向弹幕
        
    } EnemyType;
    
    cocos2d::Color3B getColor();
    void setColor(const cocos2d::Color3B& color);
    
    virtual void fire(float delta){};
    virtual void beginTrack();
    
    virtual void update(float delta) override;
protected:
    Enemy();
    virtual ~Enemy();
protected:
    EnemyType   m_EnemyType;
};
/// 线性追踪
class Circle : public Enemy
{
    friend class ActorsManager;
public:
    virtual void onEnterDead() override;
protected:
    Circle();
    virtual ~Circle();
};

/// 线性追踪
class ColorCircle : public Circle
{
    friend class ActorsManager;
public:
    virtual void onEnterDead() override;
protected:
    ColorCircle();
    virtual ~ColorCircle();
};

/// 快速追踪
class Triangle : public Enemy
{
    friend class ActorsManager;
public:
    virtual void onEnterDead() override;
    virtual void beginTrack();
protected:
    Triangle();
    virtual ~Triangle();
};

/// 快速追踪，会长距离直线冲锋，死后有几率掉落防护罩
class ColorTriangle : public Triangle
{
    friend class ActorsManager;
protected:
    ColorTriangle();
    virtual ~ColorTriangle();
public:
    virtual void update(float delta) override;
    virtual void onEnterCharge();
    virtual void onExitCharge();
private:
    float   m_fTrackTime;
    float   m_fChargeTime;
    float   m_fIdleTime;
};

#endif /* defined(__Geometry_Wars__Enemies__) */
