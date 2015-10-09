//
//  IdleEnemyState.hpp
//  Tone_Skipper
//
//  Created by 创李 on 15/10/9.
//
//

#ifndef IdleEnemyState_hpp
#define IdleEnemyState_hpp

#include "EnemyState.h"

class IdleEnemyState :public EnemyState{
    IdleEnemyState();
    
public:
    SINGLE_FUNC(IdleEnemyState);
    virtual ~IdleEnemyState();
    virtual void onEnter(Enemy *);
    virtual void update(Enemy *,float delta)  ;
    virtual void onExit(Enemy*);
private:
    float m_pDelayTime;
};

#endif /* IdleEnemyState_hpp */
