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