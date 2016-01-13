//
//  BaseBullet.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 16/1/3.
//
//

#ifndef BaseBullet_hpp
#define BaseBullet_hpp

#include "cocos2d.h"
#include "Particle3D/CCParticleSystem3D.h"
#include "Particle3D/PU/CCPUParticleSystem3D.h"
#include "BaseBoss.hpp"
class BaseBullet : public cocos2d::Node
{
public:
    typedef enum {
        BT_KOBLODLEADER = 0,            ////狗头人首领
        BT_ARCHBISHOP,                  ////网红教主
        BT_PLAYER_FIREBALL,             ////角色火球技能
        BT_PLAYER_MAGICARROW,           ////角色魔法箭矢
        BT_UNKNOWN
    } BulletType;
    
    typedef enum{
        BS_UNKNOWN,
        BS_NORMAL,
        BS_DISAPPEAR,
        BS_MAX
    } BulletState;
public:
    BulletState getBulletState() const;
    void setBulletState(BulletState state);
    void destroySelf();
protected:
    BaseBullet();
    virtual ~BaseBullet();
    
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
    
    virtual void onEnterNormal();
    virtual void onExitNormal();
    
    virtual void onEnterDisappear();
    virtual void onExitDisappear();
    
    virtual bool createParticleEffect() = 0;
protected:
    BulletType                      m_Type;
    cocos2d::PUParticleSystem3D*    m_pEffect;
    cocos2d::PUParticleSystem3D*    m_pExplosionEffect;
    BulletState                     m_State;
    Actor*                          m_pOwner;
};

#endif /* BaseBullet_hpp */
