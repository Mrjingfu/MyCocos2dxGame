//
//  AttackState.hpp
//  Tone_Skipper
//
//  Created by 创李 on 15/10/9.
//
//

#ifndef AttackState_hpp
#define AttackState_hpp

#include "EnemyState.h"

class AttackEnemyState:public EnemyState {
    
    AttackEnemyState();
public:
    SINGLE_FUNC(AttackEnemyState);
    virtual ~AttackEnemyState();
    virtual void onEnter(Enemy *);
    virtual void update(Enemy *,float delta)  ;
    virtual void onExit(Enemy*);
private:
    float m_pDelayTime;
};

#endif /* AttackState_hpp */
