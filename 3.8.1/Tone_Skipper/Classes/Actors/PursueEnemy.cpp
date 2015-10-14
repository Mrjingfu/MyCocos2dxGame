//
//  PursueEnemy.cpp
//  Tone_Skipper
//
//  Created by 创李 on 15/10/12.
//
//

#include "PursueEnemy.h"
#include "EnemyState.h"
PursueEnemy::PursueEnemy()
{
    m_EnemyType = ET_PURSUE;
}
PursueEnemy::~PursueEnemy()
{
    
}
void PursueEnemy::onLand()
{
    if (m_pEnemyState->getEnemyStateType() == EnemyStateType::ES_PURSUE) {
        m_Velocity.y = 0;
    }
}
void PursueEnemy::onCollision()
{
    if (m_pEnemyState->getEnemyStateType() == EnemyStateType::ES_PURSUE) {
//        m_Velocity.y = m_fMaxYSpeed;k
    }else
    {
        PatrolEnemy::onCollision();
    }
}
void PursueEnemy::onAir()
{
    if (m_pEnemyState->getEnemyStateType() == EnemyStateType::ES_PURSUE) {
       
    }else
    {
        PatrolEnemy::onAir();
    }

}