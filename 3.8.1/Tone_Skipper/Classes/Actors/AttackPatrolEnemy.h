//
//  PatrolEnemy.hpp
//  Tone_Skipper
//
//  Created by 创李 on 15/10/8.
//
//

#ifndef AttackPatrolEnemy_h
#define AttackPatrolEnemy_h

#include "PatrolEnemy.h"

class AttackPatrolEnemy:public PatrolEnemy
{
public:
    AttackPatrolEnemy();
    ~AttackPatrolEnemy();
public:

    virtual bool loadModel() override;
    virtual bool loadAnimations() override;


};

#endif /* AttackPatrolEnemy */
