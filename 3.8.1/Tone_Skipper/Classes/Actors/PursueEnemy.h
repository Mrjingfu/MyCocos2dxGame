//
//  PursueEnemy.hpp
//  Tone_Skipper
//
//  Created by 创李 on 15/10/12.
//
//

#ifndef PursueEnemy_hpp
#define PursueEnemy_hpp

#include "PatrolEnemy.h"

class PursueEnemy:public PatrolEnemy {
    
    
public:
    PursueEnemy();
    virtual ~PursueEnemy();
public:

    virtual void onLand() override;
    virtual void onCollision() override;
    virtual void onAir() override;
};

#endif /* PursueEnemy_hpp */
