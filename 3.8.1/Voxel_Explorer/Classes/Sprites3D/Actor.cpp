//
//  Actor.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/14.
//
//

#include "Actor.hpp"
#include "TerrainTile.hpp"
#include "VoxelExplorer.h"
USING_NS_CC;
Actor::Actor()
{
    m_dir       = AD_UNKNOWN;
}
Actor::~Actor()
{
}
Vec2 Actor::getPosInMap()
{
    return Vec2( (int)(getPositionX()/TerrainTile::CONTENT_SCALE+0.5f), int(-getPositionZ() /TerrainTile::CONTENT_SCALE+0.5f));
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
void Actor::addTerrainTileFlag(int flag)
{
    if(VoxelExplorer::getInstance()->getCurrentLevel())
    {
        int oriFlag = VoxelExplorer::getInstance()->getCurrentLevel()->getTerrainTileFlag(getPosInMap().x, getPosInMap().y);
        oriFlag |= flag;
        VoxelExplorer::getInstance()->getCurrentLevel()->setTerrainTileFlag(getPosInMap().x, getPosInMap().y, oriFlag);
    }
}
void Actor::addTerrainTileFlagByPos(int flag, const cocos2d::Vec2& pos)
{
    if(VoxelExplorer::getInstance()->getCurrentLevel())
    {
        int oriFlag = VoxelExplorer::getInstance()->getCurrentLevel()->getTerrainTileFlag(pos.x, pos.y);
        oriFlag |= flag;
        VoxelExplorer::getInstance()->getCurrentLevel()->setTerrainTileFlag(pos.x, pos.y, oriFlag);
    }
}

void Actor::removeTerrainTileFlag(int flag)
{
    if(VoxelExplorer::getInstance()->getCurrentLevel())
    {
        int oriFlag = VoxelExplorer::getInstance()->getCurrentLevel()->getTerrainTileFlag(getPosInMap().x, getPosInMap().y);
        oriFlag = oriFlag&~flag;
        VoxelExplorer::getInstance()->getCurrentLevel()->setTerrainTileFlag(getPosInMap().x, getPosInMap().y, oriFlag);
    }

}
void Actor::removeTerrainTileFlagByPos(int flag, const cocos2d::Vec2& pos)
{
    if(VoxelExplorer::getInstance()->getCurrentLevel())
    {
        int oriFlag = VoxelExplorer::getInstance()->getCurrentLevel()->getTerrainTileFlag(pos.x, pos.y);
        oriFlag = oriFlag&~flag;
        VoxelExplorer::getInstance()->getCurrentLevel()->setTerrainTileFlag(pos.x, pos.y, oriFlag);
    }
}

void Actor::setVisited(bool visited)
{
    setVisible(visited);
    unsigned int lightmask = getLightMask();
    if (visited)
        lightmask = lightmask | (unsigned int)LightFlag::LIGHT1;
    else
        lightmask = lightmask &~ (unsigned int)LightFlag::LIGHT1;
    setLightMask(lightmask);
}