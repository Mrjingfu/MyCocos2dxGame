//
//  Explosion.h
//  TinyFlare
//
//  Created by wang haibo on 15/3/17.
//
//

#ifndef __TinyFlare__Explosion__
#define __TinyFlare__Explosion__

#include "GameActor.h"
class Explosion : public GameActor
{
    friend class ActorsManager;
public:
    typedef enum {
        ET_BLUE = 0,
    } ExplosionType;
protected:
    Explosion();
    virtual ~Explosion();
    
public:
    void loadParticleSystem(const std::string& plistName);
    cocos2d::ParticleSystemQuad* getParticleSystem() const { return m_pParticleSystem; }
    
    float getLifeTime() const { return m_fLifeTime; }
    void setLifeTime(float lifeTime) { m_fLifeTime = lifeTime; }
private:
    cocos2d::ParticleSystemQuad* m_pParticleSystem;
    float   m_fLifeTime;
};

#endif /* defined(__TinyFlare__Explosion__) */
