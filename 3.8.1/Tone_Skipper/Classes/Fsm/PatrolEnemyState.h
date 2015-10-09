//
//  WalkState.hpp
//  Tone_Skipper
//
//  Created by 创李 on 15/10/8.
//
//

#ifndef WalkState_hpp
#define WalkState_hpp

#include "EnemyState.h"

class PatrolEnemyState:public EnemyState {
    PatrolEnemyState();
public:
    SINGLE_FUNC(PatrolEnemyState);
    virtual ~PatrolEnemyState();
    virtual void onEnter(Enemy *);
    virtual void update(Enemy *,float delta)  ;
    virtual void onExit(Enemy*);
private:
    void updateNormalSkull(Enemy *,float delta);
};

#endif /* WalkState_hpp */
