//
//  Explosion.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/3/17.
//
//

#include "Explosion.h"
USING_NS_CC;
Explosion::Explosion()
{
}
Explosion::~Explosion()
{
}

void Explosion::loadParticleSystem(const std::string& plistName)
{
    m_pParticleSystem = ParticleSystemQuad::create(plistName);
    if(!m_pParticleSystem)
        CCLOG("Load explosion particle system failed!");
    addChild(m_pParticleSystem);
}