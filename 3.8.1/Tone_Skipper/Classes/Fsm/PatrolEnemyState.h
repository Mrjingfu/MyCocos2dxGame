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
    void updatePatrol(Enemy *,float delta);
    void updateAttackPatrol(Enemy *,float delta);
    void updatePursue(Enemy* enemy,float delta);
private:
    float m_pDelayTime;
     cocos2d::Vec2 m_Initpt;
};

#endif /* WalkState_hpp */
