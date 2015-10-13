//
//  PatrolEnemy.hpp
//  Tone_Skipper
//
//  Created by 创李 on 15/10/8.
//
//

#ifndef PatrolEnemy_h
#define PatrolEnemy_h

#include "Enemy.h"

class PatrolEnemy:public Enemy
{
public:
    PatrolEnemy();
    virtual ~PatrolEnemy();
public:

    virtual bool loadModel() override;
    virtual bool loadAnimations() override;
    virtual void onLand() override;
    virtual void onCollision() override;
    virtual void onAir() override;
protected:
    void turnRound();
};

#endif /* PatrolEnemy_h */
