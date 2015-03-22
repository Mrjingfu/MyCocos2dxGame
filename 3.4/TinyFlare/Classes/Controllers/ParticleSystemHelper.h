//
//  ParticleSystemHelper.h
//  TinyFlare
//
//  Created by wang haibo on 15/3/18.
//
//

#ifndef __TinyFlare__ParticleSystemHelper__
#define __TinyFlare__ParticleSystemHelper__

#include "cocos2d.h"

typedef enum {
    ET_EXPLOSION_BLUE = 0,
    ET_EXPLOSION_WHITE,
    ET_EXPLOSION_BULLET_COLLISION,
    ET_EXPLOSION_ACTOR_COLLISION
} ExplosionType;

typedef enum {
    PWT_FIRE_FLARE = 0,
    PWT_TAIL
} PlayerWidgetType;
class ParticleSystemHelper
{
public:
    static cocos2d::ParticleSystemQuad* spawnExplosion(ExplosionType explosionType, const cocos2d::Vec2& pos);
    static cocos2d::ParticleSystemQuad* spawnPlayerWidget(PlayerWidgetType playerWidgetType, const cocos2d::Vec2& pos);
};

#endif /* defined(__TinyFlare__ParticleSystemHelper__) */
