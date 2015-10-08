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

class WalkState:public EnemyState {
    WalkState();
public:
    SINGLE_FUNC(WalkState);
    virtual ~WalkState();
    virtual void onEnter(Enemy *);
    virtual void update(Enemy *,float delta)  ;
    virtual void onExit(Enemy*);

};

#endif /* WalkState_hpp */
