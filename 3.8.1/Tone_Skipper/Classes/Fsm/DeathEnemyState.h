//
//  DeathEnemyState.hpp
//  Tone_Skipper
//
//  Created by 创李 on 15/10/9.
//
//

#ifndef DeathEnemyState_hpp
#define DeathEnemyState_hpp

#include "EnemyState.h"

class DeathEnemyState :public EnemyState {
    DeathEnemyState();;
    
public:
    SINGLE_FUNC(DeathEnemyState);
    virtual ~DeathEnemyState();
    virtual void onEnter(Enemy *);
    virtual void update(Enemy *,float delta)  ;
    virtual void onExit(Enemy*);
};

#endif /* DeathEnemyState_hpp */
