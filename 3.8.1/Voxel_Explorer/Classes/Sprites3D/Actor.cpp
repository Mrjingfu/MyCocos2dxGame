//
//  Actor.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/14.
//
//

#include "Actor.hpp"
#include "TerrainTile.hpp"
USING_NS_CC;
Actor::Actor()
{
    m_dir       = AD_RIGHT;
}
Actor::~Actor()
{
}
Vec2 Actor::getPosInMap()
{
    return Vec2( (int)(getPositionX()/TerrainTile::CONTENT_SCALE), int(-getPositionZ() /TerrainTile::CONTENT_SCALE));
}
void Actor::setActorDir( ActorDir dir )
{
    m_dir = dir;
    switch (m_dir) {
        case AD_FORWARD:
            setRotation3D(Vec3(0,180,0));
            break;
        case AD_LEFT:
            setRotation3D(Vec3(0,-90,0));
            break;
        case AD_RIGHT:
            setRotation3D(Vec3(0,90,0));
            break;
        case AD_BACK:
            setRotation3D(Vec3(0,0,0));
            break;
        default:
            break;
    }
}