//
//  State.hpp
//  TinyFlare
//
//  Created by 创李 on 15/10/8.
//
//

#ifndef State_hpp
#define State_hpp
#include "cocos2d.h"
#include "Enemy.h"
#include "GameConfig.h"
class EnemyState:public cocos2d::Ref{

public:
    virtual bool init(){return true;};
    virtual ~EnemyState(){};
    virtual void onEnter(Enemy *) = 0;
    virtual void update(Enemy *,float delta) = 0 ;
    virtual void onExit(Enemy*) = 0;
    virtual Enemy::EnemyStateType getEnemyStateType() const {return m_pEnemyStateType;};
    
protected:
    Enemy::EnemyStateType m_pEnemyStateType;
};

#endif /* State_hpp */
