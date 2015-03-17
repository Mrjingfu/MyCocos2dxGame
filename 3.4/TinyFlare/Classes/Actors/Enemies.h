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
        ET_BLUE,
        ET_BROWN,
        ET_CYAN,
        ET_DARKBLUE,
        ET_DARKGREEN,
        ET_GREEN,
        ET_MAGENTA,
        ET_ORANGE,
        ET_PINK,
        ET_ROSERED,
        ET_TANGERINE,
        ET_YELLOW,
        ET_UNKNOWN
    } EnemyType;
protected:
    Enemy();
    virtual ~Enemy();
    virtual void executeAI(float delta){}
public:
    EnemyType getEnemyType() const;
    void setEnemyType(EnemyType type);
protected:
    EnemyType   m_EnemyType;
};
/// 玩家镜像，高智能AI
class Blue : public Enemy
{
    friend class ActorsManager;
};
/// 最简单追踪玩家，近距离攻击
class Brown : public Enemy
{
    friend class ActorsManager;
protected:
    Brown();
    virtual ~Brown();
    virtual void executeAI(float delta) override;
};

class Cyan : public Enemy
{
    friend class ActorsManager;
};

class Darkblue : public Enemy
{
    friend class ActorsManager;
};

class Darkgreen : public Enemy
{
    friend class ActorsManager;
};

class Green : public Enemy
{
    friend class ActorsManager;
};

class Magenta : public Enemy
{
    friend class ActorsManager;
};

class Orange : public Enemy
{
    friend class ActorsManager;
};

class Pink : public Enemy
{
    friend class ActorsManager;
};

class Rosered : public Enemy
{
    friend class ActorsManager;
};

class Tangerine : public Enemy
{
    friend class ActorsManager;
};

class Yellow : public Enemy
{
    friend class ActorsManager;
};

#endif /* defined(__Geometry_Wars__Enemies__) */
