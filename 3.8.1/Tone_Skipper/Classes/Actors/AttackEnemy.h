//
//  PatrolEnemy.hpp
//  Tone_Skipper
//
//  Created by 创李 on 15/10/8.
//
//

#ifndef AttackEnemy_h
#define AttackEnemy_h

#include "Enemy.h"

class AttackEnemy:public Enemy
{
public:
    AttackEnemy();
    ~AttackEnemy();
public:

    virtual bool loadModel() override;
    virtual bool loadAnimations() override;
    virtual void onLand() override;
    virtual void onCollision() override;
    virtual void onAir() override;
private:
    void turnRound();
};

#endif /* AttackEnemy_h */
