//
//  PursueEnemyState.hpp
//  Tone_Skipper
//
//  Created by 创李 on 15/10/12.
//
//

#ifndef PursueEnemyState_hpp
#define PursueEnemyState_hpp

#include "EnemyState.h"

class PursueEnemyState :public EnemyState{
    PursueEnemyState();
    
public:
    SINGLE_FUNC(PursueEnemyState)
    virtual ~PursueEnemyState();
    virtual void onEnter(Enemy *enemy);
    virtual void update(Enemy *enemy,float delta)  ;
    virtual void onExit(Enemy*enemy) ;

};

#endif /* PursueEnemyState_hpp */
