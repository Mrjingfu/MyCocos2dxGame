//
//  PlayerMagicArrowBullet.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 16/1/12.
//
//

#ifndef PlayerMagicArrowBullet_hpp
#define PlayerMagicArrowBullet_hpp

#include "BaseBullet.hpp"
#include "Player.hpp"
#include "RibbonTrail.h"
class PlayerMagicArrowBullet : public BaseBullet
{
    PlayerMagicArrowBullet();
    virtual ~PlayerMagicArrowBullet();
    
    bool createParticleEffect();
public:
    static PlayerMagicArrowBullet* create(Player* pOwner, const cocos2d::Vec3& dir);
    
    virtual void update(float delta);
    virtual void onEnterDisappear();
    
protected:
    RibbonTrail* m_pRibbonTrail;
    float       m_fLifeTime;
    cocos2d::Vec3   m_DefaultDir;
    bool   m_bCollision;
};

#endif /* PlayerMagicArrowBullet_hpp */
