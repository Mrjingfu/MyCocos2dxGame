//
//  PlayerFireBallBullet.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 16/1/11.
//
//

#ifndef PlayerFireBallBullet_hpp
#define PlayerFireBallBullet_hpp

#include "BaseBullet.hpp"
#include "Player.hpp"
class PlayerFireBallBullet : public BaseBullet
{
    PlayerFireBallBullet();
    virtual ~PlayerFireBallBullet();
    
    bool createParticleEffect();
public:
    static PlayerFireBallBullet* create(Player* pOwner, Actor* pTarget);
    
    virtual void update(float delta);
    virtual void onEnterDisappear();
    
protected:
    Actor*      m_pTarget;
    float       m_fLifeTime;
    cocos2d::Vec3   m_DefaultDir;
};

#endif /* PlayerFireBallBullet_hpp */
