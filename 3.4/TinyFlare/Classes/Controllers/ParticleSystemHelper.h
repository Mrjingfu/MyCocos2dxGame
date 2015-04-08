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
#include "GameActor.h"
typedef enum {
    ET_EXPLOSION_BLUE = 0,
    ET_EXPLOSION_WHITE,
    ET_EXPLOSION_YELLOW,
    ET_EXPLOSION_GREEN,
    ET_EXPLOSION_ORANGE,
    ET_EXPLOSION_BULLET_COLLISION,
    ET_EXPLOSION_ACTOR_COLLISION,
    ET_EXPLOSION_ACTOR_RESPAWN,
    ET_EXPLOSION_CLEAR,
    ET_EXPLOSION_BLACK_HOLE
} ExplosionType;

typedef enum {
    AWT_FIRE_FLARE = 0,
    AWT_PLAYER_TAIL,
    AWT_COLOR_CIRCLE_TAIL,
    AWT_COLOR_TRIANGLE_TAIL,
    AWT_COLOR_DIAMOND_TAIL,
    AWT_COLOR_STAR_TAIL,
    AWT_COLOR_HEXAGON_TAIL,
} ActorWidgetType;
class ParticleSystemHelper
{
public:
    static cocos2d::ParticleSystemQuad* spawnExplosion(ExplosionType explosionType, const cocos2d::Vec2& pos);
    static cocos2d::ParticleSystemQuad* spawnActorWidget(ActorWidgetType actorWidgetType, const cocos2d::Vec2& pos, GameActor* actor);
};

#endif /* defined(__TinyFlare__ParticleSystemHelper__) */
